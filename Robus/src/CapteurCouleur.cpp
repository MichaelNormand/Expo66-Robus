#include <CapteurCouleur.h>
#include <Wire.h>


 Adafruit_TCS34725 COLORSENSOR_Setup()
{
    Adafruit_TCS34725 tcs = Adafruit_TCS34725();

    return tcs;
}

int COLORSENSOR_Update(Adafruit_TCS34725 tcs)
{
    uint16_t r, g, b, c;
    int RJB; // ou 0=jaune, 1=bleu, 2=rouge
  
    tcs.getRawData(&r, &g, &b, &c);

    Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
    Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
    Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
    Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
    Serial.println(" ");

    if(r == g && r > b){
        Serial.print("JAUNE");
        return 0; 
    }
    else if(g > b && b > r)
    {
        Serial.print("BLEU");
        return 1;
    }
    else if(r > g && g == b)
    {
        Serial.print("ROUGE");
        return 2;
    }

}