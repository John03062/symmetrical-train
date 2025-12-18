#include <Arduino.h>

static const uint8_t TXB = 0;
static const uint32_t UART_BAUD = 9600;
static const uint16_t TBIT = 1000000UL / UART_BAUD;

#define PIN_HIGH()  (PORTB |=  (1 << TXB))
#define PIN_LOW()   (PORTB &= ~(1 << TXB))

unsigned long cycles = 0;
unsigned long passCnt = 0;
unsigned long errCnt  = 0;

void softTx(uint8_t b) {
  PIN_LOW();
  delayMicroseconds(TBIT);

  uint8_t mask = 0x01;
  while (mask) {
    if (b & mask) PIN_HIGH();
    else          PIN_LOW();
    delayMicroseconds(TBIT);
    mask <<= 1;
  }

  PIN_HIGH();
  delayMicroseconds(TBIT);
}

void setup() {
  DDRB |= _BV(TXB);
  PIN_HIGH();

  Serial.begin(UART_BAUD);
  delay(2000);
}

void loop() {
  uint8_t value = 0x61;
  cycles++;

  Serial.print("#");
  Serial.print(cycles);
  Serial.print(" TX=");
  Serial.print(value, HEX);
  Serial.print(" RX=");

  softTx(value);
  delay(50);

  if (Serial.available() > 0) {
    uint8_t r = Serial.read();
    Serial.print(r, HEX);

    if (r == value) {
      passCnt++;
      Serial.println(" PASS");
    } else {
      errCnt++;
      Serial.println(" FAIL");
    }
  } else {
    errCnt++;
    Serial.println("--");
  }

  if ((cycles % 10) == 0) {
    Serial.print("CNT=");
    Serial.print(cycles);
    Serial.print(" OK=");
    Serial.print(passCnt);
    Serial.print(" NG=");
    Serial.println(errCnt);
  }

  delay(1000);
}

