#include "Ball.h"
#include "Distance.h"

void BALL_Init()
{
    BoardInit();
    Serial.begin(9600);

    int couleur;


    //depart signal ?
    AddLength(5);
    delay(1000);
    AddLength(30);
    AddRotation(90, ROTATE_RIGHT);
    AddLength(25);
    AddRotation(90, ROTATE_LEFT);
    AddLength(45);
    // regarder couleur + stocker
/*
        if(jaune){
            couleur = 0;
        }else if(bleu){
            couleur = 1;
        }else if(rose){
            couleur = 2;
        }
*/

    couleur = 1; // test

    AddLength(140);
    // fermer pince
    // lever balle
    
        if(couleur == 0){ //jaune
            AddLength(90);
            AddRotation(90, ROTATE_RIGHT);
            AddLength(25);
        }
        else if(couleur == 1){ // bleu
            AddLength(190);  
            AddRotation(90, ROTATE_LEFT);
            AddLength(25);
        }
        else if(couleur == 2){ // rose
            AddLength(270);
            AddRotation(90, ROTATE_RIGHT);
            AddLength(25);
        }
        
    // descendre balle
    // ouvrir pince
}
