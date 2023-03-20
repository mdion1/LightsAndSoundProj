from samplingParams import samplingParams
from Note import Note

def main():
    numOctaves = 4
    octaveStart = 2
    outStr = '#pragma once\n\n'

    for octave in range(octaveStart, octaveStart + numOctaves):
        for idx in Note.NoteList.keys():
            outStr += samplingParams(Note(idx, octave)).getMacrosText() + '\n\n'

    # Add on C6 to the end
    outStr += samplingParams(Note(0, 6)).getMacrosText() + '\n\n'

    with open("SamplingParams.h", "w") as text_file:
        text_file.write(outStr)


if __name__ == '__main__':
   main()