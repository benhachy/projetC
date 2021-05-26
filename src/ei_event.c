//
// Created by menouar on 25/05/2021.
//
#include "ei_event.h"
#include "ei_types.h"
#include "ei_widget.h"

ei_default_handle_func_t default_func = NULL;


void ei_event_set_default_handle_func(ei_default_handle_func_t func){
    default_func = func;
}

ei_default_handle_func_t ei_event_get_default_handle_func(void){
    return default_func;
}