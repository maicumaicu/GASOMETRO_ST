
#define SENSING_TIME 60000

#define BMP180 0
#define MQ7 1
#define MQ5 2
#define TEMT6000 3

#define SETUP 0
#define SENSING 1
#define PUBLISHING 2
#define DISPLAYING 3

bool bmpConfirmation, oledConfirmation;
int sensorsValues [4];
int sensingTimer = 0;
bool emergencyState = false;
int estadoGasometro = SETUP;


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
      setupBuzzer();
      bmpConfirmation = setupBMP180();
      oledConfirmation = setupOLED();
      estadoGasometro = SENSING;
      break;
    case SENSING:
      if (bmpConfirmation == true) {
        sensorsValues[BMP180] = readBMP180();
      } else {
        sensorsValues[BMP180] = -1;
        setupBMP180();
      }
      sensorsValues[MQ7] = readMQ7();
      sensorsValues[MQ5] = readMQ5();
      sensorsValues[TEMT6000] = readTEMT6000();
      emergencyState = emergencyCheck();
      estadoGasometro = DISPLAYING;
      sensingTimer = millis();
      break;
    case PUBLISHING:
      break;
    case DISPLAYING:

      if (oledConfirmation = true) {
        if (emergencyState == true) {
          setBuzzer();
          emergencyState();
        } else {
          displayData();
        }
      } else {
        oledConfirmation = setupOLED();
      }

      if (sensingTimer <= millis + SENSING_TIME ) {
        estadoGasometro = SENSING;
      }
      break;
  }
}

bool emergencyCheck() {
  if (sensorsValues[MQ7] >=  80 || sensorsValues[MQ7] >=  80) {
    return true;
  } else {
    return false;
  }
}
