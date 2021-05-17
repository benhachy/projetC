
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ei_application.h"
#include "ei_types.h"
#include "ei_coloring.h"
#include "struct.h"
#include "hw_interface.h"
#include "ei_event.h"
#include "ei_widgetclass.h"
#include "ei_utils.h"
#include "ei_draw_widget.h"

static int run = 1;

void ei_app_create(ei_size_t main_window_size, ei_bool_t fullscreen){
     
     hw_init();
     //On enregistre les classes de widgets ?
     ei_fram
     
     //On crée la fenêtre racine 
     ei _surface_t main_window = hw_create_window(main_window_size, fullscreen);
     //On crée et configure le widget racine
     ei_widget_t* widget_root = ei_widget_create("frame", NULL, NULL, NULL);
     ei_frame_configure(widget_root, &main_window_size, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
     ei_rect_t main_rectangle = hw_surface_get_rect(main_window);
     ei_rect_t rectangle = ei_rect(main_rectangle.top_left, main_window_size);
     widget_root->screen_location = rectangle; 
     //On configure l'offscreen
     ei_surface_t offscreen;
     offscreen = hw_surface_create(ei_app_root_surface(), main_window_size, EI_FALSE);
     }


void ei_app_free(void);


void ei_app_run(void){
     //Initialisation de l'evenement de la boucle principale
     ei_event_t evenement;
     evenement.type = ei_ev_none;
     
     //Dessin des différentes composantes
     //Pour cela on utilise une fonction dessin qui sera définie récursivement dans un module ei_draw_widget
     ei_surface_t offscreen;
     dessin(ei_app_root_widget(),ei_app_root_surface(), offscreen);
     //Tant que l'application est en marche
     while ( run == 1) {
     	hw_event_wait_next(&evenement);
     	
           
    }
}


void ei_app_invalidate_rect(ei_rect_t* rect){
	
}


void ei_app_quit_request(void){

	run = 0;
}


ei_widget_t* ei_app_root_widget(void){

	ei_widget_t* widget_root;
	return widget_root;
}


ei_surface_t ei_app_root_surface(void){
       
       ei_surface_t window;
       return window;
}

