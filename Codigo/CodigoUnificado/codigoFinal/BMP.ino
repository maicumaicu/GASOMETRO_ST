#include <SFE_BMP180.h>
#include <Wire.h>

SFE_BMP180 bmp180;

bool setupBMP180() {
    if (bmp180.begin())
      Serial.println("BMP180 iniciado correctamenten");
      return true;
    else
    {
      Serial.println("Error al iniciar el BMP180");
      return false;
  }
}


int readBMP180() {
  char status;
  double T, P;

  status = bmp180.startTemperature();//Inicio de lectura de temperatura
  if (status != 0)
  {
    delay(status); //Pausa para que finalice la lectura
    status = bmp180.getTemperature(T); //Obtener la temperatura
    if (status != 0)
    {
      status = bmp180.startPressure(3); //Inicio lectura de presión
      if (status != 0)
      {
        delay(status);//Pausa para que finalice la lectura
        status = bmp180.getPressure(P, T); //Obtenemos la presión
        if (status != 0)
        {
          Serial.print("Temperatura: ");
          Serial.print(T, 2);
          Serial.print(" *C , ");
          Serial.print("Presion: ");
          Serial.print(P, 2);
          Serial.println(" mb");
          return T;
        }
      }
    }
  }
}
