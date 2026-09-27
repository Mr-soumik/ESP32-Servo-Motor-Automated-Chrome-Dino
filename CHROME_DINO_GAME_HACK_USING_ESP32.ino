#include <ESP32Servo.h>

const int ldrPin = 32;      
const int servoPin = 15;    

Servo spacebarServo;

const int restAngle = 90;   
const int pressAngle = 110; 

// The light value threshold. 
// If the screen gets darker than this number, the servo will jump.
int darkThreshold = 1920; 

void setup() {
  // Allocate timers for the ESP32 Servo library
  ESP32PWM::allocateTimer(0);
  spacebarServo.setPeriodHertz(50); 
  spacebarServo.attach(servoPin, 500, 2400);
  
  // Move servo to the resting position on startup
  spacebarServo.write(restAngle);
  delay(1000);
}

void loop() {
  // Read the current light level from the LDR
  int ldrValue = analogRead(ldrPin); 
  
  // Check if a cactus is passing (light drops below threshold)
  if (ldrValue < darkThreshold) { 
    // Quickly press the spacebar
    spacebarServo.write(pressAngle);
    delay(80); 
    
    // Release the spacebar
    spacebarServo.write(restAngle);
    
    // Cooldown to prevent double-jumping over the same cactus
    delay(200); 
  }
  
  // No delay at the end of the loop ensures the ESP32 scans at maximum speed
}