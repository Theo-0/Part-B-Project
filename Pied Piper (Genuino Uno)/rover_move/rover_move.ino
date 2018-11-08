/* Declare pins connected to respective s̶e̶r̶v̶o̶s̶ DC gear motors */
// Rear Motors
const int VEL_R = 5; //M2 Speed Control (E2)
const int VEL_L = 6; //M1 Speed Control (E1)
const int DIR_R = 7; //M2 Direction Control (M2)
const int DIR_L = 8; //M1 Direction Control (M1)
// May replace const int's w/ #define to save on storage space

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
    //move_forward_mm(30);
    //delay(5000);
    //move_forward_mm(-30);
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

// Halt
void stop() { //Stop subroutine (Halt movement)
  
  digitalWrite(VEL_L,LOW); // Used digital to ensure it's fully off
  digitalWrite(VEL_R,LOW);
  Serial.println("stop");
}

// Rotate - Turn_Right subroutine will work w/ -ve to turn left
void turn_right_degrees (int angle) {  //Turn-Right subroutine (Half speed)
  
  int duration = (int)(abs(angle) * 21); // delay time in ms
  
  if (angle > 0) { // Right
    analogWrite (VEL_L,127);   //Left  - half speed (value of 127 = half speed)
    digitalWrite(DIR_L,LOW);   //Left  - direction control
    analogWrite (VEL_R,127);   //Right - half speed (value of 127 = half speed)
    digitalWrite(DIR_R,HIGH);  //Right - direction control
  }
  else { // Left
    analogWrite (VEL_L,127);   //Left  - half speed (value of 127 = half speed)
    digitalWrite(DIR_L,HIGH);  //Left  - direction control
    analogWrite (VEL_R,127);   //Right - half speed (value of 127 = half speed)
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
