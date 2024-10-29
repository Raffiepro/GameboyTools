#include <stdio.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

typedef unsigned char u8;
typedef unsigned short u16;

u8 get_bit(u8 data, u8 bit)
{
    return (data >> bit) & 1;
}

void read_tile(FILE* f, size_t offset, u8* img)
{
    char data[16];
    
    fseek(f, offset, SEEK_SET);
    fread(data, 1, 16, f);

    for(int y=0;y<8;y++)
    {
        for(int x=0;x<8;x++)
        {
            u8 tile=0;
            tile = get_bit(data[y*2], 7-x);
            tile += get_bit(data[y*2+1], 7-x)<<1;

            u8 color = ((float)(3-tile)/3) * 255;

            img[(y*8+x)*3] = color;
            img[(y*8+x)*3+1] = color;
            img[(y*8+x)*3+2] = color;

            switch(tile)
            {
                case 0:
                    printf("%c[%dm00", 0x1B, 37);
                    break;
                case 1:
                    printf("%c[%dm11", 0x1B, 32);
                    break;
                case 2:
                    printf("%c[%dm22", 0x1B, 34);
                    break;
                case 3:
                    printf("%c[%dm33", 0x1B, 36);
                    break;
            }
        }
        printf("%c[%dm\n", 0x1B, 37);
    }
}

int main(int argc, char *argv[])
{
    char rom_path[226];

    if(argc > 1)
    {
        strcpy(rom_path, argv[1]);
    }
    else
    {
        printf("Enter rom path: ");
        scanf("%s", rom_path);
    }

    u8 hex_offset[5];
    if(argc > 2)
    {
        strcpy(hex_offset, argv[2]);
        hex_offset[4]=0;
    }
    else
    {
        printf("Enter offset: ");
        scanf("%s", hex_offset);
    }
    unsigned int offset = (unsigned int)strtol(hex_offset, NULL, 16);
    u8 last_hex_offset[5];
    strcpy(last_hex_offset, hex_offset);

    u8 img[8*8*3];

    FILE* f = fopen(rom_path, "r");

    while(1)
    {
        read_tile(f, offset, img);

        getchar();
        printf("Enter offset ('e' to export, 'ex' to exit): ");
        scanf("%s", hex_offset);

        if(strcmp(hex_offset, "e")==0)
        {
            stbi_write_bmp(strcat(last_hex_offset, ".bmp"), 8, 8, 3, img);
            printf("Exported!\n");
            continue;
        }

        if(strcmp(hex_offset, "ex")==0) break;

        offset = (unsigned int)strtol(hex_offset, NULL, 16);
        strcpy(last_hex_offset, hex_offset);
    }

    fclose(f);
    return 0;
}
