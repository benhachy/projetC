#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ei_widget.h"
#include "ei_widgetclass.h"
#include "ei_application.h"
#include "hw_interface.h"
#include "ei_utils.h"
#include "ei_types.h"
#include "ei_draw_widget.h"
#include "ei_event.h"
//#include "ei_utils_memory.h"

/*
static uint32_t counter_pick_id = 0;
static ei_axis_set_t axis = ei_axis_none;
static ei_bool_t false = EI_FALSE;
extern ei_surface_t* offscreen;
extern ei_widgetlist_t* widgetlist;
*/




ei_widget_t*    ei_widget_create(ei_widgetclass_name_t	class_name,
                                 ei_widget_t*		parent,
                                 void*			user_data,
                                 ei_widget_destructor_t destructor)
{

    ei_widgetclass_t *w_class = ei_widgetclass_from_name(class_name);
    ei_widget_t *new_widget = w_class->allocfunc();
    w_class->setdefaultsfunc(new_widget);
    new_widget->wclass = w_class;
    new_widget->parent = parent;
    parent->children_head = new_widget;
    new_widget->user_data = user_data;
    new_widget->destructor = destructor;
    return new_widget;
    
}

void ei_widget_destroy (ei_widget_t* widget)
{
    /*
        if (widget->destructor != NULL){
                widget->destructor(widget);
        }
        widget->wclass->releasefunc(widget);
        */
}

void			ei_frame_configure		(ei_widget_t*		widget,
                                           ei_size_t*		requested_size,
                                           const ei_color_t*	color,
                                           int*			border_width,
                                           ei_relief_t*		relief,
                                           char**			text,
                                           ei_font_t*		text_font,
                                           ei_color_t*		text_color,
                                           ei_anchor_t*		text_anchor,
                                           ei_surface_t*		img,
                                           ei_rect_t**		img_rect,
                                           ei_anchor_t*		img_anchor) {

    //Modification de la couleur du widget frame

    ei_color_t *non_const_color = (ei_color_t*) malloc(sizeof(ei_color_t));
    non_const_color->red = color->red;
    non_const_color->blue = color->blue;
    non_const_color->green = color->green;
    non_const_color->alpha = color->alpha;


    widget->pick_color = non_const_color;
    ei_surface_t root_surface = ei_app_root_surface();

    if (requested_size != NULL) {
        widget->requested_size = *(requested_size);
    }





}


/*
    //On détermine la classe du widget qu'on souhaite créer
    ei_widgetclass_t* widget_class = ei_widgetclass_from_name(class_name);
    //On alloue les instances nécessaires pour le widget
    ei_widget_t* widget = widget_class->allocfunc();
    // On configure les attributs du widget
    widget->wclass = ei_widgetclass_from_name(class_name);
    uint32_t pick = 1;
    widget->pick_id = pick;
    //On encode le tableau de couleur à partir de pick qui est sur 32 bits
    //32 bits -> 8bits
    uint8_t tab_color[4];
    tab_color[0] = (uint8_t)pick;
    tab_color[1] = (uint8_t)(pick>>8);
    tab_color[2] = (uint8_t)(pick>>16);
    tab_color[3] = (uint8_t)(pick>>24);
    ei_color_t* color = malloc(sizeof(ei_color_t));
    color->red = tab_color[0];
    color->green = tab_color[1];
    color->blue = tab_color[2];
    color->alpha = tab_color[3];
    widget->pick_color = color;
    widget -> user_data = user_data;
    widget->destructor = destructor;
    // On configure la hiérarchie du widget
    widget->parent = parent;
    if (parent != NULL){
            if (widget->parent->children_tail == NULL){
                    widget->parent->children_head = widget;
                    widget->parent->children_tail = widget;
            }else{
                    widget->parent->children_tail->next_sibling = widget;
                    widget->parent->children_tail = widget;
            }
            widget->parent->children_tail->next_sibling = NULL;
    }

    // On configure la géométrie du widget
    widget->placer_params = NULL;
    widget->requested_size = ei_size_zero();
    widget->screen_location = ei_rect_zero();
    widget->content_rect = &widget->screen_location;
    widget->wclass->setdefaultsfunc(widget);

    return widget;
*/