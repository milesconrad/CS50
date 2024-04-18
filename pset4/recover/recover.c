#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *card_file = fopen(argv[1], "r");
    if (card_file == NULL)
    {
        printf("Your file could not be read.\n");
        return 1;
    }

    // 3 of the 4 jpeg header bytes, so we can check for them with a for loop
    uint8_t jpeg_bytes[3] = {0xff, 0xd8, 0xff};
    uint8_t buffer[512];

    FILE *image = NULL;
    int read_size = 0;
    int files_num = 0;
    do
    {
        read_size = fread(buffer, 1, 512, card_file);

        // checking if the block starts with the JPG header
        bool is_jpeg = true;
        for (int i = 0; i < 3; i++)
        {
            if (buffer[i] != jpeg_bytes[i])
            {
                is_jpeg = false;
                break;
            }
        }
        if ((buffer[3] & 0xf0) != 0xe0)
        {
            is_jpeg = false;
        }


        if (is_jpeg)
        {
            // if the current block is the beginning of a JPG file, close the previous JPG
            if (image != NULL)
            {
                fclose(image);
                image = NULL;
            }

            char filename[7];
            sprintf(filename, "%03d.jpg", files_num);
            files_num++;
            image = fopen(filename, "wb");
        }

        if (image != NULL)
        {
            fwrite(buffer, 1, read_size, image);
        }
    }
    while (read_size == 512); // if read size is smaller than 512, then we are on the last block on the file

    fclose(card_file);
}