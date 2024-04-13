#include <dht.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

dht DHT;
#define DHT11_PIN 5

void setup(){
 lcd.init();
 lcd.backlight();
 lcd.begin(16,2);
 Serial.begin(9600);
}

void loop()
{
   DHT.read11(DHT11_PIN);
   lcd.setCursor(0, 0);
   lcd.print("Humidity = ");
   lcd.print(DHT.humidity);
   lcd.print("%  ");
   delay(2000);
   lcd.setCursor(0, 1);
   lcd.print("Temp: ");
   lcd.print(DHT.temperature); 
   lcd.print((char)223); // print ° character
   lcd.print("C  ");
   delay(1000);
}