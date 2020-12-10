
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.\sleep(1);
 */

/* 
 * File:   main.c
 * Author: mateo
 *
 * Created on December 3, 2020, 1:22 PM
 */



#include"backend.h"
#include"hardware.h"
#include"allegro.h"

// uso srand(time(NULL)) para incializar
//rand() % 10 + 1;10 rango 1 valor inicial
int main(){
    
    int vidas =3;
    int puntaje =0;//1000 puntos se transforman en una vida
    int exit=0;
    //initallegro();//inicializa allegro
    //meterle un define o algo
   //initraspi();//inicializa librerias raspi
    //meterle define
    int nivel=-1;//-1 para test
    int direccion=1;//1 derecha, 2 izquierda
    int space [LARGO][ANCHO];
    inimat(space);//inicializo la matriz
    ininiv(space,nivel);
    printmat(space);
/*    do{
        direccion = ciclonaves(space,direccion);//mueve las naves enemigas
        ciclodisp(space,&vidas,&puntaje);//mueve los disparos
        pmov(space,&puntaje);//mueve y dispara el jugador
        navdisp(space,&vidas,&puntaje,&nivel);//hace que las naves disparen
        nivel = verparams(space,nivel);//verifica si pasaste de nivel
        printmat(space);
        sleep(1);
    }while((exit = exit_cond(&vidas))!=0);*/
        printscore(space,puntaje);
return 0;
}