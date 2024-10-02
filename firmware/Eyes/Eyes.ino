#include <EEPROM.h>
#include <FastLED.h>

#define NUM_LEDS 256  // в матрице 32х8 количество светодиодов 256
#define DATA_PIN D2   // матрица подключена к пину D2
#define CLOCK_PIN 13

#define GH_INCLUDE_PORTAL
#include <GyverHub.h>
CRGB leds[NUM_LEDS];
GyverHub hub;

static byte brightness = 15;

struct MyColor {
  byte red;
  byte green;
  byte blue;
};
#include "Pictures.h"

gh::Pos pos2;  // обработка кликов по холсту для loop




void build(gh::Builder& b) {

  b.Title_("header1", "Состояние:");
  if (b.beginRow()) {
    if (b.Slider(&brightness).label("Яркость").size(3).click()) {
      Serial.print("Яркость: ");
      Serial.println(brightness);
      hub.sendGet("Brightness", brightness);
      hub.sendStatus("online");
      FastLED.setBrightness(brightness);
    };
  }
  b.endRow();

  b.beginRow();
  gh::Canvas cv1;
  b.BeginCanvas_(F("cv1"), 32, 8, &cv1, &pos2);
  b.EndCanvas();
  b.endRow();

}  // конец билдера






void setup() {
  Serial.begin(115200);

  hub.config(F("MyDevices"), F("Глаза"), F("f2c9"));
  hub.onBuild(build);
  hub.begin();

  Serial.println("Создаю точку доступа!");
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Car-Eyes", "11111111");

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  FastLED.setBrightness(brightness);
  Serial.println("Лента стартовала!");

  draw(sleep, 2000);  // отобразить спящие закрытые глаза на 3 секунды
}






void draw(MyColor arData[], int image_delay) {
  // отрисовка на матрице
  uint32_t end_time = millis() + image_delay;



  for (int i = 0; i <= NUM_LEDS; i++) {
    leds[i].setRGB(arData[i].red, arData[i].green, arData[i].blue);
  }
/*
        Serial.print(  arData[0].red  );
        Serial.print(  "-"  );
        Serial.print(  arData[0].green  );
        Serial.print(  "-"  );
        Serial.println(  arData[0].blue  );
*/
  leds[0].setRGB(0, 0, 0);
  FastLED.show();

  Serial.println(image_delay);


  // Отрисовка на холсте
  if (hub.focused()) {
    gh::CanvasUpdate cv1("cv1", &hub);
    cv1.fill(gh::Color(0, 0, 0, random(100, 150)));
    cv1.background();
    for (int x = 0; x < 30; x++) {
      for (int y = 0; y <= 7; y++) {
        int number = (x * 8);

        if (x % 2 == 0) {
          number += 7 - y;
        } else {
          number += y;
        }

        cv1.fill(gh::Color(arData[number].red, arData[number].green, arData[number].blue));
        cv1.point(x, y);
      }
      //Serial.println();
    }
    cv1.send();
  }


  while (millis() < end_time) {
    hub.tick();
  }
}





void loop() {
  hub.tick();

  draw(middle, 5000);  // отобразить глаза в центре,
  draw(sleep, 250);
  draw(middle, 500);
  draw(sleep, 250);
  draw(middle, 500);

  draw(big, 1000);  // большие удивлённые глаза, 1 секунда

  draw(middle, 500);
  draw(left, 500);
  draw(middle, 500);
  draw(left, 500);
  draw(middle, 2000);

  draw(niz, 1500);  // зрачки вниз, сведены к носу

  draw(left, 500);

  draw(middle, 1500);


  for (int i = 0; i < 7; i++) {
    draw(sleep, 20);
    draw(middle, 100);
  }

  draw(vava1, 1000);
  draw(vava2, 1000);
  draw(vava3, 1000);
  draw(vava4, 1000);

  draw(vava1, 1000);
  draw(vava2, 1000);
  draw(vava3, 1000);
  draw(vava4, 1000);
}
