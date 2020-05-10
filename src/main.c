#include <stdio.h>
#include <stdlib.h>
#include <parse_kaomoji.h>
#include <parse_input.h>
#include <format_dialog.h>
#include <rotate_color.h>

#define MAX_LINE_LENGTH 24
#define MAX_LINE_COUNT  30
#define MAX_KAOMOJI_COUNT 200

int main(int argc, char **argv) {
    // Check for command line arguments 
    if (argc < 2) {
        printf("Usage : rainbow-dialog <kaomoji-filename>\n");
        return 1;
    }

    // Initialize kaomoji array.
    char *kaomojis[MAX_KAOMOJI_COUNT];
    int i;
    for (i = 0; i < MAX_KAOMOJI_COUNT; i++) {
        kaomojis[i] = NULL;
    }

    // Parse kaomoji file and save the result in the array.
    int kaomoji_count = parse_kaomoji(kaomojis, argv[1], MAX_KAOMOJI_COUNT, MAX_LINE_LENGTH);

    // Parse input.
    char *input_line = calloc(MAX_LINE_LENGTH * MAX_LINE_COUNT, sizeof(char));
    char *formatted_line = calloc((MAX_LINE_LENGTH + 5) * MAX_LINE_COUNT, sizeof(char));
    i = 0;
    while (get_next_dialog(input_line, MAX_LINE_LENGTH, MAX_LINE_COUNT) != NULL) {
        rotate_color();
        printf(
            "%s\n%s\n\n",
            kaomojis[i],
            box_message(formatted_line, input_line, MAX_LINE_LENGTH, MAX_LINE_COUNT)
        );
        i = (i + 1) % kaomoji_count;
    }
    free(input_line);
    free(formatted_line);

    // Clean-up kaomoji array.
    for (i = 0; i < MAX_KAOMOJI_COUNT; i++) {
        free(kaomojis[i]);
    }
    return 0;
}