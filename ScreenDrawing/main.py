import serial
import pygame
import sys


YMAX = 40
XMAX = 40
SIZE = 15

if __name__ == '__main__':
    from screenDrawing import ScreenDrawing
    pygame.init()
    screen = pygame.display.set_mode((SIZE*(XMAX+1), SIZE*(YMAX+1)))

    sc = ScreenDrawing(screen, SIZE)

    serialInst = serial.Serial()
    serialInst.baudrate = 9600
    serialInst.port = 'COM3'
    serialInst.open()

    clearScreen = False

    while 1:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

        try:
            if serialInst.in_waiting:
                string = serialInst.readline().decode().rstrip()
                print(string)
                sc.blocks(string)
                if string[1] == 'R':
                    clearScreen = True
                else:
                    clearScreen = False

        except Exception:
            pass

        if clearScreen:
            screen.fill((0, 0, 0))
