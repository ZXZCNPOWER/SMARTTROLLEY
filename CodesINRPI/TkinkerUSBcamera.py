import tkinter as tk
from tkinter.ttk import Frame, Button, Entry, Style
from tkinter import Tk, W, E
from tkinter import *

from firebase import firebase

from collections import deque
from imutils.video import VideoStream
import numpy as np
import argparse
import cv2
import imutils
import time
import serial
import sched

url ='https://hehehuehue-a9fe7.firebaseio.com/'
#token = 'AIzaSyAR5B7Eo8MQVeUzi4Wrzerjgxjku2aeBro '
firebase = firebase.FirebaseApplication(url)

root = tk.Tk()
root.withdraw()
#make it full screen
#root.wm_attributes
#root.wm_attributes('-fullscreen',1)

#Global variables
current_window = None
counter = 0
HEIGHT = 500
WIDTH = 810
openCV = False
label2 = None
label3= None
inputstr = ''
destination = 'Destination'

#CV Global variables
timePassed =0
sendchar = 'p'


###setting up serial
##ser=serial.Serial(
##port='/dev/ttyUSB0', # the default usb arduino port name
##baudrate=9600, # baud rate must be the same as arduino
##parity=serial.PARITY_NONE,
##stopbits=serial.STOPBITS_ONE,
##bytesize=serial.EIGHTBITS, #data sent is 8 bit in size
##timeout=1) #You need this to send/recieve data.Create a special variable to hold the  serial code that comes from port ttyACMO (Default arduino port)
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

colourLower1 = (0, 100, 70)
colourUpper1= (5, 255, 255)
colourLower2 = (175, 100, 70)
colourUpper2 = (180, 255, 255)    
pts = deque(maxlen=args["buffer"])

# tuple colour used to draw boundary line

green = (0,255,0)
direction = "NotYetFound"


#Define the boundaries
veryRight = 500
notSoRight = 400
Middle = 200
notSoLeft = 100
VeryLeft = 0


# if a video path was not supplied, grab the reference
# to the webcam
if not args.get("video", False):
        vs = VideoStream(src=0).start()
 
# otherwise, grab a reference to the video file
else:
        vs = cv2.VideoCapture(args["video"])
 
# allow the camera or video file to warm up
time.sleep(1.0)


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
        sendchar = 'f'
        
        return [direction,sendchar]


def stop_opencv(x):
    global openCV
    openCV = False
    print(openCV)
    # if we are not using a video file, stop the camera video stream
    if not args.get("video", False):
        vs.stop()
    # otherwise, release the camera
    else:
        vs.release()
    # close all windows
    cv2.destroyAllWindows()
    print(x)
    pass


####For reference 
def new_window():
    global counter
    counter += 1
    #replace with next window via global counting
    window = replace_window(root)
    label = tk.Label(window, text="This is window %s" % counter)
    button = tk.Button(window, text="Create a new window", command=new_window)
    label.pack(fill="both", expand=True, padx=20, pady=20)
    button.pack(padx=10, pady=10)
### This functio nis not used at all


def run_opencv():
    global openCV
    global vs
    global args
    global ap
    global direction
    global sendschar
    openCV = True
    while (openCV):
        # grab the current frame
        frame = vs.read()
 
	# handle the frame from VideoCapture or VideoStream
        frame = frame[1] if args.get("video", False) else frame
	#Draw the boundary lines
        cv2.line(frame,(100,0),(100,600),green)
        cv2.line(frame,(250,0),(250,600),green)
        cv2.line(frame,(350,0),(350,600),green)
        cv2.line(frame,(500,0),(500,600),green)
        frame = imutils.rotate(frame,180)

	# if we are viewing a video and we did not grab a frame,
	# then we have reached the end of the video
        if frame is None:
                break
 
	# resize the frame, blur it, and convert it to the HSV
	# color space
        frame = imutils.resize(frame, width=480,height=320)
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
        #for i in range(1, len(pts)):
		# if either of the tracked points are None, ignore
		# them
                #if pts[i - 1] is None or pts[i] is None:
                #        continue
 
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

        #create switch for ON/OFF functionality
        switch = '0 : OFF \n1 : ON'
        cv2.createTrackbar(switch, 'Frame',0,1,stop_opencv)
 
	# if the 'q' key is pressed, stop the loop
        if key == ord("q"):
                break
        #ser.write(sendchar.encode()) # Convert it to ASCII then send it to the Arduino


def follow_me():
    #variables and declaration
    global counter
    counter += 1
    
    window = replace_window(root)
    canvas = tk.Canvas(window,height=HEIGHT, width = WIDTH)
    canvas.pack()

    frame = tk.Frame(window, bg='pale goldenrod')
    frame.place(relwidth = 1, relheight = 1)
    
    label = tk.Label(frame, text="Press button when ready!", font = 'Helvetica 30', bg='pale goldenrod')
    button1 = tk.Button(frame, text="Follow me now", font= 'Helvetica 30',bd=0,bg='tan1',
                        highlightthickness=0, activebackground='tan1', command=run_opencv)
    button2 = tk.Button(frame, text="Go to menu!", font= 'Helvetica 30',bd=0,bg='tan1',
                        highlightthickness=0, activebackground='tan1', command=main_window)
    label.pack(side='top' , fill="x", expand=True, padx=20, pady=10)
    button1.pack(side='left', fill="both", expand=True, padx=10, pady=30)
    button2.pack(side='left',fill ="both",expand=True,padx=10,pady=30)


def show_map():
    #variables and declaration
    global counter
    global inputstr
    counter += 1
    
    window = replace_window(root)
    canvas = tk.Canvas(window,height=HEIGHT, width = WIDTH)
    canvas.pack()

    frame = tk.Frame(window, bg='pale goldenrod')
    frame.place(relwidth = 1, relheight = 1)
    
    label = tk.Label(frame, text="THE AMAZING MAP !", font = 'Helvetica 30', bg='pale goldenrod')
    button1 = tk.Button(frame, text="GO TO MENU", font= 'Helvetica 30',bd=0,bg='tan1',
                        highlightthickness=0, activebackground='tan1', command=main_window)
    label.pack(side='top' , fill="x", expand=True, padx=20, pady=10)
    button1.pack(side='left', fill="both", expand=True, padx=10, pady=30)


btnheight = 2
btnwidth = 6
def show_flight(_inputstr):
    #variables and declaration
    global counter
    global inputstr
    global btnheight
    global btnwidth
    global label2
    global label3
    global destination
    counter += 1
    #change from l
    _ipadx = 3
    _ipady = 3
    _inputstr = inputstr
    
    window = replace_window(root)
    canvas = tk.Canvas(window,height=HEIGHT, width = WIDTH)
    canvas.pack()

    frame = tk.Frame(window, bg='pale goldenrod')
    frame.place(relwidth = 1, relheight = 1)
    
    button1 = tk.Button(frame, text="1", font= 'Helvetica 20',bd=0,bg='tan1',width=btnwidth,height =btnheight,
                        highlightthickness=0, activebackground='tan2', command=lambda: input_str('1'),padx=_ipadx,pady=_ipady)    
    button2 = tk.Button(frame, text="2", font='Helvetica 20',bd=0, bg='tan1',width=btnwidth,height =btnheight,
                        highlightthickness=0, activebackground='tan2', command=lambda:input_str('2'),padx=_ipadx,pady=_ipady)
    button3 = tk.Button(frame, text="3", font='Helvetica 20',bd=0, bg='tan1',width=btnwidth,height =btnheight,
                        highlightthickness=0, activebackground='tan2', command=lambda:input_str('3'),padx=_ipadx,pady=_ipady)
    button4 = tk.Button(frame, text="4", font='Helvetica 20',bd=0, bg='tan1',width=btnwidth,height =btnheight,
                        highlightthickness=0, activebackground='tan2', command=lambda:input_str('4'),padx=_ipadx,pady=_ipady)
    button5 = tk.Button(frame, text="5", font='Helvetica 20',bd=0, bg='tan1',width=btnwidth,height =btnheight,
                        highlightthickness=0, activebackground='tan2', command=lambda:input_str('5'),padx=_ipadx,pady=_ipady)
    button6 = tk.Button(frame, text="6", font='Helvetica 20',bd=0, bg='tan1',width=btnwidth,height =btnheight,
                        highlightthickness=0, activebackground='tan2', command=lambda:input_str('6'),padx=_ipadx,pady=_ipady)
    button7 = tk.Button(frame, text="7", font='Helvetica 20',bd=0, bg='tan1',width=btnwidth,height =btnheight,
                        highlightthickness=0, activebackground='tan2', command=lambda:input_str('7'),padx=_ipadx,pady=_ipady)
    button8 = tk.Button(frame, text="8", font='Helvetica 20',bd=0, bg='tan1',width=btnwidth,height =btnheight,
                        highlightthickness=0, activebackground='tan2', command=lambda:input_str('8'),padx=_ipadx,pady=_ipady)
    button9 = tk.Button(frame, text="9", font='Helvetica 20',bd=0, bg='tan1',width=btnwidth,height =btnheight,
                        highlightthickness=0, activebackground='tan2', command=lambda:input_str('9'),padx=_ipadx,pady=_ipady)
    button10 = tk.Button(frame, text="Enter", font='Helvetica 20',bd=0, bg='tan1',width=btnwidth,height =btnheight,
                        highlightthickness=0, activebackground='tan2', command=lambda:input_str('Enter'),padx=_ipadx,pady=_ipady)
    button11 = tk.Button(frame, font='Helvetica 20',bd=0, bg='tan1',width=btnwidth,height =btnheight,
                        highlightthickness=0, activebackground='tan2',padx=_ipadx,pady=_ipady)
    button12 = tk.Button(frame, text="Delete", font='Helvetica 20',bd=0, bg='tan1',width=btnwidth,height =btnheight,
                        highlightthickness=0, activebackground='tan2',command=lambda:input_str('Delete'),padx=_ipadx,pady=_ipady)
    button13=tk.Button(frame , text = "Menu", font='Helvetica 20', bd=0 , bg = 'tan3',highlightthickness=0,activebackground='tan1',command = main_window)
    
    button1.grid(row=0,column=3)
    button2.grid(row=0,column=4)
    button3.grid(row=0,column=5)
    button4.grid(row=1,column=3)
    button5.grid(row=1,column=4)
    button6.grid(row=1,column=5)
    button7.grid(row=2,column=3)
    button8.grid(row=2,column=4)
    button9.grid(row=2,column=5)
    button10.grid(row=3,column=3)
    button11.grid(row=3,column=4)
    button12.grid(row=3,column=5)
    button13.grid(row=4,column=0,columnspan=6)
    
    label1 = tk.Label(frame, text="Enter flight number!     ", font = 'Helvetica 20', bg='pale goldenrod')
    label2 = tk.Label(frame, text=_inputstr, font = 'Helvetica 20', bg='pale goldenrod')
    label3 = tk.Label(frame, text=destination, font = 'Helvetica 20', bg='pale goldenrod')
    label1.grid(row=0,column=0,columnspan=2, sticky=W)
    label2.grid(row=1,column=0,columnspan=2, sticky=W)
    label3.grid(row=2,column=0,columnspan=2, sticky=W)



def input_str(_inputstr):

    global counter
    global inputstr
    global btnheight
    global btnwidth
    global label2
    global label3
    counter += 1
    #change from l
    flightlist = ['1','2','3']
    if ((_inputstr == 'Enter') & (inputstr  in  flightlist)):
            label3.config(text = firebase.get('/',inputstr))
            print(firebase.get('/',inputstr))
            inputstr = ''
    elif (_inputstr =='Delete'):
            inputstr = ''
            labe2.config(text=inputstr)
            
    elif(_inputstr =='Enter'):
            label3.config(text= 'No flight found D:')
            inputstr =''
            label2.config(text=inputstr)
    else:
         inputstr +=_inputstr
         label2.config(text=inputstr)
         print(inputstr)

    

def  replace_window(root):
#   Destroy current window, create new window
    global current_window
    if current_window is not None:
        current_window.destroy()
    current_window = tk.Toplevel(root)

    # if the user kills the window via the window manager,
    # exit the application. 
    current_window.wm_protocol("WM_DELETE_WINDOW", root.destroy)

    return current_window


#Start screen
def main_window():
    global counter
    counter += 1

    window = replace_window(root)
    canvas = tk.Canvas(window,height=HEIGHT, width = WIDTH)
    canvas.pack()

    frame = tk.Frame(window, bg='pale goldenrod')
    frame.place(relwidth = 1, relheight = 1)

    label = tk.Label(frame, text="Hello! :D", bg='pale goldenrod', fg='black', font = 'Helvetica 50 bold')

    button1 = tk.Button(frame, text="Map", font = 'Helvetica 20',bg='gold', 
                       highlightthickness=0, activebackground='gold', fg='black',bd=0, command=show_map) #15 characters
    
    button2 = tk.Button(frame, text="Follow Me!", font = 'Helvetica 20',bg='gold',
                       highlightthickness=0, activebackground='gold', fg='black',bd=0, command=follow_me)

    button3 = tk.Button(frame, text="Flight information!", font = 'Helvetica 20',bg='gold',
                       highlightthickness=0, activebackground='gold', fg='black',bd=0, command=lambda:show_flight(inputstr))
    
    button4 = tk.Button(frame, text="More functions!", font = 'Helvetica 20',bg='gold',
                       highlightthickness=0, activebackground='gold', fg='black',bd=0, command=None)

    label.pack(side='top' , fill="x", expand=True)
    button1.pack(side='left',expand=True ,padx=5, pady=5)
    button2.pack(side='left',expand=True ,padx=5, pady=5)
    button3.pack(side='left',expand=True ,padx=5, pady=5)
    button4.pack(side='left', expand=True ,padx=5, pady=5)

        
#main screen
window = main_window()

root.mainloop()
