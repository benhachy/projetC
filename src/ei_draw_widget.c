#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ei_draw_widget.h"
#include "ei_widget.h"
#include "ei_widgetclass.h"
#include "button.h"
#include "ei_draw.h"

ei_frame_cell frame_cell_head = {
        NULL,
        NULL,
        NULL,
        ei_relief_none,
        NULL,
};


ei_button_cell button_cell_head = {
        NULL,
        NULL,
        NULL,
        NULL,
        ei_relief_raised,
};

ei_text_cell text_cell_head = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
};


void dessin(ei_widget_t* widget, ei_surface_t surface, ei_surface_t offscreen){

     //On commence par appeler la fonction drawfunc pour dessiner le premier widget
     widget->wclass->drawfunc(widget, surface, offscreen, NULL);
     ei_widget_t* descendant = widget->children_head;
     //On appelle récursivement la fonction pour dessiner tous les descendants dans la hiérarchie
        while (descendant != NULL)
        {
                dessin(descendant, surface, offscreen);
                descendant = descendant->next_sibling;
        }


}


//                                                    ||ALLOW FUNCTIONS||




struct ei_widget_t* allowfunc_frame(void) {
    struct ei_widget_t* frame_wid = (struct ei_widget_t*)malloc(sizeof(struct ei_widget_t));

    frame_wid->wclass = NULL;
    frame_wid->pick_id = 0;
    frame_wid->pick_color = NULL;
    frame_wid->user_data = NULL;
    frame_wid->destructor = NULL;

    //Setting family parameters to NULL
    frame_wid->parent = NULL;
    frame_wid->children_head = NULL;
    frame_wid->children_tail = NULL;
    frame_wid->next_sibling = NULL;

    //Setting geometry parameters to NULL
    frame_wid->placer_params = NULL;
    frame_wid->requested_size.height = 0;
    frame_wid->requested_size.width = 0;
    frame_wid->screen_location.top_left.x = 0;
    frame_wid->screen_location.top_left.y = 0;
    frame_wid->content_rect = NULL;

    return frame_wid;


};

struct ei_widget_t* allowfunc_button(void) {
    struct ei_widget_t* button_wid = (struct ei_widget_t*)malloc(sizeof(struct ei_widget_t));

    button_wid->wclass = NULL;
    button_wid->pick_id = 0;
    button_wid->pick_color = NULL;
    button_wid->user_data = NULL;
    button_wid->destructor = NULL;

    //Setting family parameters to NULL
    button_wid->parent = NULL;
    button_wid->children_head = NULL;
    button_wid->children_tail = NULL;
    button_wid->next_sibling = NULL;

    //Setting geometry parameters to NULL
    button_wid->placer_params = NULL;
    button_wid->requested_size.height = 0;
    button_wid->requested_size.width = 0;
    button_wid->screen_location.top_left.x = 0;
    button_wid->screen_location.top_left.y = 0;
    button_wid->content_rect = NULL;

    return button_wid;
};


struct ei_widget_t* allowfunc_text(void) {
    struct ei_widget_t* text_wid = (struct ei_widget_t*)malloc(sizeof(struct ei_widget_t));

    text_wid->wclass = NULL;
    text_wid->pick_id = 0;
    text_wid->pick_color = NULL;
    text_wid->user_data = NULL;
    text_wid->destructor = NULL;

    //Setting family parameters to NULL
    text_wid->parent = NULL;
    text_wid->children_head = NULL;
    text_wid->children_tail = NULL;
    text_wid->next_sibling = NULL;

    //Setting geometry parameters to NULL
    text_wid->placer_params = NULL;
    text_wid->requested_size.height = 0;
    text_wid->requested_size.width = 0;
    text_wid->screen_location.top_left.x = 0;
    text_wid->screen_location.top_left.y = 0;
    text_wid->content_rect = NULL;

    return text_wid;
};


//                                                   ||RELEASE FUNCTIONS||




void releasefunc_frame(struct ei_widget_t* frame_wid){

    free(frame_wid->wclass);
    free(frame_wid->pick_color);
    free(frame_wid->user_data);
    free(frame_wid->destructor);

    //Setting family parameters to NULL
    free(frame_wid->parent);
    free(frame_wid->children_head);
    free(frame_wid->children_tail);
    free(frame_wid->next_sibling);

    //Setting geometry parameters to NULL
    free(frame_wid->placer_params);
    free(frame_wid->content_rect);

    free(frame_wid);

}

void releasefunc_button(struct ei_widget_t* button_wid){

    free(button_wid->wclass);
    free(button_wid->pick_color);
    free(button_wid->user_data);
    free(button_wid->destructor);

    //Setting family parameters to NULL
    free(button_wid->parent);
    free(button_wid->children_head);
    free(button_wid->children_tail);
    free(button_wid->next_sibling);

    //Setting geometry parameters to NULL
    free(button_wid->placer_params);
    free(button_wid->content_rect);

    free(button_wid);

}


void releasefunc_text(struct ei_widget_t* text_wid){

    free(text_wid->wclass);
    free(text_wid->pick_color);
    free(text_wid->user_data);
    free(text_wid->destructor);

    //Setting family parameters to NULL
    free(text_wid->parent);
    free(text_wid->children_head);
    free(text_wid->children_tail);
    free(text_wid->next_sibling);

    //Setting geometry parameters to NULL
    free(text_wid->placer_params);
    free(text_wid->content_rect);

    free(text_wid);

}


//                                                   ||DRAWING FUNCTIONS||


void	drawfunc_frame		(struct ei_widget_t*	widget,
                               ei_surface_t		surface,
                               ei_surface_t		pick_surface,
                               ei_rect_t*		clipper){

    ei_frame_cell* frame = get_frame_cell(widget);

    ei_point_t top_right = {0,0};
    ei_point_t bottom_left = {0,0};
    ei_point_t bottom_right = {0,0};
    ei_point_t top_left = widget->screen_location.top_left;
    ei_size_t size_frame = widget->screen_location.size;

    top_right.x = top_left.x + size_frame.width;
    top_right.y = top_left.y;

    bottom_left.x = top_left.x;
    bottom_left.y = top_left.y + size_frame.height;

    bottom_right.x = top_left.x + size_frame.width;
    bottom_right.y = top_left.y + size_frame.height;

    ei_linked_point_t *frame_pt = (ei_linked_point_t *)malloc(sizeof(ei_linked_point_t));
    frame_pt->point = top_left;
    frame_pt->next = (ei_linked_point_t *)malloc(sizeof(ei_linked_point_t));
    frame_pt->next->point = top_right;
    frame_pt->next->next = (ei_linked_point_t *)malloc(sizeof(ei_linked_point_t));
    frame_pt->next->next->point = bottom_right;
    frame_pt->next->next->next = (ei_linked_point_t *)malloc(sizeof(ei_linked_point_t));
    frame_pt->next->next->next->point = bottom_left;
    frame_pt->next->next->next->next = (ei_linked_point_t *)malloc(sizeof(ei_linked_point_t));
    frame_pt->next->next->next->next->point = top_left;
    frame_pt->next->next->next->next->next = NULL;

    ei_draw_polygon(surface,frame_pt,*(frame->color),clipper);
    ei_draw_polygon(pick_surface, frame_pt, *(widget->pick_color), clipper);

    //Free the points used for drawing
    while(frame_pt!= NULL){
        ei_linked_point_t *to_delete = frame_pt;
        frame_pt = frame_pt->next;
        free(to_delete);
    }


}

void	drawfunc_button		(struct ei_widget_t*	widget,
                               ei_surface_t		surface,
                               ei_surface_t		pick_surface,
                               ei_rect_t*		clipper){

    ei_button_cell* button = get_button_cell(widget);
    ei_point_t top_left = widget->screen_location.top_left;
    ei_size_t size = widget->screen_location.size;
    ei_rect_t rect = {top_left, size};
    int border_width;

    //We make sure that the border_width is not too small
    if (*(button->border_width) < 10){
        border_width = 10;
    } else {
        border_width =  *(button->border_width);
    }

    //Draws the button given its relief
    if (button->relief == ei_relief_raised) {
        draw_button(surface, pick_surface, clipper, rect, *(button->corner_radius), *(button->color),*(widget->pick_color), border_width,0);
    } else {
        draw_button(surface, pick_surface, clipper, rect, *(button->corner_radius), *(button->color),*(widget->pick_color), border_width, 1);
    }

}

void	drawfunc_text		(struct ei_widget_t*	widget,
                              ei_surface_t		surface,
                              ei_surface_t		pick_surface,
                              ei_rect_t*		clipper){
    ei_text_cell* text_cell = text_from_id(widget->pick_id, surface);
    ei_point_t* where = &(widget->screen_location.top_left);
    char* text = *(text_cell->text);
    ei_font_t  font = text_cell->text_font;
    ei_color_t  color = *(text_cell->color);

    ei_draw_text(surface, where, text, font, color, clipper);
    //Pas besoin de dessiner dans l'offscreen (le texte n'est pas un vrai widget)
}


//                                                   ||SET DEFAULT FUNCTIONS||



void	setdefaultsfunc_frame	(struct ei_widget_t*	widget){

    ei_point_t top_left = {0,0};
    //By default every frame is a square of size 10pixels
    ei_size_t size = {10,10};
    ei_rect_t screen_location = {top_left, size};
    widget->content_rect = &(widget->screen_location);

}


void	setdefaultsfunc_button	(struct ei_widget_t*	widget){

    ei_point_t top_left = {0,0};
    //By default every frame is a square of size 10pixels
    ei_size_t size = {10,10};
    ei_rect_t screen_location = {top_left, size};
    widget->content_rect = &(widget->screen_location);

}

void	setdefaultsfunc_text	(struct ei_widget_t*	widget){

    ei_point_t top_left = {0,0};
    //By default every frame is a square of size 10pixels
    ei_size_t size = {10,10};
    ei_rect_t screen_location = {top_left, size};
    widget->content_rect = &(widget->screen_location);

}

//                                                   ||GEOMNOMNOMNOM FUNCTIONS||



void	geomnotifyfunc_frame	(struct ei_widget_t*	widget,
                                 ei_rect_t		rect){

}


void	geomnotifyfunc_button	(struct ei_widget_t*	widget,
                                 ei_rect_t		rect){

}

void	geomnotifyfunc_text	(struct ei_widget_t*	widget,
                                  ei_rect_t		rect){

}

//                                                   ||CAN YOU EVEN HANDLE ME? FUNCTIONS||


ei_bool_t ei_frame_handlefunc_t (struct ei_widget_t*	widget,
                                 struct ei_event_t*	event){
    return 0;
}

ei_bool_t ei_button_handlefunc_t (struct ei_widget_t*	widget,
                                 struct ei_event_t*	event){
    return 0;
}

ei_bool_t ei_text_handlefunc_t (struct ei_widget_t*	widget,
                                  struct ei_event_t*	event){
    return 0;
}


struct ei_frame_cell* get_frame_cell(struct ei_widget_t* widget){
    ei_frame_cell *temp = &frame_cell_head;

    //Si la liste chainée est vide
    if (temp->widget == NULL){
        temp->widget = widget;
        temp->next = NULL;
        return temp;
    } else {
        if (temp->widget->pick_id == widget->pick_id){
            return temp;
        }
        while (temp->next != NULL ) {
            //Si la prochaine cellule est la bonne on la retourne
            if (temp->next->widget->pick_id == widget->pick_id){
                return temp->next;
            //Sinon on cherche encore
            } else {
                temp = temp->next;
            }
        }
        //Si on a pas trouvé de cellule on en crée une nouvelle
        if (temp->next == NULL) {
            temp->next = (ei_frame_cell*)malloc(sizeof(ei_frame_cell));
            temp->next->widget = widget;
            temp->next->next = NULL;
            return temp->next;
        }
    }
}



struct ei_button_cell* get_button_cell(struct ei_widget_t* widget){
    ei_button_cell *temp = &button_cell_head;

    //Si la liste chainée est vide
    if (temp->widget == NULL){
        temp->widget = widget;
        temp->next = NULL;
    } else {
        if (temp->widget->pick_id == widget->pick_id){
            return temp;
        }
        while (temp->next != NULL ) {
            //Si la prochaine cellule est la bonne on la retourne
            if (temp->next->widget->pick_id == widget->pick_id){
                return temp->next;
                //Sinon on cherche encore
            } else {
                temp = temp->next;
            }
        }
        //Si on a pas trouvé de cellule on en crée une nouvelle
        if (temp->next == NULL) {
            temp->next = (ei_button_cell*)malloc(sizeof(ei_button_cell));
            temp->next->widget = widget;
            temp->next->next = NULL;
            return temp->next;
        }
    }
}


struct ei_text_cell* get_text_cell(struct ei_widget_t* widget){
    ei_text_cell *temp = &text_cell_head;

    //Si la liste chainée est vide
    if (temp->widget == NULL){
        temp->widget = widget;
        temp->next = NULL;
    } else {
        if (temp->widget->pick_id == widget->pick_id){
            return temp;
        }
        while (temp->next != NULL ) {
            //Si la prochaine cellule est la bonne on la retourne
            if (temp->next->widget->pick_id == widget->pick_id){
                return temp->next;
                //Sinon on cherche encore
            } else {
                temp = temp->next;
            }
        }
        //Si on a pas trouvé de cellule on en crée une nouvelle
        if (temp->next == NULL) {
            temp->next = (ei_text_cell*)malloc(sizeof(ei_text_cell));
            temp->next->widget = widget;
            temp->next->next = NULL;
            return temp->next;
        }
    }
}


int is_widget_frame(uint32_t id, ei_surface_t surface){
    ei_frame_cell *temp = &frame_cell_head;
    while (temp->widget != NULL){
        if (ei_map_rgba(surface, *(temp->widget->pick_color) ) == id){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}


int is_widget_button(uint32_t id, ei_surface_t surface){
    ei_button_cell *temp = &button_cell_head;
    while (temp->widget != NULL){
        if (ei_map_rgba(surface, *(temp->widget->pick_color) ) == id){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

int is_widget_text(uint32_t id, ei_surface_t surface){
    ei_text_cell *temp = &text_cell_head;
    while (temp->widget != NULL){
        if (ei_map_rgba(surface, *(temp->widget->pick_color) ) == id){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}


struct ei_button_cell* button_from_id(uint32_t id, ei_surface_t surface){
    ei_button_cell *temp = &button_cell_head;
    while (temp != NULL){
        if (ei_map_rgba(surface, *(temp->widget->pick_color) ) == id){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

struct ei_frame_cell* frame_from_id(uint32_t id, ei_surface_t surface){
    ei_frame_cell *temp = &frame_cell_head;
    while (temp != NULL){
        if (ei_map_rgba(surface, *(temp->widget->pick_color) ) == id){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

struct ei_text_cell* text_from_id(uint32_t id, ei_surface_t surface){
    ei_text_cell *temp = &text_cell_head;
    while (temp != NULL){
        uint32_t id_a_voir = ei_map_rgba(surface, *(temp->widget->pick_color));
        if (temp->widget->pick_id == id){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}