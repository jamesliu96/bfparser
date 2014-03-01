#include "bf.h"

int main(int argc, char* argv[])
{
    if (argc > 1) {
        FILE *input = fopen(argv[1], "r");
        bfparser(input);
        fclose(input);
    }
    else {
        printf("%s\n", "no input file");
    }
    return 0;
}
