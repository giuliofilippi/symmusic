#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

// pins
int buttonPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int noteLeds[] = {30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41};
int octaveLeds[] = {48, 49, 50, 51, 52};
int octavedownPin = 22;
int octaveupPin = 24;
int resetPin = 26;

// vars
int rootNote = 0;

// setup
void setup() {
  MIDI.begin();

  for (int i = 0; i < 12; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    pinMode(noteLeds[i], OUTPUT);
  }

  for (int i = 0; i < 5; i++) {
    pinMode(octaveLeds[i], OUTPUT);
  }

  pinMode(octavedownPin, INPUT_PULLUP);
  pinMode(octaveupPin, INPUT_PULLUP);
  pinMode(resetPin, INPUT_PULLUP);

  digitalWrite(noteLeds[0], HIGH);
  digitalWrite(octaveLeds[2], HIGH);
}

// loop
void loop() {
    // loop vars
  static bool buttonValuesOld[12] = {HIGH};
  static bool octavedownOld = HIGH;
  static bool octaveupOld = HIGH;
  static bool resetOld = HIGH;
  static int o = 0;
  static int oOld = 0;
  static int root = 0;
  static int rootOld = 0;

    // digital reads
  bool buttonValuesNew[12];
  bool octavedownNew = digitalRead(octavedownPin);
  bool octaveupNew = digitalRead(octaveupPin);
  bool resetNew = digitalRead(resetPin);
  for (int i = 0; i < 12; i++) {
    buttonValuesNew[i] = digitalRead(buttonPins[i]);
  }

    // reset button
  if (resetOld != resetNew) {
    for (int i = 35; i < 98; i++) {
      MIDI.sendNoteOff(i, 0, 1);
    }
  }

    // octave down button
  if (octavedownNew != octavedownOld) {
    if (octavedownNew == LOW && o > -2) {
      o--;
    }
    octavedownOld = octavedownNew;
  }
    // octave up button
  if (octaveupNew != octaveupOld) {
    if (octaveupNew == LOW && o < 2) {
      o++;
    }
    octaveupOld = octaveupNew;
  }

    // octave leds
  if (oOld != o) {
    digitalWrite(octaveLeds[oOld + 2], LOW);
    digitalWrite(octaveLeds[o + 2], HIGH);
  }
  oOld = o;

    // root led
  if (rootOld != rootNote) {
    digitalWrite(noteLeds[rootOld], LOW);
    digitalWrite(noteLeds[rootNote], HIGH);
  }
  rootOld = rootNote;

    // note buttons
  for (int i = 0; i < 12; i++) {
    if (buttonsNew[i] != buttonsOld[i]){
        if (buttonsNew[i] == LOW){
        
      MIDI.sendNoteOn(62+i+12*o, 127, 1);
      //Serial.println("Note On");
      }
      else {
      MIDI.sendNoteOff(62+i+12*o, 0, 1);
      //Serial.println("Note Off");
      }
      buttonsOld[i] = buttonsNew[i];
    }}

    delay(25);
}