#ifndef _GUI_ELEMENT_H_
#define _GUI_ELEMENT_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// ----------------------------------- type definitions -----------------------

/**
 * Type's for size, positions.
 * Need because we have different displays
 */
typedef uint16_t gui_metric_t;

/* Base element type */
typedef struct {
    void * parent; /* Pointer to parent element */
    void * first_child; /* Pointer to first child element */
    void * first_friend; /* Pointer to first friend element */
    gui_metric_t x_pos; /* X position */
    gui_metric_t y_pos; /* Y position */
    gui_metric_t w_size; /* Width size */
    gui_metric_t h_size; /* Height size */
    void * options; /* Specific element options */
} gui_element_t;

#endif
