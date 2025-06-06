#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define strsize 38
const unsigned char strfind[strsize] = {
	// pea $2AE(pc)
	// bra $316
    0x48,0x7A,0x00,0x06,0x60,0x00,0x00,0x6A,
    // This program requires a 68881
    0x54,0x68,0x69,0x73,0x20,0x70,0x72,0x6F,0x67,0x72,0x61,0x6D,0x20,
    0x72,0x65,0x71,0x75,0x69,0x72,0x65,0x73,0x20,
    0x61,0x20,0x36,0x38,0x38,0x38,0x31,0x20 };

#define bufsize (strsize*2)
unsigned char buf[bufsize*2];

long fixit(const char* filename) {

    // open for read/write
    FILE* f = fopen(filename, "rb+");
    if (f) {
        // find filesize
        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        fseek(f, 0, SEEK_SET);
        // look for code to patch away
        memset(buf, 0, bufsize*2);
        for (long fpos = 0; fpos < fsize; fpos += bufsize)
        {
            memcpy(&buf[0], &buf[bufsize], bufsize);
            fread(&buf[bufsize], 1, bufsize, f);
            for (int pos=0; pos<((bufsize*2)-strsize); pos++) {
                if (memcmp(strfind, &buf[pos], strsize) == 0) {
                    // get rid of the nonsense
                    fseek(f, 0, SEEK_CUR);
                    fseek(f, pos, SEEK_SET);
                    fputc(0x4E, f); fputc(0x75, f); // rts
                    fputc(0x4E, f); fputc(0x75, f); // rts
                    fputc(0x4E, f); fputc(0x75, f); // rts
                    fputc(0x4E, f); fputc(0x75, f); // rts
                    fflush(f);
                    fclose(f);
                    return (fpos+pos);
                }
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

    // todo: add some option to batch patch all files recursively

    const char* filename = argv[1];
    long pos = fixit(filename);
    if (pos > 0) {
        printf("patched: %s at %08lx\n", filename, pos);
    }

    return 0;
}
