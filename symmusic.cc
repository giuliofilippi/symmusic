#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

int button2pin = 2;  
int button3pin = 3; 
int button4pin = 4; 
int button5pin = 5; 
int button6pin = 6;  
int button7pin = 7; 
int button8pin = 8; 
int button9pin = 9; 
int button10pin = 10;  
int button11pin = 11; 
int button12pin = 12; 
int button13pin = 13; 

int octavedown = 22;
int octaveup = 24;

int reset = 26;

int note1led = 30;
int note2led = 31;
int note3led = 32;
int note4led = 33;
int note5led = 34;
int note6led = 35;
int note7led = 36;
int note8led = 37;
int note9led = 38;
int note10led = 39;
int note11led = 40;
int note12led = 41;

int octave1led = 48;
int octave2led = 49;
int octave3led = 50;
int octave4led = 51;
int octave5led = 52;

void setup() {
  // put your setup code here, to run once:
MIDI.begin (); // MIDI START

pinMode(button2pin, INPUT_PULLUP);
pinMode(button3pin, INPUT_PULLUP);
pinMode(button4pin, INPUT_PULLUP);
pinMode(button5pin, INPUT_PULLUP);
pinMode(button6pin, INPUT_PULLUP);
pinMode(button7pin, INPUT_PULLUP);
pinMode(button8pin, INPUT_PULLUP);
pinMode(button9pin, INPUT_PULLUP);
pinMode(button10pin, INPUT_PULLUP);
pinMode(button11pin, INPUT_PULLUP);
pinMode(button12pin, INPUT_PULLUP);
pinMode(button13pin, INPUT_PULLUP);

pinMode(octavedown, INPUT_PULLUP);
pinMode(octaveup, INPUT_PULLUP);

pinMode(reset, INPUT_PULLUP);

pinMode(note1led, OUTPUT);
pinMode(note2led, OUTPUT);
pinMode(note3led, OUTPUT);
pinMode(note4led, OUTPUT);
pinMode(note5led, OUTPUT);
pinMode(note6led, OUTPUT);
pinMode(note7led, OUTPUT);
pinMode(note8led, OUTPUT);
pinMode(note9led, OUTPUT);
pinMode(note10led, OUTPUT);
pinMode(note11led, OUTPUT);
pinMode(note12led, OUTPUT);

pinMode(octave1led, OUTPUT);
pinMode(octave2led, OUTPUT);
pinMode(octave3led, OUTPUT);
pinMode(octave4led, OUTPUT);
pinMode(octave5led, OUTPUT);

// initial led's to be turned on
digitalWrite(30,HIGH);
digitalWrite(50,HIGH);

}


// main loop
void loop() {


// initial values for buttons
static bool button2valueOld = HIGH;
static bool button3valueOld = HIGH;
static bool button4valueOld = HIGH;
static bool button5valueOld = HIGH;
static bool button6valueOld = HIGH;
static bool button7valueOld = HIGH;
static bool button8valueOld = HIGH;
static bool button9valueOld = HIGH;
static bool button10valueOld = HIGH;
static bool button11valueOld = HIGH;
static bool button12valueOld = HIGH;
static bool button13valueOld = HIGH;
static bool octavedownOld = HIGH;
static bool octaveupOld = HIGH;
static bool resetOld = HIGH;

// variables
static int o = 0;
static int o_old = 0;
static int voi = 0;
static int root = 0;
static int root_old = 0;
static int shift[]={0,0,0,0,0,0,0,0,0,0,0,0};

// footswitches
bool button2valueNew = digitalRead(button2pin);
bool button3valueNew = digitalRead(button3pin);
bool button4valueNew = digitalRead(button4pin);
bool button5valueNew = digitalRead(button5pin);
bool button6valueNew = digitalRead(button6pin);
bool button7valueNew = digitalRead(button7pin);
bool button8valueNew = digitalRead(button8pin);
bool button9valueNew = digitalRead(button9pin);
bool button10valueNew = digitalRead(button10pin);
bool button11valueNew = digitalRead(button11pin);
bool button12valueNew = digitalRead(button12pin);
bool button13valueNew = digitalRead(button13pin);
bool octavedownNew = digitalRead(octavedown);
bool octaveupNew = digitalRead(octaveup);
bool resetNew = digitalRead(reset);


//reset button + voicing

    if (resetOld != resetNew) {
      for (int i = 35; i < 98; i++) {
       MIDI.sendNoteOff(i, 0, 1);
      }
       voi = 1;
      //Serial.println("reset");
    }

//Octave down button

     if (octavedownNew != octavedownOld){
      if (octavedownNew == LOW){
        if (o>-2){
          o += -1;
         }
      //Serial.println("octave down");
      }  
      octavedownOld = octavedownNew;
    }

//Octave up button

    if (octaveupNew != octaveupOld){
      if (octaveupNew == LOW){
        if (o<2){
          o += 1;
        }
      //Serial.println("octave up");
      }
      octaveupOld = octaveupNew;
    }

//Octave LED

    if (o_old != o){
      digitalWrite(50+o_old, LOW);
      digitalWrite(50+o,HIGH);
      }

    o_old = o;

//Note LED

    if (root_old != root){
      digitalWrite(30+root_old,LOW);
      digitalWrite(30+root,HIGH);    
      }

    root_old = root;

//Note 0

    if (button2valueNew != button2valueOld){
      if (button2valueNew == LOW){

        if (voi==1){
          root = 0;
          for (int i = 0; i < 12; i++) {
                shift[i]=0;
            }
          voi = 0;
          }
          
      MIDI.sendNoteOn(60 + 12*o + shift[0], 127, 1);
      //Serial.println("Note C On");
      }
      else {
      MIDI.sendNoteOff(60 + 12*o + shift[0], 0, 1);
      //Serial.println("Note C Off");
      }
      button2valueOld = button2valueNew;
    }

//Note 1

    if (button3valueNew != button3valueOld){
      if (button3valueNew == LOW){

        if (voi==1){
          root = 1;
          for (int i = 0; i < root; i++) {
                shift[i]=12;
            }
            for (int i = root; i < 12; i++) {
                shift[i]=0;
            }
          voi = 0;
          }
        
      MIDI.sendNoteOn(61+12*o + shift[1], 127, 1);
      //Serial.println("Note C On");
      }
      else {
      MIDI.sendNoteOff(61+12*o + shift[1], 0, 1);
      //Serial.println("Note C Off");
      }
      button3valueOld = button3valueNew;
    }

//Note 2

        if (button4valueNew != button4valueOld){
      if (button4valueNew == LOW){

        if (voi==1){
          root = 2;
          for (int i = 0; i < root; i++) {
                shift[i]=12;
            }
            for (int i = root; i < 12; i++) {
                shift[i]=0;
            }
          voi = 0;
          }
        
      MIDI.sendNoteOn(62+12*o + shift[2], 127, 1);
      //Serial.println("Note C On");
      }
      else {
      MIDI.sendNoteOff(62+12*o + shift[2], 0, 1);
      //Serial.println("Note C Off");
      }
      button4valueOld = button4valueNew;
    }

//Note 3

        if (button5valueNew != button5valueOld){
      if (button5valueNew == LOW){

        if (voi==1){
          root = 3;
          for (int i = 0; i < root; i++) {
                shift[i]=12;
            }
            for (int i = root; i < 12; i++) {
                shift[i]=0;
            }
          voi = 0;
          }
          
      MIDI.sendNoteOn(63+12*o + shift[3], 127, 1);
      //Serial.println("Note C On");
      }
      else {
      MIDI.sendNoteOff(63+12*o + shift[3], 0, 1);
      //Serial.println("Note C Off");
      }
      button5valueOld = button5valueNew;
    }

//Note 4

        if (button6valueNew != button6valueOld){
      if (button6valueNew == LOW){

        if (voi==1){
          root = 4;
          for (int i = 0; i < root; i++) {
                shift[i]=12;
            }
            for (int i = root; i < 12; i++) {
                shift[i]=0;
            }
          voi = 0;
          }
          
      MIDI.sendNoteOn(64+12*o + shift[4], 127, 1);
      //Serial.println("Note C On");
      }
      else {
      MIDI.sendNoteOff(64+12*o + shift[4], 0, 1);
      //Serial.println("Note C Off");
      }
      button6valueOld = button6valueNew;
    }

//Note 5

    if (button7valueNew != button7valueOld){
      if (button7valueNew == LOW){

        if (voi==1){
          root = 5;
          for (int i = 0; i < root; i++) {
                shift[i]=12;
            }
            for (int i = root; i < 12; i++) {
                shift[i]=0;
            }
          voi = 0;
          }
          
      MIDI.sendNoteOn(65+12*o + shift[5], 127, 1);
      //Serial.println("Note C On");
      }
      else {
      MIDI.sendNoteOff(65+12*o + shift[5], 0, 1);
      //Serial.println("Note C Off");
      }
      button7valueOld = button7valueNew;
    }

//Note 6

        if (button8valueNew != button8valueOld){
      if (button8valueNew == LOW){

        if (voi==1){
          root = 6;
          for (int i = 0; i < root; i++) {
                shift[i]=12;
            }
            for (int i = root; i < 12; i++) {
                shift[i]=0;
            }
          voi = 0;
          }
          
      MIDI.sendNoteOn(66+12*o + shift[6], 127, 1);
      //Serial.println("Note C On");
      }
      else {
      MIDI.sendNoteOff(66+12*o + shift[6], 0, 1);
      //Serial.println("Note C Off");
      }
      button8valueOld = button8valueNew;
    }

//Note 7

        if (button9valueNew != button9valueOld){
      if (button9valueNew == LOW){

        if (voi==1){
          root = 7;
          for (int i = 0; i < root; i++) {
                shift[i]=12;
            }
            for (int i = root; i < 12; i++) {
                shift[i]=0;
            }
          voi = 0;
          }
          
      MIDI.sendNoteOn(67+12*o + shift[7], 127, 1);
      //Serial.println("Note C On");
      }
      else {
      MIDI.sendNoteOff(67+12*o + shift[7], 0, 1);
      //Serial.println("Note C Off");
      }
      button9valueOld = button9valueNew;
    }

//Note 8

        if (button10valueNew != button10valueOld){
      if (button10valueNew == LOW){

        if (voi==1){
          root = 8;
          for (int i = 0; i < root; i++) {
                shift[i]=12;
            }
            for (int i = root; i < 12; i++) {
                shift[i]=0;
            }
          voi = 0;
          }
          
      MIDI.sendNoteOn(68+12*o + shift[8], 127, 1);
      //Serial.println("Note C On");
      }
      else {
      MIDI.sendNoteOff(68+12*o + shift[8], 0, 1);
      //Serial.println("Note C Off");
      }
      button10valueOld = button10valueNew;
    }

//Note 9

    if (button11valueNew != button11valueOld){
      if (button11valueNew == LOW){

        if (voi==1){
          root = 9;
          for (int i = 0; i < root; i++) {
                shift[i]=12;
            }
            for (int i = root; i < 12; i++) {
                shift[i]=0;
            }
          voi = 0;
          }
          
      MIDI.sendNoteOn(69+12*o + shift[9], 127, 1);
      //Serial.println("Note C On");
      }
      else {
      MIDI.sendNoteOff(69+12*o + shift[9], 0, 1);
      //Serial.println("Note C Off");
      }
      button11valueOld = button11valueNew;
    }

//Note 10

        if (button12valueNew != button12valueOld){
      if (button12valueNew == LOW){

        if (voi==1){
          root = 10;
          for (int i = 0; i < root; i++) {
                shift[i]=12;
            }
            for (int i = root; i < 12; i++) {
                shift[i]=0;
            }
          voi = 0;
          }
          
      MIDI.sendNoteOn(70+12*o + shift[10], 127, 1);
      //Serial.println("Note C On");
      }
      else {
      MIDI.sendNoteOff(70+12*o + shift[10], 0, 1);
      //Serial.println("Note C Off");
      }
      button12valueOld = button12valueNew;
    }

//Note 11

        if (button13valueNew != button13valueOld){
      if (button13valueNew == LOW){

        if (voi==1){
          root = 11;
          for (int i = 0; i < root; i++) {
                shift[i]=12;
            }
            for (int i = root; i < 12; i++) {
                shift[i]=0;
            }
          voi = 0;
          }
          
      MIDI.sendNoteOn(71+12*o + shift[11], 127, 1);
      //Serial.println("Note C On");
      }
      else {
      MIDI.sendNoteOff(71+12*o + shift[11], 0, 1);
      //Serial.println("Note C Off");
      }
      button13valueOld = button13valueNew;
    }




delay(25);
}