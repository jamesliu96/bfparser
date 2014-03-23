#include <stdio.h> 

int main(int argc, char *argv[]) 
{ 
    static unsigned sqr[]={0, 0, 0, 0, 0, 25, 36, 49, 64, 81, 100, 121, 144}; 
    unsigned char oldch, ch, i; 
    unsigned TextLen; 
    FILE *in, *out; 
    if (argc != 3) 
        return puts("MasterRay TextToBF\nTextToBF source destination\n\n  source       Specify the text file.\n  destination  Specify the filename for the converted BrainFuck file."), 0;
    if ((in = fopen(argv[1], "rb")) == NULL) 
        return puts("Cannot open the source file specified."), 1; 
    if ((out = fopen(argv[2], "wb")) == NULL) 
        return puts("Cannot write in the destination file specified."), 2; 
    fseek(in, 0, SEEK_END); 
    TextLen = ftell(in); 
    fseek(in, 0, SEEK_SET); 
    for (oldch = 0; TextLen != 0; --TextLen) 
    { 
        ch = fgetc(in); 
        if (ch == oldch) 
                fwrite(".", 1, 1, out); 
        else if ((unsigned char)(ch - oldch) <= 127) 
        { 
            ch -= oldch; 
            if (ch < 16) 
            { 
                fwrite("+++++++++++++++", ch, 1, out); 
                fwrite(".", 1, 1, out); 
            } 
            else 
            { 
                for (i = 5; sqr[i] <= ch; ++i); 
                fwrite(">+++++++++++++++", i--, 1, out); 
                fwrite("[<", 2, 1, out); 
                if (ch % i > i / 2) 
                { 
                    fwrite("+++++++++++++++", ch / i + 1, 1, out); 
                    fwrite(">-]<", 4, 1, out); 
                    fwrite("---------------", i - ch % i, 1, out); 
                } 
                else 
                { 
                    fwrite("+++++++++++++++", ch / i, 1, out);
                                        fwrite(">-]<", 4, 1, out); 
                    fwrite("+++++++++++++++", ch % i, 1, out); 
                } 
                fwrite(".", 1, 1, out); 
            } 
            oldch += ch; 
        } 
        else if ((unsigned char)(ch - oldch) > 127) 
        { 
            ch = oldch - ch; 
            if (ch < 16) 
            { 
                fwrite("---------------", ch, 1, out); 
                fwrite(".", 1, 1, out); 
            } 
            else 
            { 
                for (i = 5; sqr[i] <= ch; ++i); 
                fwrite(">+++++++++++++++", i--, 1, out); 
                fwrite("[<", 2, 1, out); 
                if (ch % i > i / 2) 
                { 
                    fwrite("---------------", ch / i + 1, 1, out); 
                    fwrite(">-]<", 4, 1, out); 
                    fwrite("+++++++++++++++", i - ch % i, 1, out); 
                } 
                else 
                { 
                    fwrite("---------------", ch / i, 1, out); 
                    fwrite(">-]<", 4, 1, out); 
                    fwrite("---------------", ch % i, 1, out); 
                } 
                fwrite(".", 1, 1, out); 
            } 
            oldch -= ch; 
        } 
    } 
    return 0; 
}