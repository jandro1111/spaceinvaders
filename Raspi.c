/* 
 * File:   Raspi.c
 * Author: magali
 *
 * Created on January 11, 2021, 7:55 PM
 */
//////////////////////////////////////////////////////////////
//                      HEADERS                             //
//////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "joydrv.h"
#include "termlib.h"
#include "disdrv.h"
//#include "libaudio.h"

#include "backend.h"
#include "menu.h"
//#include "audioRaspi.h"

////////////////////////////////////////////////////////////////
//                       FUNCIONES                            //
////////////////////////////////////////////////////////////////

///////////////// RASPINIT ///////////////
void raspinit(void);        //Inicializa el joystick y el display


///////////////// RASPRINT ////////////////
void rasprint(int matriz);  //Imprime la matriz elegida

/*
 * Recibe un int que le indica que matriz debe imprimir, la del menu o la del juego
 */


//////////////// PAUSE_MENU ////////////////
int pause_menu(void);   //Menu de pausa

/*
 * Devuelve un int que indica si se eligio terminar el juego
 */


/////////////// LLAMO_NAVES ////////////////
int llamo_naves(juego_t* componentes, int ciclos, int naves); 
//Indica cada cuantos ciclos y cuantas veces por ciclo se llama a la funcion que mueve a los enemigos

/*
 * Recibe un puntero a la estructura que tiene todos los componentes del juego,
 *  un int (ciclos) con la cantidad de ciclos que se ha realizado y otro int (naves) 
 *  que dice cada cuantos ciclos se llama a la funcion que mueve las naves
 * Devuelve un int
 */


////////////// CONTROL_AUDIO ////////////////
int control_audio(juego_t * componentes, int* nmadre);  
//Comprueba si hubo una colision y reproduce el audio correspondiente

/*
 * Recibe un puntero a la estructura con los componentes del juego y un puntero int a nmadre
 *  que dice si hay o no una nave madre en juego
 * Devuelve un int para indicar si hubo colision o no
 */


///////////////////////////////////////////////////////////////
//                      DEFINICIONES                         //
///////////////////////////////////////////////////////////////
#define THRESHOLD 40    //Límite a partir del cual se mueve el LED encendido
#define JUGAR 5         //Uso 5 y 12, porque son las posiciones en las que se encuentra el puntero
#define TERMINA 12
#define MAX_ENEM 16     //Cantidad maxima de enemigos en juego
#define MENU 2          //Opcion menu y juego para saber que matriz voy a tener que llamar a imprimir
#define GAME 1



/////////////////////////////////////////////////////////////
//                       CODIGO                            //
/////////////////////////////////////////////////////////////

int main(void) {

    raspinit(); //inicializo los componentes de la raspi



    juego_t componentes;
    inigame(&componentes, 1); //mando el nivel 1, ver si hay que elegir nivel
    inimat();

    int i, conta = 0, ciclos = 0, found = 1;
    int quit_game = 0;
    int nmadre = 0;
    int random;
    int naves = 1;
    int get_disp = 0;
    srand(time(NULL));

    
    jcoord_t coord = {0, 0}; //coordenadas medidas del joystick


    while (quit_game != 1) {
        ininiv(componentes.nivel);
        
        if (ciclos < 20) {
            random = (rand() % 10) + 21; //numero entre 20 y 30
        }
        if (random == ciclos) {
            nmadre = 1;
            random += (rand() % 10) + 21;
        }

        get_disp += (rand() % 4); //suma numeros del 0 al 3 para conseguir el disparo de los enemigos

        if (ciclos == get_disp) {
            navdisp();
        }

        naves = llamo_naves(&componentes, ciclos, naves); //Cada cuantos ciclos muevo a los enemigos
        conta = llamo_naves(&componentes, ciclos, naves); //Cuantas veces muevo a los enemigos por ciclo

        if (ciclos % naves == 0) {
            for (i = 0; i <= conta && quit_game == 0; i++) {
                quit_game = ciclonaves();
            }
        }
        if (ciclos % 2 == 0 && nmadre == 1) {
            nmadre = nav_nod();
        }
        
        while (found != 0) 
        {
            found = control_audio(&componentes, &nmadre);
            verparams(&componentes);
        }


        rasprint(GAME);

        coord = joy_get_coord(); //Guarda las coordenadas medidas
        if (joy_get_switch() == J_NOPRESS) {
            while (joy_get_switch() != J_NOPRESS) {
                quit_game = pause_menu();
                rasprint(MENU);

            }
        } else {
            if (coord.x > THRESHOLD) {
                if (coord.y < THRESHOLD) {
                    componentes.mov = 4;
                    pmov(&componentes);
                } else {
                    componentes.mov = 1;
                    pmov(&componentes);
                }
            } else if (coord.x < -THRESHOLD) {
                if (coord.y < THRESHOLD) {
                    componentes.mov = 5;
                    pmov(&componentes);
                } else {
                    componentes.mov = 2;
                    pmov(&componentes);
                }
            } else if (coord.y > THRESHOLD) {
                componentes.mov = 3;
                pmov(&componentes);
            }
            //        if (coord.y < -THRESHOLD && npos.y < DISP_MAX_Y) {
            //            npos.y++;
            //        }
            //    }
        }
        ciclos++;
        rasprint(GAME);

        if (componentes.naves == 0) {
            componentes.nivel++;
            ciclos = 0;
            matniv();
            rasprint(MENU);
        }
        if (componentes.puntaje >= 1000) {//si tengo mas de 1000 puntos gano 1 vida y vuelvo el puntaje a 0
            componentes.vidas++;
            componentes.puntaje = 0;
        }
        if (componentes.vidas == 0 || quit_game == 1) {
            printscore(componentes.puntaje);
            rasprint(MENU);
            usleep(3);
            inigame(&componentes, 1); //inicializa en nivel 1

            while (joy_get_switch() != J_NOPRESS) {
                quit_game = pause_menu();
                rasprint(MENU);

            }

        }
    }
    /*
    /* End Simple-SDL2-Audio 
    endAudio();

    /* Important to free audio after ending Simple-SDL2-Audio because they might be referenced still 
    freeAudio(sound);
    freeAudio(music);

     */

    return 0;
}
/////////////////////////
/*
 
 space[5][0]=space[5][1]=1;//escribo el puntero opcion 1 play
 *space[12][0]=space[12][1]=1;//escribo el puntero opcion 2 quit
 * 
 * acordate que tenes la funcion printscore cuando te moris
 * 
 * 
 *    dcoord_t pos = {DISP_MAX_X >> 1, DISP_MAX_Y >> 1}; //pos es la posición actual, empieza en el centro de la matriz
 *    dcoord_t npos = pos; //npos es la próxima posición
 * 
 * 
 */

////////////////////////////////////////////////////////////////
//                       FUNCIONES                            //
////////////////////////////////////////////////////////////////

//////////////////// RASPINIT /////////////////

void raspinit(void) {
    joy_init(); //inicializa el joystick
    disp_init(); //inicializa el display
    disp_clear(); //limpia todo el display
}
////////////////////////////////////////////////


////////////////// RASPRINT ////////////////////
void rasprint(int matriz) {//es el printmat para raspi
    static int disparo = 0;
    int i, j, obj;
    for (i = 0; i < ANCHO; ++i) {//copia el contenido de la matriz en el buffer de leds
        for (j = 0; j < ANCHO; ++j) {
            if (matriz == MENU) {
                obj = get_menu(i, j);
            } else {
                obj = getmat(i, j);
            }

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
////////////////////////////////////////////////

///////////////// PAUSE_MENU ///////////////////
int pause_menu(void) {
    jcoord_t coord = {0, 0}; //coordenadas medidas del joystick
    coord = joy_get_coord(); //Guarda las coordenadas medidas
    int quit_game = 0;
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
////////////////////////////////////////////////

///////////////// LLAMO_NAVES //////////////////
int llamo_naves(juego_t* componentes, int ciclos, int naves) {
    static int funcion = 1;
    static int p = 0;
    int conta = 0;
    int cantidad = MAX_ENEM - componentes->naves;

    (componentes->nivel >= 4) ? p = 4 : (p = componentes->naves);

    if (funcion % 2 == 0) //Cuantas veces llamo a la funcion que mueve a las naves enemigas
    {
        if (naves > 1) {
            conta = 1;
        } else {
            if ((componentes->naves % 4) == 0) {
                conta = (cantidad / 4);
            } else //Cada cuantos ciclos llamo a la funcion que mueve a las naves enemigas
            {
                conta = 6 - p;
                if (conta > 1 && p >= 1) {
                    if ((cantidad % 4) || ciclos % 5 == 0) {
                        conta--;
                        p--;
                    }
                } else {
                    conta = 1;
                }
            }
        }
    }
    return conta;
}

////////////////////////////////////////////////

//////////////// CONTROL_AUDIO /////////////////
int control_audio(juego_t * componentes, int* nmadre) {
    int found = 1;
    int i, j;

    coord_t evento;
    for (i = 0; i < LARGO; i++) {
        for (j = 0; j < ANCHO; j++) {
            evento = ciclodisp(componentes, i, j);
            if (evento.objeto == NAVE_ENEMIGA) {
                //audio 1

            } else if (evento.objeto == NAVE_NODRIZA) {
                //audio 2
                *nmadre = 0;
            } else if (evento.objeto == JUGADOR) {
                //audio 3
            } else if (evento.objeto == ESCUDO) {

            } else {
                found = 0;
            }
        }
    }

    return found;
}