#include "superman.h"
#include "font.h"
#include "font2.h"
#include "rm67162.h"
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

long lastMillis;
int fps=0;

#define up 21
#define down 0
#define led 38
bool deb = 0;
bool deb2 = 0;
byte bright = 5;
byte brightness[7] = {100, 120, 140, 180, 200, 230, 254 };
bool ledON = false;

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  5 
int n;

void setup()
{  
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  rm67162_init();  // amoled lcd initialization
  lcd_setRotation(1);
  sprite.createSprite(536, 240);
  sprite.setSwapBytes(1);
 
  lcd_brightness(140);
}

void draw()
{
  sprite.setTextColor(TFT_BLACK);
 sprite.fillSprite(0xBEFF);
  sprite.loadFont(font70);
 sprite.drawString("Days until",60,16,4);
 sprite.drawString("BIRTHDAY!",60,180,4);
 sprite.unloadFont();
 

   sprite.loadFont(font100);
 sprite.drawString("0257",60,82,4);
 sprite.unloadFont();

 sprite.pushImage(324,20,184,200,superman[n]);
 
 lcd_PushColors(0, 0, 536, 240, (uint16_t*)sprite.getPointer());
}

 void readButtons(){
  if (digitalRead(up) == 0) {
    if (deb == 0) {
      deb = 1;
      bright++;
      if (bright == 7) bright = 0;
      lcd_brightness(brightness[bright]);
    }
  } else deb = 0;

  if (digitalRead(down) == 0) {
    if (deb2 == 0) {
      deb2 = 1;
      ledON = !ledON;
      digitalWrite(led, ledON);
    }
  } else deb2 = 0;
}

void loop()
{
   readButtons();
   fps=1000/(millis()-lastMillis);
   lastMillis=millis();
   draw();
   
   n++;
   if(n==29) n=0;
   
}