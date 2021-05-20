//
// Created by menouar on 12/05/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ei_types.h"
#include <math.h>
#include "hw_interface.h"
#include "struct.h"
#include "ei_draw.h"

ei_linked_point_t* arc(ei_point_t center, int rayon, float start_angle, float end_angle){
    float teta = M_PI*start_angle/180;
    float end;
    float step;
    if (start_angle > end_angle) {
        end = M_PI*end_angle/180 + 2*M_PI;
        step = (start_angle-end_angle)/20;
        step = M_PI*step/180;
    } else {
        end = M_PI*end_angle/180;
        step = (end_angle-start_angle)/20;
        step = M_PI*step/180;
    }
    int x = 0;
    int y = 0;
    int x_temp;
    int y_temp;
    ei_linked_point_t* res1 = (ei_linked_point_t* )malloc(sizeof(ei_linked_point_t));
    ei_linked_point_t* res = res1;
    res->point = center;
    res->next = (ei_linked_point_t* )malloc(sizeof(ei_linked_point_t));
    res = res->next;
    while (teta <= end ){
        x_temp = floor(center.x + rayon* cos(teta) + 0.5);
        y_temp = floor(center.y - rayon*sin(teta)  + 0.5);
        if ( y_temp == y) {
            teta = teta + step;
        } else {
            x = x_temp;
            y = y_temp;
            ei_point_t new = {x, y};
            res->point = new;
            res->next = (ei_linked_point_t *) malloc(sizeof(ei_linked_point_t));
            res = res->next;
            teta = teta + step;
        }

    }
    res->point = center;
    res->next = NULL;

    return res1;
}

ei_linked_point_t* rounded_frame(ei_rect_t rect, int r, int parametre) {
    if (parametre == 1) {
        int x = rect.top_left.x;
        int y = rect.top_left.y;
        ei_point_t c1 = {x + r, y + r};
        ei_point_t c2 = {x + r, y - r + rect.size.height};
        ei_point_t c3 = {x - r + rect.size.width, y - r + rect.size.height};
        ei_point_t c4 = {x - r + rect.size.width, y + r};

        ei_linked_point_t *arc1 = arc(c1, r, 90, 180);
        ei_linked_point_t *arc2 = arc(c2, r, 180, 270);
        ei_linked_point_t *arc3 = arc(c3, r, 270, 360);
        ei_linked_point_t *arc4 = arc(c4, r, 0, 90);

        ei_linked_point_t *c_temp = arc1;
        ei_linked_point_t *c1_first = c_temp->next;
        while (c_temp->next->next != NULL) {
            c_temp = c_temp->next;
        }
        ei_linked_point_t *c1_last = c_temp;

        c_temp = arc2;
        ei_linked_point_t *c2_first = c_temp->next;
        while (c_temp->next->next != NULL) {
            c_temp = c_temp->next;
        }
        ei_linked_point_t *c2_last = c_temp;

        c_temp = arc3;
        ei_linked_point_t *c3_first = c_temp->next;
        while (c_temp->next->next != NULL) {
            c_temp = c_temp->next;
        }
        ei_linked_point_t *c3_last = c_temp;

        c_temp = arc4;
        ei_linked_point_t *c4_first = c_temp->next;
        while (c_temp->next->next != NULL) {
            c_temp = c_temp->next;
        }
        ei_linked_point_t *c4_last = c_temp;

        ei_linked_point_t *c1_first_copy = (ei_linked_point_t *) malloc(sizeof(ei_linked_point_t));
        c1_first_copy->next = NULL;
        c1_first_copy->point = c1_first->point;
        c1_last->next = c2_first;
        c2_last->next = c3_first;
        c3_last->next = c4_first;
        c4_last->next = c1_first_copy;

        return c1_first;
    } else if (parametre == 2) {
        int x = rect.top_left.x;
        int y = rect.top_left.y;
        ei_point_t c1 = {x + r, y + r};
        ei_point_t c2 = {x + r, y - r + rect.size.height};
        ei_point_t c3 = {x + floor(rect.size.height/2), y + floor(rect.size.height/2)};
        ei_point_t c4 = {x + rect.size.width - floor(rect.size.height/2), y + floor(rect.size.height/2)};
        ei_point_t c5 = {x - r + rect.size.width, y + r};

        ei_linked_point_t *arc1 = arc(c1, r, 90, 180);
        ei_linked_point_t *arc2 = arc(c2, r, 180, 230);
        ei_linked_point_t *arc3 = arc(c5, r, 45, 90);

        ei_linked_point_t *c_temp = arc1;
        ei_linked_point_t *c1_first = c_temp->next;
        while (c_temp->next->next != NULL) {
            c_temp = c_temp->next;
        }
        ei_linked_point_t *c1_last = c_temp;

        c_temp = arc2;
        ei_linked_point_t *c2_first = c_temp->next;
        while (c_temp->next->next != NULL) {
            c_temp = c_temp->next;
        }
        ei_linked_point_t *c2_last = c_temp;

        c_temp = arc3;
        ei_linked_point_t *c5_first = c_temp->next;
        while (c_temp->next->next != NULL) {
            c_temp = c_temp->next;
        }
        ei_linked_point_t *c5_last = c_temp;

        ei_linked_point_t *half_2 = (ei_linked_point_t*)malloc(sizeof(ei_linked_point_t));
        half_2->point = c4;
        half_2->next = c5_first;

        ei_linked_point_t *half_1 = (ei_linked_point_t*) malloc(sizeof(ei_linked_point_t));
        half_1->point = c3;
        half_1->next = half_2;

        ei_linked_point_t *c1_first_copy = (ei_linked_point_t *) malloc(sizeof(ei_linked_point_t));
        c1_first_copy->next = NULL;
        c1_first_copy->point = c1_first->point;
        c1_last->next = c2_first;
        c2_last->next = half_1;
        c5_last->next = c1_first_copy;

        return c1_first;
    } else {
        int x = rect.top_left.x;
        int y = rect.top_left.y;
        ei_point_t c1 = {x + r, y - r + rect.size.height};
        ei_point_t c2 = {x + floor(rect.size.height/2), y + floor(rect.size.height/2)};
        ei_point_t c3 = {x + rect.size.width - floor(rect.size.height/2), y + floor(rect.size.height/2)};
        ei_point_t c4 = {x - r + rect.size.width, y + r};
        ei_point_t c5 = {x - r + rect.size.width, y - r + rect.size.height};

        ei_linked_point_t *arc1 = arc(c1, r, 225, 270);
        ei_linked_point_t *arc2 = arc(c4, r, 0, 50);
        ei_linked_point_t *arc3 = arc(c5, r, 270, 360);

        ei_linked_point_t *c_temp = arc1;
        ei_linked_point_t *c1_first = c_temp->next;
        while (c_temp->next->next != NULL) {
            c_temp = c_temp->next;
        }
        ei_linked_point_t *c1_last = c_temp;

        c_temp = arc2;
        ei_linked_point_t *c4_first = c_temp->next;
        while (c_temp->next->next != NULL) {
            c_temp = c_temp->next;
        }
        ei_linked_point_t *c4_last = c_temp;

        c_temp = arc3;
        ei_linked_point_t *c5_first = c_temp->next;
        while (c_temp->next->next != NULL) {
            c_temp = c_temp->next;
        }
        ei_linked_point_t *c5_last = c_temp;


        ei_linked_point_t *c1_first_copy = (ei_linked_point_t *) malloc(sizeof(ei_linked_point_t));
        c1_first_copy->next = NULL;
        c1_first_copy->point = c1_first->point;
        c1_last->next = c5_first;
        c5_last->next = c4_first;

        ei_linked_point_t *half_1 = (ei_linked_point_t*) malloc(sizeof(ei_linked_point_t));
        half_1->point = c2;
        half_1->next = c1_first_copy;

        ei_linked_point_t *half_2 = (ei_linked_point_t*)malloc(sizeof(ei_linked_point_t));
        half_2->point = c3;
        half_2->next = half_1;

        c4_last->next = half_2;


        return c1_first;


    }

}

void  draw_button(ei_surface_t surface, ei_surface_t offscreen, ei_rect_t*	clipper,ei_rect_t rect, int r, ei_color_t color, ei_color_t off_color, int border_width, int param) {

    ei_color_t lighter_color;
    lighter_color.blue = color.blue + floor((255 - color.blue)*1/3);
    lighter_color.red = color.blue + floor((255 - color.red)*1/3);
    lighter_color.green = color.blue + floor((255 - color.green)*1/3);

    ei_color_t darker_color;
    darker_color.blue = floor(color.blue*1/3);
    darker_color.red = floor(color.red*1/3);
    darker_color.green = floor(color.green*1/3);

    ei_linked_point_t* upper_frame = rounded_frame(rect, r, 2);
    ei_linked_point_t* lower_frame = rounded_frame(rect, r, 3);

    ei_rect_t small_rect;
    ei_size_t small_size = {rect.size.width - border_width, rect.size.height - border_width };
    ei_point_t small_rect_point = {rect.top_left.x + border_width/2, rect.top_left.y + border_width/2};
    small_rect.top_left = small_rect_point;
    small_rect.size = small_size;

    ei_linked_point_t* inside_frame = rounded_frame(small_rect, r, 1);
    ei_linked_point_t* offscreen_frame = rounded_frame(rect, r, 1);

    //Dessin dans root_window
    if (param == 0) {
        ei_draw_polygon(surface, upper_frame, lighter_color, clipper);
        ei_draw_polygon(surface, lower_frame, darker_color, clipper);
        ei_draw_polygon(surface, inside_frame, color, clipper);
    } else {
        ei_draw_polygon(surface, upper_frame, darker_color, clipper);
        ei_draw_polygon(surface, lower_frame, lighter_color, clipper);
        ei_draw_polygon(surface, inside_frame, color, clipper);
    }

    //Dessin dans l'offscreen
    ei_draw_polygon(offscreen, offscreen_frame,off_color, clipper);

    //Upper frame, lower frame and inside frame need to be freed

}