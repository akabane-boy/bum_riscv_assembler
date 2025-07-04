#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lexer.h"


/*
 * delete_nl:
 * Gets string.
 * Changes '\n' to '\0' == Delete newline char.
 */
void delete_nl(char *line)
{
	char *nlptr = NULL;

	if ((nlptr = strchr(line, '\n')) != NULL) {
		*nlptr = '\0';
	}
}

/*
 * delete_comments:
 * Gets string.
 * If string has '#', delete all char after '#' including itself.
 */
void delete_comments(char *line)
{
	char *commentptr = NULL;

	if ((commentptr = strchr(line, '#')) != NULL) {
		*commentptr = '\0';
	}
}

/* 
 * lexer_riscv:
 * Gets a file.
 * Modify them into tokens.
 * Give it to char **arr.
 */
int lexer_riscv(FILE *fptr, char *filename, char **arr) {
	char line[256];
	char *token = NULL;
	int i = 0;

	fptr = fopen(filename, "r");

	if (fptr == NULL) {
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	/* Main Logic */
	while (fgets(line, sizeof(line), fptr) != NULL) {
		if (strcmp(line, "\n") == 0) continue; /* If line has only '\n' */
		delete_nl(line); /* delete '\n' */
		delete_comments(line); /* delete all char after '#' */

		token = strtok(line, " ,\t");
		if (token == NULL) continue;
		arr[i] = malloc(strlen(token) + 1); /* +1 is for '\0' */
		strcpy(arr[i], token);

		while ((token = strtok(NULL, " ,\t")) != NULL) {
			i++;
			arr[i] = malloc(strlen(token) + 1);
			strcpy(arr[i], token);
		}
		i++;
	}
	fclose(fptr);

	return i;
}

void free_tokens(char **arr, int size)
{
	for (int i = 0; i < size; i++) {
		free(arr[i]);
	}
}
