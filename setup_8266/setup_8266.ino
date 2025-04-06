#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <DHT.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
// Ko' wuy' nka^n pku` ho^.
// tudangkimangde
// Nhom 6 Nguoi 1
// 987654321!
const char* ssid = "Ko' wuy' nka^n pku` ho^.";
const char* password = "tudangkimangde";
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;


const int ledPin = 4;
WiFiServer server(80);
String timeWater = "";
int volumeWater;
String timeFood = "";
int massFood;
int countConnect = 0;

FirebaseData firebaseData;
#define chandht 5
#define loaidht DHT11
DHT dht(chandht, loaidht);
float nhietdo;
float doam;


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 25200, 60000);
unsigned long previousMillis = 0; 
const long interval = 0;  

void setup(){
  Serial.begin(115200);
  Serial.print("Connecting to the Newtork");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected"); 
  server.begin();
  Serial.println("Server started");
  Serial.print("IP Address of network: ");
  Serial.println(WiFi.localIP());
  Serial.print("Copy and paste the following URL: https://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  config.host = "https://iot-project-1584f-default-rtdb.firebaseio.com";
  config.api_key = "AIzaSyC0cdhxxQgB1djBR-q1C2449lzF6f-X-2Y";
  auth.user.email = "toan@gmail.com";
  auth.user.password = "271003";
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  pinMode(ledPin, OUTPUT);
  timeClient.begin();
  dht.begin();
}

void loop(){

  
  // unsigned long currentMillis = millis();
  // if (currentMillis - previousMillis >= interval) {
  //   timeClient.update();
  //   previousMillis = currentMillis;
  //   Serial.println(timeClient.getFormattedTime());
  // }
  // nhietdo = dht.readTemperature();
  // doam = dht.readHumidity();
  // Firebase.RTDB.setString(&fbdo, "/ESP/TEMP", nhietdo);
  // Firebase.RTDB.setString(&fbdo, "/ESP/HUM", doam);
  timeWater = setTimeWater();
  volumeWater = SetVolumeWater();
  timeFood = setTimeFood();
  massFood = SetMassFood();
  immediateWatering();
  immediateFood(); 
}


void immediateWatering(){
  int value;
  if (Firebase.RTDB.getInt(&fbdo, "/ESP/PUMP")) {
    if (fbdo.dataType() == "integer" || fbdo.dataTypeEnum() == firebase_rtdb_data_type_integer) {
      value = fbdo.to<int>();
      if(value == 1){
        Serial.println("c " + String(value));
      }
    }
  }
}

void immediateFood(){
  int value;
  if (Firebase.RTDB.getInt(&fbdo, "/ESP/SERVO")) {
    if (fbdo.dataType() == "integer" || fbdo.dataTypeEnum() == firebase_rtdb_data_type_integer) {
      value = fbdo.to<int>();
      if(value == 1){
        Serial.println("d " + String(value));
      }
    } 
  } 
}

String setTimeWater(){
  String value;
  if (Firebase.RTDB.getString(&fbdo, "/ESP/SETTIMEWATER")) {
    if (fbdo.dataType() == "string" || fbdo.dataTypeEnum() == firebase_rtdb_data_type_string) {
      value = fbdo.to<String>();
      if(timeWater != value){
        Serial.println("b " + value);
      }
    }
  } 
  return value;
}

int SetVolumeWater(){
  int volume;
  if (Firebase.RTDB.getInt(&fbdo, "/ESP/VOLUME")) {
    if (fbdo.dataType() == "integer" || fbdo.dataTypeEnum() == firebase_rtdb_data_type_integer) {
      volume = fbdo.to<int>();
      if(volumeWater != volume){
        Serial.println("a " + String(volume));
      }
    } 
  } 
  return volume;
}

String setTimeFood(){
  String value;
  if (Firebase.RTDB.getString(&fbdo, "/ESP/SETTIMEFOOD")) {
    if (fbdo.dataType() == "string" || fbdo.dataTypeEnum() == firebase_rtdb_data_type_string) {
      value = fbdo.to<String>();
      if(timeFood != value){
        Serial.println("e " + value);
      }
    }
  } 
  return value;
}

int SetMassFood(){
  int volume;
  if (Firebase.RTDB.getInt(&fbdo, "/ESP/MASS")) {
    if (fbdo.dataType() == "integer" || fbdo.dataTypeEnum() == firebase_rtdb_data_type_integer) {
      volume = fbdo.to<int>();
      if(massFood != volume){
        Serial.println("f " + String(volume));
      }
    } 
  } 
  return volume;
}


