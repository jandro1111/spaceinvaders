#ifndef RASPI_H
#define RASPI_H
#include <stdio.h>
#include "termlib.h"
#include "disdrv.h"
#include "joydrv.h"
#include "backend.h"
void printscore(int [][ANCHO],int );//para raspi escribe el puntaje
void printnum(int [][ANCHO],int,int[]);//funcion local para printscore
void menu (int [][ANCHO]);//para raspi printea el menu
void rasprint (int [][ANCHO]);//imprime en la pantalla de leds
void raspinit(void);//inicializa librerias
#endif
