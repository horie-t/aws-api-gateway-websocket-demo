#include <rpcWiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

#include "./setting.h"


WiFiClientSecure client;

void setup() {
  pinMode(WIO_LIGHT, INPUT);  
 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(500);
    Serial.println("Connecting..");
  }
  Serial.print("Connected to the WiFi network with IP: ");
  Serial.println(WiFi.localIP());
  client.setCACert(rootCa);
}
 
void loop() {
 if(&client) {
  
   HTTPClient http;
 
   http.begin(client, postUrl);  //Specify destination for HTTPS request
   http.addHeader("Content-type", "application/json");             //Specify content-type header

   int light = analogRead(WIO_LIGHT);
 
   int httpResponseCode = http.POST(String(light));   //Send the actual POST request
 
   if(httpResponseCode>0){
    Serial.print("HTTP Response Code: ");
    Serial.println(httpResponseCode);   //Print return code
   }else{
    Serial.print("Error on sending request: ");
    Serial.println(httpResponseCode);
   }
 
   http.end();  //Free resources
 
 }else{
    Serial.println("Unable to create client");
 }
  Serial.println();
  Serial.println("Waiting 1s before the next round...");
  delay(1000);
}
