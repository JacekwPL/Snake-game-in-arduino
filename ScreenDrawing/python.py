import pygame
import bla

pygame.init()

win = pygame.display.set_mode((800, 400))

level = '1'
while run:

    match level:
        case "1":
            bla.level1()
            break

    bla.level2()