#include <Adafruit_NeoPixel.h>
#include "WS2812_Definitions.h"
// Choose which pin the LED signal line is attached to
#define PIN 4
// Choose which pin the mode toggle button is attached to
#define BUTTON_PIN 7
// Count the number of total LEDs in the strand and put that number here
// Number 0 LED Count
#define LED_COUNT 50
// Number 1 LED Count
// #define LED_COUNT 16
// Number 3 LED Count
// #define LED_COUNT 43
// Number 8 LED Count
// #define LED_COUNT 54

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);
// Store the value of the button from the previous loop iteration
int oldButtonVal = 1;
// Defines the number of cases for light patterns
int nPatterns = 5;
// Defines the default pattern
int lightPattern = 1;
int i = 0;

void setup()
{
  // put your setup code here, to run once:
  leds.begin();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin (115200);
}

void loop()
{
  // Current value of the button
  int buttonVal;

  for (int waiting = 0; waiting < 100; waiting++)
  {
    buttonVal = digitalRead(BUTTON_PIN);
    if (buttonVal == LOW && oldButtonVal == HIGH)
    {
      lightPattern += 1;
      if (lightPattern > nPatterns)
      {
        lightPattern = 1;
      }
      Serial.println("Light");
      Serial.println(lightPattern, DEC);
    }

    oldButtonVal = buttonVal;
    delay(1);
  }
  switch (lightPattern)
  {
    case 1:
      // Insert colors based on the attached "WS2812_definitions.h"
      // Rotate takes 2 colors followed by segment length
      rotate(BLUE, PURPLE, 4);
      // This defines the direction of the rotation
      // Without this line it will not rotate
      i = i + 1;
      break;
    case 2:
      for (int a = 0; a < LED_COUNT; a++)
      {
        leds.setPixelColor(a, RED);
      }
      // If you do a solid color, you must call leds.show()
      leds.show();
      break;
    case 3:
      for (int a = 0; a < LED_COUNT; a++)
      {
        leds.setPixelColor(a, BLUE);
      }
      leds.show();
      break;
    case 4:
      for (int a = 0; a < LED_COUNT; a++)
      {
        leds.setPixelColor(a, PURPLE);
      }
      leds.show();
      break;
    case 5:
      rainbow(i);
      i = i + 1;
      break;
  }
}
// You should not need to modify any code below this line----------------
void rotate (unsigned long colora, unsigned long colorb, byte longshort)
{
  for (int j = i; j < LED_COUNT; j = j + longshort * 2)
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
