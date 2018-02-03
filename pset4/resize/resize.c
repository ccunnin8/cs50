/**
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize size infile outfile\n");
        return 1;
    }

    // remember size to increase or decrease to
    float size  = atof(argv[1]);

    if (size < 0 || size > 100.0)
    {
        fprintf(stderr, "size must be between 0 and 100");
        return 4;
    }

    //conver the float to int b/c working with whole numbers
    //if less than 1 return the inverse of size as an int for every fth pixel
    int f = size < 1 ? (int)(1/size) : (int)size;

    //remember file names
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    /**
    ORDER OF A BITMAP FILE
    BITMAPFILEHEADER 0-10
    BITMAPINFOHEADER 14-50
    RGBTRIPLES
    **/

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bf2;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf2 = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bi2;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi2 = bi;
    bi2.biHeight  = size > 1 ? bi.biHeight * f : bi.biHeight / f;
    bi2.biWidth = size > 1 ? bi.biWidth * f : bi.biWidth / f;

    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int new_padding = (4 - (bi2.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi2.biSizeImage = ((sizeof(RGBTRIPLE) * bi2.biWidth) + new_padding) * abs(bi2.biHeight);
    bf2.bfSize = bi2.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf2, sizeof(BITMAPFILEHEADER), 1, outptr);

    //write outfile's BITMAPINFOHEADER
    fwrite(&bi2, sizeof(BITMAPINFOHEADER), 1, outptr);

    //width of memory needed for a new line W/O padding
     int line_size = bi2.biWidth * sizeof(RGBTRIPLE);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //allocate mem size of new line
         RGBTRIPLE *line = malloc(line_size);

         //ERROR CHECK w/ malloc
         if (line == NULL)
         {
             fprintf(stderr, "something went wrong!");
             return 5;
         }
        int counter = 0;

        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            if (size > 1)
            {
                //multiply amount of pixels by f
                for (int k = 0; k < f; k++)
                {
                    line[counter] = triple;
                    counter++;
                }
            }
            //add only the fth pixel to the line if size < 1 (decreasing image)
            else
            {
                if (j % f == 0)
                {
                    line[counter] = triple;
                    counter++;
                }
            }
        }

        //add size amount of line to resize height
        if (size > 1)
        {
            for (int j = 0; j < f; j++)
            {
                 for (int k = 0; k < bi2.biWidth; k++)
                {
                    fwrite(&line[k], sizeof(RGBTRIPLE), 1, outptr);
                }
                // then add it back (to demonstrate how)
                for (int k = 0; k < new_padding; k++)
                {
                    fputc(0x00, outptr);
                }
            }
        }
        //only print the fth line if decreasing size
        else
        {
            if (i % f == 0)
            {
                //print the line (to keep it DRY this should really be a function)
                for (int k = 0; k < bi2.biWidth; k++)
                {
                    fwrite(&line[k], sizeof(RGBTRIPLE), 1, outptr);
                }
                // then add it back (to demonstrate how)
                for (int k = 0; k < new_padding; k++)
                {
                    fputc(0x00, outptr);
                }
            }
        }
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        //free mem
        free(line);

    }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}

