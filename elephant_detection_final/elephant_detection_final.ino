// Define pins (constants)
#define PIR 3         // PIR motion sensor pin
#define TRIG 9        // Ultrasonic sensor trigger pin
#define ECHO 10       // Ultrasonic sensor echo pin
#define VIBRATION A0  // Vibration sensor analog pin
#define LED 13        // LED pin for indication

// Threshold for vibration detection
const int vibrationThreshold = 300; // Adjust based on your sensor's sensitivity

// Function to print the alert message on spotting elephant
// Takes distance as parameter (in cm)
void elephantSpotAlert(float distance) {
  Serial.print("Elephant has been spotted at a distance of: ");
  Serial.print(distance);
  Serial.println(" cm");
}

// Function for setting up serial monitor and other components
// Returns no value (void)
void setup() {
  Serial.begin(9600);        // Set up serial monitor - baud rate is 9600
  Serial.println("System is ready");
  pinMode(PIR, INPUT);       // Set PIR to input
  pinMode(TRIG, OUTPUT);     // TRIG pin to output
  pinMode(ECHO, INPUT);      // ECHO pin to input
  pinMode(LED, OUTPUT);      // Set LED pin as output
}

// Function to measure the proximity of elephant (returns a float value)
float measureProximity() {
  long duration;
  float distance;
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration * 0.0343) / 2; // Formula to calculate distance in cm
  return distance;
}

// Function to detect motion with PIR sensor (returns true if motion is detected)
bool detectMotion() {
  return digitalRead(PIR) == HIGH;
}

// Function to detect vibration (returns true if vibration above threshold is detected)
bool detectVibration() {
  int vibrationValue = analogRead(VIBRATION);
  return vibrationValue > vibrationThreshold;
}

// Function that goes on executing (always true)
// Returns no value
void loop() {
  // Check if motion is detected by PIR and vibration is detected
  if (detectMotion() && detectVibration()) {
    Serial.println("Motion and Vibration detected!"); // Debug statement
    float proximity = measureProximity();
    elephantSpotAlert(proximity);
    digitalWrite(LED, HIGH); // Turn on LED
    delay(4000); // Time delay between two outputs
    digitalWrite(LED, LOW);  // Turn off LED
  }
}
