#include <Config.h>
#include <EasyBuzzer.h>
void setupBuzzer() {
  EasyBuzzer.setPin(19);
  Serial.println("Comienza el sonido");
  
  // Configuración del beep
  
}
 
void runBuzzer() {
  // Función para que funcione la librería
  EasyBuzzer.beep(
    5000,          // Frecuencia en herzios
    100,           // Duración beep en ms
    100,           // Duración silencio en ms
    2,             // Números de beeps por ciclos
    100,           // Duración de la pausa
    5         // Número de ciclos
  );
  EasyBuzzer.update();
}

 
void stopBuzzer() {
  // Función para que funcione la librería
  EasyBuzzer.stopBeep();
}
