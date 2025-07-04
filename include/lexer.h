#ifndef LEXER_H
#define LEXER_H

void delete_comments(char *line);
void delete_nl(char *line);
void lexer_riscv(FILE *fptr, char *filename, char **arr);
void free_tokens(char **arr);

#endif /* LEXER_H */
