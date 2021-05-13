//
// Created by menouar on 08/05/2021.
//

#ifndef PROJETC_IG_STRUCT_H
#define PROJETC_IG_STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ei_types.h"
#include "hw_interface.h"

typedef struct Segment Segment;
struct Segment
{
    ei_point_t start;
    ei_point_t end;
};


typedef struct Cell Cell;
struct Cell
{
    Segment *segment;
    Cell *next;
};

typedef struct Stack Stack;
struct Stack
{
    Cell *first;
};
typedef struct tc_carac tc_carac;
struct tc_carac {
    int y_max;
    int x_min;
    float m;
    struct tc_carac* next;
};

typedef struct tc_cell t_cell;
struct tc_cell
{
    struct tc_carac *tc_carac;
    struct tc_cell *next;
};

typedef struct tca_cell tca_cell;
struct tca_cell
{
    int y_max;
    float x_min;
    float m;
    struct tca_cell* next;
};

void add_stack(Stack *stack, Segment *segment);

Segment* pop(Stack *stack);

void print_s_Array(Segment array[], int size);

struct tc_cell* get_tc(ei_linked_point_t*	first_point);

void* tca_append(struct tca_cell** tca, int y_max, float x_min, float m);

void sort_tca(struct tca_cell** tca);

int get_min(ei_linked_point_t* first);

#endif //PROJETC_IG_STRUCT_H
