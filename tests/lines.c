#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "hw_interface.h"
#include "ei_utils.h"
#include "ei_draw.h"
#include "ei_types.h"
#include "ei_event.h"
#include "ei_coloring.h"


/* test_line --
 *
 *	Draws a simple line in the canonical octant, that is, x1>x0 and y1>y0, with
 *	dx > dy. This can be used to test a first implementation of Bresenham
 *	algorithm, for instance.
 */
void test_line(ei_surface_t surface, ei_rect_t* clipper)
{
	ei_color_t		color		= { 255, 0, 255, 255 };
	ei_linked_point_t	pts[2];

	pts[0].point.x = 200; pts[0].point.y = 200; pts[0].next = &pts[1];
	pts[1].point.x = 600; pts[1].point.y = 400; pts[1].next = NULL;
	
	ei_draw_polyline(surface, pts, color, clipper);
}



/* test_octogone --
 *
 *	Draws an octogone in the middle of the screen. This is meant to test the
 *	algorithm that draws a polyline in each of the possible octants, that is,
 *	in each quadrant with dx>dy (canonical) and dy>dx (steep).
 */
void test_octogone(ei_surface_t surface, ei_rect_t* clipper)
{
	ei_color_t		color		= { 0, 255, 0, 255 };
	ei_linked_point_t	pts[9];
	int			i, xdiff, ydiff;

	/* Initialisation */
	pts[0].point.x = 400;
	pts[0].point.y = 90;

	/* Draw the octogone */
	for(i = 1; i <= 8; i++) {
		 /*	Add or remove 70/140 pixels for next point
			The first term of this formula gives the sign + or - of the operation
			The second term is 2 or 1, according to which coordinate grows faster
			The third term is simply the amount of pixels to skip */
		xdiff = pow(-1, (i + 1) / 4) * pow(2, (i / 2) % 2 == 0) * 70;
		ydiff = pow(-1, (i - 1) / 4) * pow(2, (i / 2) % 2) * 70;

		pts[i].point.x = pts[i-1].point.x + xdiff;
		pts[i].point.y = pts[i-1].point.y + ydiff;
		pts[i-1].next = &(pts[i]);
	}

	/* End the linked list */
	pts[i-1].next = NULL;

	/* Draw the form with polylines */
	ei_draw_polyline(surface, pts, color, clipper);
}



/* test_square --
 *
 *	Draws a square in the middle of the screen. This is meant to test the
 *	algorithm for the special cases of horizontal and vertical lines, where
 *	dx or dy are zero
 */
void test_square(ei_surface_t surface, ei_rect_t* clipper)
{
	ei_color_t		color		= { 255, 0, 0, 255 };
	ei_linked_point_t	pts[5];
	int			i, xdiff, ydiff;

	/* Initialisation */
	pts[0].point.x = 300;
	pts[0].point.y = 400;

	/* Draw the square */
	for(i = 1; i <= 4; i++) {
		/*	Add or remove 200 pixels or 0 for next point
			The first term of this formula gives the sign + or - of the operation
			The second term is 0 or 1, according to which coordinate grows
			The third term is simply the side of the square */
		xdiff = pow(-1, i / 2) * (i % 2) * 200;
		ydiff = pow(-1, i / 2) * (i % 2 == 0) * 200;

		pts[i].point.x = pts[i-1].point.x + xdiff;
		pts[i].point.y = pts[i-1].point.y + ydiff;
		pts[i-1].next = &(pts[i]);
	}

	/* End the linked list */
	pts[i-1].next = NULL;

	/* Draw the form with polylines */
	ei_draw_polyline(surface, pts, color, clipper);
}



/* test_dot --
 *
 *	Draws a dot in the middle of the screen. This is meant to test the special 
 *	case when dx = dy = 0
 */
void test_dot(ei_surface_t surface, ei_rect_t* clipper)
{
	ei_color_t		color		= { 0, 0, 0, 255 };
	ei_linked_point_t	pts[3];

	pts[0].point.x = 400; pts[0].point.y = 300; pts[0].next = &(pts[1]);
	pts[1].point.x = 400; pts[1].point.y = 300; pts[1].next = NULL;

	ei_draw_polyline(surface, pts, color, clipper);
}

void test_copy(ei_surface_t destination){
    ei_size_t size = ei_size(200,200);
    ei_surface_t source = hw_surface_create(destination,size,EI_FALSE);
    ei_color_t color= {255,0,255,0};
    ei_rect_t *dst_rect;
    dst_rect = (ei_rect_t*) malloc(sizeof(ei_rect_t));
    dst_rect ->size = ei_size(200,200);
    dst_rect ->top_left = ei_point(100,100);



    ei_fill(source,&color,NULL);


    ei_copy_surface(destination,dst_rect,source,NULL,EI_TRUE);

}


/*
 * ei_main --
 *
 *	Main function of the application.
 */
int main(int argc, char** argv)
{
	ei_size_t		win_size	= ei_size(800, 600);
	ei_surface_t		main_window	= NULL;
	ei_color_t		white		= { 0xff, 0xff, 0xff, 0xff };
	ei_rect_t*		clipper_ptr	= NULL;
<<<<<<< Updated upstream
	ei_rect_t		clipper		= ei_rect(ei_point(200, 150), ei_size(100, 100));
=======
	ei_rect_t		clipper		= ei_rect(ei_point(200, 150), ei_size(400, 300));
>>>>>>> Stashed changes
	clipper_ptr		= &clipper;
	ei_event_t		event;

    char*		text = "Yey";
    ei_point_t* where ;
    where = (ei_point_t *)malloc(sizeof(ei_point_t));
    where->x = 400;
    where->y = 300;
    ei_color_t color = {0,52,0,0};

	hw_init();
		
	main_window = hw_create_window(win_size, EI_FALSE);
	
	/* Lock the drawing surface, paint it white. */
	hw_surface_lock	(main_window);

	ei_fill		(main_window, &color, NULL);

	/* Draw polylines. */
	test_line	(main_window, clipper_ptr);
<<<<<<< Updated upstream
//	test_octogone	(main_window, clipper_ptr);
//	test_square	(main_window, clipper_ptr);
//	test_dot	(main_window, clipper_ptr);
//  ei_draw_text(main_window, where, text, ei_default_font, color,NULL);
     test_copy(main_window);
=======
	test_octogone	(main_window, clipper_ptr);
	test_square	(main_window, clipper_ptr);
	test_dot	(main_window, clipper_ptr);
	
>>>>>>> Stashed changes
	/* Unlock and update the surface. */
	hw_surface_unlock(main_window);
	hw_surface_update_rects(main_window, NULL);
	
	/* Wait for a character on command line. */
	event.type = ei_ev_none;
	while (event.type != ei_ev_keydown)
		hw_event_wait_next(&event);

	hw_quit();
	return (EXIT_SUCCESS);
}
