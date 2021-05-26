//
// Created by menouar on 12/05/2021.
//

#ifndef PROJETC_IG_BUTTON_H
#define PROJETC_IG_BUTTON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ei_types.h"
#include "hw_interface.h"

/**
* @brief    REtourne une liste de points pour définir un arc 
* @param    rayon : rayon de l'arc 
*           start_angle, end_angle : angles de début et de fin de l'arc 
*           center : centre de l'arc
*
*/
ei_linked_point_t* arc(ei_point_t center, int rayon, float start_angle, float end_angle);

/**
* @brief    Retourne une liste de points pour définir un cercle
* @param    rayon : rayon du cercle
*           start_angle, end_angle : angles de début et de fin du cercle 
*           center : centre du cercle
*
*/
ei_linked_point_t* circle(ei_point_t center, int rayon, float start_angle, float end_angle);

/**
* @brief    Retourne une liste de points pour définir un cadre arrondi
* @param    rayon : rayon des arrondis
*           rect : rectangle du cadre
*
*/
ei_linked_point_t* rounded_frame(ei_rect_t rect, int r, int parameter);

/**
* @brief   Dessine un button
*/
void  draw_button(  ei_surface_t surface,
                    ei_surface_t offscreen,
                    ei_rect_t* clipper,
                    ei_rect_t rect,
                    int r,
                    ei_color_t color,
                    ei_color_t off_color,
                    int border_width,
                    int param
                    );

#endif //PROJETC_IG_BUTTON_H
