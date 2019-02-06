/*
 * Robotics with the BOE Shield - PhototransistorVoltage
 * Display voltage of phototransistor circuit output connected to A3 in
 * the serial monitor.
 * // https://learn.parallax.com/tutorials/robot/shield-bot/robotics-board-education-shield-arduino/chapter-6-light-sensitive-14
 */
#define led 13 // Test LED
// virtual earth & power for 2nd phototransistor
#define GND2 2
#define VCC2 3

void setup() {                               // Built-in initialization block
  pinMode(led, OUTPUT);                      // Configure LED pin as output
  Serial.begin(9600);                        // Set data rate to 9600 bps
  // Pull up to operating voltage(5V)

//Uncomment these lines if you wish to make them virtual power & earth
  //pinMode(VCC2, OUTPUT);
  //digitalWrite(VCC2, HIGH);
  //pinMode(GND2, OUTPUT);
  //digitalWrite(GND2, LOW);
}

void loop() {                                // Main loop auto-repeats
  Serial.print("A5 = ");                     // Display "A5 = ", used to be A3
  Serial.print(volts(A5));                   // Display measured A5 volts********************
  Serial.println(" volts");                  // Display " volts" & newline

  if(volts(A5) > 2.5)
    digitalWrite(led,HIGH);
  else
    digitalWrite(led,LOW);
  
  delay(1000);                               // Delay for 1 second
}
                                             
float volts(int adPin) {                     // Measures volts at adPin. Returns floating point voltage
 return 5 - float(analogRead(adPin)) * 5.0 / 1024.0;
}    
