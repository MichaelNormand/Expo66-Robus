int vector = sqrt(x^2 + y^2) >> 7;          //Used to adjust speed proportionnally
int dirMotor0;
int dirMotor1;
float forceMotor0;
float forceMotor1;

if(y >= 0){                                 //Foward
    dirMotor0 = 1;           
    dirMotor1 = 1;
}
else {                                      //Backwards
    dirMotor0 = -1;
    dirMotor1 = -1;
}

if(x >= 0){                                 //Right turn            
    forceMotor0 = (vector * dirMotor0);     //  Left motor full force
    forceMotor1 = (y * vector);             //  Right motor proportionnal to y value
}
else{                                       //Left turn   
    forceMotor0 = (y * vector);             //  Left motor proportionnal to y value
    forceMotor1 = (vector * dirMotor1);     //  Right motor full force
}

//dirMotor is not applied to the motor that is proportionnal because 'y' already
//  holds the right direction

// Bit operation (>> 7) to devide by 128 and get a value between 0 and 1