void setupTEMT6000() {
  pinMode(TEMT6000_PIN , INPUT);
}

int readTEMT6000() {
  int light_value = analogRead(TEMT6000_PIN );
  int light = map(light_value, 0, 4095, 0, 100);
  Serial.print(light);
  Serial.println("%");
  return light;
}
