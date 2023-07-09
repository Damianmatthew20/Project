from tkinter.font import BOLD
import pygame
import sys
from Button import Button


# Class
class Ball :
    def __init__(self, screen, color, posX, posY, radius) :
        self.screen = screen
        self.color = color
        self.posX = posX
        self.posY = posY
        self.radius = radius
        self.dx = 0
        self.dy = 0
        # self.show_ball --> used if there's no ball.show_ball() in while loop
    
    def show(self) :
        pygame.draw.circle(self.screen, self.color, (self.posX, self.posY), self.radius)
    
    def start_moving(self) :
        self.dx = 0.15
        self.dy = 0.05
    
    def move(self) :
        self.posX += self.dx
        self.posY += self.dy
        
        # self.posX = self.posX + self.dx
        # self.posY = self.posY + self.dy
    
    def paddle_collision(self) :
        self.dx = -self.dx

    def wall_collision(self) :
        self.dy = -self.dy
    
    def restart_pos(self) :
        self.posX = s_width//2
        self.posY = s_height//2
        self.dx = 0
        self.dy = 0
        self.show()

class Paddle :
    def __init__(self, screen, color, posX, posY, width, height) :
        self.screen = screen
        self.color = color
        self.posX = posX
        self.posY = posY
        self.width = width
        self.height = height
        self.state = "stop"
        # self.show_paddle --> used if there's no ball.show_paddle() in while loop

    def show(self) :
        pygame.draw.rect(self.screen, self.color, (self.posX, self.posY, self.width, self.height))

    def move(self) :
        if self.state == "up" :
            self.posY -= 0.20

        if self.state == "down" :
            self.posY += 0.20
    
    def max_movement(self) :
        if self.posY <= 0 :
            self.posY = 0
        
        if (self.posY + self.height) >= s_height :
            self.posY = s_height - self.height
    
    def restart_pos(self) :
        self.posY = s_height//2 - self.height//2
        self.state = "stop"
        self.show()

class CollisionManager :
    def ball_and_left_paddle (self, ball, left_paddle) :
        if (ball.posY + ball.radius) > left_paddle.posY and (ball.posY - ball.radius) < (left_paddle.posY + left_paddle.height) :
            if (ball.posX - ball.radius) <= (left_paddle.posX + left_paddle.width) :
                return True
        
        return False

    def ball_and_right_paddle (self, ball, right_paddle) :
        if (ball.posY + ball.radius) > right_paddle.posY and (ball.posY - ball.radius) < (right_paddle.posY + right_paddle.height) :
            if (ball.posX + ball.radius) >= right_paddle.posX :
                return True
        
        return False

    def ball_and_wall (self, ball) :
        # Top
        if ball.posY - ball.radius <= 0 :
            return True

        # Bottom
        if ball.posY + ball.radius >= s_height :
            return True
        
        return False
    
    def check_left_player_goal(self, ball) :
        return ball.posX - ball.radius <= 0
    
    def check_right_player_goal(self, ball) :
        return ball.posX + ball.radius >= s_width

class Score:
    def __init__(self, screen, point, posX, posY):
        self.screen = screen
        self.point = point
        self.posX = posX
        self.posY = posY
        self.font = pygame.font.SysFont("monospace", 75, BOLD)
        self.label = self.font.render(self.point, 0, white)
    
    def show(self):
        self.screen.blit(self.label, (self.posX - self.label.get_rect().width//2, self.posY))

    def increase(self):
        point = int(self.point) + 1
        self.point = str(point)
        self.label = self.font.render(self.point, 0, white)
    
    def restart(self):
        self.point = '0'
        self.label = self.font.render(self.point, 0, white)


# Function
def mid_line():
    pygame.draw.line(screen, white, (s_width//2, 0), (s_width//2, s_height), width = 4)

def restart():
    mid_line()
    left_score.restart()
    right_score.restart()
    ball.restart_pos()
    left_paddle.restart_pos()
    right_paddle.restart_pos()

def get_font(size):
    return pygame.font.Font("C:\Damian\Coding\Python\Python_Game_Project\Main_Menu_Data/font.ttf", size)


# Variables
s_width, s_height = 900, 500
black = (0, 0, 0)
white = (255, 255, 255)


# Set Up
pygame.init()
screen = pygame.display.set_mode((s_width, s_height))
pygame.display.set_caption("PONG")
background = pygame.image.load("C:\Damian\Coding\Python\Python_Game_Project\Main_Menu_Data/Background.png")


# Object
ball = Ball(screen, white, s_width//2, s_height//2, 10)
left_paddle = Paddle(screen, white, 20, ((s_height//2) - 60), 15, 120)
right_paddle = Paddle(screen, white, ((s_width - 20) - 15), ((s_height//2) - 60), 15, 120)
collision = CollisionManager()
left_score = Score(screen, '0', s_width//4, 15)
right_score = Score(screen, '0', s_width - (s_width//4), 15)


# Program Running
def play():
    playing = False
    
    while True :
        screen.fill(black)
        mid_line()
        ball.show()
        left_paddle.show()
        right_paddle.show()
        left_score.show()
        right_score.show()

        for event in pygame.event.get() :
            if event.type == pygame.QUIT :
                pygame.quit()
                sys.exit()
        
            if event.type == pygame.KEYDOWN :
                if event.key == pygame.K_SPACE :
                    playing = True
                    ball.start_moving()
            
                if event.key == pygame.K_r :
                    restart()
                    playing = False
            
                if event.key == pygame.K_w :
                    left_paddle.state = "up"
            
                if event.key == pygame.K_s :
                    left_paddle.state = "down"
            
                if event.key == pygame.K_UP :
                    right_paddle.state = "up"
            
                if event.key == pygame.K_DOWN :
                    right_paddle.state = "down"
        
            if event.type == pygame.KEYUP :
                left_paddle.state = "stop"
                right_paddle.state = "stop"
    
        if playing :
            # Ball Movement
            ball.move()

            # Left Paddle Movement
            left_paddle.move()
            left_paddle.max_movement()

            # Right Paddle Movement
            right_paddle.move()
            right_paddle.max_movement()

            # Collision
            if collision.ball_and_left_paddle(ball, left_paddle) :
                ball.paddle_collision()
        
            if collision.ball_and_right_paddle(ball, right_paddle) :
                ball.paddle_collision()
        
            if collision.ball_and_wall(ball) :
                ball.wall_collision()

            if collision.check_left_player_goal(ball) :
                right_score.increase()
                ball.restart_pos()
                left_paddle.restart_pos()
                right_paddle.restart_pos()
                playing = False

            if collision.check_right_player_goal(ball) :
                left_score.increase()
                ball.restart_pos()
                left_paddle.restart_pos()
                right_paddle.restart_pos()
                playing = False
    
        pygame.display.update()
    
def main_menu():
    while True:
        screen.blit(background, (0, 0))

        menu_mouse_pos = pygame.mouse.get_pos()

        menu_text = get_font(75).render("MAIN MENU", True, "#b68f40")
        menu_rect = menu_text.get_rect(center=(s_width//2, 100))

        play_button = Button(image=pygame.image.load("C:\Damian\Coding\Python\Python_Game_Project\Main_Menu_Data/Play Rect.png"), pos=(s_width//2, 250), 
                            text_input="PLAY", font=get_font(50), base_color="#d7fcd4", hovering_color="White")
        quit_button = Button(image=pygame.image.load("C:\Damian\Coding\Python\Python_Game_Project\Main_Menu_Data/Quit Rect.png"), pos=(s_width//2, 380), 
                            text_input="QUIT", font=get_font(50), base_color="#d7fcd4", hovering_color="White")

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

