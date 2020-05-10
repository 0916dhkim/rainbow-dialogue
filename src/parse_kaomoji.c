#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int parse_kaomoji(char **target, char *filename, int max_kaomoji_count, int max_kaomoji_length) {
    int kaomoji_count = 0;
    int line_position = 0;
    FILE *kaomoji_file = fopen(filename, "r");
    char c;
    while((c = fgetc(kaomoji_file)) != EOF) {
        if (c == '\n') {
            // Ignore newline.
            target[kaomoji_count++][line_position] = '\0';
            line_position = 0;
            continue;
        }
        if (target[kaomoji_count] == NULL) {
            target[kaomoji_count] = calloc(max_kaomoji_count, sizeof(char));
        }
        target[kaomoji_count][line_position++] = c;
    }
    fclose(kaomoji_file);
    return kaomoji_count;
}
