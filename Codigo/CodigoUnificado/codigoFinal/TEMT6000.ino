void setupTEMT6000(){
  pinMode(TEMT6000, INPUT); 
}

int ReadTEMT6000(){
  int light_value = analogRead(TEMT6000);
  int light = map(gas, 0, 4095, 0, 100)
  Serial.println(light);
  return light;
}
