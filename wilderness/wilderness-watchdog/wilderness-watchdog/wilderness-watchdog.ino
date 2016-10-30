/*
 * TO DO
 * 
 * -Need some way of telling if the ESP8266 is alive or dead
 * 
 */

#include <avr/sleep.h>    // Sleep Modes
#include <avr/power.h>    // Power management
#include <avr/wdt.h>      // Watchdog timer

#define SUP_PIN  1
#define LED_PIN  2
#define RST_PIN  3
#define WAKE_PIN 4
#define THRESH   3200

//#define ADC_PIN  1
//#define LED_PIN  4

int f_wdt = 0;
int adcVal = 0;
long batteryVoltage = 0;
int transition = 0;
int oldValue = 0;
int newValue = 0;
int serverUp = 0;

void setup() {
  pinMode(SUP_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  pinMode(WAKE_PIN, OUTPUT);
  digitalWrite(WAKE_PIN, HIGH);
  pinMode(RST_PIN, OUTPUT);
  digitalWrite(RST_PIN, HIGH);
  enterSleep();
}

void loop() {
  wdt_reset();
  batteryVoltage = readVcc();
  serverUp = digitalRead(SUP_PIN);
  if (batteryVoltage < THRESH ) {
    // Turn OFF FET
    digitalWrite(WAKE_PIN, LOW);
  }

/* Something wrong here. Keeps resetting */
/* Solved... had to actually wire it to pin 13 on esp :/ */
/*another problem, though: fet switch won't work at battery voltage*/
/*
/*
 * ok
 * i can't use the FET switch
 * not enough headroom
 * unless i find a better suited fet
 * take chpd low when vbat is too low
 * take chpd high when vbat is good
 * temorarily ground rst afterwards
 */

 if(batteryVoltage > THRESH){
  // TURN ESP8266 ON
  digitalWrite(WAKE_PIN, HIGH);
 }
  
  if(batteryVoltage >= THRESH && serverUp < 1) {
    // Reset ESP8266
    digitalWrite(RST_PIN, LOW);
    delay(250);
    digitalWrite(RST_PIN, HIGH);
  }
  enterSleep();
}

void enterSleep(void) {
  noInterrupts ();       // timed sequence coming up
  // pat the dog
  wdt_reset();
  // clear various "reset" flags
  MCUSR = 0;
  // allow changes, disable reset, clear existing interrupt
  WDTCR = bit (WDCE) | bit (WDE) | bit (WDIF);
  // set interrupt mode and an interval (WDE must be changed from 1 to 0 here)
  WDTCR = bit (WDIE) | bit (WDP3) | bit (WDP0);    // set WDIE, and 8 seconds delay
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable ();       // ready to sleep
  interrupts ();         // interrupts are required now
  sleep_mode ();          // sleep
  sleep_disable ();      // precaution
}

ISR(WDT_vect) {
  heartbeat();
}

void heartbeat() {
  
  // We're alive!
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  
  // Message Voltage > THRESH
  
  if(batteryVoltage > THRESH){
    for(int i = 0; i < 4; i++){
      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);
      delay(50);
    }
  }
  
  // Message Voltage < THRESH
  
  if(batteryVoltage < THRESH){
    for(int i = 0; i < 2; i++){
      digitalWrite(LED_PIN, HIGH);
      delay(500);
      digitalWrite(LED_PIN, LOW);
      delay(500);
    }
  }
  
}

long readVcc() {
  // Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
  ADMUX = _BV(MUX5) | _BV(MUX0);
#elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
  ADMUX = _BV(MUX3) | _BV(MUX2);
#else
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#endif

  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA, ADSC)); // measuring

  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH
  uint8_t high = ADCH; // unlocks both

  long result = (high << 8) | low;

  result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
  return result; // Vcc in millivolts
}

