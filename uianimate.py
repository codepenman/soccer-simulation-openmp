# Assuming Python 2.x
# For Python 3.x support change print -> print(..) and Tkinter to tkinter
from Tkinter import *
import time
import random
import Main
import thread
import copy

# Ground dimenstions : w x h : (45-90m) x (90-120m)
class FootballGround(object):
    
    def printPoints(self, points):
        for point in points:
            print point.x, point.y

    def animation(self):
        print "In Animation..."
        while self.gameOn:
            time.sleep(0.2)
            oldPoints = []
            for point in self.points:
                oldPoints.append(point)

            self.points = []
            for i in xrange(10):
                self.points.append(Main.getPlayerPositions(i))

            print "-----"
            self.printPoints(oldPoints)
            print "-----"
            self.printPoints(self.points)

            i = 0    
            print "There are ", len(self.players), "players"
            for player in self.players:
                print "X movement", self.points[i].x - oldPoints[i].x
                print "Y movement", self.points[i].y - oldPoints[i].y
                self.canvas.move(player, self.points[i].x - oldPoints[i].x, self.points[i].y - oldPoints[i].y)
                i = i + 1
            self.canvas.update()

    def play(self):
        Main.play()
        self.gameOn = False

    def __init__(self):
        self.gameOn = True
        self.width = 800
        self.height = 500
        self.root = Tk()
        self.canvas = Canvas(self.root, width=self.width, height = self.height)
        self.canvas.pack()

        self.points = []
        for i in xrange(10):
            self.points.append(Main.getPlayerPositions(i))

        self.players = []
        for point in self.points:
            player = self.canvas.create_oval(point.x, point.y, point.x + 20, point.y + 20, outline='blue', fill='blue')
            self.players.append(player)

        self.midline = self.canvas.create_line(self.width/2, 0, self.width/2, self.height)
        self.canvas.pack()
        #self.root.after(0, self.animation)
        try:
            thread.start_new_thread(self.animation, ())
            thread.start_new_thread(self.play, ())
        except Exception as e:
            print "error"
            print e
        self.root.mainloop()
FootballGround()