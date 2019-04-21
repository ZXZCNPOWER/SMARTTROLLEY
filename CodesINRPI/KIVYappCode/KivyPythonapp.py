#Import for apps
from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.gridlayout import GridLayout
from kivy.lang import Builder
from kivy.uix.screenmanager import ScreenManager
from kivy.clock import Clock
from kivy.properties import NumericProperty, ReferenceListProperty,ObjectProperty,StringProperty
from kivy.vector import Vector
from kivy.graphics import *



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
    number = NumericProperty(0)
    strnumber = StringProperty(str(number))
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
    pass

    def IncreaseVal(self,*args):
        self.number += 5
        self.ids.value.text ='{} minutes'.format(self.number)


class JackMeApp(App): #Kivy always check for a file name JackMeApp.kv
    def build(self):
        app = JackMeWidget()
        return app
    
JackMeApp().run()

        
