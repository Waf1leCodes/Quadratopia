import pygame
import os

while True:
    answer = input("What file would you like on edit?: ")
    if answer.strip().lower() == "exit":
        break
    
    path = os.path.join(os.getcwd(), answer)
    image = pygame.image.load(path)
    
    for x in range(image.get_width()):
        for y in range(image.get_height()):
            color = image.get_at((x, y))
            if color[3] < 250:
                continue
            color[3] = 255
            image.set_at((x, y), color)
    
    tail, head = os.path.splitext(path)
    pygame.image.save(image, tail + " New" + head)