#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "html.h"

#define chandht 5
#define loaidht DHT11
DHT dht(chandht, loaidht);
// Ko' wuy' nka^n pku` ho^.
// tudangkimangde
// Nhom 6 Nguoi 1
// 987654321!
const char* ssid = "Ko' wuy' nka^n pku` ho^.";
const char* password = "tudangkimangde";
float nhietdo;
float doam;


ESP8266WebServer server(80);



void Ketnoi(){
  String s = MAIN_page;
  server.send(200,"text/html",s);
} 

void docdulieunhietdo(){
  nhietdo = dht.readTemperature();
  String snhietdo = String(nhietdo);
  if(isnan(nhietdo)){
    server.send(200,"text/plain","Cam bien khong hoat dong");
  }
  else{
    server.send(200,"text/plain",snhietdo);
  }
}

void docdulieudoam(){
  doam = dht.readHumidity();
  String sdoam = String(doam);
  if(isnan(doam)){
    server.send(200,"text/plain","Cam bien khong hoat dong");
  }
  else{
    server.send(200,"text/plain",sdoam);
  }
}

void setup(){
  Serial.begin(115200);
  pinMode(chandht,INPUT);
  dht.begin();
  Serial.print("Connecting to the Newtork");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected"); 
  Serial.println("Server started");
  Serial.print("IP Address of network: ");
  Serial.println(WiFi.localIP());
  Serial.print("Copy and paste the following URL: https://");
  Serial.println(WiFi.localIP());
  server.on("/", Ketnoi);
  server.on("/docnhietdo",docdulieunhietdo);
  server.on("/docdoam",docdulieudoam);
  server.begin();
}

void loop(){
  nhietdo = dht.readTemperature();
  doam = dht.readHumidity();
  Serial.print("Nhiet do: ");
  Serial.println(nhietdo);
  Serial.print("Do am: ");
  Serial.println(doam);
  server.handleClient();
  delay(500);
}
