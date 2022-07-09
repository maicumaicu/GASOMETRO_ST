void setupTEMT6000(){
  pinMode(TEMT6000, INPUT); 
}

void ReadTEMT6000(){
  int light_value = analogRead(TEMT6000);
  float light = light_value * 0.0976;// percentage calculation
  Serial.println(light);
  return light;
}
