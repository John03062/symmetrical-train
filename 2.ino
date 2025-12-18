#include <Arduino.h>

const uint32_t UART_BAUD = 9600;
const uint16_t BIT_US = 1000000UL / UART_BAUD;

const uint8_t PB_TX = 0;

#define SET_TX()   (PORTB |=  (1 << PB_TX))
#define CLR_TX()   (PORTB &= ~(1 << PB_TX))

unsigned long seq = 0;
unsigned long tStart = 0;
unsigned long tStop  = 0;

void txByte(uint8_t v) {
  tStart = micros();

  CLR_TX();
  delayMicroseconds(BIT_US);

  for (uint8_t n = 0; n < 8; n++) {
    if (v & (1 << n)) SET_TX();
    else              CLR_TX();
    delayMicroseconds(BIT_US);
  }

  SET_TX();
  delayMicroseconds(BIT_US);

  tStop = micros();
}

void setup() {
  DDRB |= (1 << PB_TX);
  SET_TX();

  Serial.begin(9600);
  delay(2000);
}

void loop() {
  seq++;

  txByte(0x61);

  Serial.print("Frame ");
  Serial.print(seq);
  Serial.print(" : ");
  Serial.print(tStop - tStart);
  Serial.println(" us");

  delay(500);
}
