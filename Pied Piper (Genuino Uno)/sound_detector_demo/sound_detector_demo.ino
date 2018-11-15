/******************************************************************************
 * sound_detector_demo.ino
 * Sound detector sample sketch
 * Byron Jacquot @ SparkFun Electronics
 * February 19, 2014
 * https://github.com/sparkfun/Sound_Detector
 * /// Modified by: O.T. Ajuyah
 * ///https://arduino.benarent.co.uk/setup/Setting_up_for_Arduino.html
 * ///https://learn.sparkfun.com/tutorials/sound-detector-hookup-guide/all
 * ///https://arduino.stackexchange.com/questions/24868/what-is-the-sampling-rate-of-the-analogread 
 * 
 * This sketch demonstrates the use of the Sparkfun Sound Detector board.
 *
 * The Sound Detector is a small board that combines a microphone and some 
 * processing circuitry.  It provides not only an audio output, but also a 
 * binary indication of the presence of sound and an analog representation 
 * of it's amplitude.  
 *
 * This sketch demonstrates two different modes of usage for the Sound
 * Detector.  The gate output (a binary indication that is high when sound
 * is present, and low when conditions are quiet) is used to fire a pin-change 
 * ISR, which lights an LED when the sound is present.  The envelope output 
 * (an analog voltage to rises to indicate the amplitude of the sound) is 
 * sampled in the loop(), and it prints an indication of the level to the 
 * serial terminal. 
 *
 * For more details about the Sound Detector, please check the hookup guide.
 *
 * Connections:
 * The Sound Detector is connected to the Adrduino as follows:
 * (Sound Detector -> Arduino pin)
 * GND → GND
 * VCC → 5V
 * Gate → Pin 2
 * Envelope → A0
 * 
 * Resources:
 * Additional library requirements: none
 * 
 * Development environment specifics:
 * Using Arduino IDe 1.0.5
 * Tested on Redboard, 3.3v/8MHz and 5v/16MHz ProMini hardware.
 * 
 * This code is beerware; if you see me (or any other SparkFun employee) at the
 * local, and you've found our code helpful, please buy us a round!
 * 
 * Distributed as-is; no warranty is given.
 ******************************************************************************/

// Define hardware connections
#define PIN_GATE_IN  2   // GATE - 1 or 0, but fluctuates like crazy once it comes on
#define IRQ_GATE_IN  0   // IRQ_GATE_IN (Interrupt ReQuest) - GATE Signal will be sent w/o need for physical connection on outside
#define PIN_LED_OUT 13   // Optional attached LED. By default, also small onboard green LED R4

#define PIN_ANALOG_IN A0 // Envelope (Smooth avg audio voltage) connected to A0(analog input 0)

// soundISR()
// This function is installed as an interrupt service routine for the pin
// change interrupt.  When digital input 2 changes state, this routine
// is called.
// It queries the state of that pin, and sets the onboard LED to reflect that 
// pin's state.

//void soundISR()
//{
//  int pin_val;
//
//  // Uncomment this block to make LED on pin13 blink. W/o LOW it stays on(don't know why)
//  // returns either a 1 or 0. Appears to tend to fluctuate like pwm cause function is called on CHANGE
//   
//  pin_val = digitalRead(PIN_GATE_IN);
//  digitalWrite(PIN_LED_OUT, pin_val);
//  Serial.print("Gate | Analog 'Envelope': " + (String)pin_val + " | ");
//  pin_val = analogRead(PIN_ANALOG_IN);
//  Serial.println(pin_val);
//  
//  delay(1000); // delay so LED shines for a bit
//  digitalWrite(PIN_LED_OUT, LOW);
//}

void setup() {
  Serial.begin(9600); ///  setup serial

//  //  Configure LED pin as output
//  pinMode(PIN_LED_OUT, OUTPUT);
//
//
//  // configure input to interrupt
//  //pinMode(IRQ_GATE_IN, INPUT);
//  //attachInterrupt(IRQ_GATE_IN, soundISR, CHANGE); // Alt. IRQ code for interupt is simpler
//  pinMode(PIN_GATE_IN, INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(PIN_GATE_IN), soundISR, CHANGE);

  // Display status
  Serial.println("Initialized");
}

void loop() {
  int value;

  // Check the envelope input
  value = analogRead(PIN_ANALOG_IN);
  ///val = analogRead(analogPin);     // read the input pin
  ///Serial.println(val);             // debug value

  // Convert envelope value into a message
  Serial.print("Status: ");
  if(value <= 10)
  {
    Serial.print("Quiet. (");
  }
  else if( (value > 10) && ( value <= 30) )
  {
    Serial.print("Moderate. (");
  }
  else if(value > 30)
  {
    Serial.print("Loud. (");
  }

  Serial.println((String)value + ")");

  // pause for 1 second - a little delay to not hog Serial Monitor
  delay(1000);
}

// https://www.sparkfun.com/products/12642
// https://learn.sparkfun.com/tutorials/sound-detector-hookup-guide/all
// https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
// https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/
// https://www.arduino.cc/en/Tutorial/AnalogInputPins
// https://www.arduino.cc/en/Serial/Println

// https://www.tutorialspoint.com/arduino/index.htm
// http://www.ladyada.net/learn/arduino/lesson4.html // lesson 3 shows LED colour mixing
// https://www.makerspaces.com/arduino-uno-tutorial-beginners/
// https://www.makerspaces.com/simple-arduino-projects-beginners/
// https://www.sparkfun.com/categories/273
