#include "HomeSpan.h"
#include "fan.h"

int pinA = 13;
int pinB = 12;
int ledPin = 27;
int buttonPin = 14;

void setup(){
 
  Serial.begin(115200);

  pinMode(ledPin, INPUT);
  pinMode(buttonPin, OUTPUT);

  homeSpan.setControlPin(buttonPin);
  homeSpan.setStatusPin(ledPin);

  homeSpan.begin(Category::Fans,"ESP32 Fan");

  new SpanAccessory();
  
    new Service::AccessoryInformation();
      new Characteristic::Identify();  

    new ESP32Fan(pinA, pinB);

}

void loop(){

  homeSpan.poll();

}
