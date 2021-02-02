/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   backend.h
 * Author: Alejandro
 *
 * Created on 8 de diciembre de 2020, 16:01
 */

#ifndef BACKEND_H
#define BACKEND_H

#ifdef __cplusplus
extern "C" {
#endif
#define RASPI
#ifdef RASPI  
#define LARGO 16 //el largo de la matriz
#define ANCHO 16
#else 
#define LARGO 98 //el largo de la matriz
#define ANCHO 49
#endif
#define SEP_AL 9 // Separacion entre enemegios por fila para allegro
#define SEP_RASP 4 // Separacion entre enemigos por fila en raspi
#define ENEMY 1 //despues agrego mas tipos de naves
#define ENEMY_2 2 
#define ENEMY_3 3
#define ENEMYSHOT 4//tipos de naves entre 1 a 5 el 2 es el q dispara
#define NAVNOD 5//siempre se mueve de izq a der, ocupa 2 bloques
#define PSHOT 7   
#define ESHOT 6
#define PLAYER 9
#define MURO 8
#define DER 1
#define IZQ 2
#define UP 3
#define ABAJO 4
#include<stdio.h>
#include<time.h>
#include <stdlib.h>
#include <stdint.h>
#include<unistd.h>
void exit_cond(int *,int *,int *);//si te quedas sin vidas te lleva al menu
void inimat (void);//inicializa la matriz en 0
void printmat (void);//imprime la matriz (testeo)
void ininiv(int);//se fija en que nivel estas y carga cierto patron de naves, pone los escudos y la nave del player
int ciclonaves (void);//mueve las naves enemigas
void ciclodisp(int*,int*);//mueve disparos del player y el enemigo
void verparams(int *,int *);//se fija si pasaste de nivel, cambia las naves para que puedas disparar
void navdisp(int *,int *,int *,int );//decide si dispara las naves, y spawnea nave nodriza
void pmov(int *,int); //recibe el input del jugador y mueve o dispara, o se mueve en el menu /pone pausa al juego
void matniv(void);//para raspi, esccribe level up en la matriz
void nav_nod (void);//spawnea y mueve nave nod
void movmat (int,int,int);//mueve elementos de la matriz a derecha izquierda arriba o abajo de donde estan
int getmat(int,int);//te dice que hay en esas coords de la matriz
void printscore(int );//para raspi escribe el puntaje
void printnum(int,int[]);//funcion local para printscore
#ifdef __cplusplus
}
#endif

#endif /* BACKEND_H */

