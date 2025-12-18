#include <Arduino.h>

const uint8_t SW_TX_BIT = 0;
const uint32_t BAUD = 9600;
const uint16_t BIT_US = 1000000UL / BAUD;

#define SW_TX_ON()   (PORTB |=  (1 << SW_TX_BIT))
#define SW_TX_OFF()  (PORTB &= ~(1 << SW_TX_BIT))

void swTransmit(uint8_t d) {
  SW_TX_OFF();
  delayMicroseconds(BIT_US);

  for (uint8_t i = 0; i < 8; i++) {
    if (d & (1 << i)) SW_TX_ON();
    else              SW_TX_OFF();
    delayMicroseconds(BIT_US);
  }

  SW_TX_ON();
  delayMicroseconds(BIT_US);
}

void setup() {
  DDRB |= (1 << SW_TX_BIT);
  SW_TX_ON();

  Serial.begin(9600);
  delay(2000);
}

void loop() {
      Serial.write(0x61);
  swTransmit(0x61);

  delay(2000);
}
