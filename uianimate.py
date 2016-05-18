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
        self.player2 = self.canvas.create_oval(400, 400, 430, 430, outline='red', fill='red')
        self.player3 = self.canvas.create_oval(140, 140, 170, 170, outline='blue', fill='blue')
        self.player4 = self.canvas.create_oval(250, 250, 280, 280, outline='blue', fill='blue')
        self.player5 = self.canvas.create_oval(360, 360, 390, 390, outline='blue', fill='blue')

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
                self.canvas.move(self.player1, x + random.randint(0,3), y + random.randint(0,3))
                self.canvas.move(self.player2, x + random.randint(0,3), y + random.randint(0,3))
		self.canvas.move(self.player3, x, y)
                self.canvas.update()
                track = 1
                print track

            else:
                # for i in range(0, self.width/5 - 10):
                time.sleep(0.1)
                self.canvas.move(self.player1, -x - random.randint(0,3), -y - random.randint(0,3))
                self.canvas.move(self.player2, -x - random.randint(0,3), -y - random.randint(0,3))
                self.canvas.update()
                track = 0
                print track
FootballGround()
