/*
 * (c)Steffen Schütte 2025
 * License: FPV Cockpit Rudder Mixer © 2025 by Steffen Schütte is licensed under CC BY-NC-SA 4.0
 * 
 * This program converts two 0-5V input signals and generates
 * a single 0-5V output signal which is the difference of the two inputs.
 * If both signals are identical output is 2.5V so it has 50% offset.
 * 
 * This is used to control the rudder of an RC plane with two pedals
 * just like a real plane via the https://headtracker.gitbook.io/
 * 
 * Attention: The HeadTracker consumes 3.3V so the 5V output must be
 * reduved to 0-3.3V using a simple resistor based voltage divider.
 */

int pedalLeftPin = A0; 
int pedalRightPin = A1; 

int thrustLeverPin = A2; 

int rudderOutPin = 9;
int thrustOutPin = 10;

int left = 0;
float left_min = 0;
float left_max = 0;

int right = 0;
float right_min = 0;
float right_max = 0;

int thrust = 0;
float thrust_min = 0;
float thrust_max = 0;



int rudderOutput = 0;
int thrustOutput = 0;

unsigned long startMillis;

void setup() {
  startMillis = millis(); // Initial start time
  Serial.begin(9600);
  delay(1000);   

  pinMode(LED_BUILTIN, OUTPUT);

  left = analogRead(pedalLeftPin); 
  right = analogRead(pedalRightPin);
  thrust = analogRead(thrustLeverPin);
  
  left_min = left;
  left_max = left;
  right_min = right;
  right_max = right;
  thrust_min = thrust;
  thrust_max = thrust;              
}

int normalize_input(float calibrated_min, float calibrated_max, int input) 
{
   // Limit value to calibrated range to avoid blow up of the calculation formular
   input = min(calibrated_max, input); // if val is larger than calibrated max use the calibrated max
   input = max(calibrated_min, input); // if val is smaller than calibrated min use the calibrated min

   // Normalize left and right from 0 to 1023 based on calibrated min/max
   return (input - calibrated_min) * 1023 / (calibrated_max - calibrated_min);
}

void loop() {
  // Read analog values (will result in integer values between 0 and 1023)
  left = analogRead(pedalLeftPin); 
  right = analogRead(pedalRightPin); 
  thrust = analogRead(thrustLeverPin); 

  // You have 60 seconds time to push the pedals fully to calibrate the range 
  if (millis() - startMillis < 60000) {
    left_max = max(left_max, left);
    left_min = min(left_min, left);

    right_max = max(right_max, right);
    right_min = min(right_min, right);

    thrust_max = max(thrust_max, thrust);
    thrust_min = min(thrust_min, thrust);
    
    digitalWrite(LED_BUILTIN, LOW);
  }
  else
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }

  Serial.print("Left raw: ");
  Serial.println(left);
  Serial.print("Right raw: ");
  Serial.println(right);

  left = normalize_input(left_min, left_max, left);
  right = normalize_input(right_min, right_max, right);
  thrust = normalize_input(thrust_min, thrust_max, thrust);

  Serial.print("Left norm: ");
  Serial.println(left);
  Serial.print("Right norm: ");
  Serial.println(right);

  // Calculate difference and apply offset and scale to a range of 0-255
  rudderOutput = min(255, (left - right + 1023) / 8);
  Serial.print("Rudder Output: ");
  Serial.println(rudderOutput);

  // Calculate inverted output as the thurst lever angular sensor works rewards due to mounting position
  thrustOutput = min(255, 255 - thrust / 4);
  Serial.print("Thrust Output: ");
  Serial.println(thrustOutput);

  // Write output
  analogWrite(rudderOutPin, rudderOutput);
  analogWrite(thrustOutPin, thrustOutput);
  delay(10);
}
