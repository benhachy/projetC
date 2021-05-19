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

ei_bool_t ei_frame_handlefunc_t (struct ei_widget_t*	widget,
                                 struct ei_event_t*	event);

void	geomnotifyfunc_frame	(struct ei_widget_t*	widget,
                                 ei_rect_t		rect);

void	setdefaultsfunc_frame	(struct ei_widget_t*	widget);

void	drawfunc_frame		(struct ei_widget_t*	widget,
                               ei_surface_t		surface,
                               ei_surface_t		pick_surface,
                               ei_rect_t*		clipper);

void releasefunc_frame(struct ei_widget_t* frame_wid);

struct ei_widget_t* allowfunc_frame(void) ;

#endif