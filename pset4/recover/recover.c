#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *inputfile = fopen(argv[1], "r");
    FILE *outputfile = NULL;
    int filecount = 0;
    char filename[8];

    if (!inputfile)
    {
        printf("Could not open file\n");
        return 1;
    }

    BYTE buffer[512];
    size_t bytesread = fread(buffer, sizeof(BYTE), 512, inputfile);

    while (bytesread != 0 && !feof(inputfile))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            if (outputfile)
            {
                fclose(outputfile);
            }
            sprintf(filename, "%03i.jpg", filecount);
            outputfile = fopen(filename, "w");
            filecount++;
        }

        if (outputfile)
        {
            fwrite(buffer, sizeof(BYTE), 512, outputfile);
        }

        bytesread = fread(buffer, sizeof(BYTE), 512, inputfile);
    }

    fclose(outputfile);
    fclose(inputfile);

    return 0;
}
