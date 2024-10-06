#include "Joystick.h"
#define speakerPin 6
#define ledPin 10

// Create Joystick
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
  6, 0,                 // Button Count, Hat Switch Count
  true, true, false,      // X, Y, Z
  false, false, false,    // Rx, Ry, Rz
  true, true,             // Rudder, Throttle
  false, false, false);   // Accelerator, Brake, Steering

// Map the buttons to pins 2, 5, 9, 8, 7, and 3
const int pinToButtonMap[6] = {5, 2, 3, 7, 8, 9};
int lastButtonState[6] = {0, 0, 0, 0, 0, 0}; // Store the last state of each button

void setup() {
  // Set pin modes
  pinMode(LED_BUILTIN_TX,INPUT);
  pinMode(LED_BUILTIN_RX,INPUT);
  pinMode(speakerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // Configure button pins with internal pull-ups
  for (int i = 0; i < 6; i++) {
    pinMode(pinToButtonMap[i], INPUT_PULLUP);
  }

  // Joystick initialization
  Joystick.begin();
  Joystick.setXAxisRange(0, 1023);
  Joystick.setYAxisRange(0, 1023);
  Joystick.setRudderRange(0, 1023);
  Joystick.setThrottleRange(0, 1023);

  // Configure analog inputs
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  // Play tone once during initialization
  //playR2D2Sound();
          tone(speakerPin, 4000, 70); // Emit a 1000Hz tone for 100ms
}

void loop() {
  // Read potentiometers and set joystick axes
  int pot1 = analogRead(A3);
  Joystick.setXAxis(pot1);

  int pot2 = analogRead(A2);
  Joystick.setYAxis(pot2);

  int pot3 = analogRead(A1);
  Joystick.setRudder(pot3);

  int pot4 = analogRead(A0);
  Joystick.setThrottle(pot4);

  // Read buttons and update joystick button states
  for (int index = 0; index < 6; index++) {
    int currentButtonState = !digitalRead(pinToButtonMap[index]); // Invert the state since we're using INPUT_PULLUP
    if (currentButtonState != lastButtonState[index]) {
      digitalWrite(ledPin, HIGH); // Turn on the LED when the button is pressed
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
     
           // Emit a quick beep sound when button is pressed
      if (currentButtonState == 1) { // Only when button is pressed (not released)
        tone(speakerPin, 3000, 50); // Emit a 1000Hz tone for 100ms
      }
    }
  }

  delay(10);
  digitalWrite(ledPin, LOW); // Turn off the LED after updating the state
}


void playR2D2Sound() {
  // A sequência de tons e intervalos para imitar o som do R2-D2
  int tones[] = {1000, 1200, 1500, 1800, 2100, 1300, 1600, 2000, 1100, 1400};
  int durations[] = {100, 150, 120, 80, 130, 100, 90, 160, 110, 140};


  // Tocar os tons em sequência com pausas aleatórias
  for (int i = 0; i < 10; i++) {
    digitalWrite(ledPin, HIGH); // Turn on the LED when the button is pressed
    int toneFreq = tones[random(0, 10)];     // Seleciona uma frequência aleatória
    int toneDuration = durations[random(0, 10)]; // Seleciona uma duração aleatória
    tone(speakerPin, toneFreq, toneDuration); // Emite o tom
    delay(toneDuration + random(50, 150));    // Pequena pausa entre os tons
    digitalWrite(ledPin, LOW); // Turn on the LED when the button is pressed
  }
/*
  // Finaliza o som com um tom decrescente
  for (int freq = 2000; freq > 500; freq -= 100) {
    tone(speakerPin, freq, 10);  // Frequência decrescente para o som final
    delay(50);
  }
*/
}

