const uint8_t TX_PIN = 8;
const uint32_t BAUD = 9600;
const uint16_t BIT_US = 1000000UL / BAUD;

unsigned long count = 0;

void sendByte(uint8_t data) {
  digitalWrite(TX_PIN, LOW);
  delayMicroseconds(BIT_US);

  for (uint8_t i = 0; i < 8; i++) {
    digitalWrite(TX_PIN, (data >> i) & 0x01);
    delayMicroseconds(BIT_US);
  }

  digitalWrite(TX_PIN, HIGH);
  delayMicroseconds(BIT_US);
}

void setup() {
  pinMode(TX_PIN, OUTPUT);
  digitalWrite(TX_PIN, HIGH);

  Serial.begin(9600);
  delay(2000);
}

void loop() {
  count++;
  sendByte(0x61);
  delay(500);
}
