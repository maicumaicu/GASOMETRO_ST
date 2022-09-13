
#include <WiFi.h>
#include "AsyncMqttClient.h"
#include <Wire.h>
#include "time.h"
#include "Arduino.h"

#define SENSING_TIME 300000

#define BMP180 0
#define MQ7 1
#define MQ5 2
#define TEMT6000 3

#define MQ7_PIN 36
#define MQ5_PIN  39
#define TEMT6000_PIN  35
#define BUZZER_PIN 19

#define SETUP 0
#define SENSING 1
#define PUBLISHING 2
#define DISPLAYING 3

#define MQTT_HOST IPAddress(10, 162, 24, 33)
#define MQTT_PORT 1883
#define MQTT_USERNAME "esp32"
#define MQTT_PASSWORD "mirko15"
#define MQTT_PUB "/esp32/datos_sensores"
#define MQTT_PUB "/esp32/datos_sensores"

bool bmpConfirmation, oledConfirmation;
int sensorsValues [4];
int sensingTimer = 0;
bool emergencyState = false;
int estadoGasometro = SETUP;

const char* ssid = "ORT-IoT";
const char* password = "OrtIOTnew22$";

const char name_device = 17;
int i = 0;

///time
long unsigned int timestamp ;  // hora
const char* ntpServer = "south-america.pool.ntp.org";
const long  gmtOffset_sec = -10800;
const int   daylightOffset_sec = 0;

unsigned long now = millis(); ///valor actual
unsigned long lastMeasure1 = 0; ///variable para contar el tiempo actual
unsigned long lastMeasure2 = 0; ///variable para contar el tiempo actual

const unsigned long interval_envio = 30000;//Intervalo de envio de datos mqtt
const unsigned long interval_leeo =  60000;//Intervalo de lectura de datos y guardado en la cola

int indice_entra = 0;
int indice_saca = 0;
bool flag_vacio = 1;

char mqtt_payload[150] ;

AsyncMqttClient mqttClient;
TimerHandle_t mqttReconnectTimer;
TimerHandle_t wifiReconnectTimer;

typedef struct
{
  long time;
  float T1;///tempe
  float G5;///gas 5
  float G7;// gas 7
  float Presion; //presion
  float luz;
  bool Alarma;
  float ruido;
} estructura ;
/////////////////
const int valor_max_struct = 1000; ///valor vector de struct
estructura datos_struct [valor_max_struct];///Guardo valores hasta que lo pueda enviar
estructura aux2 ;




void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  maquinaGasometro();
}

void loop() {
  // put your main code here, to run repeatedly:
  maquinaGasometro();
}

void maquinaGasometro() {
  switch (estadoGasometro) {
    case SETUP:
      setupTEMT6000();
      setupMQ7();
      setupMQ5();
      setupmqtt();
      readMQ5();
      //Setup de time
      configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
      setupBuzzer();
      bmpConfirmation = setupBMP180();
      oledConfirmation = setupOLED();
      estadoGasometro = SENSING;
      break;
    case SENSING:
      if (bmpConfirmation == true) {
        sensorsValues[BMP180] = readBMP180();
        if(sensorsValues[BMP180] == 69){
          ESP.restart();
        }
      } else {
        
        sensorsValues[BMP180] = -1;
        setupBMP180();
      }
      sensorsValues[MQ7] = readMQ7();
      sensorsValues[MQ5] = readMQ5();
      sensorsValues[TEMT6000] = readTEMT6000();
      emergencyState = emergencyCheck();
      if (sensorsValues[BMP180] != -2) {
        Serial.println(sensorsValues[BMP180]);
        estadoGasometro = PUBLISHING;
        fun_entra(sensorsValues);
      }
      break;
    case PUBLISHING:
      fun_envio_mqtt();
      estadoGasometro = DISPLAYING;
      cDisplay();
      sensingTimer = millis();
      break;
    case DISPLAYING:
      if (oledConfirmation == true) {
        displayData(sensorsValues);
        if (emergencyState == true) {
          runBuzzer();
          //EmergencyState(sensorsValues);
        } else {
          stopBuzzer();
        }
      } else {
        oledConfirmation = setupOLED();
      }

      if (sensingTimer + SENSING_TIME <= millis()  ) {
        estadoGasometro = SENSING;
        Serial.print("cambiando");
      }
      break;
  }
}

bool emergencyCheck() {
  if (sensorsValues[MQ5] >=  10 || sensorsValues[MQ7] >=  10) {
    return true;
  } else {
    return false;
  }
}
