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

typedef struct ei_button_cell {

    ei_widget_t* widget;
    ei_color_t* color;
    int*			border_width;
    int*			corner_radius;
    ei_relief_t		relief;

    struct ei_button_cell* next;

}ei_button_cell;


typedef struct ei_frame_cell {

    ei_widget_t* widget;
    ei_color_t* color;
    int*			border_width;
    ei_relief_t		relief;

    struct ei_frame_cell* next;

}ei_frame_cell;


typedef struct ei_text_cell {

    ei_widget_t* widget;
    char**			text;
    ei_color_t* color;
    ei_font_t*		text_font;

    struct ei_text_cell* next;

}ei_text_cell;


typedef struct ei_toplevel_cell {

    ei_widget_t* widget;
    char**			title;
    ei_color_t* color;
    ei_bool_t*		closable;
    ei_axis_set_t*		resizable;
    ei_size_t*		min_size;

    struct ei_toplevel_cell* next;

}ei_toplevel_cell;


void dessin(ei_widget_t* widget, ei_surface_t surface, ei_surface_t offscreen);

ei_bool_t ei_frame_handlefunc_t (struct ei_widget_t*	widget,
                                 struct ei_event_t*	event);

ei_bool_t ei_button_handlefunc_t (struct ei_widget_t*	widget,
                                  struct ei_event_t*	event);

ei_bool_t ei_text_handlefunc_t (struct ei_widget_t*	widget,
                                  struct ei_event_t*	event);

ei_bool_t ei_toplevel_handlefunc_t (struct ei_widget_t*	widget,
                                struct ei_event_t*	event);



void	geomnotifyfunc_frame	(struct ei_widget_t*	widget,
                                 ei_rect_t		rect);

void	geomnotifyfunc_button	(struct ei_widget_t*	widget,
                                  ei_rect_t		rect);

void	geomnotifyfunc_text	(struct ei_widget_t*	widget,
                                  ei_rect_t		rect);

void	geomnotifyfunc_toplevel	(struct ei_widget_t*	widget,
                                ei_rect_t		rect);





void	setdefaultsfunc_frame	(struct ei_widget_t*	widget);

void	setdefaultsfunc_button	(struct ei_widget_t*	widget);

void	setdefaultsfunc_text	(struct ei_widget_t*	widget);

void	setdefaultsfunc_toplevel	(struct ei_widget_t*	widget);





void	drawfunc_frame		(struct ei_widget_t*	widget,
                               ei_surface_t		surface,
                               ei_surface_t		pick_surface,
                               ei_rect_t*		clipper);

void	drawfunc_button		(struct ei_widget_t*	widget,
                                ei_surface_t		surface,
                                ei_surface_t		pick_surface,
                                ei_rect_t*		clipper);

void	drawfunc_text		(struct ei_widget_t*	widget,
                                ei_surface_t		surface,
                                ei_surface_t		pick_surface,
                                ei_rect_t*		clipper);

void	drawfunc_toplevel		(struct ei_widget_t*	widget,
                              ei_surface_t		surface,
                              ei_surface_t		pick_surface,
                              ei_rect_t*		clipper);






void releasefunc_frame(struct ei_widget_t* frame_wid);

void releasefunc_button(struct ei_widget_t* button_wid);

void releasefunc_text(struct ei_widget_t* button_wid);

void releasefunc_toplevel(struct ei_widget_t* button_wid);




struct ei_widget_t* allowfunc_frame(void) ;

struct ei_widget_t* allowfunc_button(void);

struct ei_widget_t* allowfunc_text(void);

struct ei_widget_t* allowfunc_toplevel(void);




struct ei_frame_cell* get_frame_cell(struct ei_widget_t* widget);

struct ei_button_cell* get_button_cell(struct ei_widget_t* widget);

struct ei_text_cell* get_text_cell(struct ei_widget_t* widget);

struct ei_toplevel_cell* get_toplevel_cell(struct ei_widget_t* widget);




int is_widget_button(uint32_t id, ei_surface_t surface);

int is_widget_frame(uint32_t id, ei_surface_t surface);

int is_widget_text(uint32_t id, ei_surface_t surface);

int is_widget_toplevel(uint32_t id, ei_surface_t surface);




struct ei_button_cell* button_from_id(uint32_t id, ei_surface_t surface);

struct ei_frame_cell* frame_from_id(uint32_t id, ei_surface_t surface);

struct ei_text_cell* text_from_id(uint32_t id, ei_surface_t surface);

struct ei_toplevel_cell* toplevel_from_id(uint32_t id, ei_surface_t surface);



int mouse_on_widget(struct ei_event_t event, ei_rect_t rect);

void recursion_destroy(ei_widget_t* widget);

int is_widget_close(ei_button_cell* button_cell);

#endif