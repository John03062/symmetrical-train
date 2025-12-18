#define TX_PIN 8
#define BAUD 9600
#define BIT_US (1000000 / BAUD)

unsigned long counter = 0;

void uartSend(char data) {
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
  Serial.println("UART Waveform Test");
  Serial.println("TX: D8, Data: 'a'");
  Serial.print("Bit Time(us): ");
  Serial.println(BIT_US);

  delay(2000);
}

void loop() {
  counter++;

  Serial.print("Send #");
  Serial.print(counter);
  Serial.println(" : 'a'");

  uartSend('a');
  delay(500);
}
