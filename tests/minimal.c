#include <stdlib.h>

#include "ei_types.h"
#include "ei_event.h"
#include "ei_utils.h"
#include "ei_draw.h"
#include "struct.h"
#include "hw_interface.h"
#include "button.h"

int main(int argc, char* argv[])
{
	ei_surface_t			main_window		= NULL;
	ei_size_t			main_window_size	= ei_size(640, 480);
	ei_event_t			event;
	uint32_t			white			= 0xffffffff;
	uint32_t*			pixel_ptr;
	int				i;

	// Init access to hardware.
	hw_init();

	// Create the main window.
	main_window = hw_create_window(main_window_size, EI_FALSE);

	// Lock the surface for drawing, fill in white, unlock, update screen.
	hw_surface_lock(main_window);
	
	pixel_ptr = (uint32_t*)hw_surface_get_buffer(main_window);
	for (i = 0; i < (main_window_size.width * main_window_size.height); i++)
	    *pixel_ptr++ = white;
	
	hw_surface_unlock(main_window);
	hw_surface_update_rects(main_window, NULL);
    ei_point_t center = {200, 200};
    ei_point_t start = {50, 50};
    ei_point_t start1   = {100, 100};
    ei_point_t start2   = {20, 200};
    ei_point_t end1      = {40, 70};
    ei_point_t end      = {50, 50};
    ei_linked_point_t* linked_test = (ei_linked_point_t*)malloc(sizeof(ei_linked_point_t));
    linked_test->point = start;
    linked_test->next = (ei_linked_point_t*)malloc(sizeof(ei_linked_point_t));
    linked_test->next->point = start1;
    linked_test->next->next = (ei_linked_point_t*)malloc(sizeof(ei_linked_point_t));
    linked_test->next->next->point = start2;
    linked_test->next->next->next = (ei_linked_point_t*)malloc(sizeof(ei_linked_point_t));
    linked_test->next->next->next->point = end1;
    linked_test->next->next->next->next = (ei_linked_point_t*)malloc(sizeof(ei_linked_point_t));
    linked_test->next->next->next->next->point = end;
    linked_test->next->next->next->next->next = NULL;

    ei_size_t rect_size1 = {200, 100};
    ei_rect_t rect = {start1, rect_size1};

    //ei_linked_point_t* frame = rounded_frame(rect, 10, 3);
    //float end_p = 180;
    //float start_p = 90;
    //ei_linked_point_t* linked_test2 = arc(center, 50, start_p, end_p);
    ei_color_t test_color = {255, 0, 0};
    ei_color_t color1 = {0,255, 0, 0};
    ei_color_t color2 = {0,0,255, 0};
    //ei_draw_polyline(main_window, linked_test, test_color, NULL);
    //ei_draw_polygon(main_window, frame, test_color, NULL);
    //draw_button(main_window,rect, 10, test_color);
    ei_font_t font = hw_text_font_create(ei_default_font_filename, ei_style_normal, 60);
    char *text = "Dumb Dumb";
    /*
    hw_surface_lock(main_window);
    ei_draw_text(main_window, &start, text, font, test_color, NULL);
    hw_surface_unlock(main_window);
    hw_surface_update_rects(main_window, NULL);
    */
    hw_surface_lock(main_window);
    ei_linked_point_t* cercle = circle(start, 8, 0, 359);
    ei_linked_point_t* half_circle1 = arc(start, 11, 45, 235);
    ei_linked_point_t* half_circle2 = arc(start, 11, 225, 55);
    ei_draw_polygon(main_window, half_circle1, color1, NULL);
    ei_draw_polygon(main_window, half_circle2, color2, NULL);
    ei_draw_polygon(main_window, cercle, test_color, NULL);
    hw_surface_unlock(main_window);
    hw_surface_update_rects(main_window, NULL);
	// Wait for a key press.
	event.type = ei_ev_none;
	while (event.type != ei_ev_keydown)
		hw_event_wait_next(&event);
        //ei_draw_polyline(main_window, linked_test, test_color, NULL);
        //ei_draw_polygon(main_window, linked_test2, test_color, NULL);
	// Free hardware resources.
	hw_quit();


	// Terminate program with no error code.
	return 0;
}


