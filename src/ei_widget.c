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
    widget->pick_color = non_const_color;


    if (requested_size != NULL) {
        widget->requested_size = *(requested_size);
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
    widget->pick_color = non_const_color;


    if (requested_size != NULL) {
        widget->requested_size = *(requested_size);
    }

}