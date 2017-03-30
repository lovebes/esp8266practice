
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

//MDNSResponder mdns;
//ESP8266WebServer server(80);

//String webPage = "";

//int gpio0_pin = 0;
//int gpio2_pin = 2;
int d1 = 5;
int d2 = 4;
int d3 = 0;
int d4 = 2;
int r_pin = d2;
int g_pin = d1;
int b_pin = d3;
int w_pin = d4; 

void setup() {
// put your setup code here, to run once:

pinMode(r_pin,OUTPUT);

pinMode(g_pin,OUTPUT);

pinMode(b_pin,OUTPUT);

}

void loop() {
// put your main code here, to run repeatedly:
for(int fade = 0; fade <=255; fade +=5){
analogWrite(r_pin,fade);
delay(30);
}
for(int fade = 255; fade >= 0; fade -=5){
analogWrite(r_pin,fade);
delay(30);
}
for(int fade = 0; fade <=255; fade +=5){
analogWrite(g_pin,fade);
delay(30);
}
for(int fade = 255; fade >= 0; fade -=5){
analogWrite(g_pin,fade);
delay(30);
}
for(int fade = 0; fade <=255; fade +=5){
analogWrite(b_pin,fade);
delay(30);
}
for(int fade = 255; fade >= 0; fade -=5){
analogWrite(b_pin,fade);
delay(30);
}

}

