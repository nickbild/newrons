# Newrons

Give your memory a boost with Newrons.

<p align="center">
<img src="https://raw.githubusercontent.com/nickbild/newrons/master/media/teaser.gif">
</p>

Higher resolution video in [Media](https://github.com/nickbild/newrons#media) section below.

Newrons are smart glasses that offer a gentle memory assist by flashing a light in the wearer's peripheral vision when they are in the vicinity of an object associated with an event on their calendar.  For example, if the user has "Take Medicine" on their calendar at 2:00PM, and they are near a pill bottle around that time, a light on the glasses will flash to jog the wearer's memory.

This offers the advantage of reminding the wearer of something they need to do exactly when it is convenient to do so.  Smartphone notifications can often be dismissed and forgotten because they give an alert at a time when they are inconvenient or impossible to immediately act on.  It is also completely passive and doesn't require one to have their phone at hand.

## How It Works

A pair of glasses is fitted with a JeVois A33 Smart Machine Vision Camera, an Arduino Nano 33 IoT, an Adafruit PCF8523 Real Time Clock, and a 5050 RGB LED.  Power is supplied by a 5V battery pack.

The JeVois is configured to run a TensorFlow deep convolutional neural network trained on the ImageNet dataset for object detection.  Real-time information about detected objects is transmitted via the 4-pin serial interface to the Arduino.

The Arduino connects via WiFi to the Google Calendar API and retrieves events for the current day using information from the real time clock.  When an object is detected that is associated with a calendar event, within a specified window of time around that event, an LED is pulsed.  [Arduino Code](https://github.com/nickbild/newrons/blob/master/newrons_controller/newrons_controller.ino)

## Media

See it in action:
[YouTube](https://www.youtube.com/watch?v=C8D3Lubc3Jo)

Top view:
![top](https://raw.githubusercontent.com/nickbild/newrons/master/media/top_sm.jpg)

Front view:
![front](https://raw.githubusercontent.com/nickbild/newrons/master/media/front_sm.jpg)

Front left view:
![front left](https://raw.githubusercontent.com/nickbild/newrons/master/media/front_left_sm.jpg)

Front left angle view:
![front left angle](https://raw.githubusercontent.com/nickbild/newrons/master/media/front_left_angle_sm.jpg)

Side angle view:
![Side angle](https://raw.githubusercontent.com/nickbild/newrons/master/media/side_angle_sm.jpg)

## Bill of Materials

- JeVois A33 Smart Machine Vision Camera
- Arduino Nano 33 IoT
- Adafruit PCF8523 Real Time Clock
- 5050 RGB LED
- 5V battery pack
- Glasses or sunglasses

## About the Author

[Nick A. Bild, MS](https://nickbild79.firebaseapp.com/#!/)
