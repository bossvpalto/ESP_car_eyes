#include <EEPROM.h>
#include <FastLED.h>

#define NUM_LEDS 256    // в матрице 32х8 количество светодиодов 256
#define DATA_PIN D2     // матрица подключена к пину D2
#define CLOCK_PIN 13


#define GH_INCLUDE_PORTAL
#include <GyverHub.h>
CRGB leds[NUM_LEDS];
GyverHub hub;



struct MyColor {
  byte red;
  byte green;
  byte blue;
};
#include "Pictures.h"





void build(gh::Builder& b) {

    b.Title_("header1", "Состояние:");

    b.beginRow();
    gh::Canvas cv1;
    b.BeginCanvas(32, 8, &cv1);
    for (int x=1; x<32; x++)
      {
        cv1.point(x , 1);
        cv1.point(x , 8);
      }
    b.EndCanvas();
    b.endRow();


} // конец билдера






void setup() { 
    Serial.begin(115200);

    hub.config(F("MyDevices"), F("Глаза"), F("f2c9"));
    hub.onBuild(build);
    hub.begin();

    Serial.println("Создаю точку доступа!"); 
    WiFi.mode(WIFI_AP);
    WiFi.softAP("Car-Eyes","11111111");  

    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
    FastLED.setBrightness(25);
    Serial.println("Лента стартовала!");

    draw ( sleep , 2000); // отобразить спящие закрытые глаза на 3 секунды


}



void draw( MyColor arData[] , int image_delay )
  {
        uint32_t end_time = millis() + image_delay ;
        for(int i=0; i<NUM_LEDS;i++)
          {
              leds[i].setRGB( arData[i].red , arData[i].green , arData[i].blue );
          }
        FastLED.show();

        while ( millis() < end_time )
            {
                  hub.tick();                  
            }
  }



void loop() { 
  hub.tick();

  draw ( middle , 5000 ); // отобразить глаза в центре, 
  draw ( sleep  , 250);
  draw ( middle , 500 );
  draw ( sleep  , 250);
  draw ( middle , 500);

  draw ( big    , 1000);  // большие удивлённые глаза, 1 секунда

  draw ( middle , 500);
  draw ( left   , 500);
  draw ( middle , 500);
  draw ( left   , 500);
  draw ( middle , 2000);

  draw ( niz    , 1500);  // зрачки вниз, сведены к носу

  draw ( left , 500);

  draw ( middle , 1500);


  for(int i=0; i<7;i++)
    {
        draw ( sleep , 20);
        draw ( middle , 100);
    }

  draw ( vava1 , 1000);
  draw ( vava2 , 1000);
  draw ( vava3 , 1000 );
  draw ( vava4 , 1000 );

  draw ( vava1 , 1000);
  draw ( vava2 , 1000);
  draw ( vava3 , 1000 );
  draw ( vava4 , 1000 );

}
