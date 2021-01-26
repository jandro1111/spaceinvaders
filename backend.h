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
#define RASPI //para testeo, meter en un makefile despues
#define LARGO 16 //el largo de la matriz
#define ANCHO 16
#define ENEMY 1//despues agrego mas tipos de naves
#define ENEMYSHOT 2//tipos de naves entre 1 a 5 el 2 es el q dispara
#define NAVNOD 5//siempre se mueve de izq a der, ocupa 2 bloques
#define PSHOT 7   
#define ESHOT 6
#define PLAYER 9
#define MURO 8
#define DER 1
#define IZQ 2
#include<stdio.h>
#include<time.h>
#include <stdlib.h>
#include <stdint.h>
#include<unistd.h>
void exit_cond(int *,int *,int *);//si te quedas sin vidas te lleva al menu
void inimat (int [][ANCHO] );//inicializa la matriz en 0
void printmat (int [][ANCHO]);//imprime la matriz (testeo)
void ininiv(int[][ANCHO],int);//se fija en que nivel estas y carga cierto patron de naves, pone los escudos y la nave del player
int ciclonaves (int [][ANCHO],int);//mueve las naves enemigas
void ciclodisp(int [][ANCHO],int*,int*);//mueve disparos del player y el enemigo
int verparams(int [][ANCHO],int,int *);//se fija si pasaste de nivel, cambia las naves para que puedas disparar
void navdisp(int [][ANCHO],int *,int *,int *,int );//decide si dispara las naves, y spawnea nave nodriza
void pmov(int [][ANCHO],int *,int *,int *); //recibe el input del jugador y mueve o dispara, o se mueve en el menu /pone pausa al juego
void matniv(int [][ANCHO]);//para raspi, esccribe level up en la matriz
void printscore(int [][ANCHO],int );//para raspi escribe el puntaje
void printnum(int [][ANCHO],int,int[]);//funcion local para printscore
void menu (int [][ANCHO]);//para raspi printea el menu
#ifdef __cplusplus
}
#endif

#endif /* BACKEND_H */

