// FilteredPID.h
#ifndef FILTERED_PID_H
#define FILTERED_PID_H

class PIDController {
public:
    float Kp;
    float Ki;
    float Kd;
    float N; // Derivative filter coefficient

    float minOutput = 0;
    float maxOutput = 255;

    PIDController() {}

    void reset() {
        integral = 0;
        prevError = 0;
        derivative = 0;
    }

    float compute(float setpoint, float measurement, float dt) {
        float error = setpoint - measurement;

        // Proportional term
        float P = Kp * error;

        // Integral term
        integral += error * dt;
        float I = Ki * integral;

        // Filtered Derivative term
        float raw_derivative = (error - prevError) / dt;
        float alpha = N * dt / (1.0f + N * dt);
        derivative = alpha * raw_derivative + (1.0f - alpha) * derivative;
        float D = Kd * derivative;

        prevError = error;

        float output = P + I + D;
        if (output > maxOutput) output = maxOutput;
        else if (output < minOutput) output = minOutput;

        return output;
    }

private:
    float integral = 0;
    float prevError = 0;
    float derivative = 0;
};

#endif // FILTERED_PID_H

/* EXAMPLE USAGE

#include "FilteredPID.h"

PIDController pid;
unsigned long prevTime = 0;

void setup() {
  pid.Kp = 0.7748;
  pid.Ki = 0.0103;
  pid.Kd = 13.0115;
  pid.N  = 259.1824;
  pid.minOutput = 0;
  pid.maxOutput = 255;

  prevTime = millis();
}

void loop() {
  unsigned long now = millis();
  float dt = (now - prevTime) / 1000.0;
  prevTime = now;

  float measurement = getIMUReading(); // Replace with your actual function
  float control = pid.compute(0.0, measurement, dt);

  ledcWrite(pwmChannel, (int)control);
}

*/