/*
 * MM Wave Radar alarm
 * Roni Bandini bandini.medium.com @ronibandini
 * May 2023
 * MIT License
 * Parts: DFRobot ESP32-C3, DFRobot SEN0395 MM Wave Radar, 
*/

#include <DFRobot_mmWave_Radar.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define BOT_TOKEN ":"
#define WIFI_SSID ""
#define WIFI_PASSWORD ""
String chat_id="";
String test_photo_url = "https://www.comersus.com/images/mmwavealarm.png";

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
bool Start = false;

HardwareSerial mySerial(1);
DFRobot_mmWave_Radar sensor(&mySerial);

int LED_BLINK = 10;
int howManyMeters=2; // until 9
int loopDelay=100;
int alarmDelay=10000;
int lastStateWasClear=1;

void setup() {
  
  Serial.begin(115200);
  
  mySerial.begin(115200, SERIAL_8N1, 5, 7);  //RX,TX  
  sensor.factoryReset();      
  sensor.DetRangeCfg(0, howManyMeters);   
  sensor.OutputLatency(0, 0); 
  delay(2500);
  
  Serial.println("MMWave Radar Alarm started");
  Serial.println("Roni Bandini, May 2023");
  pinMode(LED_BLINK, OUTPUT);
  
  // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);  
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());
    
}

void loop() {
  int val = sensor.readPresenceDetection();
  
  if (val==1){
    digitalWrite(LED_BLINK, 1);  
    Serial.println("--Person or animal nearby");
    
    if (lastStateWasClear==1){      
      bot.sendPhoto(chat_id, test_photo_url, "Alarm");
      bot.sendMessage(chat_id, "There is someone behind the door - Powered by DFRobot MM Wave sensor");
    }
    
    lastStateWasClear=0;
    delay(alarmDelay);
  }
  else
  {
    Serial.println("All clear");
    digitalWrite(LED_BLINK, 0);  
    lastStateWasClear=1;
    }   
  delay(loopDelay);
}
