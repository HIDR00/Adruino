#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
// Ko' wuy' nka^n pku` ho^.
// tudangkimangde
// Nhom 6 Nguoi 1
// 987654321!
const char* ssid = "Nhom 6 Nguoi 1";
const char* password = "987654321!";
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
        

const int ledPin = 4;
WiFiServer server(80);
// int minuteWater = 61;
// int hourWater = 25; 
// int volume = 1000;

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
}

void loop(){
//  if (Firebase.RTDB.getInt(&fbdo, "/ESP/LED")) {
//   // Kiểm tra xem có lỗi không
//     if (fbdo.dataType() == "integer" || fbdo.dataTypeEnum() == firebase_rtdb_data_type_integer) {
//       // Lấy giá trị dạng int và in ra Serial Monitor
//       int ledValue = fbdo.to<int>();
//       Serial.println("Dữ liệu từ /ESP/LED (kiểu int): " + String(ledValue));
//       if(ledValue == 0){
//         digitalWrite(ledPin, LOW);
//         Serial.println("OFF");
//       }else{
//         digitalWrite(ledPin,HIGH);
//         Serial.println(ledPin);
//         Serial.println("ON");
//       }
//     } else {
//       Serial.println("Dữ liệu không phải kiểu int.");
//     }
//   } else {
//     Serial.println("Lỗi: " + fbdo.errorReason());
//   }
  // formatTime(setTimeWater());
  String tmp = setTimeWater();
  Serial.write(tmp.c_str(), tmp.length());
  // Serial.print("Step1");
  // setTimeWater();
}


String setTimeWater(){
  String time;
  if (Firebase.RTDB.getString(&fbdo, "/ESP/SETTIME")) {
  // Kiểm tra xem có lỗi không
    if (fbdo.dataType() == "string" || fbdo.dataTypeEnum() == firebase_rtdb_data_type_string) {
      // Lấy giá trị dạng int và in ra Serial Monitor
      time = fbdo.to<String>();
      Serial.println("Dữ liệu từ /ESP/TIME (kiểu String): " + time);
    } else {
      Serial.println("Dữ liệu không phải kiểu int.");
    }
  } else {
    Serial.println("Lỗi: " + fbdo.errorReason());
  }
  return time;
}

// void formatTime(String timeOnString){
// 	  int colonIndex1 = timeOnString.indexOf(':');
//   	minuteWater = timeOnString.substring(0, colonIndex1).toInt();
//   	hourWater = timeOnString.substring(colonIndex1 + 1).toInt();
// }


