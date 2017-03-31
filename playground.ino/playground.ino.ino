
/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 *  1. components
 *     - clock
 *     - alarm
 *     - LED dimming circuit
 *
 *
 *
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>

int d1_pin = 5;
int d2_pin = 4;
int d3_pin = 0;
int d4_pin = 2;
int r_pin = d2_pin;
int g_pin = d1_pin;
int b_pin = d3_pin;
int w_pin = d4_pin; 

class Flasher
{
    // Class Member Variables
    // These are initialized at startup
    int ledPin;      // the number of the LED pin
    long OnTime;     // milliseconds of on-time
    long OffTime;    // milliseconds of off-time
 
    // These maintain the current state
    int ledState;                   // ledState used to set the LED
    unsigned long previousMillis;   // will store last time LED was updated

      // Constructor - creates a Flasher 
    // and initializes the member variables and state
    public:
    Flasher(int pin, long on, long off)
    {
        ledPin = pin;
        pinMode(ledPin, OUTPUT);     
          
        OnTime = on;
        OffTime = off;

        ledState = LOW; 
        previousMillis = 0;
    }

    void Update()
    {
        // check to see if it's time to change the state of the LED
        unsigned long currentMillis = millis();
         
        if((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
        {
          ledState = LOW;  // Turn it off
          previousMillis = currentMillis;  // Remember the time
          digitalWrite(ledPin, ledState);  // Update the actual LED
        }
        else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
        {
              ledState = HIGH;  // turn it on
              previousMillis = currentMillis;   // Remember the time
              digitalWrite(ledPin, ledState);     // Update the actual LED
        }
    }
};

Flasher d1(d1_pin, 250, 1250);
Flasher d2(d2_pin, 500, 1000);
Flasher d3(d3_pin, 750, 1750);
Flasher d4(d4_pin, 1000, 2000);


//MDNSResponder mdns;
//ESP8266WebServer server(80);

//String webPage = "";

//int gpio0_pin = 0;
//int gpio2_pin = 2;

void setup() {
// put your setup code here, to run once:

// pinMode(r_pin,OUTPUT);

// pinMode(g_pin,OUTPUT);

// pinMode(b_pin,OUTPUT);
// pinMode(w_pin,OUTPUT);

}

void loop() {
// // put your main code here, to run repeatedly:
// for(int fade = 0; fade <=255; fade +=5){
// analogWrite(r_pin,fade);
// delay(30);
// }
// for(int fade = 255; fade >= 0; fade -=5){
// analogWrite(r_pin,fade);
// delay(30);
// }
// for(int fade = 0; fade <=255; fade +=5){
// analogWrite(g_pin,fade);
// delay(30);
// }
// for(int fade = 255; fade >= 0; fade -=5){
// analogWrite(g_pin,fade);
// delay(30);
// }
// for(int fade = 0; fade <=255; fade +=5){
// analogWrite(b_pin,fade);
// delay(30);
// }
// for(int fade = 255; fade >= 0; fade -=5){
// analogWrite(b_pin,fade);
// delay(30);
// }
// for(int fade = 0; fade <=255; fade +=5){
// analogWrite(w_pin,fade);
// delay(30);
// }
// for(int fade = 255; fade >= 0; fade -=5){
// analogWrite(w_pin,fade);
// delay(30);
// }
    Flasher pins[] = {d1, d2, d3, d4};
    for (int i=0; i < sizeof(pins); i++){
        pins[i].update();
    }
}

