#include <Arduino.h>
#include <WiFiUdp.h>
#include <WiFi.h>

int status = WL_IDLE_STATUS;
char ssid[] = "KURONet"; //  your network SSID (name)
char pass[] = "14051158"; 
unsigned int localPort = 2400;
byte data[8]; 
WiFiUDP myConnection;

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, pass);
  Serial.print(WiFi.softAPIP());
  
  // Serial.println("Connected to wifi");
  // IPAddress ip = WiFi.localIP();
  // Serial.print("IP Address: ");
  // Serial.println(ip);
  // Serial.println("\nStarting connection to server...");
  // // if you get a connection, report back via serial:
  myConnection.begin(localPort);


  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  if(myConnection.available()){
    myConnection.readBytes(data,1);
    Serial.println(data[0]);
  }
}
