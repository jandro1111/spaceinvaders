/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/* 
 * File:   main.c
 * Author: axel
 *
 * Created on February 2, 2021, 1:42 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include"backend.h"
#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>


int main(void){
    
 

    
        
    ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_EVENT_QUEUE * event_queue = NULL;
    ALLEGRO_BITMAP *En_1_image = NULL;
    ALLEGRO_BITMAP *En_2_image = NULL;
    ALLEGRO_BITMAP *En_3_image = NULL;
    ALLEGRO_BITMAP *En_F_image = NULL;
    ALLEGRO_BITMAP *P_image = NULL;
    
    int close_display=0;
    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    
    
   
    
 /******************************************************************************************************************************************/ 
    //Inicializo la libreria, sin ella me genera segmentation fault, MUY IMPORTANTE.
    if (!al_init()) { //Primera funcion a llamar antes de empezar a usar allegro.
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
/********************************************************************************************************************************************/    
    //Inicializo el manejo de imagenes
    if (!al_init_image_addon()) { // ADDON necesario para manejo(no olvidar el freno de mano) de imagenes 
        fprintf(stderr, "failed to initialize image addon !\n");
        return -1;
    }
    
    En_1_image = al_load_bitmap("saucer1b.bmp");
    if (!En_1_image) {
        fprintf(stderr, "failed to load image !\n");
        return 0;
    }
    En_2_image = al_load_bitmap("saucer2b.bmp");
    if (!En_2_image) {
        fprintf(stderr, "failed to load image !\n");
        return 0;
    }
    En_3_image = al_load_bitmap("saucer3b.bmp");
    if (!En_3_image) {
        fprintf(stderr, "failed to load image !\n");
        return 0;
    }
    En_F_image = al_load_bitmap("baseshipa.bmp");
    if (!En_F_image) {
        fprintf(stderr, "failed to load image !\n");
        return 0;
    }
    P_image = al_load_bitmap("baseshipa.bmp");
    if (!En_1_image) {
        fprintf(stderr, "failed to load image !\n");
        return 0;
    }
/*********************************************************************************************************************************************/
    //Genero una cola de eventos
    event_queue = al_create_event_queue(); //Allegro usa cola eventos, como las colas del super pero sin comida :( (por orden de llegada)
    //Verifico si se generó correctamente
    if (!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        return -1;
    }
/*********************************************************************************************************************************************/    
    display = al_create_display(1200, 900); // Intenta crear display de 640x480 de fallar devuelve NULL
    if (!display) {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }
    //Registra el display a la cola de eventos, los eventos del display se iran guardando en la cola 
    // a medida que vayan sucediendo 
    al_register_event_source(event_queue, al_get_display_event_source(display));
    
    al_clear_to_color(al_map_rgb(0,0,0)); //Hace clear del backbuffer del diplay al color RGB 255,255,255 (blanco)


    //queue == cola/fila en ingles 
    event_queue = al_create_event_queue(); //Allegro usa cola eventos, como las colas del super pero sin comida :( (por orden de llegada)
    if (!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        return -1;
    }

    
     al_register_event_source(event_queue, al_get_display_event_source(display));

    //void al_clear_to_color(ALLEGRO_COLOR color) , ALLEGRO_COLOR al_map_rgb( unsigned char r, unsigned char g, unsigned char b)
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();

    while (!close_display) {
        ALLEGRO_EVENT ev;
        if (al_get_next_event(event_queue, &ev)) //Toma un evento de la cola, VER RETURN EN DOCUMENT.
        {
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                close_display = true;
        }
    }
        
    
    al_destroy_display(display); //Destruir recursor empleados 
    al_destroy_event_queue(event_queue);

    
    return(0);
}