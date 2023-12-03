#include <Blynk.h>

#include <Adafruit_Sensor.h>

#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 12
int AO_SPIN = 14;
int AO_GPIN = 13;

#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);

const int buzzer = 26;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(AO_SPIN, INPUT);
  pinMode(AO_GPIN, INPUT);
//  pinMode(2,OUTPUT);
    Serial.begin(9600);
    Serial.println(F("DHTxx text"));
    Serial.println("Warming up the MQ2 sensor");
    delay(60000);  // wait for the MQ2 to warm up
    pinMode(2, OUTPUT);
    digitalWrite(2,HIGH);
    analogReadResolution(12);
    dht.begin();

}

void loop() {
  delay(2000);

  int gasValue = analogRead(AO_GPIN);
  int smokeValue = analogRead(AO_SPIN);
  float h = dht.readHumidity();

  float t = dht.readTemperature();

  if(isnan(h)||isnan(h)){
    Serial.println(F("Failed to read from DHT"));
    return;
    }

    float hic = dht.computeHeatIndex(t,h,false);//false is so the system is knows it's celsius

    Serial.print("\nGas sensor AO value: ");
    Serial.println(gasValue);
    Serial.print("\n Smoke sensor AO value: ");
    Serial.println(smokeValue);
    Serial.print(F("\n Humidity: "));
    Serial.print(h);
    Serial.print(F("%\n Temperature: "));
    Serial.print(t);
    Serial.print(F("C\n "));
    Serial.print(F("Heat Index: "));
    Serial.print(hic);
    Serial.print(F("C\n"));

    if (gasValue>1800|| t>35|| smokeValue>1800){
    digitalWrite(buzzer,HIGH);
  }
  else{
    digitalWrite(buzzer,LOW);
  }
//  delay(1000);
//  digitalWrite(2,HIGH);
//  tone(buzzer, 1000,10);
//  delay(1000);
//  digitalWrite(2,LOW);
}
