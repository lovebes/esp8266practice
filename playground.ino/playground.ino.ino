
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

//#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
//#include <ESP8266WebServer.h>
//#include <ESP8266mDNS.h>
//#include <WiFiUdp.h>

int d1_pin = 5;
int d2_pin = 4;
int d3_pin = 0;
int d4_pin = 2;
int d5_pin = 14;
int d6_pin = 12;
int d7_pin = 13;
int d8_pin = 15;
int r_pin = d8_pin;
int g_pin = d6_pin;
int b_pin = d7_pin;
int w_pin = d5_pin; 

class Flasher
{
    // Class Member Variables
    // These are initialized at startup
    int ledPin;      // the number of the LED pin
    unsigned long OnTime;     // milliseconds of on-time
    unsigned long OffTime;    // milliseconds of off-time
 
    // These maintain the current state
    int ledState;                   // ledState used to set the LED
    unsigned long previousMillis;   // will store last time LED was updated

    // Constructor - creates a Flasher 
    // and initializes the member variables and state
    public:
    Flasher(int pin, unsigned long on, unsigned long off)
    {
        ledPin = pin;
        pinMode(ledPin, OUTPUT);     
          
        OnTime = on;
        OffTime = off;

        ledState = 0; 
        previousMillis = 0;
    }

    void Update()
    {
        // check to see if it's time to change the state of the LED
        unsigned long currentMillis = millis();
        if ((ledState > 0) && (currentMillis - previousMillis >= OnTime)){
          ledState = 125/2 + 125/2*sin(PI/(currentMillis - previousMillis)*currentMillis);
          analogWrite(ledPin, ledState);
        }
        else if((ledState == 125) && (currentMillis - previousMillis >= OnTime))
        {
          ledState = LOW;  // Turn it off
          previousMillis = currentMillis;  // Remember the time
          digitalWrite(ledPin, ledState);  // Update the actual LED
        }
        else if ((ledState == 0) && (currentMillis - previousMillis >= OffTime))
        {
              ledState = 1;  // turn it on
              previousMillis = currentMillis;   // Remember the time
              analogWrite(ledPin, ledState);     // Update the actual LED
        }
    }
};

Flasher d1(d5_pin, 0, 1000);
Flasher d2(d6_pin, 250, 1250);
Flasher d3(d7_pin, 500, 1750);
Flasher d4(d8_pin, 750, 1200);


//MDNSResponder mdns;
//ESP8266WebServer server(80);

//String webPage = "";


void setup() {
// put your setup code here, to run once:

Serial.begin(115200);
delay(10);
}
void loop() {

    d1.Update();
    d2.Update();
    d3.Update();
    d4.Update();
}

