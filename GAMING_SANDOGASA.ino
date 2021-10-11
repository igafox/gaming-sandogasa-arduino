#include <FastLED.h>
#include <SR04.h>

//LEDテープ
#define LED_LENGTH 60
#define LED_CONTROL_PIN 3
#define DELAY 1

//超音波センサー
#define TRIG_PIN 13
#define ECHO_PIN 12
#define TRIGGER_DISTANCE 10
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);

CRGB leds[LED_LENGTH];

void setup() {
  Serial.begin( 9600);
  FastLED.addLeds<WS2812B, LED_CONTROL_PIN, GRB>(leds, LED_LENGTH);
}

void loop() {

  //赤と緑のグラデーション
  for(int i=0; i<=255; i+=25){
    luminous(i,255-i,0);
    delay(DELAY);
    }

    // 赤と青のグラデーション
   for(int i=0; i<=255; i+=25){
       luminous(255-i,0,i);
       delay(DELAY);
   }

   //緑と青のグラーデション
   for(int i=0; i<=255; i+=25){
       luminous(0,i,255-i);
       delay(DELAY);
   }
}

void luminous(int red, int green, int blue) {
  //センサー距離取得
  int value =sr04.Distance();
  Serial.print(value);
  Serial.println("cm");

  //指定範囲より離れてる場合は、消灯
  if(value > TRIGGER_DISTANCE) {
    for (int thisLED = 0; thisLED < LED_LENGTH; thisLED++) {
    leds[thisLED].r = 0;
    leds[thisLED].g = 0;
    leds[thisLED].b = 0;
    FastLED.show();
    }
    return;
  }

  //発光
  for (int thisLED = 0; thisLED < LED_LENGTH; thisLED++) {
    leds[thisLED].r = red;
    leds[thisLED].g = green;
    leds[thisLED].b = blue;
    FastLED.show();
    }
    Serial.print(red);
    Serial.print(":");
    Serial.print(green);
    Serial.print(":");
    Serial.println(blue);
}
