#include <TFT_eSPI.h>
#include "segaFont.h"
#include "pixel.h"
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

void setup() {
 
  tft.init();
  tft.setRotation(1);

     sprite.createSprite(320,170); 
     sprite.loadFont(pixel);
     sprite.setTextDatum(4);

     ledcSetup(0, 10000, 8);
     ledcAttachPin(38, 0);
     ledcWrite(0, 100);
}

void draw()
{
  sprite.fillSprite(TFT_BLACK);
  sprite.drawString("VOLOS",160,85);
  sprite.pushSprite(0,0);
}

void loop() {
  draw();
}
