#ifndef RASPI_H
#define RASPI_H
#include <stdio.h>
#include "termlib.h"
#include "disdrv.h"
#include "joydrv.h"
#include "backend.h"


void menu (int[][ANCHO]);//para raspi printea el menu
void rasprint (void);//imprime en la pantalla de leds
void raspinit(void);//inicializa librerias
void printscore(int [][ANCHO],int );//para raspi escribe el puntaje
void printnum(int [][ANCHO],int,int[]);//funcion local para printscore
void matniv(int [][ANCHO]);//para raspi, esccribe level up en la matriz


#endif


{0,1,0,1,0},
{1,0,1,0,1},
{0,1,0,1,0},
{0,0,1,0,0}, 