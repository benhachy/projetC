//
// Created by menouar on 06/05/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "ei_types.h"
#include "ei_coloring.h"
#include "struct.h"
#include "hw_interface.h"

uint32_t		ei_map_rgba		(ei_surface_t surface, ei_color_t color){
    int ig = 0, ia =0, ir = 0, ib = 0;
    //We put the color indices in their respective variables
    hw_surface_get_channel_indices(surface,  &ir,  &ig, &ib, &ia);

    //Initializing the parameters colors
    int B = color.blue, G = color.green, R = color.red, A = color.alpha;
    uint32_t res = 0;
    if (ia != -1) {
        //Since the last index is given by "-1" , we do a simple computation of the resulting indexes to get correct orders (0->1->2->3)
        ib = (ib + 4) % 4, ig = (ig + 4) % 4, ir = (ir + 4) % 4, ia = (ia + 4) % 4;

        //Each byte of the res variable here is placed according to the index of the color in the surface

        res = B * pow(2, ib * 8) + R * pow(2, ir * 8) + G * pow(2, ig * 8) + A * pow(2, ia * 8);
    } else {
        ib = (ib + 4) % 4, ig = (ig + 4) % 4, ir = (ir + 4) % 4;

        res = B * pow(2, ib * 8) + R * pow(2, ir * 8) + G * pow(2, ig * 8);
    }

    return res;

}






void			ei_draw_polyline	(ei_surface_t			surface,
                                     const ei_linked_point_t*	first_point,
                                     ei_color_t			color,
                                     const ei_rect_t*		clipper){
        hw_surface_lock(surface);
        ei_linked_point_t* start = (ei_linked_point_t*)malloc(sizeof(ei_linked_point_t));
        start->next = first_point->next;
        start->point = first_point->point;
        while(start->next != NULL) {


            ei_linked_point_t* end = start->next;
            int delta_x = end->point.x - start->point.x;
            int delta_y = end->point.y - start->point.y;
            uint32_t int_color = ei_map_rgba(surface, color);


            if (abs(delta_x) > abs(delta_y)) {
                if (delta_y >= 0 && delta_x > 0) {
                    ei_color_1_pos_x_pos_y(surface, int_color, start, end);
                }
                else if (delta_y <= 0 && delta_x > 0) {
                    ei_color_1_pos_x_neg_y(surface, int_color, start, end);
                }

                else if (delta_y > 0 && delta_x < 0) {
                    ei_color_1_neg_x_pos_y(surface, int_color, start, end);
                }
                else {
                    ei_color_1_neg_x_neg_y(surface, int_color, start, end);
                }
                }


            else if (abs(delta_y) > abs(delta_x)) {
                if (delta_y>0 && delta_x>=0) {
                    ei_color_2_pos_x_pos_y(surface, int_color, start, end);
                }
                else if (delta_y < 0 && delta_x >= 0) {
                    ei_color_2_pos_x_neg_y(surface, int_color, start, end);
                }
                else if (delta_y > 0 && delta_x < 0) {
                    ei_color_2_neg_x_pos_y(surface, int_color, start, end);
                }
                else {
                    ei_color_2_neg_x_neg_y(surface, int_color, start, end);
                }

            }
            else {
		if (delta_y>0 && delta_x>0){
		    ei_color_3_pos_x_pos_y(surface, int_color, start, end);
		}            	
                else if (delta_y < 0 && delta_x >= 0) {
                    ei_color_3_pos_x_neg_y(surface, int_color, start, end);
                }
                else if (delta_y > 0 && delta_x < 0) {
                    ei_color_3_neg_x_pos_y(surface, int_color, start, end);
                }
                else {
                    ei_color_3_neg_x_neg_y(surface, int_color, start, end);
                }
        }
            start = start->next;
            end = end->next;
        hw_surface_unlock(surface);
        hw_surface_update_rects(surface, NULL);
};

}







void			ei_draw_polygon		(ei_surface_t			surface,
                                        const ei_linked_point_t*	first_point,
                                        ei_color_t			color,
                                        const ei_rect_t*		clipper)
                                        {
    hw_surface_lock(surface);
    uint32_t int_color = ei_map_rgba(surface, color);
    ei_linked_point_t* first = (ei_linked_point_t*)malloc(sizeof(ei_linked_point_t));
    first->next = first_point->next;
    first->point = first_point->point;
    struct tc_cell* tc = get_tc(first);
    struct tc_cell* tc_temp = tc;
    struct tc_carac* tc_c_temp ;
    struct tca_cell* tca = NULL;
    int size = 0;
    int y = get_min(first);


    while (tc_temp->next != NULL){
        size++;
        tc_temp = tc_temp->next;
    }

    //On arrive à la première scan line non vide
    while (tc->tc_carac == NULL){
        tc = tc->next;
    }

    tc_c_temp = tc->tc_carac;
    tc = tc->next;

    while(tc_c_temp->x_min != -1){
        tca_append(&tca, tc_c_temp->y_max, (float)tc_c_temp->x_min, tc_c_temp->m);
        tc_c_temp = tc_c_temp->next;
    }
    y++;

    struct tca_cell* tca_temp = tca;
    struct tca_cell* tca_temp2 = tca->next;
    while(tca != NULL && tc != NULL){

        //Déplacer les côtés de TC(y) dans TCA
        if (tc->tc_carac != NULL){
            tc_c_temp = tc->tc_carac;
            while(tc_c_temp->x_min != -1){
                tca_append(&tca, tc_c_temp->y_max, (float)tc_c_temp->x_min, tc_c_temp->m);
                tc_c_temp = tc_c_temp->next;
            }

        }
        tc = tc->next;

        //Supprimer de TCA les côtés tel que y_max = y
        tca_temp = tca;
        //Cas une seule case restante non traité
        if (tca->y_max == y && tca->next == NULL){
            tca= NULL;
        } else {
            while (tca_temp != NULL) {
                if (tca->y_max == y && tca->next != NULL) {
                    tca = tca->next;
                    tca_temp = tca_temp->next;
                } else if (tca_temp->next != NULL) {
                    if (tca_temp->next->y_max == y) {
                        if (tca_temp->next->next == NULL) {
                            struct tca_cell *to_be_deleted = tca_temp->next;
                            tca_temp->next = NULL;
                            free(to_be_deleted);
                        } else {
                            struct tca_cell *to_be_deleted = tca_temp->next;
                            tca_temp->next = tca_temp->next->next;
                            free(to_be_deleted);
                        }
                    }
                }
                tca_temp = tca_temp->next;
                }

            }
        //Trier TCA

        sort_tca(&tca);

        //Modifier les pixels de l'image sur la scanline
        tca_temp = tca;
        tca_temp2 = tca->next;
        while(tca_temp != NULL && tca_temp2 != NULL){
            int x_start = (int)floor(tca_temp->x_min + 0.5);
            int x_end = (int)floor(tca_temp2->x_min + 0.5);
            for (int i = x_start; i <= x_end; i++){
                ei_color_pixel(surface, int_color, i, y);
            }
            tca_temp = tca_temp->next->next;
            if (tca_temp != NULL) {
                tca_temp2 = tca_temp2->next->next;
            } else {
                tca_temp2 = NULL;
            }
        }

        //Incrémenter y
        y++;

        //Mettre à jour les abscisses d'intersection
        tca_temp = tca;
        while (tca_temp != NULL){
            tca_temp->x_min = tca_temp->x_min + tca_temp->m;
            tca_temp = tca_temp->next;

        }
        }
    hw_surface_unlock(surface);
    hw_surface_update_rects(surface, NULL);
    }


void			ei_draw_text		(ei_surface_t		surface,
                                     const ei_point_t*	where,
                                     const char*		text,
                                     ei_font_t		font,
                                     ei_color_t		color,
                                     const ei_rect_t*	clipper)
                                     
                                     {
		ei_surface_t text_surface;
		text = hw_text_create_surface(		text,
					 			font,
					 			color);
		hw_surface_lock(surface);
		ei_size_t taille_text;
		taille_text = hw_surface_get_size(text);
		uint32_t *origine_text = (uint32_t*)hw_surface_get_buffer(text_surface);
		int x_max_text = taille_text.width;
		for (int i = 0 ; i< taille_text.width; i++){
		for ( int j = 0 ; j< taille_text.height; j++){
		// les 2 lignes qui suivent font : surface[i+where->x][j+where->y] = text[i][j]
		uint32_t color_text = *(origine_text + (uint32_t)(x_max_text*j) + (uint32_t)(i));
		ei_color_pixel(surface, color_text, i + where->x, j + where->y);
		
		}
		}
		hw_surface_unlock(surface);
                                     
                                     }

void			ei_fill			(ei_surface_t		surface,
                                    const ei_color_t*	color,
                                    const ei_rect_t*	clipper){


    uint32_t *origine_surface = (uint32_t *)hw_surface_get_buffer(surface);
    ei_size_t taille_surface = hw_surface_get_size(surface);
    int x_max_surface = taille_surface.width;
    int start_i = 0;
    int start_j = 0;

    ei_color_t non_const_color = {0,0,0,0};
    non_const_color.red = color->red;
    non_const_color.blue = color->blue;
    non_const_color.green = color->green;
    non_const_color.alpha = color->alpha;

    if (clipper != NULL) {
        start_i = clipper->top_left.x;
        start_j = clipper->top_left.y;
        taille_surface = clipper->size;
    }

    uint32_t int_color = ei_map_rgba(surface, non_const_color);
    for (int i = start_i ; i< taille_surface.width ; i++){
        for ( int j = start_j ; j< taille_surface.height; j++){
            *(origine_surface + (uint32_t)(x_max_surface*j) + (uint32_t)i) = int_color;

        }
    }



    // rect to linked_rect



}

int			ei_copy_surface		(ei_surface_t		destination,
                                       const ei_rect_t*	dst_rect,
                                       ei_surface_t		source,
                                       const ei_rect_t*	src_rect,
                                       ei_bool_t		alpha){



    ei_size_t taille_src = hw_surface_get_size(source);
    int x_max_src = taille_src.width;
    ei_size_t taille_dst = hw_surface_get_size(destination);
    if (taille_src.height != taille_dst.height ||taille_src.width != taille_dst.width ){return 1;}
    uint32_t *origine_src = (uint32_t *)hw_surface_get_buffer(source);
    uint32_t *origine_dst = (uint32_t *)hw_surface_get_buffer(destination);

    // Déclaration des variables d'ajustement
    int start_src_i = 0;
    int start_src_j = 0;
    int start_dst_i = 0;
    int start_dst_j = 0;

    if (dst_rect != NULL && src_rect != NULL){
        if (dst_rect->size.height != src_rect->size.height || dst_rect->size.width != src_rect->size.width) {
            return 1;}
        int y = src_rect->top_left.y;
        int x = src_rect->top_left.x;
        origine_src += (uint32_t)(x_max_src*y) + (uint32_t)(x);
        x_max_src = src_rect->size.width;
        taille_src.width = src_rect->size.width;
        taille_src.height = src_rect->size.height;
        start_src_i = x;
        start_src_j = y;
        start_dst_i = dst_rect->top_left.x;
        start_dst_j = dst_rect->top_left.y;
    }
    // Cas alpha  == False
    if (alpha == EI_FALSE){
        for (int i = start_src_i ; i< taille_src.width; i++){
            for ( int j = start_src_j ; j< taille_src.height; j++){
                uint32_t color_src = *(origine_src + (uint32_t)(x_max_src*j) + (uint32_t)(i)); // couleur de source[i][j]
                ei_color_pixel(destination, color_src, i+start_dst_i, j+start_dst_j);
            }
        }
    }

    // Cas alpha == True
    if (alpha == EI_TRUE){
        for (int i = start_src_i ; i< taille_src.width; i++){
            for ( int j = start_src_j ; j< taille_src.height; j++){
                uint32_t color_src = *(origine_src + (uint32_t)(x_max_src*j) + (uint32_t)(i)); // couleur de source[i][j]
                uint32_t color_dst = *(origine_dst + (uint32_t)(x_max_src*j) + (uint32_t)(i)); // couleur de destination[i][j]
                // Implémenation effet transparence
                // Calcul des composantes RGB
                uint8_t src_R, src_G, src_B, src_A;
                uint8_t dst_R, dst_G, dst_B, dst_A;
                int two_to_8 = pow(2,8);
                int two_to_16 = pow(2,16);
                int two_to_24 = pow(2,24);

                src_A = (color_src)%(two_to_8);
                src_B = (color_src/(two_to_8))%(two_to_8);
                src_G = (color_src/(two_to_16))%(two_to_8);
                src_R = (color_src/(two_to_24))%(two_to_8);

                dst_A = (color_dst)%(two_to_8);
                dst_B = (color_dst/(two_to_8))%(two_to_8);
                dst_G = (color_dst/(two_to_16))%(two_to_8);
                dst_R = (color_dst/(two_to_24))%(two_to_8);

                dst_B = (src_A*src_B + (255-src_A)*dst_B)/255;
                dst_G = (src_A*src_G + (255-src_A)*dst_G)/255;
                dst_R = (src_A*src_R + (255-src_A)*dst_R)/255;
                dst_A = 255;

                color_src = dst_A + dst_B*(two_to_8) + dst_G*(two_to_16) + dst_R*(two_to_24);

                ei_color_pixel(destination, color_src, i+start_dst_i, j+start_dst_j);
            }
        }
    }



    ei_linked_rect_t dst_rect_ext;
    dst_rect_ext.rect = *dst_rect;
    dst_rect_ext.next = NULL;


    return 0;
}
