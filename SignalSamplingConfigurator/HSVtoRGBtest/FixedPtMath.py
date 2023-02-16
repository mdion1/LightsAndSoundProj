

class FixPt():
    def __init__(self, val:float = 0):
        # input guards: only accept values between 0 and 1
        val = min(1, max(0, val))
        val = round(val * 65536)

        self.isOne = False
        self.int16Val = 0

        if 65536 == val:
            self.isOne = True
        else:
            self.int16Val = min(max(round(val), 0), 65535)
    
    def getInt8(self) -> int:
        if self.isOne:
            return 256
        return round(self.int16Val / 256)

    def getInt16(self) -> int:
        if self.isOne:
            return 65536
        return self.int16Val

    def setInt16(self, intVal: int):
        intVal = min(65536, max(0, intVal))

        self.isOne = False
        self.int16Val = 0

        if 65536 == intVal:
            self.isOne = True
        else:
            self.int16Val = intVal

    def getFloat(self) -> float:
        if self.isOne:
            return 1
        return self.int16Val / 65536.0

    def mult(a: "FixPt", b: "FixPt") -> "FixPt":
        if a.isOne:
            return b.getCopy()
        elif b.isOne:
            return a.getCopy()
        else:
            x = a.getInt8() * b.getInt8()
            ret = FixPt()
            ret.setInt16(x)
            return ret

    def getCopy(self) -> "FixPt":
        return FixPt(self.getFloat())

    def add(a: "FixPt", b: "FixPt") -> "FixPt":
        # does NOT check for overflow!!!!
        x = a.getInt16() + b.getInt16()
        
        ret = FixPt()
        ret.setInt16(x)
        return ret

    def subtract(a: "FixPt", b: "FixPt") -> "FixPt":
        # does NOT check for underflow!!!!
        x = a.getInt16() - b.getInt16()
        
        ret = FixPt()
        ret.setInt16(x)
        return ret