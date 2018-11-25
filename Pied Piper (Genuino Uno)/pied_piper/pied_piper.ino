/****************************************/
/***      BEWARE LOCAL MA✘IMA!!!      ***/
/****************************************/

/* ***** Red Light Detection(May just use gel filter paper)
/* ***** Getting music frequencies(perhaps analyze piece in MATLAB and import array of freqs)
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
#define PIN_PHOTO_IN  A3 // (analog input 3)

// HC-SR04 Ultrasonic sensor
#define TRIG_PIN 9
#define ECHO_PIN 10

// virtual earth & power
#define GND 11
#define VCC 12

// Testing LED
#define PIN_LED_OUT 13 // LED_ping

#define LIGHT_MAX 240 // light max threshold to stop
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
  
  // Open serial window @ 9600 baud
  Serial.begin(9600);
  Serial.println("setup");
}

/******************************************************************************/
/*** MAIN loop routine runs over and over again forever                     ***/
/******************************************************************************/
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
    //face_sound();

    ////Face sound, and wait
    face_ultra_480();
    float s = get_ultra_d_cm();
    while(s > 11) {
      move_forward_mm(10);
      delay(100);
      s = get_ultra_d_cm();
    }
    
//    face_light_480();
    
    digitalWrite(PIN_LED_OUT,HIGH);
    delay(5000);
    digitalWrite(PIN_LED_OUT,LOW);
    delay(5000);
    
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

// Might take 3-5 times quickly then avg. Depends on quality & speed performance
int getValue() {} // e.g. return analogRead(A0);

void adjust(int& distance) {
  distance = ((getValue() > LIGHT_MAX-40) || (get_ultra_d_cm() < 5)) ? (int)(distance / 2) : distance;
}

// Face_Ultrasound_Test_Simulation
void face_ultra_480_sim() {
  int dirs[8] = {115,75,65,13,124,60,130,55};
  //              0  1  2  |3| 4  5   6   7
  int theta = 60;
  int total_turns = 480/theta;
  int minIndex;
  int minValue = dirs[0];
  
  // 480 check
  for(int i=0; i<total_turns; i++) {
    Serial.println(dirs[i]);
    if(dirs[i] < minValue) {
      minValue = dirs[i];
      minIndex = i;
    }
  }

  Serial.println("Now going back. MinVal was " + (String)minValue + " at index " + (String)minIndex);
  for(int i=total_turns-1; i>=minIndex; i--)
    Serial.println(dirs[i]);
  
}
// Face closest thing using ultrasound
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
void face_sound() {
  int theta = 30;
  int cur=0, old=0;
  int significance = 7;

  // Right check
  while(true) { // **** Keep checking. Forever if 360° surround-sound
    cur = getSound();
    //if(cur < old) break; // check if intensity drops
    if((old - cur) > significance) break; // if intensity drops significantly
    turn_right_degrees(theta);
    old = cur;
  }
  turn_right_degrees(-theta);
  old = 0;

  // Left Check
  while(true) {
    cur = getSound();
    //if(cur < old) break; // check if intensity falls
    if((old - cur) > significance) break; // if intensity falls significantly
    turn_right_degrees(-theta);
    old = cur;
  }
  turn_right_degrees(theta);
  
}

bool face_light_480() {
  int light_min = 205; // approx a fifth of supply
  int theta = 15;
  int total_turns = 480/theta;
  float directions[total_turns] = {0};
  int maxIndex=0;
  float maxValue=0;

  // 480 check
  for(int i=0; i<total_turns; i++) { // **** Keep checking. Forever if 480° surround-sound
    directions[i] = getLight();
    if(directions[i] > maxValue) {
      maxValue = directions[i];
      maxIndex = i;
    }
    turn_right_degrees(theta);
    Serial.println(directions[i]);
  }

  Serial.println("Now going back. MaxVal was " + (String)maxValue + " at index " + (String)maxIndex);
  
  // Go back in similar short bursts to mimic/match original motion
  for(int i=total_turns-1; i>=maxIndex; i--) {
    turn_right_degrees(-theta);
    Serial.println(directions[i]);
  }
  
  return (maxValue > light_min);
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

int getLight() {
  int sval = 0;
  int samples = 3;
  for(int i=0; i<samples; i++)
    sval += analogRead(PIN_PHOTO_IN);
  return sval / samples;
}

// Turns ultrasound echo time to distance
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
    
    //delay(1);
  }
  duration = sval / samples;
  
  // Calculate & return distance: s = t/2 * c (t = time taken to obj & back!)
  return (duration/2) * .0343; // (c = speed of sound in dry air at 20 °C in cm/μs)
}
//✓✗

/*
 * @TODO
 * light
 * standardize motion accuracy and reliability on carpet if running for a while(i.e. depleting battery)
 */
