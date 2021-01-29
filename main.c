
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.\sleep(1);
 */

/* 
 * File:   main.c
 * Author: Alejandro
 *
 * Created on December 3, 2020, 1:22 PM
 */



#include"backend.h"
#include"raspi.h"

// uso srand(time(NULL)) para incializar
//rand() % 10 + 1;10 rango 1 valor inicial


//ESTO QUEDA ACA PARA DESPUES METER EN EL FRONTEND DE RASPI


/*int main(){
    int i,j;
    int numerorandom =0;
    srand(time(NULL));//esto cambia 1 vez x segundo
    numerorandom =rand() %10 + 1;//entonces creo esta otra variable  para poder randomizar entre segundos
    int naves =0;//marca la cantidad de naves 
    int enpausa =0;// 0 la primera vez que ejecuta la pausa, 1 si no
    int vidas =3;
    int puntaje =0;//1000 puntos se transforman en una vida
    int exit=1;
    int pausa =0;//0 si estoy en pausa 1 si no
    //initallegro();//inicializa allegro
    //meterle un define o algo
   //initraspi();//inicializa librerias raspi
    //meterle define
    int nivel=1;//-1 para test
    int direccion=1;//1 derecha, 2 izquierda
    int ops=0;//marca la opcion de mas arriba, en principio hay dos opciones, asi que esta limitado a 0 o 1, 0 es arrancar el juego
    int space [LARGO][ANCHO];
    int mataux[LARGO][ANCHO];//se usa en el menu de pausa
    inimat(space);
    inimat(mataux);
    menu(space);//printea el menu inicial, para allegro hacer otra cosa
    do{
        pmov(space,&puntaje,&pausa,&ops);//mueve y dispara el jugador
        printmat(space);//reemplazar con lo de allegro o raspberri
        usleep(1000000);//borrar despues
    }while(pausa==0);//menu de inicio
    inimat(space);//inicializo la matriz
    ininiv(space,nivel);
    if(ops==1){//si la opcion fue salir marco salir
        exit=0;
    }
    if(exit!=0){//si no le di a salir desde el menu
        printmat(space);
        do{
            while(pausa==1){//si no estoy en pausa
                enpausa=0;//
                switch(naves){
                    case 1:
                    case 2:
                        direccion = ciclonaves(space,direccion);//mueve las naves enemigas
                        ciclodisp(space,&vidas,&puntaje);//mueve los disparos
                        navdisp(space,&vidas,&puntaje,&nivel,numerorandom);//hace que las naves disparen
                        //aca recibes los datos
                        pmov(space,&puntaje,&pausa,&ops);//mueve y dispara el jugador
                        nivel = verparams(space,nivel,&naves,&puntaje);//verifica si pasaste de nivel
                        printmat(space);//reemplazar con raspi o allegro
                        usleep(250000);//ver como hacer los ciclos
                        exit_cond(&vidas,&exit,&pausa);
                    break;
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                        direccion = ciclonaves(space,direccion);//mueve las naves enemigas
                        ciclodisp(space,&vidas,&puntaje);//mueve los disparos
                        navdisp(space,&vidas,&puntaje,&nivel,numerorandom);//hace que las naves disparen
                        //aca recibes los datos
                        pmov(space,&puntaje,&pausa,&ops);//mueve y dispara el jugador
                        nivel = verparams(space,nivel,&naves,&puntaje);//verifica si pasaste de nivel
                        printmat(space);//reemplazar con raspi o allegro
                        usleep(250000);//ver como hacer los ciclos
                        exit_cond(&vidas,&exit,&pausa);
                        if(exit==0){
                            break;
                        }
                        ciclodisp(space,&vidas,&puntaje);//mueve los disparos
                        navdisp(space,&vidas,&puntaje,&nivel,numerorandom);//hace que las naves disparen
                        //aca recibes los datos
                        pmov(space,&puntaje,&pausa,&ops);//mueve y dispara el jugador
                        nivel = verparams(space,nivel,&naves,&puntaje);//verifica si pasaste de nivel
                        printmat(space);//reemplazar con raspi o allegro
                        usleep(250000);//ver como hacer los ciclos
                        exit_cond(&vidas,&exit,&pausa);
                        if(exit==0){
                            break;
                        }
                        direccion = ciclonaves(space,direccion);//mueve las naves enemigas
                        ciclodisp(space,&vidas,&puntaje);//mueve los disparos
                        navdisp(space,&vidas,&puntaje,&nivel,numerorandom);//hace que las naves disparen
                        //aca recibes los datos
                        pmov(space,&puntaje,&pausa,&ops);//mueve y dispara el jugador
                        nivel = verparams(space,nivel,&naves,&puntaje);//verifica si pasaste de nivel
                        printmat(space);//reemplazar con raspi o allegro
                        usleep(250000);//ver como hacer los ciclos
                        exit_cond(&vidas,&exit,&pausa);
                        if(exit==0){
                            break;
                        }
                        ciclodisp(space,&vidas,&puntaje);//mueve los disparos
                        navdisp(space,&vidas,&puntaje,&nivel,numerorandom);//hace que las naves disparen
                        //aca recibes los datos
                        pmov(space,&puntaje,&pausa,&ops);//mueve y dispara el jugador
                        nivel = verparams(space,nivel,&naves,&puntaje);//verifica si pasaste de nivel
                        printmat(space);//reemplazar con raspi o allegro
                        usleep(250000);//ver como hacer los ciclos
                        exit_cond(&vidas,&exit,&pausa);
                        if(exit==0){
                            break;
                        }
                        
                    break;
                    default://cuando hay mas de 8 naves
                        direccion = ciclonaves(space,direccion);//mueve las naves enemigas
                        ciclodisp(space,&vidas,&puntaje);//mueve los disparos
                        navdisp(space,&vidas,&puntaje,&nivel,numerorandom);//hace que las naves disparen
                        //aca recibes los datos
                        pmov(space,&puntaje,&pausa,&ops);//mueve y dispara el jugador
                        nivel = verparams(space,nivel,&naves,&puntaje);//verifica si pasaste de nivel
                        printmat(space);//reemplazar con raspi o allegro
                        usleep(250000);//ver como hacer los ciclos
                        exit_cond(&vidas,&exit,&pausa);
                        if(exit==0){
                            break;
                        }
                        ciclodisp(space,&vidas,&puntaje);//mueve los disparos
                        navdisp(space,&vidas,&puntaje,&nivel,numerorandom);//hace que las naves disparen
                        //aca recibes los datos
                        pmov(space,&puntaje,&pausa,&ops);//mueve y dispara el jugador
                        nivel = verparams(space,nivel,&naves,&puntaje);//verifica si pasaste de nivel
                        printmat(space);//reemplazar con raspi o allegro
                        usleep(250000);//ver como hacer los ciclos
                        exit_cond(&vidas,&exit,&pausa);
                        if(exit==0){
                            break;
                        }
                        ciclodisp(space,&vidas,&puntaje);//mueve los disparos
                        navdisp(space,&vidas,&puntaje,&nivel,numerorandom);//hace que las naves disparen
                        //aca recibes los datos
                        pmov(space,&puntaje,&pausa,&ops);//mueve y dispara el jugador
                        nivel = verparams(space,nivel,&naves,&puntaje);//verifica si pasaste de nivel
                        printmat(space);//reemplazar con raspi o allegro
                        usleep(250000);//ver como hacer los ciclos
                        exit_cond(&vidas,&exit,&pausa);
                        if(exit==0){
                            break;
                        }
                        ciclodisp(space,&vidas,&puntaje);//mueve los disparos
                        navdisp(space,&vidas,&puntaje,&nivel,numerorandom);//hace que las naves disparen
                        //aca recibes los datos
                        pmov(space,&puntaje,&pausa,&ops);//mueve y dispara el jugador
                        nivel = verparams(space,nivel,&naves,&puntaje);//verifica si pasaste de nivel
                        printmat(space);//reemplazar con raspi o allegro
                        usleep(250000);//ver como hacer los ciclos
                        exit_cond(&vidas,&exit,&pausa);
                        if(exit==0){
                            break;
                        }
                        break;
                }
                numerorandom =rand() %10 + 1;//entonces creo esta otra variable  para poder randomizar entre segundos
                if(exit==0){
                    break;
                }                
            }//puede salir x dos opciones, pausa o que perdiste, las dos te llevan al mismo menu, pero en pausa usas una mat auxil para guardar el estado del juego
            if(enpausa==0){//si recien salio del juego   
                if(vidas>0){//si sali pq pause
                    for(i=0;i<LARGO;++i){
                        for(j=0;j<ANCHO;++j){
                            mataux[i][j]=space[i][j];//guardo el estado del juego
                        }
                    }
                    printmat(mataux);
                }else{//si sali pq perdi, preparo un nuevo juego
                    printscore(space,puntaje);
                    exit=1;
                    sleep(3);
                    vidas=3;
                    puntaje=0;
                    direccion=nivel=1;
                    inimat(space);
                    ininiv(space,nivel);
                    for(i=0;i<LARGO;++i){
                        for(j=0;j<ANCHO;++j){
                            mataux[i][j]=space[i][j];//guardo el estado del juego nuevo
                        }
                    }
                }
            }//esta parte la ejecuta solo una vez cuando entra en pausa
            enpausa=1;//
            inimat(space);
            menu(space);
            pmov(space,&puntaje,&pausa,&ops);//mueve y dispara el jugador
            printmat(space);
            sleep(1);//borrar despues
            if(pausa==1&&ops==0){//si reanude el juego
                inimat(space);
                for(i=0;i<LARGO;++i){
                    for(j=0;j<ANCHO;++j){
                        space[i][j]=mataux[i][j];//restauro el estado del juego
                    }
                }
            }
            if(ops==1&&pausa==1){//si la opcion fue salir marco salir
                exit=0;
            }
        }while(exit !=0);
    }
    
return EXIT_SUCCESS;
}
 */