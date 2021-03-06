/****************************************/
/***      BEWARE LOCAL MA✘IMA!!!      ***/
/****************************************/

/* ***** Red Light Detection: Will use Red Optical Longpass Filter(590nm) Lens. (No longer gel filter paper)
/* ***** Getting music frequencies(perhaps analyze piece in MATLAB and import array of freqs) ✘
/* ***** Music Detection(?)
 */
/* Declare pins connected to respective s̶e̶r̶v̶o̶s̶ DC gear motors */
// Rear Motors
#define VEL_R 5 //M2 Speed Control (E2)
#define VEL_L 6 //M1 Speed Control (E1)
#define DIR_R 7 //M2 Direction Control (M2)
#define DIR_L 8 //M1 Direction Control (M1)

// SparkFun Sound Detector (with Headers) [SEN-14262, $11.95]
#define PIN_ANALOG_IN A0 // (analog input 0)

// RS TEPT4400 Phototransistor
#define PIN_PHOTO_IN  A5 // (analog input 5)

// HC-SR04 Ultrasonic sensor
#define TRIG_PIN 9
#define ECHO_PIN 10

// virtual earth & power
#define GND 11
#define VCC 12

// virtual earth & power for 2nd phototransistor
#define GND2 2
#define VCC2 3

// Testing LED
#define PIN_LED_OUT 13 // LED_ping

#define LIGHT_MAX 240 // light max threshold to stop

// Global variables for distance to move forward & sweep angle
// (so they're seen in loop()) * haven't tested the static keyword in loop()
int dist_mm = 400; // 40cm
int sweep_angle = 480; // arbitrary value to ensure at least one 360° sweep regardless of battery power

// ____________________________________________________________________________________________________ //
/******************************************************************************/
/*** setup routine sets up RESOURCES & runs once when you press reset       ***/
/******************************************************************************/
void setup() {

  for(int i=5; i<=8; i++)
    pinMode(i, OUTPUT); // initialize motor pins as output

  pinMode(TRIG_PIN, OUTPUT);
  //pinMode(ECHO_PIN, INPUT);
  //pinMode(PIN_ANALOG_IN, INPUT);
  //pinMode(PIN_PHOTO_IN, INPUT);
  
  pinMode(PIN_LED_OUT, OUTPUT); //  Configure LED pin as output

  // Pull up to operating voltage(5V)
  pinMode(VCC, OUTPUT);
  digitalWrite(VCC, HIGH);
  pinMode(VCC2, OUTPUT);
  digitalWrite(VCC2, HIGH);

  // Pull down to common earth (0 volts)
  pinMode(GND2, OUTPUT);
  digitalWrite(GND2, LOW);
  
  
  // Open serial window @ 9600 baud
  Serial.begin(9600);
  Serial.println("setup");
  
  // Ultrasound flush. Needed so ultrasound doesn't spaz out at start
  if((get_ultra_d_cm() <= 3.0)) Serial.println("Hi there!");
}

/******************************************************************************/
/*** MAIN loop routine runs over and over again forever                     ***/
/******************************************************************************/
//void loop1(){}
void loop() {
//    // --------------------- ~ Uncomment for actual Pied Piper Code ~ ---------------------
//    static int dist_mm = 10; // 10 mm starting loco dist
//    //static const int LIGHT_MAX = 240; // light max threshold to stop
//    
//    //if(!face_light()) face_sound(); // Uncomment in Phase 2
//    face_light();
//    adjust(dist);
//    move_forward_mm(dist);
//
//    //if((getValue() > LIGHT_MAX) || (get_ultra_d_cm() < 1)) { // Uncomment in Phase 2
//    if((getValue() > LIGHT_MAX)) {
//      // Celebrate w/ speaker, led, lcd display or fireworks/explosion!
//      //fun();
//      done();
//    }

    // ------------------------------ ~ This section is reserved for testing ~ ------------------------------

    // Check to stop robot before trying to face anything
    float bright = getLight();
    //if((getLight() > 2.0) || (get_ultra_d_cm() <= 3.0)) { // Swap w/ next line when considering ultrasound
    if((bright > 1.5)) {
      digitalWrite(PIN_LED_OUT,HIGH);
      delay(5000);
      digitalWrite(PIN_LED_OUT,LOW);
      delay(5000);
      done();
    }

    // If not too close, we can proceed...

    // Adjust angle by LIGHT INTENSITY
    // Dependent on if robot sees fixture far brighter than surrounding!
    //  e.g. doesn't mistake being close to wight surface as being 40cm away from fixture
    adjust_angle(sweep_angle, bright)
    
    // Face light
    turn_right_degrees(-sweep_angle/2); // turn left by half the angle to get ready. Might be removed
    face_light(sweep_angle);
    
    // Similarly, Adjust distance might base on either light intensity or ultrasound distance)
    move_forward_mm(dist_mm);

    
//    float distance_cm = get_ultra_d_cm();
//    Serial.println("Distance: " + (String)distance_cm);
//    delay(100); // every 1/10sec.
    
}

// __________________________________________________| = Helper functions = |__________________________________________________
// ------------------------------ ~ Exit Arduino Loop ~ -------------------------------
void done() {
  // Loop forever and do nothing
  while (true) {
    continue;
  }
}

// --------------------------------------------- ~ Mechanical (Motion) ~ ---------------------------------------------

// Halt
void stop() { //Stop subroutine (Halt movement)
  
  digitalWrite(VEL_L,LOW); // Used digital to ensure it's fully off
  digitalWrite(VEL_R,LOW);
  //Serial.println("stop");
}

// Rotate - Turn_Right subroutine will work w/ -ve to turn left
// Uses case structure to regulate how long to rotate for. This
// tries to account for the resistive force that largely affects small
// movements. Is relative to battery and subject to changes.
void turn_right_degrees (int angle) {  //Turn-Right subroutine (Half speed)
  
  int duration;
  if(abs(angle) <= 5)
    duration = (int)(abs(angle) * 20); // delay time in ms
  else if(abs(angle) <= 10)
    duration = (int)(abs(angle) * 15);
  else if(abs(angle) <= 20)
    duration = (int)(abs(angle) * 12);
  else if(abs(angle) <= 90)
    duration = (int)(abs(angle) * 11);
  else if(abs(angle) <= 200)
    duration = (int)(abs(angle) * 10);
  else if(abs(angle) <= 270)
    duration = (int)(abs(angle) * 9);
  else
    duration = (int)(abs(angle) * 9);
  
  if (angle > 0) { // Right
    analogWrite (VEL_L,255);   //Left  - full speed (value of 127 = half speed)
    digitalWrite(DIR_L,LOW);   //Left  - direction control
    analogWrite (VEL_R,255);   //Right - full speed (value of 127 = half speed)
    digitalWrite(DIR_R,HIGH);  //Right - direction control
  }
  else { // Left
    analogWrite (VEL_L,255);   //Left  - full speed (value of 127 = half speed)
    digitalWrite(DIR_L,HIGH);  //Left  - direction control
    analogWrite (VEL_R,255);   //Right - full speed (value of 127 = half speed)
    digitalWrite(DIR_R,LOW);   //Right - direction control
  }
  
  //String message = "right by " + (String)angle + " degrees";
  //Serial.println(message);
  delay(duration);
  stop(); 
  
}


// Locomotion(Translocate) - Forward subroutine will work w/ -ve to reverse
void move_forward_mm(int distance) {
  int dir = (distance > 0) ? LOW : HIGH; // (LOW is forwards FOR OUR CONFIGURATION)
  
  analogWrite (VEL_L,255);  //Left  - full speed (value of 255 is max speed)
  digitalWrite(DIR_L,dir);  //Left  - direction control (LOW is forwards FOR OUR CONFIGURATION)
  analogWrite (VEL_R,255);  //Right - full speed (value of 255 = full speed)
  digitalWrite(DIR_R,dir);  //Right - direction control
  //String msg = "forward by " + (String)distance + " mm";
  //Serial.println(msg);

  // Scale delay time depending on distance due to driving force
  // required to overcome static friction from rest
  if(abs(distance) > 50)
    delay( int(abs(distance) * 8.2) );
  else
    delay( int(abs(distance) * 12) );
  
  stop();
}

// --------------------------------------------- ~ 'Finding' Logic Definitions ~ ---------------------------------------------

//// Might take 3-5 times quickly then avg. Depends on quality & speed performance
//int getValue() {} // e.g. return analogRead(A0);

// UNDER DEVELOPMENT
// Consider: 
//   - Reduce distance if close enough to be facing the fixture(1m) &&
//   - the moving distance is large enough to be meaningful(2cm)
void adjust_distance(int& distance) {
  distance = ((getValue() > LIGHT_MAX-40) || (get_ultra_d_cm() < 5)) ? (int)(distance / 2) : distance;
}

// Adjusts given angle(by reference) according to look-up table of
// angles and light intensities to optimize search radius
// STILL UNDER DEVELOPMENT
void adjust_angle(int& angle, float intensity) {
  int max_angle = 480;
  int angle = max_angle; // set angle to max by default

  // empirically obtained best angles at certain light intensities(indicating distances)
  if(intensity > 2.25) {
    angle = 50;
  }elsif(intensity > 2.00) {
    angle = 100;
  }elsif(intensity > 1.80) {
    angle = 180;
  }// and so on... up till about a base of 480

  return;
}

//// Face_Ultrasound_Test_Simulation
//void face_ultra_480_sim() {
//  int dirs[8] = {115,75,65,13,124,60,130,55};
//  //              0  1  2  |3| 4  5   6   7
//  int theta = 60;
//  int total_turns = 480/theta;
//  int minIndex;
//  int minValue = dirs[0];
//  
//  // 480 check
//  for(int i=0; i<total_turns; i++) {
//    Serial.println(dirs[i]);
//    if(dirs[i] < minValue) {
//      minValue = dirs[i];
//      minIndex = i;
//    }
//  }
//
//  Serial.println("Now going back. MinVal was " + (String)minValue + " at index " + (String)minIndex);
//  for(int i=total_turns-1; i>=minIndex; i--)
//    Serial.println(dirs[i]);
//  
//}


// Turn 480° sweep to face closest thing (using ultrasound)
void face_ultra_480() {
  int theta = 15;
  int total_turns = 480/theta;
  float directions[total_turns] = {0};
  int minIndex=0;
  float minValue = get_ultra_d_cm();

  digitalWrite(PIN_LED_OUT,HIGH);
  
  // 480 check
  for(int i=0; i<total_turns; i++) { // **** Keep checking. Forever if 480° surround-sound
    directions[i] = get_ultra_d_cm();
    if(directions[i] < minValue) {
      minValue = directions[i];
      minIndex = i;
    }
    turn_right_degrees(theta);
    Serial.println(directions[i]);
    delay(10);
  }

  digitalWrite(PIN_LED_OUT,LOW);
  delay(5000);
  
  Serial.println("Now going back. MinVal was " + (String)minValue + " at index " + (String)minIndex);
  //turn_right_degrees((total_turns-minIndex-1) * -theta); // Doesn't match original motion
  // e.g. if 10 turns(0-9) and u want 3. Turn back 6 (i.e. 9-3)

  digitalWrite(PIN_LED_OUT,HIGH);
  
  // Go back in similar short bursts to mimic/match original motion
  for(int i=total_turns-1; i>=minIndex; i--) {
    turn_right_degrees(-theta);
    Serial.println(directions[i]);
    delay(10);
  }
  digitalWrite(PIN_LED_OUT,LOW);
  delay(5000);
}



// Turn 720° sweep to face loudest thing (using microphone)
void face_sound_720() {
  int theta = 60;
  int total_turns = 720/theta;
  int directions[total_turns] = {0};
  int maxIndex = 0;
  int maxValue = 0;
  
  // 720 check
  for(int i=0; i<total_turns; i++) { // **** Keep checking. Forever if 720° surround-sound
    directions[i] = getSound();
    if(directions[i] > maxValue) {
      maxValue = directions[i];
      maxIndex = i;
    }
    turn_right_degrees(theta);
  }
  
  turn_right_degrees((total_turns-maxIndex) * -theta);
  // e.g. if 10 turns(0-9) and u want 3. Turn back 6 (i.e. 9-3)
  
}
//// Attempt to use low-high-low method with a minimum significance level to avoid
//// errors due to very small changes 
//void face_sound() {
//  int theta = 30;
//  int cur=0, old=0;
//  int significance = 7;
//
//  // Right check
//  while(true) { // **** Keep checking. Forever if 360° surround-sound
//    cur = getSound();
//    //if(cur < old) break; // check if intensity drops
//    if((old - cur) > significance) break; // if intensity drops significantly
//    turn_right_degrees(theta);
//    old = cur;
//  }
//  turn_right_degrees(-theta);
//  old = 0;
//
//  // Left Check
//  while(true) {
//    cur = getSound();
//    //if(cur < old) break; // check if intensity falls
//    if((old - cur) > significance) break; // if intensity falls significantly
//    turn_right_degrees(-theta);
//    old = cur;
//  }
//  turn_right_degrees(theta);
//  
//}


// Turn 480° sweep to face brightest thing i.e. greatest lumens (using phototransistor)
// Returns true if light source above certain threshold(LIGHT_MIN)was found, else false
bool face_light(int sweep_angle) {
  const int LIGHT_MIN = 205; // approx a fifth of supply
  int theta = 15;
  int total_turns = sweep_angle/theta;
  float directions[total_turns] = {0};
  int maxIndex=0;
  float maxValue=0;

  // sweep_angle(480) check
  for(int i=0; i<total_turns; i++) { // **** Keep checking. Forever if 480° surround-sound
    directions[i] = getLight();
    if(directions[i] > maxValue) {
      maxValue = directions[i];
      maxIndex = i;
    }
    turn_right_degrees(theta);
  }

  Serial.println("Now going back. MaxVal was " + (String)maxValue + " at index " + (String)maxIndex);
  
  // Go back in similar short bursts to mimic/match original motion
  for(int i=total_turns-1; i>=maxIndex; i--) {
    turn_right_degrees(-theta);
    Serial.println(directions[i]);
  }
  return (maxValue > LIGHT_MIN);
}

// --------------------------------------------- ~ Sensory Systems ~ ---------------------------------------------

// Returns avg sound amp as voltage(default between 0 to 1023)
int getSound() {
  int sval = 0; // sum value
  int samples = 2000;
  for(int i=0; i<samples; i++)
    sval += analogRead(PIN_ANALOG_IN);
  return sval / samples; // avg
}

// Returns avg light amp as voltage(default between 0V to 5V)
float getLight() {
  float sval = 0;
  float samples = 3;
  for(int i=0; i<samples; i++)
    sval += analogRead(PIN_PHOTO_IN);
  return 5 - (sval / samples * (5.0 / 1024.0) );
}

// Turns average ultrasound echo time to distance & returns it in cm
float get_ultra_d_cm() {
  unsigned long duration;
  unsigned long sval = 0; // sum value
  int samples = 1;
  for(int i=0; i<samples; i++) {
    // Generate ultrasonic wave
    digitalWrite(TRIG_PIN, LOW); 
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
  
    // Read the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(ECHO_PIN, HIGH);
    sval += duration;
  }
  duration = sval / samples;
  
  // Calculate & return distance: s = t/2 * c (t = time taken to obj & back!)
  return (duration/2) * .0343; // (c = speed of sound in dry air at 20 °C in cm/μs)
}
//✓✗

/*
 * @TODO
 * RESOLVE POWER ISSUE! - Current plan is continue testing w/ power pack,
 *   then buy fresh non-rechargeable batteries for the big day
 * describe functions & their parameters a bit more perhaps
 * light + sound
 * try attempting 360°/480° sweep first, then proceeding to low-high-low method to save battery through movement minimization
 * standardize motion accuracy and reliability on carpet if running for a while(i.e. depleting battery)
 */
