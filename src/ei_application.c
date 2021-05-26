
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


    //On enregistre la classe de widgets toplevel
    ei_widgetclass_t *toplevel = (ei_widgetclass_t*) malloc(sizeof(ei_widgetclass_t));
    char toplevel_name[20] = "toplevel";
    for (int i = 0; i < 20; i++){
        toplevel->name[i] = toplevel_name[i];
    }
    toplevel->allocfunc = &allowfunc_toplevel;
    toplevel->drawfunc = &drawfunc_toplevel;
    toplevel->releasefunc = &releasefunc_toplevel;
    toplevel->geomnotifyfunc = &geomnotifyfunc_toplevel;
    toplevel->handlefunc = &ei_toplevel_handlefunc_t;
    toplevel->setdefaultsfunc = &setdefaultsfunc_toplevel;
    toplevel->next = NULL;

    ei_widgetclass_register(toplevel);

    ei_widgetclass_t *image = (ei_widgetclass_t*) malloc(sizeof(ei_widgetclass_t));
    char image_name[20] = "image";
    for (int i = 0; i < 20; i++){
        image->name[i] = image_name[i];
    }
    image->allocfunc = &allowfunc_image;
    image->drawfunc = &drawfunc_image;
    image->releasefunc = &releasefunc_image;
    image->geomnotifyfunc = &geomnotifyfunc_image;
    image->handlefunc = &ei_image_handlefunc_t;
    image->setdefaultsfunc = &setdefaultsfunc_image;
    image->next = NULL;

    ei_widgetclass_register(image);


    ei_surface_t main_window = hw_create_window(main_window_size, fullscreen);
    offscreen = hw_surface_create(main_window,main_window_size, 0);
    root_surface = main_window;
    root_widget.wclass = ei_widgetclass_from_name("frame");
    root_widget.screen_location.size = main_window_size;
    root_widget.content_rect = &(root_widget.screen_location);
    root_widget.pick_id = 0;
    root_widget.pick_color = (ei_color_t *) malloc(sizeof(ei_color_t));
    root_widget.pick_color->red = 0;
    root_widget.pick_color->blue = 0;
    root_widget.pick_color->green = 0;
    root_widget.pick_color->alpha = 0;

}


void ei_app_free(void){

    //We free all the widgets still existing
    ei_widget_destroy(&root_widget);

    hw_surface_free(root_surface);

    //We free all the widget classes
    ei_widgetclass_t* class_head = ei_widgetclass_from_name("frame");

    ei_widgetclass_t* free_class_head = class_head;

    while(class_head != NULL){
        class_head = class_head->next;
        free(free_class_head);
        free_class_head = class_head;
    }

    hw_quit();
}


void ei_app_run(void){
    int x = 0;
    int y = 0;
    int x_max = hw_surface_get_size(offscreen).width;
    uint32_t id_color = -1;
    ei_widget_t* button = NULL;
    ei_widget_t*  frame = NULL;
    ei_widget_t* toplevel = NULL;
    ei_widget_t* active_widget = NULL;
    ei_bool_t got_handled = EI_FALSE;
    ei_event_t		event;
    uint32_t* origin = (uint32_t*)hw_surface_get_buffer(offscreen);
    ei_default_handle_func_t default_func = ei_event_get_default_handle_func();
    //Dessin récursif des widgets
    update_window(root_surface, offscreen, root_widget);
    event.type = ei_ev_none;

    hw_event_wait_next(&event);
    while(event.type != ei_ev_keydown) {
        got_handled = EI_FALSE;
        x = event.param.mouse.where.x;
        y = event.param.mouse.where.y;
        id_color = *(origin + (uint32_t)(x_max*y) + (uint32_t)x);
        if (active_widget != NULL){

            got_handled = active_widget->wclass->handlefunc(active_widget, &event);
            if (got_handled != EI_TRUE){
                active_widget = NULL;
            }

        }

        if (got_handled != EI_TRUE){

            if (is_widget_button(id_color, offscreen) == 1) {
                button = &(button_from_id(id_color, offscreen))->widget;
                got_handled = button->wclass->handlefunc(button, &event);
                if (got_handled){
                    active_widget = button;
                }
            } else if (is_widget_frame(id_color, offscreen) == 1) {
                frame = &(frame_from_id(id_color, offscreen))->widget;
                got_handled = frame->wclass->handlefunc(frame, &event);
                if (got_handled){
                    active_widget = frame;
                }
            } else if (is_widget_toplevel(id_color, offscreen) == 1) {
                toplevel = &toplevel_from_id(id_color, offscreen)->widget;
                got_handled = toplevel->wclass->handlefunc(toplevel, &event);
                if (got_handled){
                    active_widget = toplevel;
                }
            } else if (default_func != NULL){
                default_func(&event);
            }

        }
        update_window(root_surface, offscreen, root_widget);
        hw_event_wait_next(&event);
    }




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

