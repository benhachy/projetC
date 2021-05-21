
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

ei_surface_t offscreen = NULL;


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


    //On enregistre la classe de widgets text
    ei_widgetclass_t *text = (ei_widgetclass_t*) malloc(sizeof(ei_widgetclass_t));
    char text_name[20] = "text";
    for (int i = 0; i < 20; i++){
        text->name[i] = text_name[i];
    }
    text->allocfunc = &allowfunc_text;
    text->drawfunc = &drawfunc_text;
    text->releasefunc = &releasefunc_text;
    text->geomnotifyfunc = &geomnotifyfunc_text;
    text->handlefunc = &ei_text_handlefunc_t;
    text->setdefaultsfunc = &setdefaultsfunc_text;
    text->next = NULL;

    ei_widgetclass_register(text);


    ei_surface_t main_window = hw_create_window(main_window_size, fullscreen);
    offscreen = hw_surface_create(main_window,main_window_size, 0);
    root_surface = main_window;
    root_widget.wclass = ei_widgetclass_from_name("frame");
    root_widget.screen_location.size = main_window_size;
    root_widget.content_rect = &(root_widget.screen_location);
    root_widget.pick_id = 0;
    root_widget.pick_color = (ei_color_t *) malloc(sizeof(ei_color_t)); //TO FREEEEEEE
    root_widget.pick_color->red = 0;
    root_widget.pick_color->blue = 0;
    root_widget.pick_color->green = 0;
    root_widget.pick_color->alpha = 0;

}


void ei_app_free(void){

}


void ei_app_run(void){
    int x = 0;
    int y = 0;
    int x_max = hw_surface_get_size(offscreen).width;
    uint32_t id_color = -1;
    ei_button_cell* button = NULL;
    ei_frame_cell* frame = NULL;
    ei_event_t		event;
    uint32_t* origin = (uint32_t*)hw_surface_get_buffer(offscreen);
    //Dessin récursif des widgets
    hw_surface_lock(root_surface);
    dessin(&root_widget, root_surface, offscreen);
    hw_surface_unlock(root_surface);
    hw_surface_update_rects(root_surface, NULL);

    event.type = ei_ev_none;
    while (event.type != ei_ev_keydown) {
        if (event.type == ei_ev_mouse_buttondown){
            x = event.param.mouse.where.x;
            y = event.param.mouse.where.y;
            id_color = *(origin + (uint32_t)(x_max*y) + (uint32_t)x);
            if(is_widget_button(id_color, offscreen) == 1){
                button = button_from_id(id_color, offscreen);
                button->relief = ei_relief_sunken;
                hw_surface_lock(root_surface);
                dessin(&root_widget, root_surface, offscreen);
                hw_surface_unlock(root_surface);
                hw_surface_update_rects(root_surface, NULL);
                hw_event_wait_next(&event);
                while(event.type == ei_ev_mouse_move && mouse_on_widget(event, button->widget->screen_location) == 1){
                    hw_event_wait_next(&event);
                }
                button->relief = ei_relief_raised;
                continue;
            }

        }
        hw_surface_lock(root_surface);
        dessin(&root_widget, root_surface, offscreen);
        hw_surface_unlock(root_surface);
        hw_surface_update_rects(root_surface, NULL);
        hw_event_wait_next(&event);
    }
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

