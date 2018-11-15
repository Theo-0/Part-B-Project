
/************************************************************************************************************************************************************************                                              
 * - Author           : BEE MB                       *                                               
 * - Modifier         : O.T. Ajuyah                  *                                               
 * - Profession       : (Developer) MEGA DAS owner   *                                                                                              
 * - Main purpose     : Industrial Application       *                                                                                  
 * - Copyright holder : No copyrights                *                                  
 * - Date             : 23/03/2017 (13/11/2018)      *
 * http://www.mediafire.com/file/8hksa7p8abws5m0/Tow_ultrasonic_sensors.rar
 * ***********************************************************************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------------------|
 This code allows you to know the distance between an Ultrasonic sensor and an object                                            |
 You can add more Ultrasonic sensors and follow the same steps two be sure that you are getting the desired information          |
---------------------------------------------------------------------------------------------------------------------------------|*/
/**
 * https://codebender.cc/sketch:356078#HC-SR04%20Ultrasonic%20Sensor%20Example.ino - (calculates time manually using t = micros();)
 * HC-SR04 Demo
 * Demonstration of the HC-SR04 Ultrasonic Sensor
 * Date: August 3, 2016 (November 13, 2018)
 * 
 * Description:
 *  Connect the ultrasonic sensor to the Arduino as per the
 *  hardware connections below. Run the sketch and open a serial
 *  monitor. The distance read from the sensor will be displayed
 *  in centimeters.
 * 
 * Hardware Connections: (Ultrasonic Sensor --> Arduino Pin)
 *  HC-SR04 | Arduino 
 *  -------------------
 *    VCC  -|>  5V      
 *    Trig -|>  9       
 *    Echo -|>  10      
 *    GND  -|>  GND (11, which I will set to 0V)
 *  
 * License:
 *  Public Domain
 */
//define the pins to be used for the HC-SR04 ultrasonic sensor
//---------------------------------------------------------------------------------------------------------------------
// Pins
const byte trigPin = 9; // TRIG_PIN
const byte echoPin = 10;// ECHO_PIN
#define LED_ping 13
#define GND 11
#define VCC 12
//----------------------------------------------------------------------------------------------------------------------
//used variables
float distance_cm;
unsigned long duration;
//----------------------------------------------------------------------------------------------------------------------
char data;
String SerialData="";
//----------------------------------------------------------------------------------------------------------------------

void setup() { // START SETUP FUNCTION

  // setup pins for sensor
  pinMode(trigPin, OUTPUT);   // transmit the ultrasonic wave
  //pinMode(echoPin, INPUT);    // read the reflected wave [Arduino (Atmega) pins default to INPUT]
  pinMode(LED_ping, OUTPUT);  // from where we will control the LED

  // Start serial data communication
  Serial.begin (9600);        // Use serial data transmission to display sensor's distance value on Serial Monitor 
  
  // initialize LED status 
  digitalWrite(LED_ping,LOW); // [init as default OUTPUT is set to HIGH]

  // Set virtual earth
  pinMode(GND, OUTPUT);
  digitalWrite(GND,LOW);

  // Pull up to operating voltage(5V)
  pinMode(VCC, OUTPUT);
  digitalWrite(VCC, HIGH);
}// END SETUP FUNCTION


void loop() { // START THE LOOP FUNCTION

    // Call the SonarSensor function to store the distance
    distance_cm = SonarSensor(trigPin, echoPin);

    // ---------------------------------------- ~ Uncomment if requesting from Serial Monitor ~  ----------------------------------------
//    // Check if user wants it displayed
//    while(Serial.available()) {
//      delay(10);
//      data = Serial.read();
//      SerialData += data;
//    }
//
//    //Print distance...
//    if(SerialData == "display distance")
//      // display the distance on the Serial Monitor
//      Serial.println("Object found at: " + (String)distance_cm + " cm");
//    
//    SerialData=""; // clear serial data
//    
    // make condition to control the LEDs
    if(distance_cm <= 5)
      digitalWrite(LED_ping,HIGH); // if distance is less than 5 Cm turn the LED ON
    else
      digitalWrite(LED_ping,LOW); // else turn the LED OFF

    //------------------------------------------------------------ ~ ~ ------------------------------------------------------------
    
    // Uncomment block if not requesting from Serial Monitor
    // Prints the distance on the Serial Monitor
    Serial.println("Distance: " + (String)distance_cm);
    delay(100); // every 1/10sec.
}//END LOOP FUNTION


// SonarSensor function used to generate and read the ultrasonic wave
float SonarSensor(const byte triggerPinSensor, const byte echoPinSensor) { // takes the trigPIN and the echoPIN
  
  // Generate the ultrasonic wave
  digitalWrite(triggerPinSensor, LOW);// Clears trigpin i.e. puts to  LOW 
  delayMicroseconds(2);// wait 2 microseconds to be sure
  
  digitalWrite(triggerPinSensor, HIGH);// Switches/Sets trigPin on HIGH state for 10μs
  delayMicroseconds(10);
  digitalWrite(triggerPinSensor, LOW);

  // Read the echoPin, returns the sound wave travel time, in microseconds ofcourse
  duration = pulseIn(echoPinSensor, HIGH);
  //pulseIn API(funtion) will return propagation time i.e. how long the configured pin remains in the stated level;
  //in this case how long the echopin stays HIGH

// // -------------------- Ignore this bit, it's a substitution for pulseIn --------------------
//  unsigned long t1, t2, pulse_width;
//  while ( digitalRead(echoPinSensor) == 1 ) ;
//  // Measure how long the echo pin was held high (pulse width)
//  // Note: the micros() counter will overflow after ~70 min
//  t1 = micros();
//  while ( digitalRead(echoPinSensor) == 0) ;
//  t2 = micros();
//  pulse_width = t2 - t1;
//  duration = pulse_width;
  
  
  // Calculating & returning the distance: s = t * v
  // remember we have to first divide the duration by two for the time taken to reach the object
  return (duration/2) * .0343; // Speed of sound is .0343 cm/μs. Approx.≈ the same as dividing by / 29.1
                               // NOTE: This is in dry air at 20°C (68°F). http://www.sengpielaudio.com/calculator-speedsound.htm
}

/****************************----------------------- END PROGRAM -----------------------****************************/

/*
 * Other resources include:
 * https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
 * https://www.hackster.io/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-036380
 * https://codebender.cc/sketch:356078#HC-SR04%20Ultrasonic%20Sensor%20Example.ino
 * https://www.hackster.io/mega-das/ultrasonic-sensor-hc-sr04-arduino-project-021d11
 * https://www.instructables.com/id/Simple-Arduino-and-HC-SR04-Example/
 * http://www.ardumotive.com/how-to-use-the-hc-sr04-ultrasonic-sensor-en.html
 * 
 * https://www.sparkfun.com/products/13959
 * https://www.robotshop.com/uk/hc-sr04-ultrasonic-range-finder.html?gclid=CjwKCAiAiarfBRASEiwAw1tYv0FOhCtL_TxNLzR_r884nnnI3mM_HX5NrBJ7XWIG_An0LXwCatptjRoCOVQQAvD_BwE
 * 
 * https://arduino.stackexchange.com/questions/12627/how-to-use-ultrasonic-sensors-trig-pin-and-why-it-is-needed
 */
