#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ei_widget.h"
#include "ei_widget_class.h"
#include "ei_application.h"
#include "hw_interface.h"
#include "ei_utils.h"
#include "ei_types.h"
#include "ei_event.h"


ei_widget_t*    ei_widget_create(ei_widgetclass_name_t	class_name,
                                 ei_widget_t*		parent,
                                 void*			user_data,
                                 ei_widget_destructor_t destructor)
{
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
        color_tab[0] = (uint8_t)pick;
        color_tab[1] = (uint8_t)(pick>>8);
        color_tab[2] = (uint8_t)(pick>>16);
        color_tab[3] = (uint8_t)(pick>>24);
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

}

void ei_widget_destroy (ei_widget_t* widget)
{
        if (widget->destructor != NULL){
                widget->destructor(widget);
        }
        widget->wclass->releasefunc(widget);
}


