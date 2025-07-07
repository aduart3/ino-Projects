import serial
import keyboard
import time

# Troque 'COM3' pela porta correta do seu Arduino
ser = serial.Serial('COM5', 9600)
time.sleep(2)  # tempo para o Arduino iniciar

print("Use as setas ↑ e ↓ para mover o motor. Pressione ESC para sair.")

while True:
    if keyboard.is_pressed('up'):
        ser.write(b'U')
        print("↑")
        time.sleep(0.2)
    elif keyboard.is_pressed('down'):
        ser.write(b'D')
        print("↓")
        time.sleep(0.2)
    elif keyboard.is_pressed('esc'):
        print("Saindo...")
        break

ser.close()
