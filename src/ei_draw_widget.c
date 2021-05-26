#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ei_draw_widget.h"
#include "ei_widget.h"
#include "ei_widgetclass.h"
#include "button.h"
#include "ei_draw.h"
#include "ei_event.h"

ei_frame_cell frame_cell_head = {
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
        0,0,
        0,
        NULL,
        0,
        ei_relief_none,
        NULL,
};


ei_button_cell button_cell_head = {
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
        0,0,
        0,
        NULL,
        0,
        0,
        ei_relief_none,
        NULL,
};

ei_text_cell text_cell_head = {
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
        0,0,
        0,
        NULL,
        0,
        NULL,
        NULL,
};

ei_toplevel_cell toplevel_cell_head = {
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
        0,0,
        0,
        NULL,
        0,
        NULL,
        NULL,
        NULL,
        NULL,
};

ei_image_cell image_cell_head = {
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
        0,0,
        0,
        NULL,
        0,
        NULL,
        NULL,
};



void dessin(ei_widget_t* widget, ei_surface_t surface, ei_surface_t offscreen, ei_rect_t* clipper){

     //On commence par appeler la fonction drawfunc pour dessiner le premier widget
     widget->wclass->drawfunc(widget, surface, offscreen, clipper);
     ei_widget_t* descendant = widget->children_head;
     //On appelle récursivement la fonction pour dessiner tous les descendants dans la hiérarchie
        while (descendant != NULL)
        {
                dessin(descendant, surface, offscreen, widget->content_rect);
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


struct ei_widget_t* allowfunc_toplevel(void) {
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

struct ei_widget_t* allowfunc_image(void) {
    struct ei_widget_t* image_wid = (struct ei_widget_t*)malloc(sizeof(struct ei_widget_t));

    image_wid->wclass = NULL;
    image_wid->pick_id = 0;
    image_wid->pick_color = NULL;
    image_wid->user_data = NULL;
    image_wid->destructor = NULL;

    //Setting family parameters to NULL
    image_wid->parent = NULL;
    image_wid->children_head = NULL;
    image_wid->children_tail = NULL;
    image_wid->next_sibling = NULL;

    //Setting geometry parameters to NULL
    image_wid->placer_params = NULL;
    image_wid->requested_size.height = 0;
    image_wid->requested_size.width = 0;
    image_wid->screen_location.top_left.x = 0;
    image_wid->screen_location.top_left.y = 0;
    image_wid->content_rect = NULL;

    return image_wid;
};




//                                                   ||RELEASE FUNCTIONS||




void releasefunc_frame(struct ei_widget_t* frame_wid){


    free(frame_wid->pick_color);
    free(frame_wid->user_data);
    free(frame_wid->destructor);


    //Setting geometry parameters to NULL
    free(frame_wid->placer_params);
    if (frame_wid->pick_id != 0) {
        free(frame_wid->content_rect);
        free(frame_wid);
    }


}

void releasefunc_button(struct ei_widget_t* button_wid){

    free(button_wid->pick_color);
    free(button_wid->user_data);
    free(button_wid->destructor);


    //Setting geometry parameters to NULL
    free(button_wid->placer_params);
    free(button_wid->content_rect);

    free(button_wid);

}


void releasefunc_text(struct ei_widget_t* text_wid){


    free(text_wid->pick_color);
    free(text_wid->user_data);
    free(text_wid->destructor);

    //Setting geometry parameters to NULL
    free(text_wid->placer_params);
    free(text_wid->content_rect);

    free(text_wid);

}


void releasefunc_toplevel(struct ei_widget_t* text_wid){

    free(text_wid->pick_color);
    free(text_wid->user_data);
    free(text_wid->destructor);


    //Setting geometry parameters to NULL
    free(text_wid->placer_params);
    free(text_wid->content_rect);

    free(text_wid);

}

void releasefunc_image(struct ei_widget_t* text_wid){

    free(text_wid->pick_color);
    free(text_wid->user_data);
    free(text_wid->destructor);


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
    if (button->border_width != NULL) {
        if (*(button->border_width) < 10) {
            border_width = 10;
        } else {
            border_width = *(button->border_width);
        }
    }

    //Draws the button given its relief
    if (button->relief == ei_relief_raised) {
        if (button->corner_radius != NULL && button->color != NULL ) {
            draw_button(surface, pick_surface, clipper, rect, *(button->corner_radius), *(button->color),
                        *(widget->pick_color), border_width, 0);
        } else {
            draw_button(surface, pick_surface, clipper, rect, 10, *(widget->pick_color),
                        *(widget->pick_color), border_width, 0);
        }
        } else {
            if (button->corner_radius != NULL && button->color != NULL ) {
                 draw_button(surface, pick_surface, clipper, rect, *(button->corner_radius), *(button->color),
                            *(widget->pick_color), border_width, 1);
            } else {
                draw_button(surface, pick_surface, clipper, rect, 10, *(widget->pick_color),
                            *(widget->pick_color), border_width, 1);
        }
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


void	drawfunc_toplevel		(struct ei_widget_t*	widget,
                              ei_surface_t		surface,
                              ei_surface_t		pick_surface,
                              ei_rect_t*		clipper){
    ei_toplevel_cell* toplevel = toplevel_from_id(widget->pick_id, surface);

    //Dessin de la barre d'en tête :
    ei_size_t bande_size = {widget->screen_location.size.width, 45};
    ei_rect_t bande_rect = {widget->screen_location.top_left, bande_size};
    ei_linked_point_t* bande_frame = rounded_frame(bande_rect, 15, 1);
    ei_color_t bande_color = {95, 105, 100, 1};
    ei_draw_polygon(surface, bande_frame, bande_color, clipper);


    //Dessin du corp de la toplevel
    ei_size_t border_size = {widget->screen_location.size.width, widget->screen_location.size.height};
    ei_point_t border_top_left = {widget->screen_location.top_left.x, widget->screen_location.top_left.y + 30};
    ei_rect_t border_rect = {border_top_left, border_size};
    ei_linked_point_t* border_frame = rounded_frame(border_rect, 0, 1);
    ei_draw_polygon(surface, border_frame, bande_color, clipper);

    //Dessin du corp de la toplevel
    ei_size_t corp_size = {widget->screen_location.size.width - 10, widget->screen_location.size.height -10};
    ei_point_t corp_top_left = {widget->screen_location.top_left.x + 5, widget->screen_location.top_left.y + 35};
    ei_rect_t corp_rect = {corp_top_left, corp_size};
    ei_linked_point_t* corp_frame = rounded_frame(corp_rect, 0, 1);
    ei_draw_polygon(surface, corp_frame, *(toplevel->color), clipper);






}

void	drawfunc_image		(struct ei_widget_t*	widget,
                               ei_surface_t		surface,
                               ei_surface_t		pick_surface,
                               ei_rect_t*		clipper){
    ei_image_cell* image_cell = image_from_id(widget->pick_id, surface);
    ei_point_t* where = &(widget->screen_location.top_left);

    ei_surface_t image = image_cell->img;
    ei_rect_t* img_rect = *(image_cell->img_rect);


    ei_size_t dst_size = hw_surface_get_size(surface);



    ei_rect_t dst_rect = {*where, dst_size};
    ei_rect_t src_rect;
    if (img_rect != NULL) {
        src_rect = *img_rect;
    } else {
        src_rect = widget->parent->screen_location;
    }

    ei_copy_surface(surface, &dst_rect, image, &src_rect, EI_TRUE);
    //Pas besoin de dessiner dans l'offscreen (Un image n'est pas un vrai widget)
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

void	setdefaultsfunc_toplevel	(struct ei_widget_t*	widget){

    ei_point_t top_left = {0,0};
    //By default every frame is a square of size 10pixels
    ei_size_t size = {10,10};
    ei_rect_t screen_location = {top_left, size};
    widget->content_rect = &(widget->screen_location);

}

void	setdefaultsfunc_image	(struct ei_widget_t*	widget){

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

void	geomnotifyfunc_toplevel	(struct ei_widget_t*	widget,
                                ei_rect_t		rect){

}

void	geomnotifyfunc_image	(struct ei_widget_t*	widget,
                                 ei_rect_t		rect){

}



//                                                   ||CAN YOU EVEN HANDLE ME? FUNCTIONS||


ei_bool_t ei_frame_handlefunc_t (struct ei_widget_t*	widget,
                                 struct ei_event_t*	event){
    return 0;
}

ei_bool_t ei_button_handlefunc_t (struct ei_widget_t*	widget,
                                 struct ei_event_t*	event){

    ei_button_cell*  button = (ei_button_cell*)widget;
    if (mouse_on_widget(*event, *(widget->content_rect)) == 1) {
        if (event->type == ei_ev_mouse_buttondown) {
            button->relief = ei_relief_sunken; //Pas besoin de disjonction de cas
            return EI_TRUE;
        } else if (event->type == ei_ev_mouse_buttonup) {
            if (is_widget_close(button) == 1) {
                //If the button has been pushed we close the toplevel
                if (button->relief == ei_relief_sunken) {
                    ei_widget_destroy(widget->parent);
                    return EI_TRUE;
                } else {
                    //Else nothing happens and the event isn't handled
                    return EI_FALSE;
                }
            } else {
                if (button->relief == ei_relief_sunken) {
                    button->relief = ei_relief_raised;
                    return EI_TRUE;
                } else {
                    return EI_FALSE;
                }
            }
        } else {
            if (event->type == ei_ev_mouse_move) {
                return EI_TRUE;
            }
            return EI_FALSE;
        }
    } else {
        if (event->type == ei_ev_mouse_buttondown){

        } else if (event->type == ei_ev_mouse_buttonup) {
            if (button->relief == ei_relief_sunken){
                button->relief = ei_relief_raised;
                return EI_TRUE;
            } else {
                return EI_FALSE;
            }
        } else {
            if (button->relief == ei_relief_sunken){
                return EI_TRUE;
            } else {
                return EI_FALSE;
            }
        }
    }

}

ei_bool_t ei_text_handlefunc_t (struct ei_widget_t*	widget,
                                  struct ei_event_t*	event){
    return 0;
}

ei_bool_t ei_toplevel_handlefunc_t (struct ei_widget_t*	widget,
                                struct ei_event_t*	event){
    return 0;
}

ei_bool_t ei_image_handlefunc_t (struct ei_widget_t*	widget,
                                 struct ei_event_t*	event){

    return 0;
}



struct ei_frame_cell* get_frame_cell(struct ei_widget_t* widget){
    ei_frame_cell *temp = &frame_cell_head;
    ei_widget_t* temp_widget = (ei_widget_t*)temp;
    //Si la liste chainée est vide
    if (temp_widget->wclass == NULL){
        temp->widget = *widget;
        temp->next = NULL;
        return temp;
    }  else {
        temp_widget = (ei_widget_t*)temp;
        if (temp_widget->pick_id == widget->pick_id){
            return temp;
        }
        while (temp->next != NULL ) {
            //Si la prochaine cellule est la bonne on la retourne
            temp_widget = (ei_widget_t*)temp->next;
            if (temp_widget->pick_id == widget->pick_id){
                return temp->next;
            //Sinon on cherche encore
            } else {
                temp = temp->next;
            }
        }
        //Si on a pas trouvé de cellule on en crée une nouvelle
        if (temp->next == NULL) {
            temp->next = (ei_frame_cell*)malloc(sizeof(ei_frame_cell));
            temp->next->widget = *widget;
            temp->next->next = NULL;
            return temp->next;
        }
    }
}



struct ei_button_cell* get_button_cell(struct ei_widget_t* widget){
    ei_button_cell *temp = &button_cell_head;
    ei_widget_t* temp_widget = (ei_widget_t*)temp;
    //Si la liste chainée est vide
    if (temp_widget->wclass == NULL){
        temp->widget = *widget;
        temp->next = NULL;
        return temp;
    }  else {
        temp_widget = (ei_widget_t*)temp;
        if (temp_widget->pick_id == widget->pick_id){
            return temp;
        }
        while (temp->next != NULL) {
            //Si la prochaine cellule est la bonne on la retourne
            temp_widget = (ei_widget_t*)temp->next;
            if (temp_widget->pick_id == widget->pick_id){
                return temp->next;
                //Sinon on cherche encore
            } else {
                temp = temp->next;
            }
        }
        //Si on a pas trouvé de cellule on en crée une nouvelle
        if (temp->next == NULL) {
            temp->next = (ei_button_cell*)malloc(sizeof(ei_button_cell));
            temp->next->widget = *widget;
            temp->next->next = NULL;
            return temp->next;
        }
    }
}


struct ei_text_cell* get_text_cell(struct ei_widget_t* widget){
    ei_text_cell *temp = &text_cell_head;
    ei_widget_t* temp_widget = (ei_widget_t*)temp;
    //Si la liste chainée est vide
    if (temp_widget->wclass == NULL){
        temp->widget = *widget;
        temp->next = NULL;
        return temp;
    }  else {
        temp_widget = (ei_widget_t*)temp;
        if (temp_widget->pick_id == widget->pick_id){
            return temp;
        }
        while (temp->next != NULL) {
            //Si la prochaine cellule est la bonne on la retourne
            temp_widget = (ei_widget_t*)temp->next;
            if (temp_widget->pick_id == widget->pick_id){
                return temp->next;
                //Sinon on cherche encore
            } else {
                temp = temp->next;
            }
        }
        //Si on a pas trouvé de cellule on en crée une nouvelle
        if (temp->next == NULL) {
            temp->next = (ei_text_cell*)malloc(sizeof(ei_text_cell));
            temp->next->widget = *widget;
            temp->next->next = NULL;
            return temp->next;
        }
    }
}


struct ei_toplevel_cell* get_toplevel_cell(struct ei_widget_t* widget){
    ei_toplevel_cell *temp = &toplevel_cell_head;
    ei_widget_t* temp_widget = (ei_widget_t*)temp;
    //Si la liste chainée est vide
    if (temp_widget->wclass == NULL){
        temp->widget = *widget;
        temp->next = NULL;
        return temp;
    } else {
        temp_widget = (ei_widget_t*)temp;
        if (temp_widget->pick_id == widget->pick_id){
            return temp;
        }
        while (temp->next != NULL) {
            //Si la prochaine cellule est la bonne on la retourne
            temp_widget = (ei_widget_t*)temp->next;
            if (temp_widget->pick_id == widget->pick_id){
                return temp->next;
                //Sinon on cherche encore
            } else {
                temp = temp->next;
            }
        }
        //Si on a pas trouvé de cellule on en crée une nouvelle
        if (temp->next == NULL) {
            temp->next = (ei_toplevel_cell*)malloc(sizeof(ei_toplevel_cell));
            temp->next->widget = *widget;
            temp->next->next = NULL;
            return temp->next;
        }
    }
}

struct ei_image_cell* get_image_cell(struct ei_widget_t* widget){
    ei_image_cell *temp = &image_cell_head;
    ei_widget_t* temp_widget = (ei_widget_t*)temp;
    //Si la liste chainée est vide
    if (temp_widget->wclass == NULL){
        temp->widget = *widget;
        temp->next = NULL;
        return temp;
    }  else {
        temp_widget = (ei_widget_t*)temp;
        if (temp_widget->pick_id == widget->pick_id){
            return temp;
        }
        while (temp->next != NULL) {
            //Si la prochaine cellule est la bonne on la retourne
            temp_widget = (ei_widget_t*)temp->next;
            if (temp_widget->pick_id == widget->pick_id){
                return temp->next;
                //Sinon on cherche encore
            } else {
                temp = temp->next;
            }
        }
        //Si on a pas trouvé de cellule on en crée une nouvelle
        if (temp->next == NULL) {
            temp->next = (ei_image_cell*)malloc(sizeof(ei_image_cell));
            temp->next->widget = *widget;
            temp->next->next = NULL;
            return temp->next;
        }
    }
}





int is_widget_frame(uint32_t id, ei_surface_t surface){
    ei_frame_cell *temp = &frame_cell_head;
    ei_widget_t* temp_widget = (ei_widget_t*)temp;
    while (temp_widget != NULL){
        if (ei_map_rgba(surface, *(temp_widget->pick_color) ) == id){
            return 1;
        }
        temp = temp->next;
        temp_widget = (ei_widget_t*)temp;
    }
    return 0;
}


int is_widget_button(uint32_t id, ei_surface_t surface){
    ei_button_cell *temp = &button_cell_head;
    ei_widget_t* temp_widget = (ei_widget_t*)temp;
    while (temp_widget != NULL){
        if (temp_widget->pick_color != NULL) {
            if (ei_map_rgba(surface, *(temp_widget->pick_color)) == id) {
                return 1;
            }
            temp = temp->next;
            temp_widget = (ei_widget_t *) temp;
        } else {
            return 0;
        }
    }
    return 0;
}


int is_widget_text(uint32_t id, ei_surface_t surface){
    ei_text_cell *temp = &text_cell_head;
    ei_widget_t* temp_widget = (ei_widget_t*)temp;
    while (temp_widget != NULL){
        if (ei_map_rgba(surface, *(temp_widget->pick_color) ) == id){
            return 1;
        }
        temp = temp->next;
        temp_widget = (ei_widget_t*)temp;
    }
    return 0;
}

int is_widget_toplevel(uint32_t id, ei_surface_t surface){
    ei_toplevel_cell *temp = &toplevel_cell_head;
    ei_widget_t* temp_widget = (ei_widget_t*)temp;
    while (temp_widget != NULL){
        if (ei_map_rgba(surface, *(temp_widget->pick_color) ) == id){
            return 1;
        }
        temp = temp->next;
        temp_widget = (ei_widget_t*)temp;
    }
    return 0;
}


struct ei_button_cell* button_from_id(uint32_t id, ei_surface_t surface){
    ei_button_cell *temp = &button_cell_head;
    ei_widget_t* temp_widget = (ei_widget_t*)temp;
    while (temp != NULL){
        if (ei_map_rgba(surface, *(temp_widget->pick_color) ) == id){
            return temp;
        }
        temp = temp->next;
        temp_widget = (ei_widget_t*)temp;
    }
    return NULL;
}

struct ei_frame_cell* frame_from_id(uint32_t id, ei_surface_t surface){
    ei_frame_cell *temp = &frame_cell_head;
    ei_widget_t* temp_widget = (ei_widget_t*)temp;
    while (temp != NULL){
        if (ei_map_rgba(surface, *(temp_widget->pick_color) ) == id){
            return temp;
        }
        temp = temp->next;
        temp_widget = (ei_widget_t*)temp;
    }
    return NULL;
}

struct ei_text_cell* text_from_id(uint32_t id, ei_surface_t surface){
    ei_text_cell *temp = &text_cell_head;
    ei_widget_t* temp_widget = (ei_widget_t*)temp;
    while (temp != NULL){
        if (temp_widget->pick_id == id){
            return temp;
        }
        temp = temp->next;
        temp_widget = (ei_widget_t*)temp;
    }
    return NULL;
}

struct ei_toplevel_cell* toplevel_from_id(uint32_t id, ei_surface_t surface){
    ei_toplevel_cell *temp = &toplevel_cell_head;
    ei_widget_t* temp_widget = (ei_widget_t*)temp;
    while (temp != NULL){
        if (temp_widget->pick_id  == id){
            return temp;
        }
        temp = temp->next;
        temp_widget = (ei_widget_t*)temp;
    }
    return NULL;
    }

struct ei_image_cell* image_from_id(uint32_t id, ei_surface_t surface){
    ei_image_cell *temp = &image_cell_head;
    ei_widget_t* temp_widget = (ei_widget_t*)temp;
    while (temp != NULL){
        if (temp_widget->pick_id == id){
            return temp;
        }
        temp = temp->next;
        temp_widget = (ei_widget_t*)temp;
    }
    return NULL;
}




int mouse_on_widget(struct ei_event_t event, ei_rect_t rect){
    int x = event.param.mouse.where.x;
    int y = event.param.mouse.where.y;
    if (x>= rect.top_left.x && x <= rect.top_left.x + rect.size.width){
        if (y>= rect.top_left.y && y <= rect.top_left.y + rect.size.height){
            return 1;
        } else return 0;
    } else return 0;
}

void recursion_destroy (ei_widget_t* widget){

    ei_widget_t* temp_child = widget->children_head;
    ei_widget_t* actual_child = widget->children_head;
    while(temp_child != NULL){
        actual_child = temp_child;
        temp_child = temp_child->next_sibling;
        //Destroys the current child
        if (actual_child->children_head != NULL){
            ei_widget_destroy(actual_child);
        } else {
            if (actual_child->destructor != NULL) {
                actual_child->destructor(actual_child);
            } else {
                actual_child->wclass->releasefunc(actual_child);
            }
        }

    }
}

int is_widget_close(ei_button_cell* button_cell){
    ei_widget_t* widget = (ei_widget_t*)button_cell;
    if (strcmp(widget->parent->wclass->name, "toplevel") == 0){
        if (widget->content_rect->top_left.y <= widget->parent->content_rect->top_left.y + 30){
            return 1;
        } else {
            return  0;
        }
    } else {
        return 0;
    }
}

void update_window(ei_surface_t root_surface, ei_surface_t offscreen, struct ei_widget_t root_widget){

    hw_surface_lock(root_surface);
    dessin(&root_widget, root_surface, offscreen, NULL);
    hw_surface_unlock(root_surface);
    hw_surface_update_rects(root_surface, NULL);

}

struct ei_button_cell get_button_cell_head(void){
    return button_cell_head;
}

