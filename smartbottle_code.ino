#include<DHT.h>
DHT dht(D5,DHT11);
int trig=D3;
int echo=D4;
int buzzer=D8;
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include<ESP8266WiFi.h>
#include<WiFiClientSecure.h>
#include<UniversalTelegramBot.h>
#include<Arduinojson.h>
const char* ssid="Madhu.";
const char* password="123456789";

#define BotToken "6504515570:AAH7z1Q5Anoc1m_lQqwgJR7SVT72w7Lnvws"
#define Chatid "6264454925"

WiFiClientSecure client;
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
UniversalTelegramBot bot(BotToken,client);


void setup() {
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
    dht.begin();
  Serial.begin(9600);
  pinMode(buzzer,OUTPUT);
  lcd.init();
  lcd.backlight(); 
  configTime(0,0,"pool.ntp.org");
  client.setTrustAnchors(&cert);
  WiFi.mode(WIFI_STA);
  delay(1000);
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }
  Serial.println("WIFI CONNECTED");
}

void loop() {
  
 digitalWrite(trig,0);
 delayMicroseconds(2);
 digitalWrite(trig,1);
 delayMicroseconds(10);
 digitalWrite(trig,0);
 float duration=pulseIn(echo,1);
 duration=duration/2;
 float distance=(0.034)*duration;
 Serial.println("Level");
 Serial.println(distance);


 float h=dht.readHumidity();
 float t=dht.readTemperature();
 if(isnan(h) || isnan(t))
    { return;}
 Serial.println("Humidity:");
 Serial.println(h);
 lcd.setCursor(0,0);
 lcd.println("Humidity");
 lcd.println(h);
 
 Serial.println(",Temperature:");
 Serial.println(t);
 lcd.setCursor(0,1);
 lcd.println("Temperature");
 lcd.println(t);

 digitalWrite(buzzer,1);

    bot.sendMessage(Chatid,"you are not on track");
 delay(4000);
 digitalWrite(buzzer,0);
 
    bot.sendMessage(Chatid,"You are on the track");
 
 delay(20000);

 


}
