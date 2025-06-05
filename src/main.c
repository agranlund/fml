#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define bufsize 4096
unsigned char buf[bufsize];

const char* strfind = "This program requires a 68881 or higher";
const char* strmark = "This is insane...       ";

long fixit(const char* filename) {

    // open for read/write
    FILE* f = fopen(filename, "rb+");
    if (f) {
        // we expect mintlib detection somewhere at
        // the start of the file
        fseek(f, 0, SEEK_SET);
        memset(buf, 0, bufsize);
        fread(buf, 1, bufsize, f);
        int findlen = strlen(strfind);
        for (int pos=8; pos<(bufsize-findlen-1); pos++) {
            if (memcmp(strfind, &buf[pos], findlen) == 0) {
                // get rid of the nonsense
                fseek(f, 0, SEEK_CUR);
                fseek(f, pos-8, SEEK_SET);
                fputc(0x4E, f); fputc(0x75, f); // rts
                fputc(0x4E, f); fputc(0x75, f); // rts
                fputc(0x4E, f); fputc(0x75, f); // rts
                fputc(0x4E, f); fputc(0x75, f); // rts
                fflush(f);
                // and mark so patcher wont detect again
                for (int i=0; i<strlen(strmark); i++) {
                    fputc(strmark[i], f);
                }
                fflush(f);
                fclose(f);
                return pos;
            }
        }
        fclose(f);
    }
    return 0;
}

int main(int args, char* argv[]) {

    if (args < 2) {
        printf("Usage: fml <program>\n");
        return 0;
    }

    // todo: add some option to recursively patch all files
    const char* filename = argv[1];
    long pos = fixit(filename);
    if (pos > 0) {
        printf("patched: %s at %08lx\n", filename, pos);
    }

    return 0;
}
