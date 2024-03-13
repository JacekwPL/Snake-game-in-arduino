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

    def blocks(self, positions: str):  # +0501+0401+0301+0201
        pos = positions.split(";")
        for elem in pos[1:]:
            match elem[0]:
                case ' ':
                    self.draw(self.green, elem[1:])
                case '+':
                    self.draw(self.red, elem[1:])
                case '-':
                    self.draw(self.black, elem[1:])
                case 'R':
                    self.screen.fill((0, 0, 0))

                    font = pygame.font.SysFont("Arial", 36)

                    text = font.render("Game Over!", True, self.white)

                    self.screen.blit(text, (self.screen.get_width()//2 - text.get_width() // 2,
                                            self.screen.get_height()//2 - text.get_height() // 2))

                    text = font.render(f"Your score: {elem[1:]}", True, self.white)

                    self.screen.blit(text, (self.screen.get_width()//2 - text.get_width() // 2,
                                            self.screen.get_height()//2 + 50 - text.get_height() // 2))
                    pygame.display.update()

        pygame.display.update()

    def draw(self, col: pygame.color, pos: str) -> None:
        pygame.draw.rect(self.screen, col, (int(pos[0:2]) * self.SIZE, int(pos[2:4]) * self.SIZE, self.SIZE, self.SIZE))


if __name__ == '__main__':
    string = '''; 0805;+0505;+0405;+0305;+0205;+0105'''

    pygame.init()
    screen = pygame.display.set_mode((400, 300))

    sc = ScreenDrawing(screen, 15)

    sc.blocks(string)

    start = time.time()
    while 1:

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
