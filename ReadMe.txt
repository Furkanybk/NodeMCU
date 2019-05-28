I created this project for my IoT lesson, 

used hardwares and softwares in project;

-NodeMCU LoLin ESP8266
-Arduino UNO

-Adxl345 Accelerometer
-HC SR04 Ultrasonic sensor
-Buzzer

-Arduino IDE
-Blynk

The idea is: when a car crashes to an obstacle, the distance sensor detects a disturb in 
its measurement, also the accelerometer detects a sudden deceleration. 
The NodeMCU send email and notifiy to an emergency contact our phone via Blynk.

I didn't use gps module because it is extra for my project. 
if you want to locate to accident location and mail it, you can use google geolocation api or gps module.

Note:I used arduino for hc sr04, cause hc sr04 couldn't work with 3v from coming NodeMCU.
I find solution with arduino for get 5v.