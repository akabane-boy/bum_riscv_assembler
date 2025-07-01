#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void delete_comments(char *line);
void delete_nl(char *line);

int main(void)
{
	FILE *fptr;
	char line[256];

	fptr = fopen("../example.s", "r");

	if (fptr == NULL) {
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	/* Main Logic */
	while (fgets(line, sizeof(line), fptr) != NULL) {
		if (strcmp(line, "\n") == 0) continue;
		delete_nl(line); /* delete '\n' */
		delete_comments(line); /* delete all char after '#' */
		printf("%s\n", line);
	}

	/* close a file */
	fclose(fptr);

	return 0;
}

void delete_nl(char *line)
{
	char *nlptr = NULL;

	if ((nlptr = strchr(line, '\n')) != NULL) {
		*nlptr = '\0';
	}
}

void delete_comments(char *line)
{
	char *commentptr = NULL;

	if ((commentptr = strchr(line, '#')) != NULL) {
		*commentptr = '\0';
	}
}

