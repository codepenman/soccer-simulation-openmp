# Assuming Python 2.x
# For Python 3.x support change print -> print(..) and Tkinter to tkinter
from Tkinter import *
import time
import random

# Ground dimenstions : w x h : (45-90m) x (90-120m)
class FootballGround(object):
     def __init__(self):
        self.width = 800
        self.height = 500
        self.root = Tk()
        self.canvas = Canvas(self.root, width=self.width, height = self.height)
        self.canvas.pack()
        self.player1 = self.canvas.create_oval(20, 20, 50, 50, outline='blue', fill='blue')
        self.player2 = self.canvas.create_oval(400, 400, 430, 430, outline='blue', fill='blue')
        self.player3 = self.canvas.create_oval(20, 140, 50, 170, outline='blue', fill='blue')
        self.player4 = self.canvas.create_oval(250, 250, 280, 280, outline='blue', fill='blue')
        self.player5 = self.canvas.create_oval(360, 250, 390, 280, outline='blue', fill='blue')

        self.player6 = self.canvas.create_oval(140, 40, 170, 70, outline='red', fill='red')
        self.player7 = self.canvas.create_oval(250, 270, 280, 300, outline='red', fill='red')
        self.player8 = self.canvas.create_oval(120, 170, 150, 200, outline='red', fill='red')
        self.player9 = self.canvas.create_oval(320, 270, 350, 300, outline='red', fill='red')
        self.player10 = self.canvas.create_oval(360, 70, 390, 100, outline='red', fill='red')

        self.midline = self.canvas.create_line(self.width/2, 0, self.width/2, self.height)
        self.canvas.pack()
        self.root.after(0, self.animation)
        self.root.mainloop()

     def animation(self):
        track = 0
        while True:
            x = 2
            y = 2
            if track == 0:
                # for i in range(0, self.width/5 - 10):
                time.sleep(0.1)
                self.canvas.move(self.player1, x + random.randint(0,5), y + random.randint(0,3))
                self.canvas.move(self.player2, x + random.randint(0,5), y + random.randint(0,3))
                self.canvas.move(self.player3, x + random.randint(0,5), y + random.randint(0,3))
                self.canvas.move(self.player4, x + random.randint(0,5), y + random.randint(0,3))
                self.canvas.move(self.player5, x + random.randint(0,5), y + random.randint(0,3))
                
                self.canvas.move(self.player6, - x - random.randint(0,5), - y - random.randint(0,3))
                self.canvas.move(self.player7, - x - random.randint(0,5), - y - random.randint(0,3))
                self.canvas.move(self.player8, - x - random.randint(0,5), - y - random.randint(0,3))
                self.canvas.move(self.player9, - x - random.randint(0,5), - y - random.randint(0,3))
                self.canvas.move(self.player10, - x - random.randint(0,5), - y - random.randint(0,3))
                self.canvas.update()
                track = 1
                print track

            else:
                # for i in range(0, self.width/5 - 10):
                time.sleep(0.1)
                self.canvas.move(self.player1, - x - random.randint(0,5), - y - random.randint(0,3))
                self.canvas.move(self.player2, - x - random.randint(0,5), - y - random.randint(0,3))
                self.canvas.move(self.player3, - x - random.randint(0,5), - y - random.randint(0,3))
                self.canvas.move(self.player4, - x - random.randint(0,5), - y - random.randint(0,3))
                self.canvas.move(self.player5, - x - random.randint(0,5), - y - random.randint(0,3))
                
                self.canvas.move(self.player6, x + random.randint(0,5), y + random.randint(0,5))
                self.canvas.move(self.player7, x + random.randint(0,5), y + random.randint(0,5))
                self.canvas.move(self.player8, x + random.randint(0,5), y + random.randint(0,5))
                self.canvas.move(self.player9, x + random.randint(0,5), y + random.randint(0,5))
                self.canvas.move(self.player10, x + random.randint(0,5), y + random.randint(0,5))
                self.canvas.update()
                track = 0
                print track
FootballGround()
