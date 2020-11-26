#ifndef CONFIG_H
#define CONFIG_H

//Return status
#define NOT_DONE 0
#define DONE 1

//Movement correction
#define FORWARD 2
#define STOP 0
#define HALTED 1
#define ROTATE 3

#define ON 1
#define OFF 0

//Robus Mode
#define MANUAL 1
#define AUTO 0

//Gripper
#define UP 1
#define DOWN 0
#define OPEN 1
#define CLOSE 0

//Gripper
#define GRIPPER 0
#define WRIST 1
#define UP_VAL 120
#define DOWN_VAL 180

#define DIS 0
#define DEG 1
#define DIR 2
#define STATE 3

#define GET 0
#define SET 1

#define INIT 0
#define START 1
#define RESET 2
#define SWEEPSTOP 3

#endif