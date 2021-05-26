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

int corner_default = 10;
int* corner_default_ptr = &corner_default;

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


    //Computing the chain of the parent's children
    ei_widget_t* temp_child = parent->children_head;
    if (temp_child == NULL){
        parent->children_head = new_widget;
    } else {
        while (temp_child->next_sibling !=NULL){
            temp_child = temp_child->next_sibling;
        }
        temp_child->next_sibling = new_widget;
    }


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

    recursion_destroy(widget);
    if (widget->parent == NULL){
        //On ne fait rien si le widget est le widget racine
    } else if (widget->parent->children_head == widget) {
        if (widget->next_sibling == NULL) {
            widget->parent->children_head = NULL;
        } else {
            widget->parent->children_head = widget->next_sibling;
        }
    } else {
        ei_widget_t* temp_child = widget->parent->children_head;
        while(temp_child->next_sibling->pick_id != widget->pick_id){
            temp_child = temp_child->next_sibling;
        }
        temp_child->next_sibling = temp_child->next_sibling->next_sibling;
    }

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
    int zero = 0;
    int* ptr_to_zero = &zero;
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
    if (border_width != NULL) {
        frame->border_width = border_width;
    } else {
        frame->border_width = ptr_to_zero;
    }
    if (relief != NULL){
        frame->relief = *relief;
    } else {
        frame->relief = ei_relief_none;
    }

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
        float r = 0.35;
        float y_rel = 0.25;
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

        free(text_width);
        free(text_height);
    }


    if (img != NULL) {

        ei_widget_t *image_widget = ei_widget_create("image", widget, NULL, NULL);
        ei_place(image_widget, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
        int *img_width = (int *) malloc(sizeof(int));
        int *img_height = (int *) malloc(sizeof(int));

        if (img_anchor != NULL) {
            image_widget->placer_params->anchor = img_anchor;
            image_widget->placer_params->anchor_data = *img_anchor;
        }
        ei_image_cell *image_cell = get_image_cell(image_widget);


        image_cell->img_rect = img_rect;

        image_cell->img = *img;

        int r = *(frame->border_width);
        int y_rel = *(frame->border_width);
        int *ptr = &r;
        int *ptr_y = &y_rel;

        image_widget->placer_params->x_data = r;
        image_widget->placer_params->y_data = y_rel;
        image_widget->placer_params->x = ptr;
        image_widget->placer_params->y = ptr_y;
        image_widget->placer_params->w = img_width;
        image_widget->placer_params->h = img_height;
        ei_placer_run(image_widget);

        free(img_width);
        free(img_height);

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
    if (corner_radius != NULL) {
        button->corner_radius = corner_radius;
    } else {
        button->corner_radius = corner_default_ptr;
    }

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
        float r = 0.35;
        float y_rel = 0.25;
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
    if (img != NULL) {

        ei_widget_t *image_widget = ei_widget_create("image", widget, NULL, NULL);
        ei_place(image_widget, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
        int *img_width = (int *) malloc(sizeof(int));
        int *img_height = (int *) malloc(sizeof(int));

        if (img_anchor != NULL) {
            image_widget->placer_params->anchor = img_anchor;
            image_widget->placer_params->anchor_data = *img_anchor;
        }
        ei_image_cell *image_cell = get_image_cell(image_widget);


        image_cell->img_rect = img_rect;

        image_cell->img = *img;

        int r = *(button->border_width);
        int y_rel = *(button->border_width);
        int *ptr = &r;
        int *ptr_y = &y_rel;

        image_widget->placer_params->x_data = r;
        image_widget->placer_params->y_data = y_rel;
        image_widget->placer_params->x = ptr;
        image_widget->placer_params->y = ptr_y;
        image_widget->placer_params->w = img_width;
        image_widget->placer_params->h = img_height;
        ei_placer_run(image_widget);

        free(img_width);
        free(img_height);

    }


    if (callback != NULL){
        button->callback = *callback;
    } else {
        button->callback = NULL;
    }

    if (user_param != NULL){
        button->user_param = user_param;
    }

}

void			ei_toplevel_configure		(ei_widget_t*		widget,
                                              ei_size_t*		requested_size,
                                              ei_color_t*		color,
                                              int*			border_width,
                                              char**			title,
                                              ei_bool_t*		closable,
                                              ei_axis_set_t*		resizable,
                                              ei_size_t**		min_size){

    ei_toplevel_cell* toplevel = get_toplevel_cell(widget);

    //We make sure that the toplevel isn't too small
    if (min_size != NULL){
        if (*min_size != NULL) {
            ei_size_t *act_min_size = *min_size;
            if (act_min_size->height < 100) {
                act_min_size->height = 100;
            }
            if (act_min_size->width < 100) {
                act_min_size->width = 100;
            }
            toplevel->min_size = act_min_size;
        }
    } else {
        ei_size_t* ptr_to_size = (ei_size_t*)malloc(sizeof(ei_size_t));
        ptr_to_size->width = 100;
        ptr_to_size->height = 100;
        toplevel->min_size = ptr_to_size;
    }

    //Configuring the resizable parametre
    if (resizable != NULL){
        toplevel->resizable = resizable;
    } else {
        ei_axis_set_t axis = ei_axis_none;
        toplevel->resizable = &axis;
    }

    //Configuring the closable parametre
    if (closable != NULL){
        toplevel->closable = closable;
    } else {
        ei_bool_t closeness = EI_FALSE;
        toplevel->closable = &closeness;
    }

    //If the requested size is given :
    if (requested_size != NULL){
        widget->requested_size = *requested_size;
    }

    //Computation of the background frame color
    if (color != NULL){
        toplevel->color = color;
    } else {
        toplevel->color = (ei_color_t*) malloc(sizeof(ei_color_t));
        toplevel->color->alpha = 255;
        toplevel->color->red = 255;
        toplevel->color->green = 255;
        toplevel->color->blue = 255;
    }

    if (closable != NULL) {
        ei_widget_t *button_widget = ei_widget_create("button", widget, NULL, NULL);
        int width = 16;
        int height = 16;
        int x = 12;
        int y_rel = 5;
        int* ptr = &x;
        int* ptr_y = &y_rel;
        int* ptr_width = &width;
        int* ptr_height = &height;
        ei_place(button_widget, NULL, ptr, ptr_y, ptr_width, ptr_height, NULL, NULL, NULL, NULL);


        ei_button_cell *button_cell = get_button_cell(button_widget);
        ei_color_t red_color = {255, 0, 0};

        button_cell->color = &red_color;
        button_cell->relief = ei_relief_raised;
        ei_placer_run(button_widget);
    }
    if (title != NULL) {
        if (*title != NULL) {
            ei_widget_t *text_widget = ei_widget_create("text", widget, NULL, NULL);
            ei_place(text_widget, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            int *text_width = (int *) malloc(sizeof(int));
            int *text_height = (int *) malloc(sizeof(int));

            ei_text_cell *text_cell = get_text_cell(text_widget);


            ei_color_t  black_color = {0,0,0,0};
            text_cell->color = &black_color;
            text_cell->text = title;
            text_cell->text_font = ei_default_font;

            float r = 0.15;
            float y_rel = 0;
            float *ptr = &r;
            float *ptr_y = &y_rel;
            hw_text_compute_size(*title, text_cell->text_font, text_width, text_height);
            text_widget->placer_params->rx_data = r;
            text_widget->placer_params->ry_data = y_rel;
            text_widget->placer_params->rx = ptr;
            text_widget->placer_params->ry = ptr_y;
            text_widget->placer_params->w = text_width;
            text_widget->placer_params->h = text_height;
            ei_placer_run(text_widget);

            free(text_width);
            free(text_height);
        }
    }


}


