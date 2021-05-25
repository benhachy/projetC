//
// Created by menouar on 07/05/2021.
//

#ifndef PROJETC_IG_EI_COLORING_H
#define PROJETC_IG_EI_COLORING_H



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ei_types.h"
#include "hw_interface.h"
/**
 * \brief Colors the pixel of the given coordinates with a certain color given in the parameters
 *
 * @param surface   The surface that contains the pixel we want to color
 * @param color     The color we want to give to our pixel
 * @param x         The abscissa index of our pixel in the given surface
 * @param y         The ordinate index of our pixel in the given surface
*/
void        ei_color_pixel(ei_surface_t    surface,
                           uint32_t 	   color,
                           int             x,
                           int             y);

/**
 *  \brief Draws a line of x-dominant slope with a positive x-slope and a positive y-slope
 *
 *  @param surface The surface that contains the points of our line
 *  @param color   The wanted color of the line
 *  @param start   The starting point of the line
 *  @param end     The ending point of the line
*/
void        ei_color_1_pos_x_pos_y(ei_surface_t        surface,
                                   uint32_t            color,
                                   ei_linked_point_t*  start,
                                   ei_linked_point_t*  end,
                                   ei_rect_t* clipper);


/**
 *  \brief Draws a line of x-dominant slope with a positive x-slope and a negative y-slope
 *
 *  @param surface The surface that contains the points of our line
 *  @param color   The wanted color of the line
 *  @param start   The starting point of the line
 *  @param end     The ending point of the line
*/
void        ei_color_1_pos_x_neg_y(ei_surface_t        surface,
                                   uint32_t            color,
                                   ei_linked_point_t*  start,
                                   ei_linked_point_t*  end,
                                   ei_rect_t* clipper);


/**
 *  \brief Draws a line of x-dominant slope with a negative x-slope and a positive y-slope
 *
 *  @param surface The surface that contains the points of our line
 *  @param color   The wanted color of the line
 *  @param start   The starting point of the line
 *  @param end     The ending point of the line
*/
void        ei_color_1_neg_x_pos_y(ei_surface_t        surface,
                                   uint32_t            color,
                                   ei_linked_point_t*  start,
                                   ei_linked_point_t*  end,
                                   ei_rect_t* clipper);

/**
 *  \brief Draws a line of x-dominant slope with a negative x-slope and a negative y-slope
 *
 *  @param surface The surface that contains the points of our line
 *  @param color   The wanted color of the line
 *  @param start   The starting point of the line
 *  @param end     The ending point of the line
*/
void        ei_color_1_neg_x_neg_y(ei_surface_t        surface,
                                   uint32_t            color,
                                   ei_linked_point_t*  start,
                                   ei_linked_point_t*  end,
                                   ei_rect_t* clipper);


/**
 *  \brief Draws a line of y-dominant slope with a positive x-slope and a positive y-slope
 *
 *  @param surface The surface that contains the points of our line
 *  @param color   The wanted color of the line
 *  @param start   The starting point of the line
 *  @param end     The ending point of the line
*/
void        ei_color_2_pos_x_pos_y(ei_surface_t        surface,
                                   uint32_t            color,
                                   ei_linked_point_t*  start,
                                   ei_linked_point_t*  end,
                                   ei_rect_t* clipper);


/**
 *  \brief Draws a line of y-dominant slope with a positive x-slope and a negative y-slope
 *
 *  @param surface The surface that contains the points of our line
 *  @param color   The wanted color of the line
 *  @param start   The starting point of the line
 *  @param end     The ending point of the line
*/
void        ei_color_2_pos_x_neg_y(ei_surface_t        surface,
                                   uint32_t            color,
                                   ei_linked_point_t*  start,
                                   ei_linked_point_t*  end,
                                   ei_rect_t* clipper);


/**
 *  \brief Draws a line of y-dominant slope with a negative x-slope and a positive y-slope
 *
 *  @param surface The surface that contains the points of our line
 *  @param color   The wanted color of the line
 *  @param start   The starting point of the line
 *  @param end     The ending point of the line
*/
void        ei_color_2_neg_x_pos_y(ei_surface_t        surface,
                                   uint32_t            color,
                                   ei_linked_point_t*  start,
                                   ei_linked_point_t*  end,
                                   ei_rect_t* clipper);


/**
 *  \brief Draws a line of y-dominant slope with a negative x-slope and a negative y-slope
 *
 *  @param surface The surface that contains the points of our line
 *  @param color   The wanted color of the line
 *  @param start   The starting point of the line
 *  @param end     The ending point of the line
*/
void        ei_color_2_neg_x_neg_y(ei_surface_t        surface,
                                   uint32_t            color,
                                   ei_linked_point_t*  start,
                                   ei_linked_point_t*  end,
                                   ei_rect_t* clipper);
/**
 *  \brief Draws a line of x-dominant slope with a positive x-slope and a positive y-slope
 *
 *  @param surface The surface that contains the points of our line
 *  @param color   The wanted color of the line
 *  @param start   The starting point of the line
 *  @param end     The ending point of the line
*/
void        ei_color_3_pos_x_pos_y(ei_surface_t        surface,
                                   uint32_t            color,
                                   ei_linked_point_t*  start,
                                   ei_linked_point_t*  end,
                                   ei_rect_t* clipper);
                                   
/**
 *  \brief Draws a line of x-dominant slope with a positive x-slope and a negative y-slope
 *
 *  @param surface The surface that contains the points of our line
 *  @param color   The wanted color of the line
 *  @param start   The starting point of the line
 *  @param end     The ending point of the line
*/
void        ei_color_3_pos_x_neg_y(ei_surface_t        surface,
                                   uint32_t            color,
                                   ei_linked_point_t*  start,
                                   ei_linked_point_t*  end,
                                   ei_rect_t* clipper);
                                   
/**
 *  \brief Draws a line of x-dominant slope with a negative x-slope and a positive y-slope
 *
 *  @param surface The surface that contains the points of our line
 *  @param color   The wanted color of the line
 *  @param start   The starting point of the line
 *  @param end     The ending point of the line
*/
void        ei_color_3_neg_x_pos_y(ei_surface_t        surface,
                                   uint32_t            color,
                                   ei_linked_point_t*  start,
                                   ei_linked_point_t*  end,
                                   ei_rect_t* clipper);

/**
 *  \brief Draws a line of x-dominant slope with a negative x-slope and a negative y-slope
 *
 *  @param surface The surface that contains the points of our line
 *  @param color   The wanted color of the line
 *  @param start   The starting point of the line
 *  @param end     The ending point of the line
*/
void        ei_color_3_neg_x_neg_y(ei_surface_t        surface,
                                   uint32_t            color,
                                   ei_linked_point_t*  start,
                                   ei_linked_point_t*  end,
                                   ei_rect_t* clipper);

#endif //PROJETC_IG_EI_COLORING_H
