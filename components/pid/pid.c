#include "pid.h"

void PIDController_Init(PIDController *pid, float Kp, float Ki, float Kd, float dt, float limMin, float limMax) {
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->dt = dt;
    pid->limMin = limMin;
    pid->limMax = limMax;
    
    pid->integrator = 0.0f;
    pid->prevMeasurement = 0.0f;
}

float PIDController_Update(PIDController *pid, float setpoint, float measurement) {
    /* 1. Calculate error */
    float error = setpoint - measurement;

    /* 2. Proportional Term */
    float proportional = pid->Kp * error;

    /* 3. Integral Term (Discrete trapezoidal or rectangular integration) */
    pid->integrator += pid->Ki * error * pid->dt;

    /* Anti-windup: Clamp the integrator to avoid saturation delays */
    if (pid->integrator > pid->limMax) {
        pid->integrator = pid->limMax;
    } else if (pid->integrator < pid->limMin) {
        pid->integrator = pid->limMin;
    }

    /* 4. Derivative Term (Calculated on measurement to prevent step-change spikes) */
    float derivative = -pid->Kd * (measurement - pid->prevMeasurement) / pid->dt;

    /* 5. Compute total output */
    float output = proportional + pid->integrator + derivative;

    /* 6. Clamp final controller output to hardware limits */
    if (output > pid->limMax) {
        output = pid->limMax;
    } else if (output < pid->limMin) {
        output = pid->limMin;
    }

    /* 7. Keep history track for next iteration */
    pid->prevMeasurement = measurement;

    return output;
}