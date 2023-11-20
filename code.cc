/*BIOPORI 3C*/
 
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_TEMPLATE_ID "T*******"
#define BLYNK_TEMPLATE_NAME "BIOPORI 3C"
#define BLYNK_AUTH_TOKEN "*******************8"
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
char auth[] = "*********8";
char ssid[] = "fredli15";
char pass[] = "*********";
 
BlynkTimer timer;
bool pinValue = 0;
 
#define trig D3
#define echo D4
#define relay D5
 
void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(relay, OUTPUT);
  Wire.begin(D2, D1);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(10L, Wlevel);
  digitalWrite(relay, HIGH);
}
 
BLYNK_WRITE(V0) {
  pinValue = param.asInt();
}
 
void loop() {
  Blynk.run();
  timer.run();
}
 
void Wlevel() {
  if (pinValue == 1) {
    digitalWrite(relay, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Motor is ON ");
  } else if (pinValue == 0) {
    digitalWrite(relay, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Motor is OFF");
  }
 
  digitalWrite(trig, LOW);
  delayMicroseconds(4);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long t = pulseIn(echo, HIGH);
  long cm = t / 29 / 2;
 
  Blynk.virtualWrite(V1, cm);
  Serial.println(cm);
  lcd.setCursor(0, 0);
  lcd.print("Water Level: ");
  lcd.print(cm);
  lcd.print("   ");
}