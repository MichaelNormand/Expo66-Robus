#include <CapteurCouleur.h>

//Ne pas oublier de mettre l'endroit ou tout est branché
#define s0 1
#define s1 2
#define s2 3
#define s3 4
#define out 5

int frequence = 0;


void SetupCapteurCouleur()
{
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);

  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);
}

int CapteurCouleurRouge()
{
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);

    frequence = pulseIn(out, LOW);//Est-ce que ça fait la même affaire si on met HIGH?

    frequence = map(frequence, 25, 72, 255, 0); //Potentiellement à changer, valeurs théoriques

    return frequence;
}

int CapteurCouleurBleu()
{
    digitalWrite(s2, LOW);
    digitalWrite(s3, HIGH);

    frequence = pulseIn(out, LOW);

    frequence = map(frequence, 25, 70, 255, 0); //Potentiellement à changer, valeurs théoriques

    return frequence;
}

int CapteurCouleurVert()
{
    digitalWrite(s2, HIGH);
    digitalWrite(s3, HIGH);

    frequence = pulseIn(out, LOW);

    frequence = map(frequence, 30, 90, 255, 0); //Potentiellement à changer, valeurs théoriques

    return frequence;
}
