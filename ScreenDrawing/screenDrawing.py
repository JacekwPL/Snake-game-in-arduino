import pygame
import sys
import time


class ScreenDrawing:
    def __init__(self, _screen, _size):
        self.screen = _screen

        self.red = (255, 0, 0)
        self.green = (0, 255, 0)
        self.blue = (0, 0, 255)
        self.white = (255, 255, 255)
        self.black = (0, 0, 0)

        self.SIZE = _size

    def draw(self, positions: str): # +0501+0401+0301+0201
        print(positions)
        pygame.draw.rect(self.screen, self.black, (0, 0, 9999, 9999))

        pos = positions.split("+")

        pygame.draw.rect(self.screen, self.green, (int(pos[0][0:2])*self.SIZE, int(pos[0][2:4])*self.SIZE, self.SIZE, self.SIZE))
        for cords in pos[1:]:
            pygame.draw.rect(self.screen, self.red, (int(cords[0:2]) * self.SIZE, int(cords[2:4]) * self.SIZE, self.SIZE, self.SIZE))

        pygame.display.update()


if __name__ == '__main__':
    string = '''0709+2108+2008+1908+1808+1708
0709+2208+2108+2008+1908+1808
0709+2308+2208+2108+2008+1908
0709+2408+2308+2208+2108+2008
0709+2508+2408+2308+2208+2108'''

    string = string.split('\n')

    pygame.init()
    screen = pygame.display.set_mode((400, 300))

    sc = ScreenDrawing(screen)
    i = 0

    start = time.time()
    while 1:

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

        if time.time() - start > 2:
            i += 1
            sc.draw(string[i % len(string)].rstrip())
            start = time.time()

