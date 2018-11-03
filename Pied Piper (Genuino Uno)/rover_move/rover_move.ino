/* Declare pins connected to respective s̶e̶r̶v̶o̶s̶ DC gear motors */
// Rear Motors
const int vel_r = 5; //M2 Speed Control (E2)
const int vel_l = 6; //M1 Speed Control (E1)
const int dir_r = 7; //M2 Direction Control (M2)
const int dir_l = 8; //M1 Direction Control (M1)

// ____________________________________________________________________________________________________ //
/******************************************************************************/
/*** setup routine sets up RESOURCES & runs once when you press reset       ***/
/******************************************************************************/
void setup() {
  
  for(int i=5; i<=8; i++)
    pinMode(i, OUTPUT); // initialize pins as output

  // Open serial window @ 9600 baud
  Serial.begin(9600);
  Serial.println("setup");

  //while (!Serial) {
  //  ; // wait for serial port to connect. Needed for native USB port only (debugging)
  //}
  //Serial.println("connected");
}

/******************************************************************************/
/*** MAIN loop routine runs over and over again forever                     ***/
/******************************************************************************/
void loop() {
  
  int i = 0;
  if(true) {

    // Test turning
    turn_right_degrees(360);
    delay(5000);

    // Test moving forward and back
    //move_forward_cm(30);
    //delay(5000);
    //move_forward_cm(-30);
    //delay(5000);
    
    // if executed 4 times, stop:
    if (i == 3) {
      // This loop loops forever and does nothing
      while (true) {
        continue;
      }
    }
    
    i++; // increment counter
    
  }

}

// ---------------------------------------- ~ Helper functions ~ ----------------------------------------


void stop() { //Stop subroutine (Halt movement)
  
  digitalWrite(vel_l,LOW); // Used digital to ensure it's fully off
  digitalWrite(vel_r,LOW);
  Serial.println("stop");
}

void turn_right_degrees (int angle) {  //Turn-Right subroutine (Half speed)
  int duration = (int)(angle * 21); // delay time in ms
  
  analogWrite (vel_l,127);   //Left  - half speed (value of 127 = half speed)
  digitalWrite(dir_l,LOW);   //Left  - direction control
  analogWrite (vel_r,127);   //Right - half speed (value of 127 = half speed)
  digitalWrite(dir_r,HIGH);  //Right - direction control
  //String message = "right by " + (String)angle + " degrees";
  //Serial.println(message);
  delay(duration);
  stop();
}

// ***** Test Forward subroutine (currently about a cm @ distance = 1)
//Needs argument to specify distance(maybe later in mm), will work w/ -ve to reverse
void move_forward_cm(int distance) {
  int dir = (distance > 0) ? LOW : HIGH; // (LOW is forwards FOR OUR CONFIGURATION)
  
  analogWrite (vel_l,255);  //Left  - full speed (value of 255 is max speed)
  digitalWrite(dir_l,dir);  //Left  - direction control (LOW is forwards FOR OUR CONFIGURATION)
  analogWrite (vel_r,255);  //Right - full speed (value of 255 = full speed)
  digitalWrite(dir_r,dir);  //Right - direction control
  String msg = "forward by " + (String)distance + " cm";
  Serial.println(msg);
  delay(distance * 100);
  stop();
}
