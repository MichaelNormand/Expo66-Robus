#include <PID.h>

void PID(float *speed, float *encoder, int mode)
{
    float errorLeft;
    float errorRight;

    float speedRatio;
    float encoderRatio;

    //KP
    speedRatio = 1;

    if(mode == MANUAL)
        speedRatio = (speed[RIGHT] + 0.001) / (speed[LEFT] + 0.001);
        
    encoderRatio = (encoder[RIGHT] + 0.001) / (encoder[LEFT] + 0.001);

    errorLeft = (encoderRatio - speedRatio) / 2;
    errorRight = errorLeft * -1;

    if(((int)encoder[LEFT] ^ (int)encoder[RIGHT]) < 0)
    {
        if(encoder[RIGHT] >= 0)
            errorLeft = (speedRatio + encoderRatio) / 2;
        else
            errorLeft = (speedRatio + encoderRatio) / -2;
        errorRight = errorLeft;   
    }
    
    speed[LEFT] = speed[LEFT] + (KP * errorLeft);
    speed[RIGHT] = speed[RIGHT] + (KP * errorRight);
}