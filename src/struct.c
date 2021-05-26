//
// Created by menouar on 08/05/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "ei_types.h"
#include "struct.h"
#include "hw_interface.h"

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _b : _a; })

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })


void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void swap_seg(Segment *a, Segment *b) {
    Segment t = *a;
    *a = *b;
    *b = t;
}

struct tca_cell* get_cell_tca(struct tca_cell** tca, int i){
    struct  tca_cell* temp1 =  *tca;
    int step = 0;

    while(step != i){
        temp1 = (temp1->next);
        step++;
    }

    return temp1;
}

void* swap_tca(struct tca_cell** tca, int i, int j) {

    struct tca_cell* cell_i = get_cell_tca(tca, i);
    struct tca_cell* cell_j = get_cell_tca(tca, j);
    struct tca_cell* t = (tca_cell*)malloc(sizeof(struct tca_cell*));

    t->x_min = cell_i->x_min;
    t->y_max = cell_i->y_max;
    t->m = cell_i->m;

    cell_i->x_min = cell_j->x_min;
    cell_i->y_max = cell_j->y_max;
    cell_i->m = cell_j->m;

    cell_j->x_min = t->x_min;
    cell_j->y_max = t->y_max;
    cell_j->m = t->m;

    free(t);
}


int partition_tca(int array[], struct tca_cell** tca, int low, int high) {

    int pivot = array[high];

    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {

            i++;

            swap(&array[i], &array[j]);
            swap_tca(tca, i, j);
        }
    }
    swap(&array[i + 1], &array[high]);
    swap_tca(tca, i+1, high);

    return (i + 1);
}

int quickSort_tca(int array[],struct tca_cell** tca, int low, int high) {
    if (low < high) {

        // find the pivot element such that
        // elements smaller than pivot are on left of pivot
        // elements greater than pivot are on right of pivot
        int pi = partition_tca(array, tca, low, high);

        // recursive call on the left of pivot
        quickSort_tca(array, tca, low, pi - 1);

        // recursive call on the right of pivot
        quickSort_tca(array, tca, pi + 1, high);
    }
}

void sort_tca(struct tca_cell** tca){
    int size = 0;
    struct tca_cell* temp = *tca;
    while(temp != NULL){
        size++;
        temp = temp->next;
    }


    temp = *tca;
    int array[size];
    for (int i = 0; i < size; i++){
        array[i] = (int)floor(temp->x_min + 0.5);
        temp = temp->next;
    }

    quickSort_tca(array, tca, 0, size-1);
}

int partition(int array[], Segment s_array[], int low, int high) {

    int pivot = array[high];

    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {

            i++;

            swap(&array[i], &array[j]);
            swap_seg(&s_array[i], &s_array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    swap_seg(&s_array[i+1], &s_array[high]);

    return (i + 1);
}

int quickSort(int array[],Segment s_array[], int low, int high) {
    if (low < high) {

        // find the pivot element such that
        // elements smaller than pivot are on left of pivot
        // elements greater than pivot are on right of pivot
        int pi = partition(array, s_array, low, high);

        // recursive call on the left of pivot
        quickSort(array, s_array, low, pi - 1);

        // recursive call on the right of pivot
        quickSort(array, s_array, pi + 1, high);
    }
}

void printArray(int array[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d  ", array[i]);
    }
    printf("\n");
}

void print_s_Array(Segment array[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("Start : (%i,%i), End : (%i,%i)\n", array[i].start.x, array[i].start.y, array[i].end.x, array[i].end.y);
    }
    printf("\n");
}

void print_tc(struct tc_cell* start) {
    while (start->next != NULL){
        if (start->tc_carac == NULL){
            printf("NULL\n");
        } else {
            tc_carac* tourist = start->tc_carac;
            while (tourist->x_min != -1){
                printf("y_max %i , x_min : %i, m : %f --->", tourist->y_max, tourist->x_min, tourist->m);
                tourist = tourist->next;
            }
            printf("\n");
        }
        start = start->next;
    }
}

void* tca_append(struct tca_cell** tca, int y_max, float x_min, float m){
    if ((*tca) == NULL){
        *tca = (struct tca_cell*) malloc(sizeof(struct tca_cell));
        (*tca)->y_max = y_max;
        (*tca)->x_min = x_min;
        (*tca)->m = m;
        (*tca)->next = NULL;
    } else {
        struct tca_cell *tca_temp = *tca;
        while (tca_temp->next != NULL) {
            tca_temp = tca_temp->next;
        }
        tca_temp->next = (tca_cell *) malloc(sizeof(struct tca_cell *));
        tca_temp->next->y_max = y_max;
        tca_temp->next->x_min = x_min;
        tca_temp->next->m = m;
        tca_temp->next->next = NULL;
    }
}

int get_min(ei_linked_point_t* first){
    int min = first->point.y;
    ei_linked_point_t* temp = first;
    while(temp != NULL){
        if (temp->point.y < min){
            min = temp->point.y;
        }
        temp= temp->next;
    }
    return min;
}

struct tc_cell* get_tc(ei_linked_point_t*	first_point){

    int n = 0;
    ei_linked_point_t *temp = first_point;
    while(temp != NULL) {
        temp = temp->next;
        n++;
    }

    temp = first_point;
    int array[n-1];
    Segment s_array[n-1];
    for (int i = 0; i < n-1; i++){
        s_array[i] = (struct Segment){temp->point, temp->next->point};
        array[i] = min(temp->point.y, temp->next->point.y);
        temp = temp->next;
    }
    quickSort(array,s_array,0,n-2);
    //print_s_Array(s_array, n);
    //printArray(array, n);

    int max_y = max(s_array[n-2].start.y, s_array[n-2].end.y);

    struct tc_cell* tc_start = (struct tc_cell*)malloc(sizeof(struct tc_cell));

    struct tc_cell* tc_res = tc_start;
    int scan_start = min(s_array[0].start.y, s_array[0].end.y) - 1;
    int i = 0;
    int x_y_min = 0;
    int count_non_hori = 0;

    while (scan_start < max_y +1){
        //Si on rencontre un segment à la scan-line
        if (scan_start ==  array[i]) {
            count_non_hori = 0;
            while(scan_start == array[i] ) {

                //Si la ligne est horizontale on l'ignore et on initialise la prochaine case
                if ((float) (s_array[i].end.y - s_array[i].start.y) != 0) {

                    //Initialisation des valeurs relatives au nouveau segment rencontré
                    float m = (float) (s_array[i].end.x - s_array[i].start.x) /
                              (float) (s_array[i].end.y - s_array[i].start.y);
                    int y_max = max(s_array[i].start.y, s_array[i].end.y);
                    if (s_array[i].start.y < s_array[i].end.y) {
                        x_y_min = s_array[i].start.x;
                    } else {
                        x_y_min = s_array[i].end.x;
                    }

                    //Cas où un plusieurs segments sont rencontré à la même scan-line
                    tc_carac* tourist = tc_start->tc_carac;
                    while (tourist->x_min != -1){
                        tourist = tourist->next;
                    }

                    tourist->y_max = y_max;
                    tourist->x_min = x_y_min;
                    tourist->m = m;
                    tourist->next = (struct tc_carac *) malloc(sizeof(struct tc_carac));
                    tourist->next->x_min = -1;


                    count_non_hori++;
                }
                i++;

            }

            if (count_non_hori == 0) {
                tc_start->tc_carac = NULL;
            }
            //On intialise la prochaine case de TC
            tc_start->next = (struct tc_cell *) malloc(sizeof(struct tc_cell));
            tc_start->next->tc_carac = (struct tc_carac *) malloc(sizeof(struct tc_carac));
            tc_start->next->tc_carac->x_min = -1;
            tc_start = tc_start->next;
            scan_start++;

        } else {

            //Sinon on incrémente l'index de scan-line en initialisant les cases de TC vides
            tc_start->tc_carac = NULL;
            tc_start->next = (struct tc_cell *) malloc(sizeof(struct tc_cell));
            tc_start->next->tc_carac = (struct tc_carac*) malloc(sizeof(struct tc_carac));
            tc_start->next->tc_carac->x_min = -1;
            tc_start = tc_start->next;
            scan_start++;
        }
    }
    tc_start->tc_carac = NULL;
    tc_start->next = NULL;

    return tc_res;

}


