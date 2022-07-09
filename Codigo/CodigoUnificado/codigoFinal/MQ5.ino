void setupMQ5() {
  pinMode(MQ5, INPUT);
}

int readMQ5() {
  int gas = analogRead(MQ5);
  int gasPercentage = map(gas, 0, 4095, 0, 100);
  Serial.print(gasPercentage);
  Serial.println("%");
  return gasPercentage;
}
