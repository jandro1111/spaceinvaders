#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>


#define STATE_MENU  0
#define STATE_PLAY  1
#define STATE_STATS 2
#define STATE_EXIT  3
#define STATE_PAUSE 4

#define BLACK   al_map_rgb(0,0,0)
#define WHITE   al_map_rgb(155,155,155)
#define RED     al_map_rgb(255,0,0)

int game_states;

ALLEGRO_MOUSE_STATE mouse;

void must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

#define BUFFER_W 640
#define BUFFER_H 480
#define DISP_SCALE 1
#define DISP_W (BUFFER_W * DISP_SCALE)
#define DISP_H (BUFFER_H * DISP_SCALE)

ALLEGRO_DISPLAY* disp;
ALLEGRO_BITMAP* buffer;

void disp_init()
{
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    disp = al_create_display(DISP_W, DISP_H);
    must_init(disp, "display");

    buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
    must_init(buffer, "bitmap buffer");
}

void disp_deinit()
{
    al_destroy_bitmap(buffer);
    al_destroy_display(disp);
}

void disp_pre_draw()
{
    al_set_target_bitmap(buffer);
}

void disp_post_draw()
{
    al_set_target_backbuffer(disp);
    al_draw_scaled_bitmap(buffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, DISP_W, DISP_H, 0);

    al_flip_display();
}


// --- keyboard ---

#define KEY_SEEN     1
#define KEY_RELEASED 2
unsigned char key[ALLEGRO_KEY_MAX];

void keyboard_init()
{
    memset(key, 0, sizeof(key));
}

void keyboard_update(ALLEGRO_EVENT* event)
{
    switch(event->type)
    {
        case ALLEGRO_EVENT_TIMER:
            for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                key[i] &= KEY_SEEN;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            key[event->keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
            break;
        case ALLEGRO_EVENT_KEY_UP:
            key[event->keyboard.keycode] &= KEY_RELEASED;
            break;
    }
}

//------------------------
ALLEGRO_SAMPLE* sample_shot;
ALLEGRO_SAMPLE* sample_explode[2];

void audio_init()
{
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(128);

    sample_shot = al_load_sample("shot.flac");
    must_init(sample_shot, "shot sample");

    sample_explode[0] = al_load_sample("explode1.flac");
    must_init(sample_explode[0], "explode[0] sample");
    sample_explode[1] = al_load_sample("explode2.flac");
    must_init(sample_explode[1], "explode[1] sample");
}

void audio_deinit()
{
    al_destroy_sample(sample_shot);
    al_destroy_sample(sample_explode[0]);
    al_destroy_sample(sample_explode[1]);
}

//------------------------

typedef struct BUTTON {
    int x;
    int y;
    int w; 
    int h;
    const char * text;
    ALLEGRO_FONT * font;
} BUTTON; 

int button_update(ALLEGRO_EVENT ev, BUTTON * button){
    if((mouse.x >= button->x && mouse.y >= button->y && mouse.x < (button->x + button->w) && mouse.y < (button->y + button->h))){
        if(al_mouse_button_down(&mouse, 1))
            return 1;
        else 
            return 2;
    }
}

void menu_update(ALLEGRO_EVENT ev, BUTTON * buttons[]){
    /*if(ev.type != ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        return 0;*/
   /* return((mouse.x >= button->x && mouse.y >= button->y && 
            mouse.x < (button->x + button->w) && mouse.y < (button->y + button->h)) && al_mouse_button_down(&mouse, 1));*/
    switch(game_states){
        case(STATE_MENU):
            if(button_update(ev, &buttons[0][0]) == 1) {game_states = STATE_PLAY;}
            if(button_update(ev, &buttons[0][1]) == 1) {game_states = STATE_STATS;}
            if(button_update(ev, &buttons[0][2]) == 1) {game_states = STATE_EXIT;}
            break;
            
        case(STATE_PLAY):
            if(key[ALLEGRO_KEY_ENTER]) {game_states = STATE_PAUSE;}
            keyboard_update(&ev);
            break;
            
        case(STATE_STATS):
          if(button_update(ev, &buttons[1][0]) == 1) {game_states = STATE_MENU;}
          break;
          
        case(STATE_PAUSE):
            if(button_update(ev, &buttons[2][0]) == 1) {game_states = STATE_PLAY;}
            if(button_update(ev, &buttons[2][1]) == 1) {game_states = STATE_MENU;}
            break;
    }
}

void menu_draw(ALLEGRO_EVENT ev, BUTTON * buttons[]){
    
    switch(game_states){
        case(STATE_MENU):
            al_clear_to_color(al_map_rgb(0,0,0));
            for(int i=0; i<3; i++){
                if(button_update(ev, &buttons[0][i]) == 2)
                    al_draw_text(buttons[0][i].font, RED, buttons[0][i].x, buttons[0][i].y, 0, buttons[0][i].text);
                else
                    al_draw_text(buttons[0][i].font, WHITE, buttons[0][i].x, buttons[0][i].y, 0, buttons[0][i].text);
            }
            break;
        case(STATE_PLAY):
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_text(buttons[0][0].font, WHITE, buttons[0][0].x, buttons[0][0].y + 150, 0, "Holis 1");
            break;
            
        case(STATE_STATS):
            al_clear_to_color(al_map_rgb(0,0,0));
            if(button_update(ev, &buttons[1][0]) == 2)
                al_draw_text(buttons[1][0].font, RED, buttons[1][0].x, buttons[1][0].y, 0, buttons[1][0].text);
            else
                al_draw_text(buttons[1][0].font, WHITE, buttons[1][0].x, buttons[1][0].y, 0, buttons[1][0].text);
            break;
        case(STATE_PAUSE):
            al_clear_to_color(al_map_rgb(0,0,0));
            for(int i=0; i<2; i++){
                if(button_update(ev, &buttons[2][i]) == 2)
                    al_draw_text(buttons[2][i].font, RED, buttons[2][i].x, buttons[2][i].y, 0, buttons[2][i].text);
                else
                    al_draw_text(buttons[2][i].font, WHITE, buttons[2][i].x, buttons[2][i].y, 0, buttons[2][i].text);
            }
            break;
    }
}
    /*
    if(!(menu[0].pressed && menu[1].pressed && menu[2].pressed)){
        
    }
    if(menu[0].pressed){
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_text(menu[0].font, color, menu[0].x, menu[0].y + 150, 0, "Holis 1");
        menu[0].pressed = 0; 
    }
    if(menu[1].pressed){
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_text(menu[1].font, color, menu[1].x, menu[1].y + 150, 0, "Holis 2");
        menu[1].pressed = 0;
    }
/*
void update(ALLEGRO_EVENT ev){
    switch(MenuStates){
        case PLAY:
        case OPCIONES:
        case SALIR:
            break
    }
}
*/

int main(void){
    
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");
    must_init(al_install_audio(), "audio");
    must_init(al_init_acodec_addon(), "audio codecs");
    must_init(al_reserve_samples(16), "reserve samples");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");
    
    ALLEGRO_FONT * font = al_create_builtin_font();
    must_init(font, "font");
    
    disp_init();
    //audio_init();
    keyboard_init();
    
    //Inicializar display, fuentes, etc.
    
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());
    
    BUTTON buttons_menu [] = {{300,50,100,25, "START", font},
                        {300,100,100,25, "STATS", font},
                        {300,150,100,25, "EXIT", font}};
    
    BUTTON buttons_stats [] = {300,200,100,25, "VOLVER", font};
    
    BUTTON buttons_pause [] = {{300,100,100,25, "VOLVER", font}, {300,200,100,25, "SALIR", font}};
    
    /*BUTTON * pbuttons_menu = buttons_menu;
    BUTTON * pbuttons_stats = buttons_stats;*/
    
    BUTTON * buttons[3];
    
    buttons[0] = buttons_menu;
    buttons[1] = buttons_stats;
    buttons[2] = buttons_pause;
    
    //typedef struct BUTTON ARR_BUTTON [];
    
    //BUTTON (*buttons[2])[3] = {&buttons_menu, &buttons_stats};
    
   /* buttons[0] = &buttons_menu[0];
    buttons[1] = &buttons_stats[0];*/
    
    bool redraw = true;
    
    bool done = false;
    
    game_states = STATE_MENU;
    
    ALLEGRO_EVENT event;
    
    al_start_timer(timer);
    
    while(!done){
        
        al_wait_for_event(queue, &event);
        
        if(redraw && al_is_event_queue_empty(queue)){
            disp_pre_draw();
            menu_draw(event, buttons);
            disp_post_draw();
            redraw = false;
        }
            
        switch(event.type){
            case ALLEGRO_EVENT_TIMER:
                al_get_mouse_state(&mouse);
                //update();
                if(key[ALLEGRO_KEY_ESCAPE])
                    done = true;
                redraw = true;
                menu_update(event, buttons);
                if(game_states == STATE_EXIT)
                    done = true;
                
                break;
                
                
            
            /*case ALLEGRO_EVENT_KEY_CHAR:
                if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                    salida = true;    */
                
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }
        
        keyboard_update(&event);
    }
    
    disp_deinit();
    //audio_deinit();
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    
    return 0;
    
}

