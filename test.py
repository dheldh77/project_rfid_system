#!/usr/bin/python
#--------------------------------------
#    ___  ___  _ ____          
#   / _ \/ _ \(_) __/__  __ __ 
#  / , _/ ___/ /\ \/ _ \/ // / 
# /_/|_/_/  /_/___/ .__/\_, /  
#                /_/   /___/   
#
#  RC522 Simple Read Example
#
# This script requires a RC522 RFID reader
# with SPI enabled.
# 
# It uses the following libraries :
# https://github.com/lthiery/SPI-Py.git
# https://github.com/mxgxw/MFRC522-python
#
# Please see https://www.raspberrypi-spy.co.uk/
# for more information.
#
# Author : Matt Hawkins
# Date   : 23/02/2018
#
#--------------------------------------

import time
import RPi.GPIO as GPIO
import MFRC522
import sqlite3

# Create an object of the class MFRC522
MIFAREReader = MFRC522.MFRC522()

# Welcome message
print("Looking for cards")
print("Press Ctrl-C to stop.")

# This loop checks for chips. If one is near it will get the UID
try:
  
  while True:

    # Scan for cards
    (status,TagType) = MIFAREReader.MFRC522_Request(MIFAREReader.PICC_REQIDL)

    # Get the UID of the card
    (status,uid) = MIFAREReader.MFRC522_Anticoll()

    # If we have the UID, continue
    if status == MIFAREReader.MI_OK:

      # Print UID
      print("Card UID: "+str(uid[0])+","+str(uid[1])+","+str(uid[2])+","+str(uid[3]))
	  custom = str(uid[0])+","+str(uid[1])+","+str(uid[2])
	  pyautogui.typewrite(custom)
	  pyautogui.press('enter')
      time.sleep(2)

except KeyboardInterrupt:
  GPIO.cleanup()

