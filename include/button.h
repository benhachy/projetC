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

ei_linked_point_t* arc(ei_point_t center, int rayon, float start_angle, float end_angle);

ei_linked_point_t* rounded_frame(ei_rect_t rect, int r);

#endif //PROJETC_IG_BUTTON_H
