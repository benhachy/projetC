#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ei_draw_widget.h"
#include "ei_widget.h"
#include "ei_widgetclass.h"



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


};

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

void	drawfunc_frame		(struct ei_widget_t*	widget,
                               ei_surface_t		surface,
                               ei_surface_t		pick_surface,
                               ei_rect_t*		clipper){
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

    ei_draw_polygon(surface,frame_pt,*(widget->pick_color),clipper);

    //Free the points used for drawing
    while(frame_pt!= NULL){
        ei_linked_point_t *to_delete = frame_pt;
        frame_pt = frame_pt->next;
        free(to_delete);
    }


}

void	setdefaultsfunc_frame	(struct ei_widget_t*	widget){

    ei_point_t top_left = {0,0};
    //By default every frame is a square of size 10pixels
    ei_size_t size = {10,10};
    ei_rect_t screen_location = {top_left, size};
    widget->content_rect = &(widget->screen_location);

}

void	geomnotifyfunc_frame	(struct ei_widget_t*	widget,
                                 ei_rect_t		rect){

}

ei_bool_t ei_frame_handlefunc_t (struct ei_widget_t*	widget,
                                 struct ei_event_t*	event){
    return 0;
}

