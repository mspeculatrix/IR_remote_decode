/*
 * IR remote decode
 * 
 * See: https://mansfield-devine.com/speculatrix/category/projects/home-control/esp32-ir-hub/
 * 
 * Decode signals from an infrared remote controller.
 * 
 * Uses the 1838T receiver connected to pin RECV_PIN. 
 * 
 * Should work with most Arduinos, ESPs etc.
 * 
 */

#include <IRremote.h>
#include "irdecode-simple.h"

#define LED_PIN 6   // any pin capable of digital output
#define RECV_PIN 5  // any pin capable if digital input

// IR receiver and results objects
IRrecv irrecv(RECV_PIN);
decode_results results;

void flashLED(uint8_t times, int pulseLen) {
   for (uint8_t i = 0; i < times; i++) {
     digitalWrite(LED_PIN, HIGH);
     delay(pulseLen);
     digitalWrite(LED_PIN, LOW);
     delay(pulseLen);
   }
}

// ***************************************************************************************
// ***  SETUP                                                                          ***
// ***************************************************************************************
void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  flashLED(3, 250);

  // Enable the IR Receiver
  irrecv.enableIRIn();
  Serial.println("Listening for signals...");
}

// ***************************************************************************************
// ***  LOOP                                                                           ***
// ***************************************************************************************
void loop() {
  if (irrecv.decode(&results)) {
    // The value of 0xFFFFFFFF indicates repeat sending of the same code,
    // so we don't need it.
    if(results.value != 0xFFFFFFFF) {
      flashLED(2, 10);
      Serial.print("0x"); Serial.print(results.value, HEX);
      Serial.print("  "); Serial.print(results.value, HEX);
      Serial.print("  "); Serial.print(results.bits);
      Serial.print("  "); Serial.println(decodeType(results.decode_type));
    }
    irrecv.resume();
  }
}
