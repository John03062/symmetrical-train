#include <Arduino.h>

const uint8_t SW_TX = 0;
const uint32_t BAUD = 9600;
const uint16_t BIT_US = 1000000UL / BAUD;

#define TX_ON()   (PORTB |=  (1 << SW_TX))
#define TX_OFF()  (PORTB &= ~(1 << SW_TX))

unsigned long total = 0;
unsigned long ok = 0;
unsigned long fail = 0;

void swSend(uint8_t v) {
  TX_OFF();
  delayMicroseconds(BIT_US);

  for (uint8_t i = 0; i < 8; i++) {
    if (v & (1 << i)) TX_ON();
    else              TX_OFF();
    delayMicroseconds(BIT_US);
  }

  TX_ON();
  delayMicroseconds(BIT_US);
}

void setup() {
  DDRB |= (1 << SW_TX);
  TX_ON();

  Serial.begin(9600);
  delay(2000);
}

void loop() {
  total++;
  uint8_t tx = 0x61;

  Serial.print("[");
  Serial.print(total);
  Serial.print("] TX ");
  Serial.print(tx, HEX);
  Serial.print(" -> ");

  swSend(tx);
  delay(50);

  if (Serial.available()) {
    uint8_t rx = Serial.read();
    Serial.print(rx, HEX);

    if (rx == tx) {
      ok++;
      Serial.println(" OK");
    } else {
      fail++;
      Serial.println(" ERR");
    }
  } else {
    fail++;
    Serial.println(" NO DATA");
  }

  if (total % 10 == 0) {
    Serial.print("TOTAL=");
    Serial.print(total);
    Serial.print(" OK=");
    Serial.print(ok);
    Serial.print(" FAIL=");
    Serial.println(fail);
  }

  delay(1000);
}
