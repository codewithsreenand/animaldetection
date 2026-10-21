AI ANIMAL DETECTION — ESP32 DEVKIT V1

Files
- index.html: browser camera + TensorFlow.js COCO-SSD animal detector.
- esp32_animal_receiver.ino: ESP32 DevKit V1 serial receiver for an external LED and active buzzer.

WIRING
1) LED: ESP32 GPIO 25 -> 220–330 ohm resistor -> LED anode (long leg); LED cathode -> GND.
2) Active buzzer module: signal/+ input -> GPIO 26, GND/- -> GND, ONLY if it is suitable for a 3.3 V GPIO signal and its current draw is within the ESP32 GPIO rating.
   If unsure, use a transistor driver. Do not drive a high-current buzzer directly from GPIO. Do not feed 5 V into an ESP32 GPIO.

SETUP
1) Open esp32_animal_receiver.ino in Arduino IDE.
2) Select a suitable ESP32 Dev Module / ESP32 DevKit V1 board and its USB port.
3) Upload the sketch.
4) Close Arduino IDE Serial Monitor/Plotter so the website can use the serial port.
5) In the folder containing index.html, start a local server:
   python3 -m http.server 8080
6) Open http://localhost:8080 in desktop Chrome or Edge.
7) Click "Start camera + AI" and allow camera access.
8) Click "Connect ESP32 USB" and select the ESP32 serial port.
9) When one of the supported animals is detected with at least 55% confidence, GPIO 25 and GPIO 26 go HIGH. When no supported animal is detected, both go LOW.

PROTOCOL
Website sends ANIMAL:1 followed by newline when an animal is detected.
Website sends ANIMAL:0 followed by newline when no supported animal is detected.
Serial baud rate is 9600.

SUPPORTED COCO-SSD CLASSES
bird, cat, dog, horse, sheep, cow, elephant, bear, zebra, giraffe.
A deer is not in this model's supported class list.

NOTES
- Internet access is needed to load TensorFlow.js, the COCO-SSD model and model weights from the CDN.
- Use desktop Chrome or Edge; Web Serial needs a supported browser and localhost/HTTPS.
- Keep the MacBook awake, the browser page open, and the USB cable connected while using the system.
- This is a prototype. Detection can miss animals or mistake objects; test it safely.
