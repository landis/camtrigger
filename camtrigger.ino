/*
Arduino sketch for simulating a Canon RC-1 IR remote control to do timelapse photography with a compatible Canon DSLR
2010, Martin Koch
http://controlyourcamera.blogspot.com/
Huge thanks go to http://www.doc-diy.net/photo/rc-1_hacked/index.php for figuring out the IR code.
*/

#define irLED 12 
#define statusLED 13
#define pushBUTTON 7
#define piezo A0

int interval = 15; //seconds
int timelapseDuration = 60; //seconds
int numberOfShots = timelapseDuration / interval;

// piezo read variable
byte pzread = 0;
int thresh = 100;
int flashdelay = 100;

void setup() {
  pinMode(irLED, OUTPUT);                               //    IR LED
  pinMode(statusLED, OUTPUT);                           //    Status LED
  pinMode(pushBUTTON, INPUT);
  digitalWrite(pushBUTTON, HIGH);
  
}

void loop() { 

    //#####   Exposure/Interval (Shutter)
  if (digitalRead(pushBUTTON) == LOW) {
    digitalWrite(statusLED, HIGH); //Timelapse active
    for (int i=0; i <= numberOfShots; i++) {
      sendInfraredSignal();
      if (i < numberOfShots) delay(interval * 1000); //ms
    }
    // shutter is now opened
    
    //{sense loud sound}
    pzread = analogRead(piezo);
    if (pzread >= thresh) {
  
      // flash trigger
      delay(flashdelay);
      digitalWrite(flashPin, HIGH);
      digitalWrite(flashPin, LOW);
      delay(4000);
    }
    
    // turn off the light, we're done
    digitalWrite(statusLED, LOW);
  }
  
  //#####   Flash sensor code
  //
  //
  //
  //
  //
  
}

void sendInfraredSignal() {
  for(int i=0; i<16; i++) { 
    digitalWrite(irLED, HIGH);
    delayMicroseconds(11);
    digitalWrite(irLED, LOW);
    delayMicroseconds(11);
   } 
   delayMicroseconds(7330); 
   for(int i=0; i<16; i++) { 
     digitalWrite(irLED, HIGH);
     delayMicroseconds(11);
     digitalWrite(irLED, LOW);
     delayMicroseconds(11);
   }   
}