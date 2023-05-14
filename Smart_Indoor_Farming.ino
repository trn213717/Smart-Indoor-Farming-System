#define BLYNK_TEMPLATE_ID "TMPL3oBO_ubnN"
#define BLYNK_TEMPLATE_NAME "Embedded"
#define BLYNK_AUTH_TOKEN "iwYSogL9TspBxowKIEQQ2mvKZoJpCBU5"


#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DFRobot_DHT11.h>




//#include<DHT.h>
//#define DHTPIN 27
#define DHT11_PIN 27
//#define DHTTYPE DHT11
DFRobot_DHT11 DHT;
//DHT dht(DHTPIN, DHTTYPE);
int sm_sensor=34;
int light_sensor=35;
int WATER_PUMP_PIN = 4;
int LED_PIN = 18;
int  MOTOR_PIN = 2;
















 BLYNK_WRITE(V3)
{
  int pinvalue = param.asInt();
  digitalWrite(15,pinvalue);
}  




char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "1927";  // type your wifi name
char pass[] = "12345678";  // type your wifi password




BlynkTimer timer;




void sendSensor()
{
  //Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  DHT.read(DHT11_PIN);
 // float h = dht.readHumidity();
       float h =DHT.humidity;
  // Read temperature as Celsius (the default)
  //float t = dht.readTemperature();
float t =DHT.temperature;
  int moisture_sensor= analogRead(sm_sensor);
  int light_intensity =analogRead(light_sensor);
 
  // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V0, t);
    Blynk.virtualWrite(V1, h);
    Blynk.virtualWrite(V2, moisture_sensor);
    Blynk.virtualWrite(V4, light_intensity);
    delay(500);
}
void setup()
{  
 
   Serial.begin(9600);
   pinMode (15,OUTPUT);
  // Initialize pins as inputs or outputs
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(WATER_PUMP_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100L, sendSensor);
 
  }




void loop()
{
  float h = DHT.humidity;
  Serial.print(h);
  delay(100);
  if (h > 60) {
    digitalWrite(MOTOR_PIN, HIGH);
  } else {
    digitalWrite(MOTOR_PIN, LOW);
  }




 int moisture_sensor= analogRead(sm_sensor);
   // Control Water Pump based on moisture
  if (moisture_sensor < 2500) {
    digitalWrite(WATER_PUMP_PIN, HIGH);
  } else {
    digitalWrite(WATER_PUMP_PIN, LOW);
  }
 int light_intensity =analogRead(light_sensor);
   // Control LED based on light intensity
  if (light_intensity > 500) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN,
    LOW);
  }




  Blynk.run();
  timer.run();
 }