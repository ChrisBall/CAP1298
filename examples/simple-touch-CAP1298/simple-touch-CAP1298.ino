#include <CAP1298.h>

CAP1298 touchSensor;

void setup() {
  Serial.begin(115200);
  touchSensor.begin();
}

void loop() {
  //printBits(touchSensor.readRegister(0x00)&1);
  //printBits(touchSensor.readRegister(0x38));
  if (touchSensor.touchStatusChanged()) {
    touchSensor.updateTouchData();
    for (int i = 0; i < 8; i++) {
      if (touchSensor.isNewTouch(i)) {
        Serial.println("Electrode " + String(i) + " was just touched.");
      }
      if (touchSensor.isNewRelease(i)) {
        Serial.println("Electrode " + String(i) + " was just released.");
      }
    }
  }
  delay(50);
}

void printBits(byte myByte) {
  for (byte mask = 0x80; mask; mask >>= 1) {
    if (mask  & myByte)
      Serial.print('1');
    else
      Serial.print('0');
  }
  Serial.println();
}

