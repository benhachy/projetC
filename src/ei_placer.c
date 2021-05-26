//
// Created by menouar on 16/05/2021.
//

#include "ei_types.h"
#include "ei_widget.h"
#include "ei_draw_widget.h"

void ei_placer_run(struct ei_widget_t* widget){

    ei_button_cell head = get_button_cell_head();
    ei_button_cell* button_cell;

    if(strcmp(widget->wclass->name,"button")==0){
        button_cell = get_button_cell(widget);
    }

    ei_rect_t *new_rect = (ei_rect_t*)malloc(sizeof(ei_rect_t));
    ei_rect_t  new_parent_location = widget->parent->screen_location;
    ei_point_t parent_top_left = widget->parent->screen_location.top_left;

    int actual_width = 0;
    int actual_height = 0;

    if (strcmp(widget->wclass->name,"button") == 0){
        actual_width = 100;
        actual_height = 40;
    } else {
        actual_width = 10;
        actual_height = 10;
    }

    int actual_x = parent_top_left.x;
    int actual_y = parent_top_left.y;
    ei_anchor_t actual_anchor = ei_anc_northwest;

    if (widget->placer_params->w != NULL){
        actual_width = widget->placer_params->w_data;
    } else if (widget->placer_params->rw != NULL){
        actual_width = widget->parent->screen_location.size.width*(widget->placer_params->rw_data);
    } else
        {
         //Si le programmeur a demandé une largeur spécifique....
         if (widget->requested_size.width != 0) {
             actual_width = widget->requested_size.width;
         } else {
             //Sinon on utilise une largeur par défaut : Soit...
             if (widget->children_head != NULL) {
                 if (widget->children_head->placer_params->w != NULL) {
                        //La largeur du premier enfant + 5px
                        if (strcmp(widget->wclass->name,"button") != 0) {
                          actual_width = widget->children_head->placer_params->w_data + 5;
                      }
                     }
               }
           }
    }

    //On fait de même pour la hauteur du widget :

    if (widget->placer_params->h != NULL){
        actual_height = widget->placer_params->h_data;
    }else if (widget->placer_params->rh != NULL){
        actual_width = widget->parent->screen_location.size.height*(widget->placer_params->rh_data);
    } else {
        if (widget->requested_size.height != 0) {
            actual_height = widget->requested_size.height;
        } else {
            if (widget->children_head != NULL) {
                if (widget->children_head->placer_params->h != NULL) {
                    if (strcmp(widget->wclass->name,"button") != 0) {
                        actual_height = widget->children_head->placer_params->h_data + 5;
                    }
                }
            }
        }
    }


    if (widget->placer_params->anchor != NULL || widget->placer_params->anchor_data == ei_anc_none){
        actual_anchor = widget->placer_params->anchor_data;
    }

    if(widget->placer_params->x != NULL){
        if (widget->placer_params->rx != NULL) {
            actual_x = parent_top_left.x + widget->placer_params->x_data + (widget->placer_params->rx_data*(float)new_parent_location.size.width);
        } else {
            actual_x = parent_top_left.x + widget->placer_params->x_data;
        }
    } else {
        if (widget->placer_params->rx != NULL) {
            actual_x = parent_top_left.x + (widget->placer_params->rx_data*(float)new_parent_location.size.width);
        }
    }

    if(widget->placer_params->y != NULL){
        if (widget->placer_params->ry != NULL) {
            actual_y = parent_top_left.y + widget->placer_params->y_data + (widget->placer_params->ry_data*(float)new_parent_location.size.height);
        } else {
            actual_y = parent_top_left.y + widget->placer_params->y_data;
        }
    } else {
        if (widget->placer_params->ry != NULL) {
            actual_y = parent_top_left.y + (widget->placer_params->ry_data*(float)new_parent_location.size.height);
        }
    }

    //In the case of a toplevel_widget, we make sure that it isn't too small
    if (strcmp(widget->wclass->name,"toplevel") == 0){

        if (actual_width < 100){
            actual_width = 100;
        }
        if (actual_height < 100){
            actual_height = 100;
        }

    }

    if (actual_anchor == ei_anc_center){

        new_rect->size.width = actual_width;
        new_rect->size.height = actual_height;
        new_rect->top_left.x = actual_x - actual_width/2;
        new_rect->top_left.y = actual_y - actual_height/2;

        widget->content_rect = new_rect;
        widget->screen_location = *new_rect;

    } else if (actual_anchor == ei_anc_north){
        new_rect->size.width = actual_width;
        new_rect->size.height = actual_height;
        new_rect->top_left.x = actual_x - actual_width/2;
        new_rect->top_left.y = actual_y;

        widget->content_rect = new_rect;
        widget->screen_location = *new_rect;
    } else if (actual_anchor == ei_anc_northeast){
        new_rect->size.width = actual_width;
        new_rect->size.height = actual_height;
        new_rect->top_left.x = actual_x - actual_width;
        new_rect->top_left.y = actual_y;

        widget->content_rect = new_rect;
        widget->screen_location = *new_rect;
    } else if (actual_anchor == ei_anc_east){
        new_rect->size.width = actual_width;
        new_rect->size.height = actual_height;
        new_rect->top_left.x = actual_x - actual_width;
        new_rect->top_left.y = actual_y - actual_height/2;

        widget->content_rect = new_rect;
        widget->screen_location = *new_rect;
    } else if (actual_anchor == ei_anc_southeast){
        new_rect->size.width = actual_width;
        new_rect->size.height = actual_height;
        new_rect->top_left.x = actual_x - actual_width;
        new_rect->top_left.y = actual_y - actual_height;

        widget->content_rect = new_rect;
        widget->screen_location = *new_rect;
    } else if (actual_anchor == ei_anc_south){
        new_rect->size.width = actual_width;
        new_rect->size.height = actual_height;
        new_rect->top_left.x = actual_x - actual_width/2;
        new_rect->top_left.y = actual_y - actual_height;

        widget->content_rect = new_rect;
        widget->screen_location = *new_rect;
    } else if (actual_anchor == ei_anc_southwest){
        new_rect->size.width = actual_width;
        new_rect->size.height = actual_height;
        new_rect->top_left.x = actual_x;
        new_rect->top_left.y = actual_y - actual_height;

        widget->content_rect = new_rect;
        widget->screen_location = *new_rect;
    } else if (actual_anchor == ei_anc_west) {
        new_rect->size.width = actual_width;
        new_rect->size.height = actual_height;
        new_rect->top_left.x = actual_x;
        new_rect->top_left.y = actual_y - actual_height/2;

        widget->content_rect = new_rect;
        widget->screen_location = *new_rect;
    } else {
        new_rect->size.width = actual_width;
        new_rect->size.height = actual_height;
        new_rect->top_left.x = actual_x;
        new_rect->top_left.y = actual_y;

        widget->content_rect = new_rect;
        widget->screen_location = *new_rect;
        printf("piou");
    }

    if(strcmp(widget->wclass->name,"button")==0){
        button_cell->widget = *widget;
        printf("piou");
    }
}

void		ei_place	(struct ei_widget_t*	widget,
                         ei_anchor_t*		anchor,
                         int*			x,
                         int*			y,
                         int*			width,
                         int*			height,
                         float*			rel_x,
                         float*			rel_y,
                         float*			rel_width,
                         float*			rel_height) {

    //Si c'est la première fois que le widget est placé
    if (widget->placer_params == NULL) {
        widget->placer_params = (ei_placer_params_t *) malloc(sizeof(ei_placer_params_t));

        //On initialise les paramètres du placeur à NULL
        widget->placer_params->h = NULL;
        widget->placer_params->w = NULL;
        widget->placer_params->x = NULL;
        widget->placer_params->y = NULL;
        widget->placer_params->rh = NULL;
        widget->placer_params->rw = NULL;
        widget->placer_params->rx = NULL;
        widget->placer_params->ry = NULL;
    }

        //Si des paramètres non null sont donnés on les modifie
        if (anchor != NULL){
            widget->placer_params->anchor = anchor;
            widget->placer_params->anchor_data = *anchor;
        }
        if (x != NULL) {
            widget->placer_params->x = x;
            widget->placer_params->x_data = *x;
        }
        if (y != NULL){
            widget->placer_params->y = y;
            widget->placer_params->y_data = *y;
        }
        if (width != NULL){
            widget->placer_params->w = width;
            widget->placer_params->w_data = *width;
        }
        if (height != NULL){
            widget->placer_params->h = height;
            widget->placer_params->h_data = *height;
        }
        if (rel_x != NULL){
            widget->placer_params->rx = rel_x;
            widget->placer_params->rx_data = *rel_x;
        }
        if (rel_y != NULL){
            widget->placer_params->ry = rel_y;
            widget->placer_params->ry_data = *rel_y;
        }
        if (rel_width != NULL){
            widget->placer_params->rw = rel_width;
            widget->placer_params->rw_data = *rel_width;
        }
        if (rel_height != NULL){
            widget->placer_params->rh = rel_height;
            widget->placer_params->rh_data = *rel_height;
        }

    //On run le placeur une première fois pour positionner le widget selon son parent
    ei_placer_run(widget);

    //On repositionne tous les enfants du widgets si on a fait un nouvel appel à ei_place
    ei_widget_t* child = widget->children_head;
    while(child != NULL){
        ei_placer_run(child);
        child = child->next_sibling;
    }
    }
