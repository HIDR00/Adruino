#include <Servo.h>

const int ledPin = 13;
Servo myservo;
int pos = 0;

int minuteWater = 61;
int hourWater = 25;
int minuteFood = 61;
int hourFood = 25;
unsigned long volume = 100;
unsigned long mass = 100;
unsigned long startWateringTime = 0;
bool isWatering1 = false;
bool isWatering = false;
bool isFood1 = false;
bool isFood = false;
int immediateWatering = 0;
int immediateFood = 0;
int hour = 0, minute = 0, second = 0;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  myservo.attach(9);
}

void loop() {
  // DateTime now = RTC.now();
  // Serial.print(now.hour(), DEC);
  // Serial.print(":");
  // Serial.print(now.minute(), DEC);
  // Serial.print(":");
  // Serial.print(now.second(), DEC);
  // Serial.println();

  // for(pos = 0; pos < 180; pos += 1){
  //       myservo.write(pos);
  //       delay(15);
  //   }

  //   for(pos = 180; pos>=1; pos-=1) {
  //       myservo.write(pos);
  //       delay(15);
  //   }

  receiveData();
  checkWater(minute, hour, second);
  checkFood(minute, hour, second);
  waterNow();
  foodNow();
}

void receiveData() {
  if (Serial.available()) {
    String c = Serial.readStringUntil('\n');
    if (c[0] == 'b') {
      formatTime(c);
    } else if (c[0] == 'a') {
      formatVolume(c);
    } else if (c[0] == 'c') {
      formatImmediateWatering(c);
    } else if (c[0] == 'd') {
      formatImmediateFood(c);
    } else if (c[0] == 'e') {
      formatTime(c);
    } else if (c[0] == 'f') {
      formatVolume(c);
    } else {
      formatTimeAlert(c);
    }
  }
  delay(1000);
}

void waterNow() {
  if (immediateWatering == 1 && !isWatering) {
    Serial.print("on");
    digitalWrite(ledPin, HIGH);
    startWateringTime = millis();
    isWatering = true;
  }
  if (isWatering && millis() - startWateringTime >= volume * 10) {
    Serial.print("off");
    digitalWrite(ledPin, LOW);
    isWatering = false;
    immediateWatering = 0;
  }
}

void foodNow() {
  if (immediateFood == 1 && !isFood) {
    Serial.print("on");
    pos = 180;
    myservo.write(pos);
    startWateringTime = millis();
    isFood = true;
  }
  if (isFood && millis() - startWateringTime >= 1000) {
    Serial.print("off");
    pos = 0;
    myservo.write(pos);
    isFood = false;
    immediateFood = 0;
  }
}

void checkWater(int nowMinute, int nowHour, int nowSecond) {
  if (minuteWater == nowMinute && hourWater == nowHour && !isWatering1 && (nowSecond < (volume / 100))) {
    Serial.print("on");
    digitalWrite(ledPin, HIGH);
    startWateringTime = millis();
    isWatering1 = true;
  }
  if (isWatering1 && millis() - startWateringTime >= volume * 10) {
    Serial.print("off");
    digitalWrite(ledPin, LOW);
    isWatering1 = false;
    immediateWatering = 0;
  }
}

void checkFood(int nowMinute, int nowHour, int nowSecond) {
  if (minuteFood == nowMinute && hourFood == nowHour && !isFood1 && (nowSecond < (volume / 100))) {
    Serial.print("on");
    pos = 180;
    myservo.write(pos);
    startWateringTime = millis();
    isFood1 = true;
  }
  if (isFood1 && millis() - startWateringTime >= volume * 10) {
    Serial.print("off");
    pos = 0;
    myservo.write(pos);
    isFood1 = false;
  }
}

void formatTimeAlert(const String &timeString) {
  int colonIndex1 = timeString.indexOf(':');
  int colonIndex2 = timeString.lastIndexOf(':');

  hour = timeString.substring(0, colonIndex1).toInt();
  minute = timeString.substring(colonIndex1 + 1, colonIndex2).toInt();
  second = timeString.substring(colonIndex2 + 1).toInt();
  Serial.print("Time: ");
  Serial.print(hour);
  Serial.print(":");
  Serial.print(minute);
  Serial.print(":");
  Serial.println(second);
}

void formatTime(String timeOnString) {
  int colonIndex1 = timeOnString.indexOf(':');
  if (timeOnString[0] == 'b') {
    hourWater = timeOnString.substring(2, colonIndex1).toInt();
    minuteWater = timeOnString.substring(colonIndex1 + 1).toInt();
    Serial.println("TimeWater:");
    Serial.println(hourWater);
    Serial.println(minuteWater);
  } else if (timeOnString[0] == 'e') {
    hourFood = timeOnString.substring(2, colonIndex1).toInt();
    minuteFood = timeOnString.substring(colonIndex1 + 1).toInt();
    Serial.println("TimeFood:");
    Serial.println(hourFood);
    Serial.println(minuteFood);
  }
}


void formatVolume(String value) {
  if (value[0] == 'a') {
    Serial.println("Volume");
    volume = value.substring(2).toInt();
    Serial.println(volume);
  } else if (value[0] == 'f') {
    Serial.println("Mass");
    mass = value.substring(2).toInt();
    Serial.println(mass);
  }
}


void formatImmediateWatering(String value) {
  immediateWatering = value.substring(2).toInt();
  Serial.println(immediateWatering);
}
void formatImmediateFood(String value) {
  immediateFood = value.substring(2).toInt();
  Serial.println(immediateFood);
}
