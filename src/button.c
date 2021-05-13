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

ei_linked_point_t* arc(ei_point_t center, int rayon, float start_angle, float end_angle){
    float teta = M_PI*start_angle/180;
    float end;
    float step;
    if (start_angle > end_angle) {
        end = M_PI*end_angle/180 + 2*M_PI;
        step = (start_angle-end_angle)/4;
        step = M_PI*step/180;
    } else {
        end = M_PI*end_angle/180;
        step = (end_angle-start_angle)/4;
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

ei_linked_point_t* rounded_frame(ei_rect_t rect, int r) {
    int x = rect.top_left.x;
    int y = rect.top_left.y;
    r = ceil(rect.size.width/10);
    ei_point_t c1 = {x+r, y+r};
    ei_point_t c2 = {x+r, y-r+rect.size.height};
    ei_point_t c3 = {x-r+rect.size.width, y-r+rect.size.height};
    ei_point_t c4 = {x-r+rect.size.width, y+r};

    ei_linked_point_t* arc1 = arc(c1,r,90,180);
    ei_linked_point_t* arc2 = arc(c2,r,180,270);
    ei_linked_point_t* arc3 = arc(c3,r,270,360);
    ei_linked_point_t* arc4 = arc(c4,r,0,90);

    ei_linked_point_t* c_temp = arc1;
    ei_linked_point_t* c1_first = c_temp->next;
    while (c_temp->next->next != NULL){
        c_temp = c_temp->next;
    }
    ei_linked_point_t* c1_last = c_temp;

    c_temp = arc2;
    ei_linked_point_t* c2_first = c_temp->next;
    while (c_temp->next->next != NULL){
        c_temp = c_temp->next;
    }
    ei_linked_point_t* c2_last = c_temp;

    c_temp = arc3;
    ei_linked_point_t* c3_first = c_temp->next;
    while (c_temp->next->next != NULL){
        c_temp = c_temp->next;
    }
    ei_linked_point_t* c3_last = c_temp;

    c_temp = arc4;
    ei_linked_point_t* c4_first = c_temp->next;
    while (c_temp->next->next != NULL){
        c_temp = c_temp->next;
    }
    ei_linked_point_t* c4_last = c_temp;

    ei_linked_point_t* c1_first_copy = (ei_linked_point_t*)malloc(sizeof(ei_linked_point_t));
    c1_first_copy->next = NULL;
    c1_first_copy->point = c1_first->point;
    c1_last->next = c2_first;
    c2_last->next = c3_first;
    c3_last->next = c4_first;
    c4_last->next = c1_first_copy;

    printf("On est là fréro !");
    return c1_first;

}