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
#endif
