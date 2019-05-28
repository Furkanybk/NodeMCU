#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
 
#define Threshold 1.5
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

char auth[] = "your blynk auth";

char ssid[] = "ssid";
char pass[] = "pass";

SimpleTimer timer;
 
float Accel_X = 0;
float Accel_Y = 0;
float Accel_Z = 0;

// for adxl345 SCL pin to D1 and SDA pin to D2
const int trigPin = 12;  //D6
const int echoPin = 14;  //D5

const int buzzer = 15;   //D8

bool accident_state;

// defines variables
long duration;
int distance;

void sendSensor()
{
   Blynk.virtualWrite(V4,Accel_X);
   Blynk.virtualWrite(V5,Accel_Y);
   Blynk.virtualWrite(V6,Accel_Z);
   Blynk.virtualWrite(V2,distance);
}


void setup(void) 
{
  accel.begin();
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  Serial.println("ADXL345 Accelerometer Calibration"); 
  Serial.println("");
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buzzer, OUTPUT);
  
  digitalWrite(buzzer, LOW);

  accident_state = false;
  timer.setInterval(1000L, sendSensor);
}
 
void loop(void)
{
    Blynk.run(); // Blynk başlat
    timer.run(); // basit zamanlayıcı başlat
    
    if((Accel_X>Threshold || Accel_X<-Threshold || Accel_Y>Threshold || Accel_Y<-Threshold ||Accel_Z>10+Threshold || Accel_Z<-10-Threshold)&& distance <= 5 && accident_state == false) 
    {
        Serial.println("Kaza oldu.");
        digitalWrite(buzzer, HIGH);
        accident_state = true;
        Blynk.notify("Kaza oldu...");
        Blynk.email("yourmail@gmail.com", "ACIL !!!", "Kaza Oldu...");
    }
    
    else
    {
      check();
    }
}

void check()
{
    sensors_event_t accelEvent;  
    accel.getEvent(&accelEvent);
    
    Accel_X = accelEvent.acceleration.x;
    Accel_Y = accelEvent.acceleration.y;
    Accel_Z = accelEvent.acceleration.z;

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
    Serial.print("Accel Values: "); 
    Serial.print(Accel_X); 
    Serial.print("  ");
    Serial.print(Accel_Y); 
    Serial.print("  "); 
    Serial.print(Accel_Z); 
    Serial.println();
    
    duration = pulseIn(echoPin, HIGH);
    distance= duration*0.034/2;
    Serial.print("Distance: ");
    Serial.println(distance);
    
    delay(100);
}
