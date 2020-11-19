#ifndef SONAR_H
#define SONAR_H

#define SONAR_ECHOPIN 2
#define SONAR_TRIGPIN 3

void sonar_init(void);
void sonar_update(void);
float sonar_get_data(void);

#endif