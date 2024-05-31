import pygame
def level1():
    width = 10
    height = 10
    x = 0
    y = 0
    velocity = 1
    clock = pygame.time.Clock()

    run = True

    # test_font = pygame.font.Font(pygame.R(10, 10, 10, 10), 50)
    # sky_surface = pygame.Rect(10, 10, 10, 10)
    # ground_surface = pygame.image.load("graphics/ground.png")
    # text_surface = test_font.render("My game", False, "Black")

    snail_surface = pygame.Rect(10, 10, 10, 10)
    player_surf = pygame.image.load("graphics/player/player_walk_1.png")
    player_rect = player_surf.get_rect(midbottom=(80, 300))
    snail_rect = snail_surface.get_rect(midbottom=(600, 300))
    gravity = 1
    jump_velocity = -15
    player_velocity_y = 0
    playing = True

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
            if playing:
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_w and player_rect.midbottom[1] >= 300:
                        player_velocity_y = jump_velocity
            else:
                if event.type == pygame.KEYDOWN and event.key == pygame.K_r:
                    playing = True
                    player_rect = player_surf.get_rect(midbottom=(80, 300))
        if playing:
            keys = pygame.key.get_pressed()

            if keys[pygame.K_a]:
                player_rect.move_ip((-3, 0))
            if keys[pygame.K_d]:
                player_rect.move_ip((3, 0))

            # Grawitacja
            if player_rect.bottom < 300 or player_velocity_y < 0:
                player_velocity_y += gravity
                player_rect.move_ip((0, player_velocity_y))

            # Zatrzymanie na ziemi
            if player_rect.bottom > 300:
                player_rect.midbottom = (player_rect.midbottom[0], 300)
                player_velocity_y = 0

            win.blit(sky_surface, (0, 0))
            win.blit(ground_surface, (0, 300))
            win.blit(text_surface, (300, 50))
            win.blit(snail_surface, snail_rect)
            win.blit(player_surf, player_rect)

            if player_rect.colliderect(snail_rect):
                playing = False

        else:
            win.fill('black')
        pygame.display.update()

        clock.tick(60)