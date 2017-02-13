#include <KeyboardController.h>

USBHost usb;

KeyboardController keyboard(usb);


void keyPressed() {
  printKey();
}

void keyReleased() {
}

void printKey() {
  switch (keyboard.getOemKey()) {
    case 40: sendKey(13); break;
    case 42: sendKey(8); break;
    default: sendKey(keyboard.getKey()); break;
  }
}

void sendKey(int key) {
  Serial.println(key, DEC);
  Serial2.println(key, DEC);
}

void setup() {
  Serial.begin(250000);
  Serial2.begin(250000);
  Serial.println("Started!");
  delay(200);
}

void loop() {
  usb.Task();
}
