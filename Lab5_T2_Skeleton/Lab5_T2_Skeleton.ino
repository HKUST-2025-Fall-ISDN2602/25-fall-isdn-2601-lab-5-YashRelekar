// -------------------- Pins --------------------
#define IN1  27   // Motor L input 1
#define IN2  32  // Motor L input 2
#define AL   34  // Encoder A of Motor L
#define BL   35  // Encoder B of Motor L

#define IN3  16  // Motor R input 1
#define IN4  17  // Motor R input 2
#define AR   36  // Encoder A of Motor R
#define BR   13  // Encoder B of Motor R

// -------------------- Encoder Data --------------------
int AL_data = 0;
int BL_data = 0;

int AR_data = 0;
int BR_data = 0;

String command;

// -------------------- Motor Control Functions --------------------
void moveForward() {
  // Left Motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Right Motor forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  // Left Motor backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  // Right Motor backward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnRight() {
  // Left Motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Right Motor backward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  // Left Motor backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  // Right Motor forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// -------------------- Setup --------------------
void setup() {
  Serial.begin(115200);

  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Encoder pins
  pinMode(AL, INPUT);
  pinMode(BL, INPUT);
  pinMode(AR, INPUT);
  pinMode(BR, INPUT);

  // Start stopped
  stopMotors();
}

// -------------------- Main Loop --------------------
void loop() {
  // --------- Read serial command ---------
  if (Serial.available() > 0) {
    command = Serial.readStringUntil('\n'); // read line
    command.trim();                         // remove spaces, \r, etc.

    if (command == "F") {
      moveForward();
    } else if (command == "B") {
      moveBackward();
    } else if (command == "R") {
      turnRight();
    } else if (command == "L") {
      turnLeft();
    } else if (command == "S") {
      stopMotors();
    }
  }

  // --------- Read Encoder Signals ---------
  AL_data = digitalRead(AL);
  BL_data = digitalRead(BL);

  AR_data = digitalRead(AR);
  BR_data = digitalRead(BR);

  // --------- Print for Serial Plotter ---------
  // Format: label:value separated by commas, all on one line
  Serial.print("AL:");
  Serial.print(AL_data);
  Serial.print(",");

  Serial.print("BL:");
  Serial.print(BL_data);
  Serial.print(",");

  Serial.print("AR:");
  Serial.print(AR_data);
  Serial.print(",");

  Serial.print("BR:");
  Serial.print(BR_data);
  Serial.println(); // end of line for Serial Plotter

  //Delay 
  delay(5);
}