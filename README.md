# mmWaveAlarm
Detect human presence behind doors and walls with Telegram Notification - DFRobot SEN0395 and ESP32C

# Parts
ESP32C3 https://www.dfrobot.com/product-2566.html?tracking=61357a929f73e  
MM Wave Radar https://www.dfrobot.com/product-2282.html?tracking=61357a929f73e 

# Brief
Sometimes you need to know what is going on outside your door. Of course you can install a PIR sensor or HCSR04 distance sensor with cables and all but, wouldn't be cool to use an indoor Milimiter Wave Radar sensor instead?

# Circuit
Connect the Wave radar to 3.3v, GND and TX to GPIO5 and RX to GPIO7

# Libraries
#include <DFRobot_mmWave_Radar.h>
#include <UniversalTelegramBot.h>

# Settings

#define BOT_TOKEN ":"
#define WIFI_SSID ""
#define WIFI_PASSWORD ""
String chat_id="";
String test_photo_url = "";
int LED_BLINK = 10;
int howManyMeters=2; // until 9
int loopDelay=1000;
int alarmDelay=10000;
int lastStateWasClear=1;

# Contact
If you need to customize this project or to create a new one for specific electronics you are welcome to contact me 
@RoniBandini 
bandini.medium.com
