#include <FastLED.h>
#include <DS1302.h> //часы

#define LED_PIN     6 //пин подключения ленты
#define COLOR_ORDER GRB //последовательность цветов (можно откалибровать, заполнив, например, зеленым и переставляя буквы до получения зеленого цвета) GRB is correct?
#define CHIPSET     WS2812 //модель светодиодов
#define NUM_LEDS    120 //количество светодиодов в ленте
#define BASIC_BRIGHTNESS 105 // базовая яркость, рекомендую от 50 до 150, если хотите чтоб лента не перегревалась и бегаюшая "волна" была заметной

#define FRAMES_PER_SECOND 30 //скорость обновления кадров

#define RED_COL 0
#define GREEN_COL 100
#define YELLOW_COL 64
#define BLUE_COL 160
//выше обьявление цветов в формате HSV (значение H) https://alloyui.com/examples/color-picker/hsv

CRGB leds[NUM_LEDS];


DS1302 rtc(8, 9, 10); // (RST , DAT, CLK)

//настройки режима работы часов
//  rtc.halt(false);
//  rtc.writeProtect(true);

//Установка времени на часах, раскомментировать для установки и установить rtc.writeProtect(false);
//  rtc.setDOW(SUNDAY);        // День недели
//  rtc.setTime(15, 54, 30);     // Часы, минуты, секунды
//  rtc.setDate(23, 12, 2018);   // Число, Месяц, Год

int  BRIGHTNESS = BASIC_BRIGHTNESS;
int  BRIGHTNESS50 = BRIGHTNESS + 10;
int  BRIGHTNESS100 = BRIGHTNESS + 20;
int  BRIGHTNESS150 = BRIGHTNESS + 30;

int actualColor = GREEN_COL;
int  actualTime = 15;

void setup() {
  delay(10000); // sanity delay
  //настройки режима работы часов
  rtc.halt(false);
  rtc.writeProtect(true);

  //Установка времени на часах, раскомментировать для установки и установить rtc.writeProtect(false);
  //  rtc.setDOW(SUNDAY);        // День недели
  //  rtc.setTime(15, 54, 30);     // Часы, минуты, секунды
  //  rtc.setDate(23, 12, 2018);   // Число, Месяц, Год

  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );
  FastLED.setMaxPowerInVoltsAndMilliamps(5,2000); 

//Serial.begin(9600);

}

void loop()
{

  for (int i=0,d=1;i<(NUM_LEDS+1);i=i+d) {
    if (i<(NUM_LEDS-9))  {
      leds[i+9] = CHSV(actualColor , 255, BRIGHTNESS);
    }
    if (i<(NUM_LEDS-6)) {
      leds[i+6] = CHSV(actualColor , 200, BRIGHTNESS50);
    }
    if (i<(NUM_LEDS-3)) {
      leds[i+3] = CHSV(actualColor , 170, BRIGHTNESS100);
    }

      leds[i] = CHSV(actualColor , 100, BRIGHTNESS150);

    if (i>2) {
      leds[i-3] = CHSV(actualColor , 170, BRIGHTNESS100);
    }
    if (i>5) {
      leds[i-6] = CHSV(actualColor , 200, BRIGHTNESS50);
    }
    if (i>8) {
      leds[i-9] = CHSV(actualColor , 255, BRIGHTNESS);
    }
    if (i==NUM_LEDS) {
      d=-1;
    }
    if (i==0) {
      d=1;
    }
    

    
    FastLED.show();
    FastLED.delay(2000 / FRAMES_PER_SECOND);

//    Serial.print("TIME:");
//    Serial.println(rtc.getTime().hour);
//    Serial.print("Color:");
//    Serial.println(actualColor);
//    Serial.print("Brightness:");
//    Serial.println(BRIGHTNESS);
//    FastLED.delay(1000);

  
   if (actualTime != rtc.getTime().hour) {
//    Serial.println("Смена цвета");
//    Serial.println(actualColor);
    actualTime = rtc.getTime().hour;
    switch (actualTime) {
      case 0:
        actualColor = RED_COL;
        BRIGHTNESS = BASIC_BRIGHTNESS - 30;
        BRIGHTNESS50 = BRIGHTNESS + 10;
        BRIGHTNESS100 = BRIGHTNESS + 20;
        BRIGHTNESS150 = BRIGHTNESS + 30;
         break;
      case 1:
        BRIGHTNESS = BASIC_BRIGHTNESS - 60;
        BRIGHTNESS50 = BRIGHTNESS + 10;
        BRIGHTNESS100 = BRIGHTNESS + 20;
        BRIGHTNESS150 = BRIGHTNESS + 30;
        break;
      case 8:
        actualColor = BLUE_COL;
        BRIGHTNESS = BASIC_BRIGHTNESS;
        BRIGHTNESS50 = BRIGHTNESS + 10;
        BRIGHTNESS100 = BRIGHTNESS + 20;
        BRIGHTNESS150 = BRIGHTNESS + 30;
        break;
      case 10:
        actualColor = GREEN_COL;
        break;
      case 11:
        BRIGHTNESS = 0;
        BRIGHTNESS50 = BRIGHTNESS + 10;
        BRIGHTNESS100 = BRIGHTNESS + 20;
        BRIGHTNESS150 = BRIGHTNESS + 30;
        break;
      case 21:
        BRIGHTNESS = BASIC_BRIGHTNESS;
        BRIGHTNESS50 = BRIGHTNESS + 10;
        BRIGHTNESS100 = BRIGHTNESS + 20;
        BRIGHTNESS150 = BRIGHTNESS + 30;
        break;
      case 23:
        actualColor = YELLOW_COL;
        break;
      default:
        break;
      } // закрываем switch
      
   } //закрываем if

  } //закрываем for

    

 
} // закрываем loop
