/*
 * (c)Steffen Schütte 2025
 * License: CC0
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

int outPin = 9;

int left = 0;
float left_min = 0;
float left_max = 0;
int right = 0;
float right_min = 0;
float right_max = 0;



int output = 0;

void setup() {
  Serial.begin(9600);
  delay(1000);   

  left = analogRead(pedalLeftPin); 
  right = analogRead(pedalRightPin);
  left_min = left;
  left_max = left;
  right_min = right;
  right_max = right;       
}

// Norm left and right from 0 to 1024 based on min/max
int normalize_input(float min, float max, int val) 
{
  return (val - min) * 1024/(max-min);
}

void loop() {
  // Read analog values
  left = analogRead(pedalLeftPin); 
  right = analogRead(pedalRightPin); 

  left_max = max(left_max, left);
  left_min = min(left_min, left);

  right_max = max(right_max, right);
  right_min = min(right_min, right);

  Serial.print("Left raw: ");
  Serial.println(left);
  Serial.print("Right raw: ");
  Serial.println(right);

  
  left = normalize_input(left_min, left_max, left);
  right = normalize_input(right_min, right_max, right);

  Serial.print("Left norm: ");
  Serial.println(left);
  Serial.print("Right norm: ");
  Serial.println(right);

  // Calculate difference and apply offset and scale to a range of 0-255
  output = (left-right+1023)/8;
  Serial.print("Output: ");
  Serial.println(output);

  // Write output
  analogWrite(outPin, output);
  delay(50);
}
