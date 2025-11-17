#define IN1  32  // H-bridge input 1
#define IN2  33  // H-bridge input 2
#define A    25  // Encoder A (ESP32 supports internal pull-up)
#define B    26  // Encoder B (ESP32 supports internal pull-up)

int A_data = 0;
int B_data = 0;

String command;

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Use INPUT_PULLUP if your encoder needs pull-ups (typical for mechanical/OC encoders)
  // Otherwise, keep as INPUT if the encoder actively drives high/low.
  pinMode(A, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);

  // Optional: set a default direction
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "C") {
      // clockwise rotation
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    } else if (command == "A") {
      // anticlockwise rotation
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    }
  }

  // Read encoder channels
  A_data = digitalRead(A);
  B_data = digitalRead(B);
1
  // Serial Plotter: either labeled consistent keys or plain numbers.
  // Option 1: labels (consistent every line)
  // Serial.print("A:"); Serial.print(A_data); Serial.print(" B:"); Serial.println(B_data);

  // Option 2: simple numeric format (recommended)
  Serial.print(A_data);
  Serial.print(' ');
  Serial.println(B_data);

  delay(5); // tame the plot rate
}