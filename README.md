# CSV writer

very small library to write a CSV file

usage: 

```c

#include <stdio.h>

#include "csv.h"

int main(void) {

    FILE *file = fopen("example.csv", "w");
    csv_t csv = {};

    csv.out = file;
    csv.separator = ',';

    csv_writeRow(&csv, "field 1", "field 2", "field 3", NULL);

    return 0;
}

```