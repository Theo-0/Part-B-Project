/****************************************/
/***      BEWARE LOCAL MAXIMA!!!      ***/
/****************************************/

/* ***** Red Light Detection(May just use gel filter paper)
/* ***** Getting music frequencies(perhaps analyze piece in MATLAB and import array of freqs)
/* ***** Music Detection(?)

/* Declare pins connected to respective s̶e̶r̶v̶o̶s̶ DC gear motors */
// Rear Motors
const int VEL_R = 5; //M2 Speed Control (E2)
const int VEL_L = 6; //M1 Speed Control (E1)
const int DIR_R = 7; //M2 Direction Control (M2)
const int DIR_L = 8; //M1 Direction Control (M1)
// May replace const int's w/ #define to save on storage spaces

#define LIGHT_MAX 240 // light max threshold to stop
// ____________________________________________________________________________________________________ //
/******************************************************************************/
/*** setup routine sets up RESOURCES & runs once when you press reset       ***/
/******************************************************************************/
void setup() {

  for(int i=5; i<=8; i++)
    pinMode(i, OUTPUT); // initialize pins as output

  // Open serial window @ 9600 baud
  //Serial.begin(9600);
  //Serial.println("setup");

  face_sound();
}

/******************************************************************************/
/*** MAIN loop routine runs over and over again forever                     ***/
/******************************************************************************/
void loop() {
    static int dist = 10; // 10 cm starting loco dist
    //static const int LIGHT_MAX = 240; // light max threshold to stop
    
    if(!face_light()) face_sound();
    move_forward_cm(dist);
    dist = ((getValue() > LIGHT_MAX-40) && (get_ultra_d_cm() < 5)) ? dist : dist / 2;

    if((getValue() > LIGHT_MAX) || (get_ultra_d_cm() < 1)) {
      // Celebrate w/ speaker, led or lcd display!
      //fun();
      done();
    }
    
}

// ---------------------------------------- ~ Helper functions ~ ----------------------------------------
// ------------------------- ~ Exit Arduino Loop ~ -------------------------
void done() {
  // Loop forever and do nothing
  while (true) {
    continue;
  }
}

// ------------------------- ~ Mechanical (Motion) ~ -------------------------
// Halt
void stop() { //Stop subroutine (Halt movement)
  
  digitalWrite(VEL_L,LOW); // Used digital to ensure it's fully off
  digitalWrite(VEL_R,LOW);
  Serial.println("stop");
}

// Rotate
void turn_right_degrees (int angle) {  //Turn-Right subroutine (Half speed)
  int duration = (int)(angle * 21); // delay time in ms
  
  analogWrite (VEL_L,127);   //Left  - half speed (value of 127 = half speed)
  digitalWrite(DIR_L,LOW);   //Left  - direction control
  analogWrite (VEL_R,127);   //Right - half speed (value of 127 = half speed)
  digitalWrite(DIR_R,HIGH);  //Right - direction control
  //String message = "right by " + (String)angle + " degrees";
  //Serial.println(message);
  delay(duration);
  stop();
}

// Locomotion(Translocate)
// ***** Test Forward subroutine (currently about a cm @ distance = 1)
//Needs argument to specify distance(maybe later in mm), will work w/ -ve to reverse
void move_forward_cm(int distance) {
  int dir = (distance > 0) ? LOW : HIGH; // (LOW is forwards FOR OUR CONFIGURATION)
  
  analogWrite (VEL_L,255);  //Left  - full speed (value of 255 is max speed)
  digitalWrite(DIR_L,dir);  //Left  - direction control (LOW is forwards FOR OUR CONFIGURATION)
  analogWrite (VEL_R,255);  //Right - full speed (value of 255 = full speed)
  digitalWrite(DIR_R,dir);  //Right - direction control
  //String msg = "forward by " + (String)distance + " cm";
  //Serial.println(msg);
  delay(distance * 100);
  stop();
}

// ------------------------- ~ Sensory ~ -------------------------

void face_sound() {
  int theta = 5;
  int cur=0, old=0;

  // Right check
  while(true) { // **** Keep checking. Forever if 360° surround-sound
    cur = getValue();
    if(cur < old) break; // check if intensity drops
    turn_right_degrees(theta);
    old = cur;
  }
  turn_right_degrees(-theta);

  // Left Check
  while(true) {
    cur = getValue();
    if(cur < old) break; // check if intensity falls
    turn_right_degrees(-theta);
    old = cur;
  }
  turn_right_degrees(theta);
  
}

bool face_light() {
  int cur;// ditto w/ sound. Can change ϑ
  int light_min = 40; // light min threshold to trust
  return (cur > light_min);
}

// Turns ultrasound echo time to distance
int get_ultra_d_cm() {
  // s = v * t (v = speed of sound in dry air at 20 °C. Adjust if needed)
  return 343 * getValue() * 100;
}

// Might take 3-5 times quickly then avg. Depends on quality & speed performance
int getValue() {} // e.g. return analogRead(A0);
