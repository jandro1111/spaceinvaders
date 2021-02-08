/* 
 * File:   menu.h
 * Author: magali
 *
 * Created on February 2, 2021, 9:44 PM
 */

#ifndef MENU_H
#define MENU_H

#define LARGO 16 
#define ANCHO 16

void menu (int[][ANCHO]);//para raspi printea el menu
void printscore(int [][ANCHO],int );//para raspi escribe el puntaje
void printnum(int [][ANCHO],int,int[]);//funcion local para printscore
void matniv(int [][ANCHO]);//para raspi, esccribe level up en la matriz

#endif






