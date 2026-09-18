import serial
import time

arduino = serial.Serial("COM5", 9600)

time.sleep(2)

while True:

    message = arduino.readline().decode().strip()

    print("Arduino :", message)

    if message == "MOUVEMENT":
        print("Mouvement détecté !")

        arduino.write(b"PYTHON_BIEN_RECU\n")
