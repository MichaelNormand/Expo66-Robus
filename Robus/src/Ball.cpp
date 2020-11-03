#include "Ball.h"
#include "Distance.h"

void BALL_Init()
{
    BoardInit();
    Serial.begin(9600);

    int couleur;

    //depart signal ?
    AddLength(5);
    delay(2000);
    AddLength(30);
    AddRotation(90, ROTATE_RIGHT);
    AddLength(25);
    AddRotation(90, ROTATE_LEFT);
    AddLength(180);
    delay(2000);
    couleur = 2; // test

    // fermer pince
    // lever balle
    
        if(couleur == 0){ //jaune
            AddLength(100);
            AddRotation(90, ROTATE_RIGHT);
            AddLength(20);
        }
        else if(couleur == 1){ // bleu
            AddLength(175);  
            AddRotation(90, ROTATE_LEFT);
            AddLength(30);
        }
        else if(couleur == 2){ // rose
            AddLength(270);
            AddRotation(90, ROTATE_RIGHT);
            AddLength(5);
        }
        
   
    // descendre balle
    // ouvrir pince
}
