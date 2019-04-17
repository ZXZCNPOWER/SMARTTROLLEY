#Import necessary apps
from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.gridlayout import GridLayout
from kivy.lang import Builder
from kivy.uix.screenmanager import ScreenManager
from kivy.clock import Clock
from kivy.properties import NumericProperty, ReferenceListProperty,ObjectProperty
from kivy.vector import Vector
from kivy.graphics import *
from kivy.properties import BooleanProperty


from collections import deque
from imutils.video import VideoStream
import numpy as np
import argparse
import cv2
import imutils
import time
import serial
import sched


Builder.load_file('awesome.kv')

class JackMeWidget(ScreenManager):


    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.cvActivated = False
        print(self.cvActivated)

    ##OPEN CV SETTING UP
    #variables
        self.timePassed =0
        self.sendchar = 'p'
        #self.event1

##    #setting up serial
##    ser=serial.Serial(
##    port='/dev/ttyUSB0', # the default usb arduino port name
##    baudrate=9600, # baud rate must be the same as arduino
##    parity=serial.PARITY_NONE,
##    stopbits=serial.STOPBITS_ONE,
##    bytesize=serial.EIGHTBITS, #data sent is 8 bit in size
##    timeout=1) #You need this to send/recieve data.Create a special variable to hold the  serial code that comes from port ttyACMO (Default arduino port)

     
    # construct the argument parse and parse the arguments
        self.ap = argparse.ArgumentParser()
        self.ap.add_argument("-v", "--video",
                help="path to the (optional) video file")
        self.ap.add_argument("-b", "--buffer", type=int, default=64,
                help="max buffer size")
        self.args = vars(self.ap.parse_args())

    # define the lower and upper boundaries of the colour
    # ball in the HSV color space, then initialize the
    # list of tracked points
        self.colourLower1 = (0, 100, 70)
        self.colourUpper1= (5, 255, 255)

        self.colourLower2 = (175, 100, 70)
        self.colourUpper2 = (180, 255, 255)    
        self.pts = deque(maxlen=self.args["buffer"])


    # tuple colour used to draw boundary line
        self.green = (0,255,0)


    #Define the boundaries
        self.veryRight = 500
        self.notSoRight = 350
        self.Middle = 250
        self.notSoLeft = 100
        self.VeryLeft = 0
  
    #If not ball found 
        self.direction = "NotYetFound"
    # if a video path was not supplied, grab the reference
    # to the webcam
        if not self.args.get("video", False):
                self.vs = VideoStream(src=0).start()
     
    # otherwise, grab a reference to the video file
        else:
                self.vs = cv2.VideoCapture(self.args["video"])
     
    # allow the camera or video file to warm up
    time.sleep(1.0)
    
##    pass

    def start_CV(self):
        self.event1 = Clock.schedule_interval(self.open_CV,1/60)

    def stop_CV(self):
        Clock.unschedule(self.event1)
        cv2.destroyAllWindows()

    def open_CV(self,dt):
        self.cvActivated = True
        print(str(self.cvActivated) + "functionran")
        # grab the current frame
        frame = self.vs.read()
	# handle the frame from VideoCapture or VideoStream
        frame = frame[1] if self.args.get("video", False) else frame
	#Draw the boundary lines
        cv2.line(frame,(100,0),(100,600),self.green)
        cv2.line(frame,(250,0),(250,600),self.green)
        cv2.line(frame,(350,0),(350,600),self.green)
        cv2.line(frame,(500,0),(500,600),self.green)
 

 
	# resize the frame, blur it, and convert it to the HSV
	# color space
        frame = imutils.resize(frame, width=800)
        #blurred = cv2.GaussianBlur(frame, (11, 11), 0)
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        # construct a mask for the color , then perform
        # a series of dilations and erosions to remove any small
        # blobs left in the mask
        mask1 = cv2.inRange(hsv, self.colourLower1, self.colourUpper1)
        mask2 = cv2.inRange(hsv, self.colourLower2, self.colourUpper2)
        mask = mask1 + mask2
        #mask = cv2.erode(mask, None, iterations=2)
        #mask = cv2.dilate(mask, None, iterations=2)

        mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, np.ones((2,2),np.uint8))
        mask = cv2.morphologyEx(mask, cv2.MORPH_DILATE, np.ones((2,2),np.uint8))


	# find contours in the mask and initialize the current
	# (x, y) center of the ball
        cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
        cnts = imutils.grab_contours(cnts)
        center = None
 
	# only proceed if at least one contour was found
        if len(cnts) > 0:
		# find the largest contour in the mask, then use
		# it to compute the minimum enclosing circle and
		# centroid
                c = max(cnts, key=cv2.contourArea)
                ((x, y), radius) = cv2.minEnclosingCircle(c)
                M = cv2.moments(c)
                center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
                 
		# only proceed if the radius meets a minimum size
                if radius > 25:
			# draw the circle and centroid on the frame,
			# then update the list of tracked points
                        self.direction = self.location(int(x))[0]
                        self.sendchar = self.location(int(x))[1]
                        cv2.circle(frame, (int(x), int(y)), int(radius),(0, 255, 255), 2)
                        cv2.circle(frame, center, 5, (0, 0, 255), -1)
			
                else:
                        direction = self.trackerlost()[0]
                        sendchar = self.trackerlost()[1]



	# update the points queue
        self.pts.appendleft(center)

	# loop over the set of tracked points
        for i in range(1, len(self.pts)):
		# if either of the tracked points are None, ignore
		# them
                if self.pts[i - 1] is None or self.pts[i] is None:
                        continue
 
		# otherwise, compute the thickness of the line and
		# draw the connecting lines
                thickness = int(np.sqrt(self.args["buffer"] / float(i + 1)) * 2.5)
                cv2.line(frame, self.pts[i - 1], self.pts[i], (0, 0, 255), thickness)

        #Put the text in frame
        cv2.putText(frame, self.direction, (10, 30), cv2.FONT_HERSHEY_SIMPLEX,0.65, (0, 0, 255), 3)
	
	# show the frame and mask to our screen
        cv2.imshow("Frame", frame)
        cv2.imshow("Mask",mask)
        key = cv2.waitKey(1) & 0xFF
 
	# if the 'q' key is pressed, stop the loop
        #if key == ord("q"):
                #break    
        
    def location(self,x):
            sendstr = ''
            if x >  veryRight :
                    direction = "VeryRight"
                    sendchar = 'd'
            elif  x > notSoRight :
                    direction = "NotSoRight"
                    sendchar = 'c'
            elif x > Middle:
                    direction = "Middle"
                    sendchar = 'f'
            elif x > notSoLeft:
                    direction = "NotSoLeft"
                    sendchar = 'b'
            elif x > VeryLeft:
                    direction = "VeryLeft"
                    sendchar = 'a'
            return [direction,sendchar]

    def trackerlost(self):
            direction = "TrackerLost"
            sendchar = 'f'
            return [direction,sendchar]
        
    def helloABCD(self):
        print('hello')


class JackMeApp(App):
    def build(self):
        app = JackMeWidget()
        return app
    
JackMeApp().run()

        
