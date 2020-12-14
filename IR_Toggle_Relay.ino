
// The following program uses a Ifrared remote controller to 
// toggle a relay in series with a 120 volt residential outlet.

//HARDWARE
/*
 IR RECEIVER: TSOP-1740
 With the semi_circular cone facing you:
      ___
     |___|
       I
 ______I_______
  |    |    |
 GND  VCC Data_In


  RELAY: JQC 3FF-S-Z
 _____________
  |    |    |
 VCC  Data GND

  0V: The right two pins are shorted
  ____________
  |    |    |
       |____|

  5v: The left two pins are shorted
  ____________
  |    |    |
  |____|    |
 
 */

#include <IRremote.h>
IRrecv irrecv(RECEIVE_PIN);
decode_results results;

//SIGNAL represents a button being pressed on the controller
#define SIGNAL 0x20DF30CF //Star button

//CONSTANTS
const int RECEIVE_PIN = 11;
const int IR_VCC = 13;
const int RELAY_DATA_PIN = 6;
const int RELAY_VCC = 7;
const int RELAY_GND = 5; //GROUND PIN MUST BE CONNECTED TO GND, NOT A 'LOW' DIGITAL PORT
const int BAUD_RATE = 9600;
bool relay_on = 0;

void setup() {
  //RELAY
  pinMode(RELAY_DATA_PIN, OUTPUT);
  pinMode(RELAY_VCC, OUTPUT);
  pinMode(RELAY_GND, OUTPUT);
  digitalWrite(RELAY_DATA_PIN, LOW);
  digitalWrite(RELAY_VCC, HIGH);
  digitalWrite(RELAY_GND, LOW);

  //IR RECEIVER
  pinMode(RELAY_DATA_PIN, OUTPUT);
  pinMode(IR_VCC, OUTPUT);
  digitalWrite(IR_VCC, HIGH);

  //IR LIBARAY
  Serial.begin(BAUD_RATE);
  irrecv.enableIRIn();
}

void loop() {

  //SINGAL DETECTED
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX); //print signal

    //CHANGE
    if (results.value == SIGNAL) 
        change();

    //RESUME
    irrecv.resume();
  }
}


void change() {
  Serial.println(relay_on);
  if (relay_on)
    relay_on = 0;
  else
    relay_on = 1;
    
  digitalWrite(RELAY_DATA_PIN, relay_on);
}
