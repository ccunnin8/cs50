#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
int const chunk_size = 512;

int main(int argc, char *argv[])
{
    //Make sure user enters a file
    if (argc != 2)
    {
        fprintf(stderr,"proper usage: recover filename");
        return 1;
    }

     //create numbered files
    int file_num = 0;
    char filename[7] = {};
    sprintf(filename, "%03i.jpg", file_num);

    //Make sure file is found
    FILE *raw = fopen(argv[1],"r");
    if (raw == NULL)
    {
        fprintf(stderr,"%s not found",argv[1]);
        return 2;
    }

    //parse file!
    //creates an array of BYTEs size = 512
    BYTE chunk[chunk_size];

    //read in chunks of 512 until we find a jpeg
    fread(chunk,chunk_size,1,raw);
    while (chunk[0] != 0xff || chunk[1] != 0xd8 || chunk[2] != 0xff || (chunk[3] & 0xf0) != 0xe0)
    {
        fread(&chunk,chunk_size,1,raw);
    }

    //write first part of mem card
    FILE *jpeg = fopen(filename,"w");
    if (jpeg == NULL)
    {
        fprintf(stderr, "Error.... closing");
        return 5;
    }
    int count = 1;
    fwrite(chunk,chunk_size,1,jpeg);
    //check to see if this is the last file chunk size is < 512
    while(fread(chunk,chunk_size,1,raw) == 1)
    {
        //once JPEG found write to a new file until we hit another jpeg
        if (chunk[0] == 0xff && chunk[1] == 0xd8 && chunk[2] == 0xff && (chunk[3] & 0xf0) == 0xe0)
        {
            //close old file
            fclose(jpeg);
            //start a new file
            sprintf(filename,"%03i.jpg",count++);
            jpeg = fopen(filename,"w");
            if (jpeg == NULL)
            {
                fprintf(stderr,"some type of error happened");
                return 3;
            }
            fwrite(chunk,chunk_size,1,jpeg);
        }
        else
        {
            //write into old file
            fwrite(chunk,chunk_size,1,jpeg);
        }
    }
    fclose(jpeg);
    printf("loop exited");
    return 0;
}