/*
    Розробив Roman
    Канал на YouTube: https://goo.gl/x8FL2o
    Відео з проектом: 
    Спроба подружити ESP8266 з MRF49XA. 
    За основу було взято схему піротехнічного пульта на 31 команду з цієї статі: https://goo.gl/GNG4hi
    Деякі компоненти WEB-інтерфейс було взято звідси: https://github.com/tretyakovsa/Sonoff_WiFi_switch 
    2018 Roman
*/


#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266WebServer.h>   
#include <ESP8266WiFi.h> 
#include <ESP8266SSDP.h>     
#include <ArduinoJson.h>  // Ставимо через менеджер бібліотек
#include <QueueList.h>    // https://playground.arduino.cc/Code/QueueList
#include <time.h>  
#include <SPI.h>   
#include <FS.h> 

//--------------------------------------------------------------------
// MRF49XA SPI commands:
//--------------------------------------------------------------------
#define    CREG                  0x801F         
#define    FSREG                 0xAE10         
#define    TCREG                 0x98F0
#define    AFCREG                0xC400        
#define    PMREG0                0x8239         
#define    PMREG1                0x8201         
//--------------------------------------------------------------------
//  FSK/DATA/FSEL:
//--------------------------------------------------------------------
#define    DATA                  5
#define    PERIOD                170
//--------------------------------------------------------------------
//  Default data:
//--------------------------------------------------------------------
// Об'єкт для оновлення web сторінки
ESP8266HTTPUpdateServer httpUpdater;
// Web інтерфейс для пристрою
ESP8266WebServer HTTP(80);
// Для файлової системи
File fsUploadFile;

String configSetup = "{}";
String configJson = "{}";

byte DataABCDEiD[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0xFF};

QueueList <byte> bytesQueue;
byte FlagQueue = 0x00;
uint32_t timeQueue = 0;
uint8_t countQueue = 0;

void setup() {
  Serial.begin(115200);
  delay(5);
  Serial.println("");
  Serial.println("Start FS");
  FS_init();
  Serial.println("Step FileConfig");
  configSetup = readFile("config.json", 4096);
  jsonWrite(configJson, "SSDP", jsonRead(configSetup, "SSDP"));
  Serial.println(configSetup);
  Serial.println("Start WIFI");
  WIFIinit();
  Serial.println("Start Time");
  Time_init();
  Serial.println("Start SSDP");
  SSDP_init();
  Serial.println("Start WebServer");
  HTTP_init();
  LANG_init();
  BUTTONS_init();
  MRF49XA_init();
  Serial.println("");
  Serial.println("Time Ready!");
  Serial.println(GetTime());
  Serial.println(GetDate());
}

void loop() {
 HTTP.handleClient();
 QueueListener();
 if (FlagQueue != 0x02) delay(1);
}









