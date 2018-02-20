#include <Adafruit_NeoPixel.h>
#include "WS2812_Definitions.h"
//WRITE WITH TWO BUTTONS
#define PIN 4
#define LED_COUNT 51
Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);
int buttonPin = 7;
int oldButtonVal = 0;
int nPatterns = 4;
int lightPattern = 1;
int i = 0;
void setup()
{
  // put your setup code here, to run once:
  leds.begin();
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin (115200);
}

void loop()
{
  int buttonVal;
  for (int waiting = 0; waiting < 100; waiting++)
  {
    buttonVal = digitalRead(buttonPin);
    if (buttonVal == LOW && oldButtonVal == HIGH)
    {
      lightPattern = lightPattern + 1;
      Serial.println("Light");
      Serial.print (lightPattern, DEC);
    }

    oldButtonVal = buttonVal;
    if (lightPattern > nPatterns)
    {
      lightPattern = 1;
    }
    delay (1);
  }
  switch (lightPattern)
  {
    case 1:
      rotate (BLUE, PURPLE, 4);
      break;
    case 2:
      rotate (BLUE, PURPLE, 10);
      i = i - 1;
      break;
    case 3:
      for (int a = 36; a < 78; a++)
      {
        leds.setPixelColor(a, BLUE);
      }
      leds.show();
      break;
    case 4:
      for (int a = 36; a < 78; a++)
      {
        leds.setPixelColor(a, BLUE);
      }
      leds.show();
      break;
    case 5:
      for (int a = 36; a < 78; a++)
      {
        leds.setPixelColor(a, BLUE);
      }
      leds.show();
      break;
    case 6:
      rainbow(i);
      i = i +1;
      break;
  }
}

void rotate (unsigned long colora, unsigned long colorb, byte longshort)
{
  for (int j = i; j < LED_COUNT; j = j + (longshort * 2))
  {
    for (int k = 0; k < longshort; k++)
    {
      leds.setPixelColor(j + k, colora);
    }
    for (int m = longshort; m < longshort * 2; m++)
    {
      leds.setPixelColor(j + m, colorb);
    }
  }
  for (int n = i; n > 0; n = n - longshort * 2)
  {
    for (int k = 0; k < longshort; k++)
    {
      leds.setPixelColor(n - k - 1, colorb);
    }
    for (int m = longshort; m < longshort * 2; m++)
    {
      leds.setPixelColor(n - m - 1, colora);
    }
  }
  leds.show();
}

void rainbow(byte startPosition)
{
  // Need to scale our rainbow. We want a variety of colors, even if there
  // are just 10 or so pixels.
  int rainbowScale = 192 / LED_COUNT;

  // Next we setup each pixel with the right color
  for (int i = 0; i < LED_COUNT; i++)
  {
    // There are 192 total colors we can get out of the rainbowOrder function.
    // It'll return a color between red->orange->green->...->violet for 0-191.
    leds.setPixelColor(i, rainbowOrder((rainbowScale * (i + startPosition)) % 192));
  }
  // Finally, actually turn the LEDs on:
  leds.show();
}

// Input a value 0 to 191 to get a color value.
// The colors are a transition red->yellow->green->aqua->blue->fuchsia->red...
//  Adapted from Wheel function in the Adafruit_NeoPixel library example sketch
uint32_t rainbowOrder(byte position)
{
  // 6 total zones of color change:
  if (position < 31)  // Red -> Yellow (Red = FF, blue = 0, green goes 00-FF)
  {
    return leds.Color(0xFF, position * 8, 0);
  }
  else if (position < 63)  // Yellow -> Green (Green = FF, blue = 0, red goes FF->00)
  {
    position -= 31;
    return leds.Color(0xFF - position * 8, 0xFF, 0);
  }
  else if (position < 95)  // Green->Aqua (Green = FF, red = 0, blue goes 00->FF)
  {
    position -= 63;
    return leds.Color(0, 0xFF, position * 8);
  }
  else if (position < 127)  // Aqua->Blue (Blue = FF, red = 0, green goes FF->00)
  {
    position -= 95;
    return leds.Color(0, 0xFF - position * 8, 0xFF);
  }
  else if (position < 159)  // Blue->Fuchsia (Blue = FF, green = 0, red goes 00->FF)
  {
    position -= 127;
    return leds.Color(position * 8, 0, 0xFF);
  }
  else  //160 <position< 191   Fuchsia->Red (Red = FF, green = 0, blue goes FF->00)
  {
    position -= 159;
    return leds.Color(0xFF, 0x00, 0xFF - position * 8);
  }
}
