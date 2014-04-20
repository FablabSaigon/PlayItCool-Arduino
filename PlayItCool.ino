#include "DHT.h"
#include <SoftwareSerial.h>

#define DHTPIN 2
//#define DHTTYPE DHT11
#define DHTTYPE DHT22 // DHT 22 (AM2302)

DHT dht(DHTPIN,DHTTYPE);

#define Rx 0
#define Tx 1

SoftwareSerial myBluetooth(Rx, Tx);

unsigned int humidity = 0;
unsigned int temperature = 0;

char data;
char buf[100];

void setup() {
  Serial.begin(9600);
  //Serial.begin(57600);
  dht.begin();
  myBluetooth.begin(9600);
  //myBluetooth.begin(57600);
}

void loop() {
   // read temperature and humidity from sensor
   temperature = dht.readTemperature();
   humidity = dht.readHumidity();
   
   if (isnan(temperature) || isnan(humidity)) {
     Serial.println("Failed to read from DHT");
   }
   
   // Read data from Bluetooth
   if (myBluetooth.available()) {
     data = myBluetooth.read();
     if (data == '1') {
        sprintf(buf, "Temp:%d;Hum:%d;Lat:%s;Long:%s", temperature, humidity, "10.1122333", "20.1122333");
        Serial.println(buf);
        //myBluetooth.print("\r\n");
        myBluetooth.write(buf);
        //myBluetooth.print("\r\n");
     }
   }
}
