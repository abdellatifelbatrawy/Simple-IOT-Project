#define BLYNK_TEMPLATE_ID "TMPL21XKd0Kcs"
#define BLYNK_TEMPLATE_NAME "Smart Home"
#define BLYNK_AUTH_TOKEN "C4-etB96EP93Mc-06wbgzYEn6KuW2Jmy"

#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>
#include <utility/wifi_drv.h>
#include <DHT.h>

#define GREEN_PIN 25
#define RED_PIN 26
#define BLUE_PIN 27

BlynkTimer t;
DHT dht(4, DHT11);

void setup(){
  Serial.begin(115200); // Config Serial

  WiFiDrv::pinMode(RED_PIN, OUTPUT);                        // config RED_PIN through wifi
  WiFiDrv::pinMode(GREEN_PIN, OUTPUT);                      // config GREEN_PIN through wifi
  WiFiDrv::pinMode(BLUE_PIN, OUTPUT);                       // config BLUE_PIN through wifi

  Serial.println("Hello From Arduino.");
  Serial.println("Welcome Boss 🫡");

  t.setInterval(2000L, sendData);                           // Config timer
  Blynk.begin(BLYNK_AUTH_TOKEN, "HUAWEI Y7a", "12345678");  // Config WiFi & Connect with Blynk
  Serial.println("Blynk isConnected!");

  dht.begin();                                              // Config the DHT11 sensor
}

void loop(){
  Blynk.run();
  t.run();
}

BLYNK_WRITE(V4){
  int red = param.asInt();
  Serial.print("Red: ");
  Serial.println(red);

  WiFiDrv::analogWrite(RED_PIN, red);
}

BLYNK_WRITE(V5){
  int green = param.asInt();
  Serial.print("Green: ");
  Serial.println(green);

  WiFiDrv::analogWrite(GREEN_PIN, green);
}

BLYNK_WRITE(V6){
  int blue = param.asInt();
  Serial.print("Blue: ");
  Serial.println(blue);

  WiFiDrv::analogWrite(BLUE_PIN, blue);
}

void sendData(){
  Serial.println("Sending Data to Dashboard.");
  
  double Temp = dht.readTemperature();
  double hum = dht.readHumidity();

  Blynk.virtualWrite(V0, Temp);
  Blynk.virtualWrite(V1, hum);

}

BLYNK_WRITE(V7){
  int red = param[0].asInt();
  int green = param[1].asInt();
  int blue = param[2].asInt();
  
  Serial.print("Red: ");
  Serial.println(red);
  Serial.print("Green: ");
  Serial.println(green);
  Serial.print("Blue: ");
  Serial.println(blue);

  WiFiDrv::analogWrite(RED_PIN, red);
  WiFiDrv::analogWrite(GREEN_PIN, green);
  WiFiDrv::analogWrite(BLUE_PIN, blue);
}
