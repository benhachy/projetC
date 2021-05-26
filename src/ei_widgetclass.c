//
// Created by menouar on 18/05/2021.
//

#include "ei_widgetclass.h"
#include "ei_widget.h"
#include "ei_draw.h"
#include <string.h>
#include "ei_draw_widget.h"

//On initialise la tête de la liste 
ei_widgetclass_t head_class = {
        "head",
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
};

ei_widgetclass_t* head_class_p = &head_class;


void			ei_widgetclass_register		(ei_widgetclass_t* widgetclass){
   
    ei_widgetclass_t *temp = &head_class;
    while(temp->next != NULL){
        temp = temp->next;
    }
    //On ajoute la classe en queue de liste
    temp->next = widgetclass;
    temp->next->next = NULL;
}

ei_widgetclass_t*	ei_widgetclass_from_name	(ei_widgetclass_name_t name){

    ei_widgetclass_t *temp = head_class_p;

    while(strcmp(temp->name,name) != 0){
        temp = temp->next;
    }

    return temp;

}
