void setupMQ7() {
  pinMode(MQ7_PIN , INPUT);
}

int readMQ7() {
  int gas = analogRead(MQ7_PIN );
  int gasPercentage = map(gas, 0, 4095, 0, 100);
  Serial.print(gasPercentage);
  Serial.println("%");
  return gasPercentage;
}
