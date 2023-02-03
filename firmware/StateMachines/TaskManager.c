#include "TaskManager.h"
#include "LEDManager.h"
#include "Sleep.h"
#include "SignalSampling.h"
#include "SignalAnalysis.h"

typedef struct
{
    void (*p_taskFn)(void);
    uint16_t interval;
    uint16_t tPrev;
}task_t;

/* Private variable declarations */

// List of states
typedef enum {
    PWR_SAVE = 0,
    STBY_SAMPLING,
    ACTIVE
}TaskMgrState_t;

// State machine
#define MAX_NUM_TASKS 8
static struct
{
    TaskMgrState_t state;
    task_t taskList[MAX_NUM_TASKS];
    uint8_t taskListLen;
}SM;

// Task intervals
#define SIG_SAMP_TASK_INT (4 * TSAMP_PERIOD)    // todo: convert clock ticks into systick intervals
#define SIG_ANALYSIS_TASK_INT (4 * TSAMP_PERIOD)
#define LED_MANAGER_TASK_INT 1000   // todo: dummy value
#define SLEEP_TASK_INT 1000   // todo: dummy value

/* Private function declarations */
void registerTask(void (*p_taskFn)(void), uint16_t interval);   // intervals must be <= 32767
static void setupState(TaskMgrState_t state);
static void setupStbySampling();    //todo: bundle into setupState()?
static void stbySamplingTasks();
static void activeTasks();


/* Public function definitions */

void TaskMgr_init(void)
{
    /* Initialize all modules */
    SigSamp_init();
    SigAnalysis_init();
    LEDMgr_init();
    Sleep_init();
    
    /* Register tasks */
    registerTask(&SigSamp_tasks, SIG_SAMP_TASK_INT);
    registerTask(&SigAnalysis_tasks, SIG_ANALYSIS_TASK_INT);
    registerTask(&LEDMgr_tasks, LED_MANAGER_TASK_INT);
    registerTask(&Sleep_tasks, SLEEP_TASK_INT);
    
    Systick_start();
}

void TaskMgr_loopNoReturn(void)
{
    while(1)
    {
        switch (SM.state)
        {
            case PWR_SAVE:
            {
                /* Upon waking from power save, start "standby sampling."
                 *      - Set up triggered ADC sampling
                 *      - Set up wake-on-conversion-complete
                 *      -
                */
               // Upon waking from power save, setup "standby sampling."
               setupStbySampling();
               SM.state = STBY_SAMPLING;
            }
            break;
            case STBY_SAMPLING:
            {
                stbySamplingTasks();
            }
            break;
            case ACTIVE:
            default:
            {
                activeTasks();
            }
            break;
        }



    }
}


/* Private function definitions */
// Params:  !!intervals must be <= 32767!!
void registerTask(void (*p_taskFn)(void), uint16_t interval)
{
    /* Time interval math is done with unsigned 16-bit integers, so to avoid overflow/wraparound error
     * the maximum interval must be < 2^15
     */
    if (interval > 32778) {
        return;
    }
    
    /* Guard against array overflow */
    if (SM.taskListLen < MAX_NUM_TASKS)
    {
        SM.taskList[SM.taskListLen].p_taskFn = p_taskFn;
        SM.taskList[SM.taskListLen].interval = interval;
        SM.taskList[SM.taskListLen].tPrev = 0;
    }
}


static void setupStbySampling()
{
    /* Set up triggered ADC sampling
     * Set up wake-on-conversion-complete
     * Start first conversion
     */
}

static void activeTasks()
{
        
    uint16_t t_now = hal_Systick16();       //todo: instead of system time, go by sampling timer? Or use this later to reduce pwr consumption?
    
    for (uint8_t i = 0; i < SM.taskListLen; i++)
    {
        task_t* task = &SM.taskList[i];
        bool once = true;
        while (t_now - task->tPrev >= task->interval)       //TODO: THIS BREAKS DUE TO WRAPAROUND
        {
            // only call the task once, even if several intervals have expired
            if (once) {
                (*task->p_taskFn)();    //call registered task function
                once = false;
            }
            
            /* Add interval to tPrev until tPrev + interval > t_now */
            task->tPrev += task->interval;
        }
    }
}