# import the necessary packages
from collections import deque
from imutils.video import VideoStream
import numpy as np
import argparse
import cv2
import imutils
import time
import serial
import sched

#variables
timePassed =0
sendchar = 'p'

#setting up serial
ser=serial.Serial(
port='/dev/ttyACM0', # the default usb arduino port name
baudrate=9600, # baud rate must be the same as arduino
parity=serial.PARITY_NONE,
stopbits=serial.STOPBITS_ONE,
bytesize=serial.EIGHTBITS, #data sent is 8 bit in size
timeout=1) #You need this to send/recieve data.Create a special variable to hold the  serial code that comes from port ttyACMO (Default arduino port)

 
# construct the argument parse and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-v", "--video",
	help="path to the (optional) video file")
ap.add_argument("-b", "--buffer", type=int, default=64,
	help="max buffer size")
args = vars(ap.parse_args())

# define the lower and upper boundaries of the colour
# ball in the HSV color space, then initialize the
# list of tracked points
colourLower1 = (115, 100, 70)
colourUpper1= (140, 255, 255)

colourLower2 = (140, 100, 70)
colourUpper2 = (147, 255, 255)    
pts = deque(maxlen=args["buffer"])


# tuple colour used to draw boundary line
green = (0,255,0)


#Define the boundaries
veryRight = 500
notSoRight = 400
Middle = 200
notSoLeft = 100
VeryLeft = 0



#If not ball found 
direction = "NotYetFound"

def location(x):
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

def trackerlost():
        direction = "TrackerLost"
        sendchar = 's'
        
        return [direction,sendchar]
 
# if a video path was not supplied, grab the reference
# to the webcam
if not args.get("video", False):
        vs = VideoStream(src=0).start()
 
# otherwise, grab a reference to the video file
else:
        vs = cv2.VideoCapture(args["video"])
 
# allow the camera or video file to warm up
time.sleep(2.0)




# keep looping
while True:
	# grab the current frame
        frame = vs.read()
 
	# handle the frame from VideoCapture or VideoStream
        frame = frame[1] if args.get("video", False) else frame
	#Draw the boundary lines
        cv2.line(frame,(100,0),(100,600),green)
        cv2.line(frame,(250,0),(250,600),green)
        cv2.line(frame,(350,0),(350,600),green)
        cv2.line(frame,(500,0),(500,600),green)
 
	# if we are viewing a video and we did not grab a frame,
	# then we have reached the end of the video
        if frame is None:
                break
 
	# resize the frame, blur it, and convert it to the HSV
	# color space
        frame = imutils.resize(frame, width=800)
        #blurred = cv2.GaussianBlur(frame, (11, 11), 0)
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        # construct a mask for the color , then perform
        # a series of dilations and erosions to remove any small
        # blobs left in the mask
        mask1 = cv2.inRange(hsv, colourLower1, colourUpper1)
        mask2 = cv2.inRange(hsv, colourLower2, colourUpper2)
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
                        direction = location(int(x))[0]
                        sendchar = location(int(x))[1]
                        cv2.circle(frame, (int(x), int(y)), int(radius),(0, 255, 255), 2)
                        cv2.circle(frame, center, 5, (0, 0, 255), -1)
			
                else:
                        direction = trackerlost()[0]
                        sendchar = trackerlost()[1]



	# update the points queue
        pts.appendleft(center)

	# loop over the set of tracked points
        for i in range(1, len(pts)):
		# if either of the tracked points are None, ignore
		# them
                if pts[i - 1] is None or pts[i] is None:
                        continue
 
		# otherwise, compute the thickness of the line and
		# draw the connecting lines
                #thickness = int(np.sqrt(args["buffer"] / float(i + 1)) * 2.5)
                #cv2.line(frame, pts[i - 1], pts[i], (0, 0, 255), thickness)

        #Put the text in frame
        cv2.putText(frame, direction, (10, 30), cv2.FONT_HERSHEY_SIMPLEX,0.65, (0, 0, 255), 3)
	
	# show the frame and mask to our screen
        cv2.imshow("Frame", frame)
        cv2.imshow("Mask",mask)
        key = cv2.waitKey(1) & 0xFF
 
	# if the 'q' key is pressed, stop the loop
        if key == ord("q"):
                break
        
        ser.write(sendchar.encode()) # Convert it to ASCII then send it to the Arduino
        #time.sleep(0.1)

# if we are not using a video file, stop the camera video stream
if not args.get("video", False):
        vs.stop()
 
# otherwise, release the camera
else:
        vs.release()
 
# close all windows
cv2.destroyAllWindows()
