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
#include "menu.h"
#include "libaudio.h"
#include "audioRaspi.h"

/*
 * 
 */


#define THRESHOLD 40 //Límite a partir del cual se mueve el LED encendido
#define JUGAR 5 //Uso 5 y 12, porque son las posiciones en las que se encuentra el puntero
#define TERMINA 12

int main(void) {

    raspinit(); //inicializo los componentes de la raspi

    juego_t componentes;
    inigame(juego_t, 1); //mando el nivel 1, ver si hay que elegir nivel
    inimat();

    coord_t evento;

    int i, conta = 0, ciclos = 0;
    int quit_game = 0;
    int nmadre = 0;
    int random;
    int naves = 1;
    srand(time(NULL));

    //    dcoord_t pos = {DISP_MAX_X >> 1, DISP_MAX_Y >> 1}; //pos es la posición actual, empieza en el centro de la matriz
    //    dcoord_t npos = pos; //npos es la próxima posición
    //    jcoord_t coord = {0, 0}; //coordenadas medidas del joystick


    while (quit_game != 1) {
        ininiv(componentes.nivel);
        //ciclo naves
        //nav_nod
        //coord_t ciclodisp(juego_t *juego, int i, int j)
        //numero random para nav disp

        random = (rand() % 10) + 21; //numero entre 20 y 30

        if (random == ciclos) {
            nmadre = 1;
        }

        naves = llamo_naves(&componentes, ciclos, naves);  //Cada cuantos ciclos muevo a los enemigos
        conta = llamo_naves(&componentes, ciclos, naves);  //Cuantas veces muevo a los enemigos por ciclo

        if (ciclos % naves == 0) {
            for (i = 0; i <= conta && quit_game = 0; i++) {
                quit_game = ciclonaves();
            }
        }
        if (ciclos % 2 == 0 && nmadre == 1) {
            nmadre = nav_nod();
        }
        //while (evento.objeto != NADA)  -> DONDE VA? ADENTRO DEL FOR O AFUERA?
        for (i = 0; i < LARGO; i++) {
            for (j = 0; j < ANCHO; j++) {
                evento = ciclodisp(&componentes, i, j);
                if (evento.objeto == NAVE_ENEMIGA) {
                    //audio 1
                    //verparams
                } else if (evento.objeto == NAVE_NODRIZA) {
                    //audio 2
                } else if (evento.objeto == JUGADOR) {
                    //audio 3
                }

            }
        }

        rasprint();


        if (joy_get_switch() == J_NOPRESS) {
            while (joy_get_switch() != J_NOPRESS) {
                quit_game = pause_menu();

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
        rasprint();

        if (componentes.naves == 0) {
            componentes.nivel++;
            matniv();
        }
        if (puntaje >= 1000) {//si tengo mas de 1000 puntos gano 1 vida y vuelvo el puntaje a 0
            componentes.vidas++;
            componentes.puntaje = 0;
        }
        if (componentes.vidas == 0 || quit_game = 1) {
            printscore(componentes.puntaje);
            usleep(3);
            quit_game = pause_menu();
            inigame(&componentes, 1); //inicializa en nivel 1
        }
    }

    /* End Simple-SDL2-Audio */
    endAudio();

    /* Important to free audio after ending Simple-SDL2-Audio because they might be referenced still */
    freeAudio(sound);
    freeAudio(music);

    return 0;
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

void rasprint() {//es el printmat para raspi
    static int disparo = 0;
    int i, j, obj;
    for (i = 0; i < ANCHO; ++i) {//copia el contenido de la matriz en el buffer de leds
        for (j = 0; j < ANCHO; ++j) {
            obj = getmat(i, j);
            if (obj == PSHOT || obj == ESHOT) {//si no es 0 prende el led
                if (disparo == 0) {
                    dcoord_t myPoint = {i, j};
                    disp_write(myPoint, D_ON);
                    disparo = 1;
                } else {
                    dcoord_t myPoint = {i, j};
                    disp_write(myPoint, D_OFF);
                    disparo = 0;
                }

            } else if (obj > 0 && obj != PSHOT && obj != ESHOT) {
                dcoord_t myPoint = {i, j};
                disp_write(myPoint, D_ON);
            } else {//lo apaga
                dcoord_t myPoint = {i, j};
                disp_write(myPoint, D_OFF);
            }
        }
    }
    disp_update();
}
/////////////////////////////////////////////////////////////////////////////////////////

int pause_menu() {

    int opcion;
    if (coord.y > THRESHOLD) { //&& npos.y < DISP_MAX_Y
        opcion = JUGAR;
        menu(opcion);
        quit_game = 0;
    } else if (coord.y > -THRESHOLD) {
        quit_game = 1;
        opcion = TERMINA;
        menu(opcion);
    }
    return quit_game;
}

//////////////////////////////////////////////////////////////////////////////////////////

int llamo_naves(juego_t* componentes, int ciclos, int naves) {
    static int funcion = 1;
    int conta = 0;
    int p=0;
    componentes->nivel>=5?p=5:p=componentes->naves;
    //A TENER EN CUENTA nivel, cant de naves, catidad de veces que llame a la funcion
    if (funcion % 2 == 0) //Cuantas veces llamo a la funcion que mueve a las naves enemigas
    {
        if (naves > 1)
        {
            conta=1;
        }
        else{
            
        }
    } else //Cada cuantos ciclos llamo a la funcion que mueve a las naves enemigas
    {
        
    }


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