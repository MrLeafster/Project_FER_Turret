import serial
import struct

mController = serial.Serial("COM6")

while mController.isOpen():
    random_byte = mController.read()

    while random_byte[0] not in [0x10, 0x11, 0x12]:
        random_byte = mController.read()
    
    if random_byte[0] == 0x10:
        print("Gamepad connected!")
        continue
    elif random_byte[0] == 0x11:
        print("Gamepad disconnected!")
        continue
    
    data = bytes([])
    random_byte = mController.read()

    while random_byte[0] != 17:
        data += random_byte
        random_byte = mController.read()

    #print(list(data))
    
    dpad = struct.unpack("<B", data[0:1])[0]
    buttons = struct.unpack("<B", data[1:2])[0]
    
    axisLX = struct.unpack("<i", data[4:8])[0]
    axisLY = struct.unpack("<i", data[8:12])[0]

    axisRX = struct.unpack("<i", data[12:16])[0]
    axisRY = struct.unpack("<i", data[16:20])[0]

    throttleL = struct.unpack("<i", data[20:24])[0]
    throttleR = struct.unpack("<i", data[24:28])[0]

    print(f"dpad = {dpad: 1d}, buttons = {buttons: 3d}, axisLX = {axisLX: 4d}, axisLY = {axisLY: 4d}, axisRX = {axisRX: 4d}, axisRY = {axisRY: 4d}, throttleL = {throttleL: 5d}, throttleR = {throttleR: 5d}")
