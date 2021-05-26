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

/** 
* @brief Définition d'une structure de segments
*/

typedef struct Segment Segment;
struct Segment
{
    ei_point_t start;
    ei_point_t end;
};

/** 
* @brief Définition d'une structure de liste chainée de segments
*/
typedef struct Cell Cell;
struct Cell
{
    Segment *segment;
    Cell *next;
};

/** 
* @brief Définition d'une structure de pile
*/

typedef struct Stack Stack;
struct Stack
{
    Cell *first;
};

/** 
* @brief Définition des types de la structure TC
*/
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

/** 
* @brief Définition des types de la structure TCA
*/
typedef struct tca_cell tca_cell;
struct tca_cell
{
    int y_max;
    float x_min;
    float m;
    struct tca_cell* next;
};

/** 
* @brief  Ajoute un segment dans une pile de segments
*/
void add_stack(Stack *stack, Segment *segment);

/** 
* @brief  Retourne le segment enlevé de la pile
*/ 
Segment* pop(Stack *stack);

void print_s_Array(Segment array[], int size);

/** 
* @brief  Retourne la structure Tc nécessaire au dessin du polygone 
          défini par l'ensemble de points donné
*/ 
struct tc_cell* get_tc(ei_linked_point_t*	first_point);

/** 
* @brief  Ajoute à la srutcuture tca_cell une nouvelle cellule avec les attributs données en paramètre 
*/ 
void* tca_append(struct tca_cell** tca, int y_max, float x_min, float m);

void sort_tca(struct tca_cell** tca);

int get_min(ei_linked_point_t* first);

#endif //PROJETC_IG_STRUCT_H
