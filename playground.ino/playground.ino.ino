
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
    int maxIntensity;
    int ledState;                   // ledState used to set the LED
    int targetLedState;             // current interim level of LED intensity "in transit"
    int progressLedState;           // target LED intensity
    float levelFuncA;                  // 'a' in ax+b intensity linear func
    float levelFuncB;                  // 'b' in ax+b intensity linear func
    unsigned long previousMillis;   // will store last time LED was updated
    
    // Constructor - creates a Flasher 
    // and initializes the member variables and state
    public:
    Flasher(int pin)
    {
        ledPin = pin;
        pinMode(ledPin, OUTPUT);     
          
    
        ledState = 0; 
        previousMillis = 0;

        maxIntensity = 512;

        progressLedState = ledState;
        targetLedState = ledState;
        levelFuncA = 0;
        levelFuncB = 0;
    }
    void setOnOffParams(unsigned long on, unsigned long off){
        OnTime = on;
        OffTime = off;
    }

    void Update()
    {
        OnOffAnimate();
        walkToTargetIntensity();
    }

    void OnOffAnimate(){
        // check to see if it's time to change the state of the LED
        unsigned long currentMillis = millis();
        if ((ledState > 0) && (currentMillis - previousMillis >= OnTime)){
          ledState = maxIntensity/2 + maxIntensity/2*sin(PI/OnTime*(currentMillis - previousMillis));
          analogWrite(ledPin, ledState);
          Serial.println(ledState);
        }
        else if((ledState == maxIntensity) && (currentMillis - previousMillis >= OnTime))
        {
          ledState = 0;  // Turn it off
          previousMillis = currentMillis;  // Remember the time
          analogWrite(ledPin, ledState);  // Update the actual LED
        }
        else if ((ledState == 0) && (currentMillis - previousMillis >= OffTime))
        {
              ledState = 1;  // turn it on
              previousMillis = currentMillis;   // Remember the time
              analogWrite(ledPin, ledState);     // Update the actual LED
        }
    }

    void formIntensityFunc(int intensity, float duration){
        // calculate a and b in ax+b based on target intensity
        /*
        a = rise/run = (targetInt - ledState) / (time)
        b = ledState

        */

        targetLedState = intensity;
        levelFuncB = ledState;
        levelFuncA = (targetLedState - ledState) / duration;
        previousMillis = millis();
        Serial.println(levelFuncA);
    }

    void walkToTargetIntensity(){
        // run ax+b
        if (progressLedState < targetLedState){
            unsigned long now = millis();
            progressLedState = levelFuncA * (now - previousMillis) + levelFuncB;
            // Serial.println(progressLedState);
            analogWrite(ledPin, progressLedState);
        }
    }    
};

Flasher d1(d5_pin);
Flasher d2(d6_pin);
Flasher d3(d7_pin);
Flasher d4(d8_pin);


//MDNSResponder mdns;
//ESP8266WebServer server(80);

//String webPage = "";


void setup() {
// put your setup code here, to run once:
Serial.begin(115200);
delay(10);


d1.formIntensityFunc(255, 45000);
d2.formIntensityFunc(255, 45000);
d3.formIntensityFunc(255, 45000);
d4.formIntensityFunc(255, 45000);
d1.setOnOffParams(1000, 1000);
d2.setOnOffParams(250, 1250);
d3.setOnOffParams(500, 1750);
d4.setOnOffParams(750, 1200);




}
void loop() {

    d1.Update();
     d2.Update();
     d3.Update();
     d4.Update();
}



