#include <ESP8266WiFi.h> //masukkan library
#include<BlynkSimpleEsp8266.h>
#include "DHT.h" 
#define BLYNK_PRINT Serial
#define DHTPIN D6 //pin D6
#define DHTTYPE DHT11 //definisi tipe DHT yang digunakan
#define kipas D7
#define BLYNK_AUTH_TOKEN "pPcFET9CvX7AbdFQN-4L8s6efk4M24mI"
WidgetLED indikator_kipas(V8);
DHT dht (DHTPIN, DHTTYPE); //Pengenalan sensor
BlynkTimer timer;

char auth[]= BLYNK_AUTH_TOKEN ;
char ssid[]="Rasya";
char pass[]="lupapassword";

int Tombol,BatasAtas,BatasBawah,Jedah;

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  pinMode(kipas, OUTPUT);
  timer.setInterval(100L, kirim_data);
}

void loop()
{
  Blynk.run();
  timer.run();
}

void kirim_data(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Blynk.virtualWrite(V6,t);
  Blynk.virtualWrite(V7, h);
  Serial.print("Suhu: ");
  Serial.print(t);
  Serial.print("*C ");
  Serial.print("kelembapan: ");
  Serial.print(h);
  Serial.print("% ");
  Serial.print("BatasAtas : ");
  Serial.print(BatasAtas);
  Serial.print(" BatasBawah ");
  Serial.print(BatasBawah);
  Serial.print(" Jeda: ");
  Serial.println(Jedah = BatasAtas-BatasBawah);

  if(t >=BatasAtas || Tombol == 1){
    digitalWrite (kipas,HIGH);
    indikator_kipas.on();
  }
  else if(t <= Jedah & Tombol == 0){
    digitalWrite(kipas, LOW);
    indikator_kipas.off();
  }
}

BLYNK_WRITE(V9){
 Tombol = param.asInt();
 if(Tombol == 0){
  digitalWrite (kipas,LOW);
  indikator_kipas.off();
 }
}

BLYNK_WRITE(V10){
  BatasAtas = param.asInt();
}

BLYNK_WRITE(V11){
  BatasBawah = param.asInt();
}
