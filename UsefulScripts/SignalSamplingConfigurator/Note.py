from typing import Dict, List

class Note:
    NoteList: Dict[int, str] = {
        0: "C",
        1: "C#/Db",
        2: "D",
        3: "D#/Eb",
        4: "E",
        5: "F",
        6: "F#/Gb",
        7: "G",
        8: "G#Ab",
        9: "A",
        10: "A#/Bb",
        11: "B",
    }
    FreqList: Dict[int, float] = {
        0: 261.6255653,
        1: 277.182631,
        2: 293.6647679,
        3: 311.1269837,
        4: 329.6275569,
        5: 349.2282314,
        6: 369.9944227,
        7: 391.995436,
        8: 415.3046976,
        9: 440,
        10: 466.1637615,
        11: 493.8833013,
    }

    def __init__(self, idx: int, octave: int):
        if idx not in Note.NoteList.keys():
            raise KeyError("Note index must be between 0-11!")
            return
        
        self._idx: int = idx
        self._octave = octave
        self._noteName: str = f'{Note.NoteList[idx]}{octave}'
        self._freq: float = Note.FreqList[idx] * (2**(octave - 4))       # FreqList is based on octave 4

    def toStr(self) -> str:
        return self._noteName

    def toFriendlyStrList(self) -> List[str]:       # if note name has an alias (e.g. C#/Db), this returns list (e.g. ['C#', 'Db'])
        alia = f'{Note.NoteList[self._idx]}'.split('/')
        for idx in range(0, len(alia)):
            alia[idx] = alia[idx].replace('#','sharp')
            alia[idx] += f'{self._octave}'
        return alia

    def getFreq(self) -> float:
        return self._freq