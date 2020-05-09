// Concat n chars to original string and return pointer to char
// right after the last added char.
char *concat_straight_line(char *original, char c, int n) {
    // Find null terminator.
    while (*original != '\0') {
        original++;
    }

    // Concat.
    int i;
    for (i = 0; i < n; i++) {
        *(original++) = c;
    }

    return original;
}

char *box_message(char *out, char *original, int maxlinelength, int maxlinecount) {
    char *cur = out;
    // Top border.
    cur = concat_straight_line(cur, '#', maxlinelength + 4);
    *(cur++) = '\n';
    // Top margin.
    *(cur++) = '#';
    cur = concat_straight_line(cur, ' ', maxlinelength + 2);
    *(cur++) = '#';
    *(cur++) = '\n';

    // Iterate lines.
    int line_position = maxlinelength;
    while (*original != '\0' || line_position != maxlinelength) {
        if (line_position == maxlinelength) {
            // Need to start a new line.
            *(cur++) = '#';
            *(cur++) = ' ';
            line_position = 0;
        }

        if (*original == '\0') {
            *(cur++) = ' '; // Original depleted. Fill the space.
        } else {
            if (*original == '\n') {
                original++; // Skip newline char from original.
            }
            *(cur++) = *(original++); // Copy 1 char from original.
        }
        line_position++;
        if (line_position == maxlinelength) {
            // Need to end and break line.
            *(cur++) = ' ';
            *(cur++) = '#';
            *(cur++) = '\n';
        }
    }

    // Bottom margin.
    *(cur++) = '#';
    cur = concat_straight_line(cur, ' ', maxlinelength + 2);
    *(cur++) = '#';
    *(cur++) = '\n';
    // Bottom border.
    cur = concat_straight_line(cur, '#', maxlinelength + 4);
    *(cur++) = '\0';
}