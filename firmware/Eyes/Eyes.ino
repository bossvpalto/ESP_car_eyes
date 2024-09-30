#include <FastLED.h>


#define NUM_LEDS 256    // в матрице 32х8 количество светодиодов 256

#define DATA_PIN D2     // матрица подключена к пину D2
#define CLOCK_PIN 13

CRGB leds[NUM_LEDS];


struct MyColor {
  byte red;
  byte green;
  byte blue;
};

#include "Pictures.h"




void setup() { 
    Serial.begin(115200);
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
    FastLED.setBrightness(25);
    Serial.println("Лента стартовала!");

    draw ( sleep , 3000); // отобразить спящие закрытые глаза на 3 секунды


}



void draw( MyColor arData[] , int image_delay )
  {
          for(int i=0; i<NUM_LEDS-1;i++)
            {
                leds[i].setRGB( arData[i].red , arData[i].green , arData[i].blue );
                Serial.println(i);
            }
          FastLED.show();
          delay( image_delay );
  }



void loop() { 


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
