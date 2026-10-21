/*
  AI Animal Detection — ESP32 DevKit V1 receiver
  Serial protocol from website at 9600 baud:
    ANIMAL:1 = supported animal detected
    ANIMAL:0 = no supported animal detected

  Wiring:
    GPIO 25 -> 220-330 ohm resistor -> LED anode; LED cathode -> GND.
    GPIO 26 -> active buzzer module input (only if GPIO-safe), GND -> GND.
  For a higher-current buzzer, use a transistor driver and suitable supply.
*/



/*
  AI Animal Detection - ESP32 Receiver

  Serial commands:
    ANIMAL:1  -> LED ON, buzzer ON
    ANIMAL:0  -> LED OFF, buzzer OFF

  USB serial baud rate: 9600

  LED:
    GPIO25 -> 220-330 ohm resistor -> LED anode (+)
    LED cathode (-) -> GND

  Active buzzer module:
    GPIO26 -> buzzer signal input
    GND    -> buzzer GND
*/

#include <Arduino.h>

const int LED_PIN = 13;
const int BUZZER_PIN = 4;

String inputBuffer = "";

bool animalDetected = false;

void setOutputs(bool active) {
  animalDetected = active;

  digitalWrite(LED_PIN, active ? HIGH : LOW);
  digitalWrite(BUZZER_PIN, active ? HIGH : LOW);

  if (active) {
    Serial.println("Animal detected: LED ON, buzzer ON");
  } else {
    Serial.println("No animal: LED OFF, buzzer OFF");
  }
}

void processCommand(String command) {
  command.trim();

  if (command == "ANIMAL:1") {
    if (!animalDetected) {
      setOutputs(true);
    }
  }
  else if (command == "ANIMAL:0") {
    if (animalDetected) {
      setOutputs(false);
    }
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.begin(9600);

  inputBuffer.reserve(32);

  Serial.println();
  Serial.println("==============================");
  Serial.println("AI Animal Detection ESP32");
  Serial.println("Serial baud rate: 9600");
  Serial.println("Waiting for browser commands...");
  Serial.println("==============================");
}

void loop() {
  while (Serial.available() > 0) {
    const char incoming = (char)Serial.read();

    if (incoming == '\n') {
      processCommand(inputBuffer);
      inputBuffer = "";
    }
    else if (incoming != '\r') {
      if (inputBuffer.length() < 64) {
        inputBuffer += incoming;
      } else {
        inputBuffer = "";
        Serial.println("Warning: command too long; buffer cleared.");
      }
    }
  }
}
