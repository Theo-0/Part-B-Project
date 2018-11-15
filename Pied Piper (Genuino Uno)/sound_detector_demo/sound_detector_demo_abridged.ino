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
#define analogPin A0 // Envelope (Smooth avg audio voltage) connected to A0(analog input 0)

void setup1() {
  Serial.begin(9600); //  setup serial
  Serial.println("Initialized"); // Display status
}

void loop1() {
  int val;

  // Check the envelope input
  val = analogRead(analogPin);     // read the input pin
  Serial.println(val);             // debug value

  
// -------------------- ~ Extra ~ --------------------
  // Convert envelope value into a message
  Serial.print("Status: ");
  if(val <= 10)
  {
    Serial.print("Quiet. (");
  }
  else if( (val > 10) && ( val <= 30) )
  {
    Serial.print("Moderate. (");
  }
  else if(val > 30)
  {
    Serial.print("Loud. (");
  }

  Serial.println((String)val + ")");

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
