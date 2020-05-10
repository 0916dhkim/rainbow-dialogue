// Concat n chars to original string and return pointer to
// the new null terminator.
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

    // Null terminate.
    *original = '\0';
    return original;
}

// Concat another string to original string and return pointer to
// the new null terminator.
char *concat_string(char *original, char *addition) {
    // Find null terminator.
    while (*original != '\0') {
        original++;
    }

    // Concat.
    while (*addition != '\0') {
        *(original++) = *(addition++);
    }

    // Null terminate.
    *original = '\0';
    return original;
}

char *box_message(char *out, char *original, int maxlinelength, int maxlinecount) {
    // Start from an empty string.
    char *cur = out;
    *cur = '\0';
    // Top border.
    cur = concat_straight_line(cur, '#', maxlinelength + 4);
    cur = concat_string(cur, "\n");
    // Top margin.
    cur = concat_string(cur, "#");
    cur = concat_straight_line(cur, ' ', maxlinelength + 2);
    cur = concat_string(cur, "#\n");

    // Iterate lines.
    int line_position = maxlinelength;
    while (*original != '\0' || line_position != maxlinelength) {
        if (line_position == maxlinelength) {
            // Need to start a new line.
            cur = concat_string(cur, "# ");
            line_position = 0;
        }

        if (*original == '\0') {
            cur = concat_string(cur, " "); // Original depleted. Fill the space.
        } else {
            if (*original == '\n') {
                original++; // Skip newline char from original.
            }
            cur = concat_straight_line(cur, *(original++), 1); // Copy 1 char from original.

        }
        line_position++;
        if (line_position == maxlinelength) {
            // Need to end and break line.
            cur = concat_string(cur, " #\n");
        }
    }

    // Bottom margin.
    cur = concat_string(cur, "#");
    cur = concat_straight_line(cur, ' ', maxlinelength + 2);
    cur = concat_string(cur, "#\n");
    // Bottom border.
    cur = concat_straight_line(cur, '#', maxlinelength + 4);
    *cur = '\0';
    return out;
}