#include <stdio.h>
#include <stdarg.h>

#include "csv.h"

int csv_writeValue(csv_t *csv, char *value) {

    uint8_t quote = 0;
    size_t i = 0;

    for (; value[i] != 0; i++) {
        if (value[i] == '\n' || value[i] == '"' || value[i] == csv->separator) {
            quote = 1;
            break;
        }
    }

    i = 0;

    if (quote)
        if(fputc('"', csv->out) == EOF)
            return -__LINE__;

    for (; value[i] != 0; i++) {
        if (value[i] == '"') {
            if(fputs("\"\"", csv->out) == EOF)
                return -__LINE__;
        } else if (value[i] == '\n' && (i == 0 || value[i-1] != '\r')) {
            if(fputs("\r\n", csv->out) == EOF)
                return -__LINE__;
        } else {
            if(fputc(value[i], csv->out) == EOF)
                return -__LINE__;
        }
    }

    if (quote)
        if(fputc('"', csv->out) == EOF)
            return -__LINE__;

    return 0;
}

int csv_writeRow(csv_t *csv, ...) {
    va_list ap;
    int ret = 0;
    uint8_t newline = 0;
    char *cvalue = NULL;

    va_start(ap, csv);
    cvalue = va_arg(ap, char *);

    for (; cvalue != NULL; cvalue = va_arg(ap, char *)) {

        if (newline) {
            if(fputc(csv->separator, csv->out) == EOF) {
                va_end(ap);
                return -__LINE__;
            }
        }

        if ((ret = csv_writeValue(csv, cvalue)) < 0) {
            va_end(ap);
            return ret;
        }
        newline = 1;
    }

    if(fputs("\r\n", csv->out) == EOF) {
        va_end(ap);
        return -__LINE__;
    }
    
    va_end(ap);
    return 0;
}