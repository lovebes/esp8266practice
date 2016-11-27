
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

MDNSResponder mdns;
ESP8266WebServer server(80);

String webPage = "";

int gpio0_pin = 0;
int gpio2_pin = 2;

int gpio0_analog_level = 0;
int ANALOG_MAX = 255;

#define PIN 4
const char* ssid     = "imo";
const char* password = "dlahdlah";

//*** FINISH NTP TIME Setting logic ***//

void setwifi() {
  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  delay(5000);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int stringToInteger(String s)
{
   char arr[12];
   s.toCharArray(arr, sizeof(arr));
   return atoi(arr);
}
//**************************** SETUP() ***************//
void setup() {

  // preparing GPIOs
  pinMode(gpio0_pin, OUTPUT);
  digitalWrite(gpio0_pin, LOW);
  pinMode(gpio2_pin, OUTPUT);
  digitalWrite(gpio2_pin, LOW);
  
  Serial.begin(115200);
  delay(10);

  setwifi();
  // web server setup

  webPage += "<h1>ESP8266 Web Server</h1><p>Socket #1 <a href=\"socket1On\"><button>ON</button></a>&nbsp;<a href=\"socket1Off\"><button>OFF</button></a></p>";
  webPage += "<p>Socket #2 <a href=\"socket2On\"><button>ON</button></a>&nbsp;<a href=\"socket2Off\"><button>OFF</button></a></p>";

  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }

  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  server.on("/socket1On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio0_pin, HIGH);
    delay(1000);
  });
  server.on("/socket1Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio0_pin, LOW);
    delay(1000); 
  });
  server.on("/socket2On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio2_pin, HIGH);
    delay(1000);
  });
  server.on("/socket2Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio2_pin, LOW);
    delay(1000); 
  });
  server.on("/dim", [](){
    int level = stringToInteger(server.arg("level"));
    server.send(200, "text/html", webPage);
    analogWrite(gpio0_pin, level);
//    Serial.println("level for gpio2 change to: "+level);
    delay(1000); 
  });
  server.begin();
  Serial.println("HTTP server started");
  
}

/*******
 * LED fade in function
 */
void fade_in_gpio0() {
  if (gpio0_analog_level <= ANALOG_MAX){
    gpio0_analog_level += 1;
  }
  analogWrite(gpio0_pin, gpio0_analog_level);
  delay(30);
}
// END LED FADE IN FUNCTION
void loop() {
  
  server.handleClient();
}


