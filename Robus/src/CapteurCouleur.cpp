#include <CapteurCouleur.h>

//Ne pas oublier de mettre l'endroit ou tout est branché
#define s0_1 1
#define s1_1 2
#define s2_1 3
#define s3_1 4
#define out_1 5
#define s0_2 1
#define s1_2 2
#define s2_2 3
#define s3_2 4
#define out_2 5

int frequence = 0;

void SetupCapteurCouleur(int capteur)
{
    if (capteur == 1)
    {
        pinMode(s0_1, OUTPUT);
        pinMode(s1_1, OUTPUT);
        pinMode(s2_1, OUTPUT);
        pinMode(s3_1, OUTPUT);
        pinMode(out_1, INPUT);

        digitalWrite(s0_1, HIGH);
        digitalWrite(s1_1, LOW);
    }

    else if (capteur == 2)
    {
        pinMode(s0_2, OUTPUT);
        pinMode(s1_2, OUTPUT);
        pinMode(s2_2, OUTPUT);
        pinMode(s3_2, OUTPUT);
        pinMode(out_2, INPUT);

        digitalWrite(s0_2, HIGH);
        digitalWrite(s1_2, LOW);
    }

    else
    {
        Serial.println("Le capteur choisi n'existe pas");
    }
}

int CapteurCouleurRouge(int capteur)
{
    if (capteur == 1)
    {
        digitalWrite(s2_1, LOW);
        digitalWrite(s3_1, LOW);

        frequence = pulseIn(out_1, LOW); //Est-ce que ça fait la même affaire si on met HIGH?
    }

    else if (capteur == 2)
    {
        digitalWrite(s2_2, LOW);
        digitalWrite(s3_2, LOW);

        frequence = pulseIn(out_2, LOW); //Est-ce que ça fait la même affaire si on met HIGH?
    }

    frequence = map(frequence, 25, 72, 255, 0); //Potentiellement à changer, valeurs théoriques

    return frequence;
}

int CapteurCouleurBleu(int capteur)
{
    if (capteur == 1)
    {
        digitalWrite(s2_1, LOW);
        digitalWrite(s3_1, HIGH);

        frequence = pulseIn(out_1, LOW); //Est-ce que ça fait la même affaire si on met HIGH?
    }

    else if (capteur == 2)
    {
        digitalWrite(s2_2, LOW);
        digitalWrite(s3_2, HIGH);

        frequence = pulseIn(out_2, LOW); //Est-ce que ça fait la même affaire si on met HIGH?
    }

    frequence = map(frequence, 25, 70, 255, 0); //Potentiellement à changer, valeurs théoriques

    return frequence;
}

int CapteurCouleurVert(int capteur)
{
    if (capteur == 1)
    {
        digitalWrite(s2_1, HIGH);
        digitalWrite(s3_1, HIGH);

        frequence = pulseIn(out_1, LOW); //Est-ce que ça fait la même affaire si on met HIGH?
    }

    else if (capteur == 2)
    {
        digitalWrite(s2_2, HIGH);
        digitalWrite(s3_2, HIGH);

        frequence = pulseIn(out_2, LOW); //Est-ce que ça fait la même affaire si on met HIGH?
    }

    frequence = map(frequence, 30, 90, 255, 0); //Potentiellement à changer, valeurs théoriques

    return frequence;
}
