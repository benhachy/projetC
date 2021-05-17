/**
 * @file	ei_draw_widget.h
 *
 * @brief 	Contient des fonctions utiles au dessin de composantes qui contiennent des widgets
 */
 
#ifndef EI_DRAW_WIDGET_H
#define EI_DRAW_WIDGET_H

#include "ei_types.h"
#include "ei_draw.h"
#include "ei_widget.h"

/**
 * @brief	draw widget, surface and offscreen
 *
 */

void dessin(ei_widget_t* widget, ei_surface_t surface, ei_surface_t offscreen);
