#ifndef LABEL_H
#define LABEL_H

#include <stdint.h>

#define MAX_LABEL_TABLE 256

typedef struct {
	char *label;
	uint8_t address;
} labelEntry;

extern labelEntry label_table[MAX_LABEL_TABLE];
extern int label_count;

#endif /* LABEL_H */
