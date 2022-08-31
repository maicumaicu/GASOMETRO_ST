#include <SFE_BMP180.h>
#include <Wire.h>

#define STARTING 0
#define READING 1
#define SENDING 2

SFE_BMP180 bmp180;
int readingState;
int BMPTimer;


bool setupBMP180() {
  if (bmp180.begin()) {
    Serial.println("BMP180 iniciado correctamenten");
    return true;
  }
  else
  {
    Serial.println("Error al iniciar el BMP180");
    return false;
  }
}


int readBMP180() {
  char status;
  double T, P;

  switch (readingState) {
    case STARTING:
      status = bmp180.startTemperature();
      if (status != 0) {
        BMPTimer = millis();
        readingState = READING;
      }
      return -2;
      break;
    case READING:
      if (BMPTimer < millis() + status) {
        status = bmp180.getTemperature(T);
        if (status != 0) {
          return T;
        }
      }
      return -2;
      break;
  }
}
