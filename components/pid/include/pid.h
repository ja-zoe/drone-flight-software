#pragma once
#include <stdint.h>

typedef struct {
    /* Controller Gains */
    float Kp;
    float Ki;
    float Kd;

    /* Sampling Time (seconds) */
    float dt;

    /* Output Constraints (Anti-windup limits) */
    float limMin;
    float limMax;

    /* Integrator and Derivative Memories */
    float integrator;
    float prevMeasurement; 
} PIDController;

void PIDController_Init(PIDController *pid, float Kp, float Ki, float Kd, float dt, float limMin, float limMax);
float PIDController_Update(PIDController *pid, float setpoint, float measurement);