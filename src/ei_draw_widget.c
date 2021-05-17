#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ei_draw_widget.h"
#include "ei_widget.h"
#include "ei_widgetclass.h"

void dessin(ei_widget_t* widget, ei_surface_t surface, ei_surface_t offscreen){
     
     //On commence par appeler la fonction drawfunc pour dessiner le premier widget
     widget->wclass->drawfunc(widget, surface, offscreen, (widget->content_rect));
     ei_widget_t* descendant = widget->children_head;
     //On appelle récursivement la fonction pour dessiner tous les descendants dans la hiérarchie
        while (descendant != NULL)
        {
                dessin(descendant, surface, offscreen);
                descendant = descendant->next_sibling;
        }


}
