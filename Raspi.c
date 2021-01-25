/* 
 * File:   Raspi.c
 * Author: magali
 *
 * Created on January 11, 2021, 7:55 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "joydrv.h"
#include "termlib.h"
#include "disdrv.h"
#include "backend.h"

/*
 * 
 */

#define THRESHOLD 40 //Límite a partir del cual se mueve el LED encendido

int main(void) 
{
    joy_init(); //inicializa el joystick
    disp_init(); //inicializa el display
    disp_clear(); //limpia todo el display
    dcoord_t pos = {DISP_MAX_X >> 1, DISP_MAX_Y >> 1}; //pos es la posición actual, empieza en el centro de la matriz
    dcoord_t npos = pos; //npos es la próxima posición
    jcoord_t coord = {0, 0}; //coordenadas medidas del joystick
    
        

        
        if (coord.x > THRESHOLD && npos.x < DISP_MAX_X) {
            if (coord.y < -THRESHOLD && npos.y < DISP_MAX_Y) {
            //llamo fun der y disp
            }
            else
            {
                //llamo fun der
            }
        }
        if (coord.x < -THRESHOLD && npos.x > DISP_MIN) {
            if (coord.y < -THRESHOLD && npos.y < DISP_MAX_Y) {
            //llamo fun izq y disp
            }
            else
            {
                //llamo izq
            }
        }
        if (coord.y > THRESHOLD && npos.y > DISP_MIN) {
            npos.y--;
        }
        if (coord.y < -THRESHOLD && npos.y < DISP_MAX_Y) {
            npos.y++;
        }
    
        disp_write(pos, D_OFF); //apaga la posición vieja en el buffer
        disp_write(npos, D_ON); //enciende la posición nueva en el buffer
        pos = npos; //actualiza la posición actual

    } while (joy_get_switch() == J_NOPRESS); //termina si se presiona el switch
}
