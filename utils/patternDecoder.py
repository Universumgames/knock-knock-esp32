import os

with open("pattern_1.bin", "rb") as f:
    version = int.from_bytes(f.read(1))
    id = int.from_bytes(f.read(4), byteorder='little')
    totalMillis = int.from_bytes(f.read(2), byteorder='little')
    patternLength = int.from_bytes(f.read(4), byteorder='little')
    print("Version: ", version)
    print("ID:", id)
    print("Total Millis: ", totalMillis)
    print("Pattern Length: ", patternLength)
    print("Pattern: ", end='')
    for i in range(0, patternLength):
        pattern = int.from_bytes(f.read(2), byteorder='little')
        print(pattern, end=' ')
    print()