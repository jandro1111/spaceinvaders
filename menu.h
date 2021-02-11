/* 
 * File:   menu.h
 * Author: magali
 *
 * Created on February 2, 2021, 9:44 PM
 */

#ifndef MENU_H
#define MENU_H

typedef numero int[4][4];

numero n0={
    { 0, 1, 1, 0},
    { 1, 0, 0, 1},
    { 1, 0, 0, 1},
    { 0, 1, 1, 0}};

numero n1={
    { 0, 0, 1, 0},
    { 0, 1, 1, 0},
    { 0, 0, 1, 0},
    { 0, 0, 1, 0}};

numero n2={
    { 1, 1, 1, 0},
    { 0, 0, 1, 0},
    { 0, 1, 0, 0},
    { 1, 1, 1, 0}};

numero n3={
    { 1, 1, 1, 0},
    { 0, 1, 1, 0},
    { 0, 0, 1, 0},
    { 1, 1, 1, 0}};

numero n4={
    { 0, 0, 1, 0},
    { 0, 1, 1, 0},
    { 1, 1, 1, 0},
    { 0, 0, 1, 0}};

numero n5={
    { 1, 1, 1, 1},
    { 1, 1, 1, 0},
    { 0, 0, 0, 1},
    { 1, 1, 1, 0}};

numero n6={
    { 1, 1, 1, 1},
    { 1, 1, 1, 0},
    { 1, 0, 0, 1},
    { 1, 1, 1, 0}};

numero n7={
    { 0, 1, 1, 1},
    { 0, 0, 0, 1},
    { 0, 0, 1, 0},
    { 0, 1, 0, 0}};

numero n8={
    { 0, 1, 1, 0},
    { 0, 1, 1, 0},
    { 0, 1, 1, 0},
    { 0, 1, 1, 0}};

numero n9={
    { 0, 1, 1, 0},
    { 0, 1, 1, 0},
    { 0, 0, 1, 0},
    { 0, 0, 1, 0}};

numero V={
    { 1, 0, 1, 0},
    { 1, 0, 1, 0},
    { 1, 0, 1, 1},
    { 0, 1, 0, 0}};

numero L={
    { 0, 1, 0, 0},
    { 0, 1, 0, 0},
    { 0, 1, 0, 0},
    { 0, 1, 1, 1}};  

numero U={
    { 1, 0, 0, 1},
    { 1, 0, 0, 1},
    { 1, 0, 0, 1},
    { 0, 1, 1, 0}};

numero P={
    { 1, 1, 1, 1},
    { 1, 0, 1, 1},
    { 1, 1, 1, 0},
    { 1, 0, 0, 0}};

numero E={
    { 1, 1, 1, 0},
    { 1, 1, 0, 0},
    { 1, 0, 0, 0},
    { 1, 1, 1, 0}};

numero N={
    { 1, 0, 0, 1},
    { 1, 1, 0, 1},
    { 1, 0, 1, 1},
    { 1, 0, 0, 1}};

numero D={
    { 1, 1, 0, 0},
    { 1, 0, 1, 0},
    { 1, 0, 1, 0},
    { 1, 1, 0, 0}};

numero PLAY={
    { 1, 0, 0, 0},
    { 1, 1, 1, 0},
    { 1, 1, 0, 0},
    { 1, 0, 0, 0}};




void menu (int opcion);//para raspi printea el menu
void printscore(int puntaje);//para raspi escribe el puntaje
void printnum(int num,int digit[]);//funcion local para printscore
void matniv(void);//para raspi, esccribe level up en la matriz
int get_menu (int i, int j);

#endif



       

