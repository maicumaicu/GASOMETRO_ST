#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_D1   23
#define OLED_D0    18
#define OLED_DC     16
#define OLED_CS     5
#define OLED_RESET  17

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_D1, OLED_D0, OLED_DC, OLED_RESET, OLED_CS);


bool setupOLED()
{
  if (!display.begin(SSD1306_SWITCHCAPVCC))
  {
    Serial.println(F("SSD1306 allocation failed"));
    return false;
  }
  Serial.println(F("correcto"));
  display.clearDisplay();
  display.display();
  return true;
}

/*void emergencyState(int* values) {

  }*/
  void cDisplay(){
    display.clearDisplay();
  }
  

void displayData(int *values) {
  DisplayBMP180(values[BMP180]);
  DisplayMQ7(values[MQ7]);
  DisplayMQ5(values[MQ5]);
  DisplayTEMT6000(values[TEMT6000]);
}

void DisplayBMP180(int value) {
  //display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(1, 28);
  display.print("BMP: ");
  if (value == -1) {
    display.println("No disponible");
  } else {
    display.println(value);
  }
  display.display();
}

void DisplayMQ5(int value) {
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  //display.setCursor(6, 28);
  display.print("MQ5: ");
  display.println(value);
  display.display();
}

void DisplayMQ7(int value) {
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  //display.setCursor(7, 28);
  display.print("MQ7: ");
  display.println(value);
  display.display();
}

void DisplayTEMT6000(int value) {
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  //display.setCursor(8, 28);
  display.print("TEMT: ");
  display.println(value);
  display.display();
}

/*void AllPixels()
  {
  int i;
  int j;
  display.clearDisplay();
  for (i = 0; i < 64; i++)
  {
    for (j = 0; j < 128; j++)
    {
      display.drawPixel(j, i, SSD1306_WHITE);

    }
    display.display();
    delay(30);
  }

  for (i = 0; i < 64; i++)
  {
    for (j = 0; j < 128; j++)
    {
      display.drawPixel(j, i, SSD1306_BLACK);

    }
    display.display();
    delay(30);
  }

  }

  void TextDisplay()
  {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5, 28);
  display.println("Electronics Hub");
  display.display();
  delay(3000);
  }

  void InvertedTextDisplay()
  {
  display.clearDisplay();
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  display.setCursor(5, 28);
  display.println("Electronics Hub");
  display.display();
  delay(3000);
  }

  void ScrollText()
  {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println("This is a");
  display.println("Scrolling");
  display.println("Text!");
  display.display();
  delay(100);
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  //display.stopscroll();
  //delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  //display.stopscroll();
  //delay(1000);
  display.startscrolldiagright(0x00, 0x0F);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  }

  void DisplayChars()
  {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.cp437(true);

  for (int16_t i = 0; i < 256; i++)
  {
    if (i == '\n')
    {
      display.write(' ');
    }
    else
    {
      display.write(i);
    }
  }

  display.display();
  delay(4000);
  }
  void TextSize()
  {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Size: 1"));
  display.println(F("ABC"));

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.println("Size: 2");
  display.println(F("ABC"));

  display.display();
  delay(3000);
  }

  void DrawRectangle()
  {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Rectangle");
  display.drawRect(0, 15, 90, 45, SSD1306_WHITE);
  display.display();
  delay(2000);
  }

  void DrawFilledRectangle()
  {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Filled Rectangle");
  display.fillRect(0, 15, 90, 45, SSD1306_WHITE);
  display.display();
  delay(2000);

  }

  void DrawRoundRectangle()
  {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Round Rectangle");
  display.drawRoundRect(0, 15, 90, 45, 10, SSD1306_WHITE);
  display.display();
  delay(2000);
  }

  void DrawFilledRoundRectangle()
  {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Filled Round Rect");
  display.fillRoundRect(0, 15, 90, 45, 10, SSD1306_WHITE);
  display.display();
  delay(2000);

  }

  void DrawCircle()
  {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Circle");
  display.drawCircle(30, 36, 25, SSD1306_WHITE);
  display.display();
  delay(2000);
  }
  void DrawFilledCircle()
  {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Filled Circle");
  display.fillCircle(30, 36, 25, SSD1306_WHITE);
  display.display();
  delay(2000);

  }

  void DrawTriangle()
  {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Triangle");
  display.drawTriangle(30, 15, 0, 60, 60, 60, SSD1306_WHITE);
  display.display();
  delay(2000);
  }

  void DrawFilledTriangle()
  {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Filled Triangle");
  display.fillTriangle(30, 15, 0, 60, 60, 60, SSD1306_WHITE);
  display.display();
  delay(2000);
  }
*/
