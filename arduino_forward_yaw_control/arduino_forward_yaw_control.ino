int m2i1 = 7;
int m2i2 = 6;
int m2e  = 9;

int m1i1 = 5;
int m1i2 = 4;
int m1e  = 3;

void setup() {
  // Set motor pins as output
  pinMode(m1i1, OUTPUT);
  pinMode(m1i2, OUTPUT);
  pinMode(m1e, OUTPUT);
  
  pinMode(m2i1, OUTPUT);
  pinMode(m2i2, OUTPUT);
  pinMode(m2e, OUTPUT);

  // Start serial at the same baud rate
  Serial.begin(9600);
  
  // Initialize motors to off
  stopMotors();
}

void loop() {
  if (Serial.available() >= 2) {
    int left_pwm = Serial.read();
    int right_pwm = Serial.read();

    // Clamp values
    left_pwm = constrain(left_pwm, 0, 255);
    right_pwm = constrain(right_pwm, 0, 255);

    // Run motors forward
    runMotorForward(m1i1, m1i2, m1e, right_pwm); // Right motor
    runMotorForward(m2i1, m2i2, m2e, left_pwm);  // Left motor

    // Print debug info
    Serial.print("Left PWM: ");
    Serial.print(left_pwm);
    Serial.print(" | Right PWM: ");
    Serial.println(right_pwm);
  }
}

void runMotorForward(int i1, int i2, int e, int pwm) {
  digitalWrite(i1, LOW);
  digitalWrite(i2, HIGH);
  analogWrite(e, pwm);
}

void stopMotors() {
  digitalWrite(m1i1, LOW);
  digitalWrite(m1i2, LOW);
  analogWrite(m1e, 0);

  digitalWrite(m2i1, LOW);
  digitalWrite(m2i2, LOW);
  analogWrite(m2e, 0);
}
