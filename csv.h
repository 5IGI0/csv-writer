#ifndef __CSV_H__
#define __CSV_H__

#include <stdio.h>
#include <stdint.h>

typedef struct {
    FILE *out;
    char separator;
} csv_t;

int csv_writeRow(csv_t *csv, ...);

#endif