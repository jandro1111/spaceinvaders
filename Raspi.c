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
#define JUGAR 5 //Uso 5 y 12, porque son las posiciones en las que se encuentra el puntero
#define TERMINA 12

int main(void) {

    raspinit(); //inicializo los componentes de la raspi

    int space[LARGO][ANCHO]; //CREO QUE NO ES NECESARIA, CAMBIAR FUNCIONES

    juego_t componentes;
    inigame(juego_t, 1); //mando el nivel 1, ver si hay que elegir nivel
    inimat();

    coord_t evento;

    int i, conta = 0, ciclos = 0;
    int quit_game = 0;
    int nmadre = 0;
    int random;
    int naves = 0;
    srand(time(NULL));

    //    dcoord_t pos = {DISP_MAX_X >> 1, DISP_MAX_Y >> 1}; //pos es la posición actual, empieza en el centro de la matriz
    //    dcoord_t npos = pos; //npos es la próxima posición
    //    jcoord_t coord = {0, 0}; //coordenadas medidas del joystick


    while (quit_game != 1) {
        ininiv(componentes.nivel);
        //ciclo naves
        //nav_nod
        //coord_t ciclodisp(juego_t *juego, int i, int j)
        //

        random = (rand() % 10) + 21; //numero entre 20 y 30

        if (random == ciclos) {
            nmadre = 1;
        }
        naves = llamo_naves(&componentes, ciclos);

        if (ciclos % naves == 0) {
            for (i = 0; i <= conta; i++) {
                ciclosnaves();
            }
            if (ciclos % 2 == 0 && nmadre == 1) {
                nmadre = nav_nod();
            }

            rasprint(space);
        }

        if (joy_get_switch() == J_NOPRESS) {
            while (joy_get_switch() != J_NOPRESS) {
                pause_menu(space, quit_game);

            } //do nothing 
        } else {
            if (coord.x > THRESHOLD) {
                if (coord.y < THRESHOLD) {
                    pmov(4, &componentes);
                } else {
                    pmov(1, &componentes);
                }
            } else if (coord.x < -THRESHOLD) {
                if (coord.y < THRESHOLD) {
                    pmov(5, &componentes);
                } else {
                    pmov(2, &componentes);
                }
            } else if (coord.y > THRESHOLD) {
                pmov(3, &componentes);
            }
            //        if (coord.y < -THRESHOLD && npos.y < DISP_MAX_Y) {
            //            npos.y++;
            //        }
            //    }
        }
        ciclos++;

        if (componentes.naves == 0) {
            componentes.nivel++;
            matniv(space);
        }
        if (puntaje >= 1000) {//si tengo mas de 1000 puntos gano 1 vida y vuelvo el puntaje a 0
            componentes.vidas++;
            componentes.puntaje = 0;
        }
        if (componentes.vidas == 0) {
            printscore(space, componentes.puntaje);
            usleep(3);
            pause_menu(space, quit_game);
            inigame(&componentes, 1); //inicializa en nivel 1
        }
    }
}
/////////////////////////
/*
 
 space[5][0]=space[5][1]=1;//escribo el puntero opcion 1 play
 *space[12][0]=space[12][1]=1;//escribo el puntero opcion 2 quit
 * 
 * acordate que tenes la funcion printscore cuando te moris
 */
/////////////////////////////////////////////////////////

void raspinit(void) {
    joy_init(); //inicializa el joystick
    disp_init(); //inicializa el display
    disp_clear(); //limpia todo el display
}
/////////////////////////////////////////////////////////////

void rasprint(int space [][ANCHO]) {//es el printmat para raspi
    int i, j, obj;
    for (i = 0; i < ANCHO; ++i) {//copia el contenido de la matriz en el buffer de leds
        for (j = 0; j < ANCHO; ++j) {
            obj = getmat(i, j);
            if (obj > 0) {//si no es 0 prende el led
                dcoord_t myPoint = {i, j};
                disp_write(myPoint, D_ON);
            } else {//lo apaga
                dcoord_t myPoint = {i, j};
                disp_write(myPoint, D_ON);
            }
        }
    }
    disp_update();
}
/////////////////////////////////////////////////////////////////////////////////////////

int pause_menu(space[][ANCHO], int quit_game) {

    int opcion;
    if (coord.y > THRESHOLD) { //&& npos.y < DISP_MAX_Y
        opcion = JUGAR;
        menu(space, opcion);
        quit_game = 0;
    } else if (coord.y > -THRESHOLD) {
        quit_game = 1;
        opcion = TERMINA;
        menu(space, opcion);
    }
    return quit_game;
}

//////////////////////////////////////////////////////////////////////////////////////////

int llamo_naves(juego_t* componentes, int ciclos) {
    int conta = 0;
    //A TENER EN CUENTA nivel, cant de naves, catidad de veces que llame a la funcion
    if (componentes->naves <)


        return conta;
}
/*
 * AL PRINCIPIO TENGO QUE LLAMARLO UNA CADA 2 O CADA 3 VECES QUE SE MUEVE EL JUGADOR
 * LA PUEDO LLAMAR SIEMPRE QUE SEA PAR O MULTIPLO DE 3 Y MAS ADELANTE AUMENTAR EL NUMERO ADENTRO DEL FOR PARA COMPENSAR
 * 
 * 
 * 
 * LA NAVE MADRE SE LLAMA CADA 2 DE JUGADOR
 * 
 * LAS BALAS SE LLAMAN 3 O 4 VECES POR MOV DE JUGADOR
 *  
 * TENGO QUE ACTUALIZAR EL DISPLAY CADA VEZ QUE MUEVO A LOS ENEMIGOS/BALAS/NAVE MADRE  (?)
 * TENGO QUE METER TODO ADENTRO DE UN FOR Y AHI HACER SEGUN SEA PAR O MULTIPLO DE X NUMERO
 */