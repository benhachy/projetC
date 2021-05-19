
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ei_application.h"
#include "ei_draw_widget.h"
#include "ei_types.h"
#include "ei_coloring.h"
#include "struct.h"
#include "hw_interface.h"
#include "ei_event.h"
#include "ei_widgetclass.h"
#include "ei_utils.h"

static int run = 1;

struct ei_widget_t root_widget =  {
        NULL,
        0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        0,
        0,
        0,
        0,
        0,
        0,
        NULL
};

ei_surface_t root_surface = NULL;


void ei_app_create(ei_size_t main_window_size, ei_bool_t fullscreen){
     
    hw_init();
    //On enregistre la classe de widgets frame
    ei_widgetclass_t *frame = (ei_widgetclass_t*) malloc(sizeof(ei_widgetclass_t));
    char frame_name[20] = "frame";
    for (int i = 0; i < 20; i++){
        frame->name[i] = frame_name[i];
    }
    frame->allocfunc = &allowfunc_frame;
    frame->drawfunc = &drawfunc_frame;
    frame->releasefunc = &releasefunc_frame;
    frame->geomnotifyfunc = &geomnotifyfunc_frame;
    frame->handlefunc = &ei_frame_handlefunc_t;
    frame->setdefaultsfunc = &setdefaultsfunc_frame;
    frame->next = NULL;

    ei_widgetclass_register(frame);
     

    //On enregistre la classe de widgets button
    ei_widgetclass_t *button = (ei_widgetclass_t*) malloc(sizeof(ei_widgetclass_t));
    char button_name[20] = "button";
    for (int i = 0; i < 20; i++){
        button->name[i] = button_name[i];
    }
    button->allocfunc = &allowfunc_button;
    button->drawfunc = &drawfunc_button;
    button->releasefunc = &releasefunc_button;
    button->geomnotifyfunc = &geomnotifyfunc_button;
    button->handlefunc = &ei_button_handlefunc_t;
    button->setdefaultsfunc = &setdefaultsfunc_button;
    button->next = NULL;

    ei_widgetclass_register(button);


    ei_surface_t main_window = hw_create_window(main_window_size, fullscreen);
    root_surface = main_window;
    root_widget.wclass = ei_widgetclass_from_name("frame");
    root_widget.screen_location.size = main_window_size;
    root_widget.content_rect = &(root_widget.screen_location);



}


void ei_app_free(void){

}


void ei_app_run(void){
    ei_event_t		event;
    //Dessin récursif des widgets
    hw_surface_lock(root_surface);
    dessin(&root_widget, root_surface, root_surface);
    hw_surface_unlock(root_surface);
    hw_surface_update_rects(root_surface, NULL);

    event.type = ei_ev_none;
    while (event.type != ei_ev_keydown)
        hw_event_wait_next(&event);
    //getchar();
}


void ei_app_invalidate_rect(ei_rect_t* rect){
	
}


void ei_app_quit_request(void){

	//run = 0;
}


ei_widget_t* ei_app_root_widget(void){

	return &root_widget;

}


ei_surface_t ei_app_root_surface(void){

       return root_surface;

}

