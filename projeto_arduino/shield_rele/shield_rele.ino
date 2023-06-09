const int shield_rele = 7;

void setup() {
  pinMode(shield_rele, OUTPUT);

}

void loop() {
  digitalWrite(shield_rele, HIGH);
  delay(5000);
  digitalWrite(shield_rele, LOW);
  delay(5000);

}
