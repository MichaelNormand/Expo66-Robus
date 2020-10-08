#ifndef CONFIG_H
#define CONFIG_H

#define MOTOR0 0
#define MOTOR1 1
#define STEP  20    // Resolution for ENCODER_Read().
#define RPS   100   // RPS = Rotation per step -> just like RPM but with a different time base.

#define KP 0.001    // Constants need tuning.
#define KI 0.007
#define KD 0.004

#define SPEED0 0.3
#define SPEED1 0.3

#define NOT_DONE 0
#define DONE 1

#define ROTATE_LEFT 1
#define ROTATE_RIGHT -1
#define MOVE_SAMPLE_DELAY 10
#define LENGTH 0
#define ROTATION 1

#define OPENED 1
#define CLOSED 0

#endif