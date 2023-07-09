import pygame
import sys
from Button import Button
import numpy as np


# Function
def draw_lines() :
    # Horizontal
    pygame.draw.line(screen, line_color, (0, 200), (s_width, 200), line_width)
    pygame.draw.line(screen, line_color, (0, 400), (s_width, 400), line_width)

    # Vertical
    pygame.draw.line(screen, line_color, (200, 0), (200, s_height), line_width)
    pygame.draw.line(screen, line_color, (400, 0), (400, s_height), line_width)

def mark_square(row, col, player) :
    board[row][col] = player

def available_square(row, col) :
    return board[row][col] == 0
    
    '''
    if board[row][col] == 0 :
        return True
    
    else :
        return False
    '''

def board_full() :
    for row in range(board_rows) :
        for col in range (board_cols) :
            if board[row][col] == 0 :
                return False
            
    return True

def draw_figures() :
    for row in range(board_rows) :
        for col in range(board_cols) :
            if board[row][col] == 1 :
                pygame.draw.circle(screen, circle_color, (int((col * square_size) + half_square_size), int(row * square_size + half_square_size)), circle_radius, circle_width)
            
            elif board[row][col] == 2 :
                pygame.draw.line(screen, cross_color, ((col * square_size) + space, (row * square_size) + space), ((col * square_size) + 200 - space, (row * square_size) + 200 - space), cross_width) # \
                pygame.draw.line(screen, cross_color, ((col * square_size) + space, (row * square_size) + 200 - space), ((col * square_size) + 200 - space, (row * square_size) + space), cross_width) # /

def check_win(player) :
    # Vertical Win Check
    for col in range(board_cols) :
        if board[0][col] == player and board[1][col] == player and board[2][col] == player :
            draw_vertical_winning_line(col, player)
            return True
        
    # Horizontal Win Check
    for row in range(board_rows) :
        if board[row][0] == player and board[row][1] == player and board[row][2] == player :
            draw_horizontal_winning_line(row, player)
            return True
    
    # Ascending Diagonal Win Check
    if board[2][0] == player and board[1][1] == player and board [0][2] == player :
        draw_ascending_diagonal_winning_line(player)
        return True
    
    # Descending Diagonal Win Check
    if board[0][0] == player and board[1][1] == player and board [2][2] == player :
        draw_descending_diagonal_winning_line(player)
        return True
    
    return False

def draw_vertical_winning_line(col, player) :
    posX = (col * square_size) + half_square_size

    if player == 1 :
        color = circle_color
    
    if player == 2 :
        color = cross_color
    
    pygame.draw.line(screen, color, (posX, 15), (posX, s_height - 15), win_line_width)

def draw_horizontal_winning_line(row, player) :
    posY = (row * square_size) + half_square_size

    if player == 1 :
        color = circle_color
    
    if player == 2 :
        color = cross_color
    
    pygame.draw.line(screen, color, (15, posY), (s_width - 15, posY), win_line_width)

def draw_ascending_diagonal_winning_line(player) :
    if player == 1 :
        color = circle_color
    
    if player == 2 :
        color = cross_color
    
    pygame.draw.line(screen, color, (15, s_height - 15), (s_width - 15, 15), win_line_width)

def draw_descending_diagonal_winning_line(player) :
    if player == 1 :
        color = circle_color
    
    if player == 2 :
        color = cross_color

    pygame.draw.line(screen, color, (15, 15), (s_width - 15, s_height - 15), win_line_width)

def restart() :
    screen.fill(bg_color)
    draw_lines()

    for row in range(board_rows) :
        for col in range (board_cols) :
            board[row][col] = 0

def get_font(size):
    return pygame.font.Font("C:\Damian\Coding\Python\Python_Game_Project\Main_Menu_Data/font.ttf", size)


# Variables
s_width = 600
s_height = 600
board_rows = 3
board_cols = 3
line_width = 15
win_line_width = 15
circle_radius = 60
circle_width = 15
cross_width = 25
square_size = s_width // board_cols
half_square_size = square_size // 2
space = square_size // 4

bg_color = (28, 170, 156)
line_color = (23, 145, 135)
circle_color = (239, 231, 200)
cross_color = (66, 66, 66)


# Set Up
pygame.init()
screen = pygame.display.set_mode((s_width, s_height))
pygame.display.set_caption("TIC TAC TOE")
background = pygame.image.load("C:\Damian\Coding\Python\Python_Game_Project\Main_Menu_Data/Background.png")


# Board
board = np.zeros((board_rows, board_cols))


# Program Running
def play():
    game_over = False
    player = 1
    screen.fill(bg_color)
    draw_lines()
    
    while True :
        for event in pygame.event.get() :
            if event.type == pygame.QUIT :
                pygame.quit()
                sys.exit()
        
            if event.type == pygame.MOUSEBUTTONDOWN and not game_over:
                mouseX = event.pos[0] # 0 will give x coordinate
                mouseY = event.pos[1] # 1 will give y coordinate

                clicked_row = int(mouseY//200)
                clicked_col = int(mouseX//200)

                if available_square(clicked_row, clicked_col) :
                    mark_square(clicked_row, clicked_col, player)

                    if check_win(player) :
                        game_over = True
                
                    player = (player % 2) + 1
                
                    draw_figures()
                
                    '''
                    if player == 1 :
                        mark_square(clicked_row, clicked_col, 1)
                        if check_win(player) :
                            game_over = True
                        player = 2
                
                    elif player == 2 :
                        mark_square(clicked_row, clicked_col, 2)
                        if check_win(player) :
                            game_over = True
                        player = 1
                    '''
        
            if event.type == pygame.KEYDOWN :
                if event.key == pygame.K_r :
                    restart()
                    player = 1
                    game_over = False

        pygame.display.update()

def main_menu():
    while True:
        screen.blit(background, (0, 0))

        menu_mouse_pos = pygame.mouse.get_pos()

        menu_text = get_font(60).render("MAIN MENU", True, "#b68f40")
        menu_rect = menu_text.get_rect(center=(s_width//2, 100))

        play_button = Button(image=pygame.image.load("C:\Damian\Coding\Python\Python_Game_Project\Main_Menu_Data/Play Rect.png"), pos=(s_width//2, 250), 
                            text_input="PLAY", font=get_font(40), base_color="#d7fcd4", hovering_color="White")
        quit_button = Button(image=pygame.image.load("C:\Damian\Coding\Python\Python_Game_Project\Main_Menu_Data/Quit Rect.png"), pos=(s_width//2, 380), 
                            text_input="QUIT", font=get_font(40), base_color="#d7fcd4", hovering_color="White")

        screen.blit(menu_text, menu_rect)

        for button in [play_button, quit_button]:
            button.change_color(menu_mouse_pos)
            button.update(screen)
        
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

            if event.type == pygame.MOUSEBUTTONDOWN:
                if play_button.check_for_input(menu_mouse_pos):
                    play()
                    
                if quit_button.check_for_input(menu_mouse_pos):
                    pygame.quit()
                    sys.exit()

        pygame.display.update()

main_menu()
