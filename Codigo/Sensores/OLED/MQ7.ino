void setupMQ7() {
  pinMode(MQ7, INPUT);
}

void readMQ7() {
  int gas = analogRead(MQ7);
  int gasPercentage = map(gas, 0, 4095, 0, 100);
  Serial.print(gasPercentage);
  Serial.println("%");
}
