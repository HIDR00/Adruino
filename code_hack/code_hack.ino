#include <WiFi.h>
#include <Firebase_ESP_Client.h>

#define CAMERA_MODEL_AI_THINKER 


// const char* ssid = "Toan";
// const char* password = "tudangkimangde";
const char* ssid = "Ko' wuy' nka^n pku` ho^.";
const char* password = "tudangkimangde";
int countConnect = 0;

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);

  // Cài đặt ESP32-CAM như một điểm truy cập Wi-Fi7
  // WiFi.softAP(ssid, password);

  // Serial.println();
  // Serial.print("IP address: ");
  // Serial.println(WiFi.softAPIP());  

  WiFi.begin(ssid, password);
  WiFi.setSleep(false);
  while (WiFi.status() != WL_CONNECTED) {
    countConnect++;
    if(countConnect == 10){
      ssid = "Nhom 6 Nguoi";
      password = "987654321!";
      WiFi.begin(ssid, password);
    }
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  config.host = "https://iot-project-1584f-default-rtdb.firebaseio.com";
  config.api_key = "AIzaSyC0cdhxxQgB1djBR-q1C2449lzF6f-X-2Y";
  auth.user.email = "toan@gmail.com";
  auth.user.password = "271003";
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  immediateWatering();
}


void immediateWatering(){
  int value;
  if (Firebase.RTDB.getInt(&fbdo, "/ESP/PUMP")) {
    if (fbdo.dataType() == "integer" || fbdo.dataTypeEnum() == firebase_rtdb_data_type_integer) {
      value = fbdo.to<int>();
      Serial.println("value: " + String(value));
    }
  }
}