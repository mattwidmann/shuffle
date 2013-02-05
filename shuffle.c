#include <stdlib.h>
#include <stdio.h>
#include <time.h>

size_t read_lines(FILE * input, char * * * lines);
size_t grow_allocation(int allocation);
void swap_lines(char * * first, char * * second);

int main(void)
{
    char * * lines;
    ssize_t n_lines = read_lines(stdin, &lines);

    srandom(time(NULL));

    // randomly swap lines
    for (int i = 0; i < n_lines; i++) {
        swap_lines(&(lines[i]), &(lines[random() % n_lines]));
    }

    for (int i = 0; i < n_lines; i++) {
        printf("%s", lines[i]);
    }
    for (int i = 0; i < n_lines; i++) {
        free(lines[i]);
    }

    free(lines);

    return 0;
}

#define BUF_SIZE 15

size_t read_lines(FILE * input, char * * * lines)
{
    if (!lines) {
        return 0;
    }

    int lines_allocated = BUF_SIZE;
    *lines = malloc(sizeof (char *) * lines_allocated);
    if (!*lines) {
        perror("ERROR");
        exit(EXIT_FAILURE);
    }

    ssize_t n_lines = 0;
    char * line = NULL;
    size_t line_size = 0;
    while (getline(&line, &line_size, input) > 0) {
        (*lines)[n_lines++] = line;
        line = NULL;
        line_size = 0;

        if (n_lines == lines_allocated) {
            // grow the array of lines
            lines_allocated = grow_allocation(lines_allocated);
            char * * temp = realloc(*lines, sizeof (char *) * lines_allocated);
            if (!temp) {
                for (int i = 0; i < n_lines; i++) {
                    free((*lines)[i]);
                }
                free(*lines);

                perror("ERROR");
                exit(EXIT_FAILURE);
            }
            *lines = temp;
        }
    }

    return n_lines;
}

void swap_lines(char * * first, char * * second)
{
    char * temp = *first;
    *first = *second;
    *second = temp;
}

size_t grow_allocation(int allocation)
{
    return (allocation + 1) * 2 - 1;
}

