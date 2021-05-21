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


int red_id = 0;

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

    ei_color_t* id_color = (ei_color_t*)malloc(sizeof(ei_color_t));
    red_id++;
    id_color->red = red_id;
    id_color->blue = 0;
    id_color->green = 0;
    id_color->alpha = 0;
    uint32_t int_color = red_id;
    new_widget->pick_color = id_color;
    new_widget->pick_id = int_color;

    return new_widget;
}

void ei_widget_destroy (ei_widget_t* widget)
{

        if (widget->destructor != NULL){
                widget->destructor(widget);
        } else {
            widget->wclass->releasefunc(widget);
        }
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

    ei_frame_cell* frame = get_frame_cell(widget);

    //Modification de la couleur du widget frame

    //Si aucune couleur donnée , on utilise la couleur par défaut
    if (color == NULL ) {
        if (frame->color == NULL) {
            frame->color = (ei_color_t *) malloc(sizeof(ei_color_t));
            frame->color->red = ei_default_background_color.red;
            frame->color->blue = ei_default_background_color.blue;
            frame->color->green = ei_default_background_color.green;
            frame->color->alpha = ei_default_background_color.alpha;
        }
    } else {
        if (frame->color == NULL){
            frame->color = (ei_color_t *) malloc(sizeof(ei_color_t));
        }
        frame->color->red = color->red;
        frame->color->blue = color->blue;
        frame->color->green = color->green;
        frame->color->alpha = color->alpha;
    }


    //Configuration du requested size
    if (requested_size != NULL) {
        widget->requested_size = *(requested_size);
    }

    //Configuration de la bordure et du relief
    frame->border_width = border_width;
    if (relief != NULL){
        frame->relief = *relief;
    } else {
        frame->relief = ei_relief_none;
    }

}

void			ei_button_configure		(ei_widget_t*		widget,
                                            ei_size_t*		requested_size,
                                            const ei_color_t*	color,
                                            int*			border_width,
                                            int*			corner_radius,
                                            ei_relief_t*		relief,
                                            char**			text,
                                            ei_font_t*		text_font,
                                            ei_color_t*		text_color,
                                            ei_anchor_t*		text_anchor,
                                            ei_surface_t*		img,
                                            ei_rect_t**		img_rect,
                                            ei_anchor_t*		img_anchor,
                                            ei_callback_t*		callback,
                                            void**			user_param){

    ei_button_cell* button = get_button_cell(widget);

    //Modification de la couleur du widget frame
    ei_color_t *non_const_color = (ei_color_t *) malloc(sizeof(ei_color_t));
    //Si aucune couleur donnée , on utilise la couleur par défaut
    if (color == NULL) {
        non_const_color->red = ei_default_background_color.red;
        non_const_color->blue = ei_default_background_color.blue;
        non_const_color->green = ei_default_background_color.green;
        non_const_color->alpha = ei_default_background_color.alpha;
    } else {
        non_const_color->red = color->red;
        non_const_color->blue = color->blue;
        non_const_color->green = color->green;
        non_const_color->alpha = color->alpha;
    }
    button->color = non_const_color;


    if (requested_size != NULL) {
        widget->requested_size = *(requested_size);
    }

    //Configuration de la bordure et du relief
    button->border_width = border_width;
    if (relief != NULL){
        button->relief = *relief;
    } else {
        button->relief = ei_relief_raised;
    }
    button->corner_radius = corner_radius;

    //Si présence de texte on configure le widget text enfant:
    if (text != NULL) {
        ei_widget_t *text_widget = ei_widget_create("text", widget, NULL, NULL);
        ei_place(text_widget, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
        int* text_width = (int*)malloc(sizeof(int));// TO FREEEEEE
        int* text_height= (int*)malloc(sizeof(int));//TO FREEEEEE
        if (text_anchor != NULL) {
            text_widget->placer_params->anchor = text_anchor;
            text_widget->placer_params->anchor_data = *text_anchor;
        }
        ei_text_cell *text_cell = get_text_cell(text_widget);

        text_cell->color = text_color;
        text_cell->text = text;
        if (text_font != NULL) {
            text_cell->text_font = text_font;
        } else {
            text_cell->text_font = ei_default_font;
        }
        float r = 0.15;
        float y_rel = 0.4;
        float* ptr = &r;
        float* ptr_y = &y_rel;
        hw_text_compute_size(*text, text_cell->text_font, text_width, text_height);
        text_widget->placer_params->rx_data = r;
        text_widget->placer_params->ry_data = y_rel;
        text_widget->placer_params->rx = ptr;
        text_widget->placer_params->ry = ptr_y;
        text_widget->placer_params->w = text_width;
        text_widget->placer_params->h = text_height;
        ei_placer_run(text_widget);
    }

}