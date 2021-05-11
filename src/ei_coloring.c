//
// Created by menouar on 07/05/2021.
// Updated by benhachem on 09/05/2021.
//

#include <stdint.h>
#include "ei_coloring.h"
#include "hw_interface.h"
#include "ei_types.h"

void        ei_color_pixel(ei_surface_t    surface,
                           uint32_t 	   color,
                           int             x,
                           int             y){
    uint32_t* origin = (uint32_t*)hw_surface_get_buffer(surface);
    ei_size_t surface_size = hw_surface_get_size(surface);
    int x_max = surface_size.width;
    int y_max = surface_size.height;
    origin = origin + (uint32_t)(x_max*y) + (uint32_t)x;
    *origin = color;
}


void        ei_color_1_pos_x_pos_y(ei_surface_t        surface,
                                   uint32_t            color,
                                   ei_linked_point_t*  start,
                                   ei_linked_point_t*  end){

    int delta_x = end->point.x - start->point.x;
    int delta_y = end->point.y - start->point.y;
    int curr_x = start->point.x;
    int curr_y = start->point.y;
    int error = 0;
    int end_x = end->point.x;
    while(curr_x != end_x) {
        ei_color_pixel(surface, color, curr_x, curr_y);
        curr_x++;
        error = error + delta_y;
        if (2 * error > delta_x) {
            curr_y++;
            error = error - delta_x;

        }
    }
}


void        ei_color_1_pos_x_neg_y(ei_surface_t        surface,
                                   uint32_t            color,
                                   ei_linked_point_t*  start,
                                   ei_linked_point_t*  end){

    int delta_x = end->point.x - start->point.x;
    int delta_y = end->point.y - start->point.y;
    int curr_x = start->point.x;
    int curr_y = start->point.y;
    int error = 0;
    int end_x = end->point.x;
    while(curr_x != end_x) {
        ei_color_pixel(surface, color, curr_x, curr_y);
        curr_x++;
        error = error - delta_y;
        if (2 * error > delta_x) {
            curr_y--;
            error = error - delta_x;

        }
    }
}


void        ei_color_1_neg_x_pos_y(ei_surface_t        surface,
                                   uint32_t            color,
                                   ei_linked_point_t*  start,
                                   ei_linked_point_t*  end){

    int delta_x = end->point.x - start->point.x;
    int delta_y = end->point.y - start->point.y;
    int curr_x = start->point.x;
    int curr_y = start->point.y;
    int error = 0;
    int end_x = end->point.x;
    while(curr_x != end_x) {
        ei_color_pixel(surface, color, curr_x, curr_y);
        curr_x--;
        error = error + delta_y;
        if (2 * error > -delta_x) {
            curr_y++;
            error = error + delta_x;

        }
    }
}


void        ei_color_1_neg_x_neg_y(ei_surface_t        surface,
                                   uint32_t            color,
                                   ei_linked_point_t*  start,
                                   ei_linked_point_t*  end){

    int delta_x = end->point.x - start->point.x;
    int delta_y = end->point.y - start->point.y;
    int curr_x = start->point.x;
    int curr_y = start->point.y;
    int error = 0;
    int end_x = end->point.x;
    while(curr_x != end_x) {
        ei_color_pixel(surface, color, curr_x, curr_y);
        curr_x--;
        error = error - delta_y;
        if (2 * error > -delta_x) {
            curr_y--;
            error = error + delta_x;

        }
    }
}



void        ei_color_2_pos_x_pos_y(ei_surface_t        surface,
                                   uint32_t            color,
                                   ei_linked_point_t*  start,
                                   ei_linked_point_t*  end){

    int delta_x = end->point.x - start->point.x;
    int delta_y = end->point.y - start->point.y;
    int curr_x = start->point.x;
    int curr_y = start->point.y;
    int error = 0;
    int end_y = end->point.y;
    while(curr_y != end_y) {
        ei_color_pixel(surface, color, curr_x, curr_y);
        curr_y++;
        error = error + delta_x;
        if (2 * error > delta_y) {
            curr_x++;
            error = error - delta_y;

        }
    }
}


void        ei_color_2_pos_x_neg_y(ei_surface_t        surface,
                                   uint32_t            color,
                                   ei_linked_point_t*  start,
                                   ei_linked_point_t*  end){

    int delta_x = end->point.x - start->point.x;
    int delta_y = end->point.y - start->point.y;
    int curr_x = start->point.x;
    int curr_y = start->point.y;
    int error = 0;
    int end_y = end->point.y;
    while(curr_y != end_y) {
        ei_color_pixel(surface, color, curr_x, curr_y);
        curr_y--;
        error = error + delta_x;
        if (2 * error > -delta_y) {
            curr_x++;
            error = error + delta_y;

        }
    }
}


void        ei_color_2_neg_x_pos_y(ei_surface_t        surface,
                                   uint32_t            color,
                                   ei_linked_point_t*  start,
                                   ei_linked_point_t*  end){

    int delta_x = end->point.x - start->point.x;
    int delta_y = end->point.y - start->point.y;
    int curr_x = start->point.x;
    int curr_y = start->point.y;
    int error = 0;
    int end_y = end->point.y;
    while(curr_y != end_y) {
        ei_color_pixel(surface, color, curr_x, curr_y);
        curr_y++;
        error = error - delta_x;
        if (2 * error > delta_y) {
            curr_x--;
            error = error - delta_y;

        }
    }
}


void        ei_color_2_neg_x_neg_y(ei_surface_t        surface,
                                   uint32_t            color,
                                   ei_linked_point_t*  start,
                                   ei_linked_point_t*  end){

    int delta_x = end->point.x - start->point.x;
    int delta_y = end->point.y - start->point.y;
    int curr_x = start->point.x;
    int curr_y = start->point.y;
    int error = 0;
    int end_y = end->point.y;
    while(curr_y != end_y) {
        ei_color_pixel(surface, color, curr_x, curr_y);
        curr_y--;
        error = error - delta_x;
        if (2 * error > -delta_y) {
            curr_x--;
            error = error + delta_y;

        }
    }
}
void        ei_color_3_pos_x_pos_y(ei_surface_t        surface,
                                   uint32_t            color,
                                   ei_linked_point_t*  start,
                                   ei_linked_point_t*  end){
    int curr_x = start->point.x;
    int curr_y = start->point.y;
    while(curr_x != end->point.x)
    {
    ei_color_pixel(surface, color, curr_x, curr_y);
    curr_x++;
    curr_y++;
    }
   
    
}
    
void        ei_color_3_pos_x_neg_y(ei_surface_t        surface,
                                   uint32_t            color,
                                   ei_linked_point_t*  start,
                                   ei_linked_point_t*  end){
    int curr_x = start->point.x;
    int curr_y = start->point.y;
    
    while(curr_x != end->point.x){
    ei_color_pixel(surface, color, curr_x, curr_y);
    curr_x++;
    curr_y--;
    }
    
    
}

void        ei_color_3_neg_x_pos_y(ei_surface_t        surface,
                                   uint32_t            color,
                                   ei_linked_point_t*  start,
                                   ei_linked_point_t*  end){
    int curr_x = start->point.x;
    int curr_y = start->point.y;
    
    while(curr_x != end->point.x){
    ei_color_pixel(surface, color, curr_x, curr_y);
    curr_x--;
    curr_y++;
    }
    
    
}
    
void        ei_color_3_neg_x_neg_y(ei_surface_t        surface,
                                   uint32_t            color,
                                   ei_linked_point_t*  start,
                                   ei_linked_point_t*  end){
    int curr_x = start->point.x;
    int curr_y = start->point.y;
    
    while(curr_x != end->point.x){
    ei_color_pixel(surface, color, curr_x, curr_y);
    curr_x--;
    curr_y--;
    }
}
