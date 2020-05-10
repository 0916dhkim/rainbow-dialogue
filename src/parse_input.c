#include <parse_input.h>
#include <stdio.h>
#include <stdlib.h>

char *get_next_dialogue(char *s, int maxlinelength, int maxlinecount) {
    // Start with an empty string.
    char *cur = s;
    *cur = '\0';

    int end_of_dialogue = 0; // End of dialogue reached. (newline or EOF)
    int end_of_file = 0; // EOF reached.
    int linecount;
    for (linecount = 0; linecount < maxlinecount; linecount++) {
        int linelength;
        for (linelength = 0; linelength < maxlinelength; linelength++) {
            // Read 1 char.
            char c = (char) fgetc(stdin);
            // Handle newline and EOF
            if (c == '\n') {
                end_of_dialogue = 1;
                end_of_file = 0;
                break;
            }
            if (c == EOF){
                end_of_dialogue = 1;
                end_of_file = 1;
                break;
            }
            // Concat 1 char.
            *(cur++) = c;
        }

        if (end_of_dialogue) {
            break;
        }
        // Wrap dialogue line.
        *(cur++) = '\n';
    }

    if (s == cur && end_of_file) {
        // Could not read string
        // because EOF is reached.
        return NULL;
    }
    // Null terminate and return.
    *(cur++) = '\0';
    return s;
}
