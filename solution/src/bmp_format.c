//
// Created by beregom on 04.01.23.
//

#include "bmp_format.h"
#include <malloc.h>

enum read_status from_bmp( FILE* in, struct image* img, struct bmp_header* header){
    fread(header,sizeof(struct bmp_header), 1, in);
    if (header->bfType != 'M'*256+'B') {
        return READ_INVALID_SIGNATURE;
    }
    printf("\n\n\tINFO: %d %d %d\n\n", header->biWidth, header->biHeight, header->biBitCount);
    img->height = header->biHeight;
    img->width = header->biWidth;
    img->data = malloc(sizeof(struct pixel*)*img->height);
    for(int i=0;i<img->height; ++i)
        img->data[i] = malloc(sizeof(struct pixel) * img->width);
    fseek(in, header->bOffBits, 0); // sizeof(struct bmp_header) +
    for (int i = 0; i < header->biHeight; ++i) {
        for (int j = 0; j < header->biWidth; ++j) {
            fread(&img->data[i][j], sizeof(struct pixel), 1, in);
        }
        if( header->biWidth % 4 != 0){
            uint8_t trash;
            int repeat = (int)header->biWidth*3 - ((int)header->biWidth*3)%4 + 4 - (int)header->biWidth*3;
            for(int k=0; k < repeat; ++k)
                fread(&trash, 1, 1, in);
        }
    }
    return READ_OK;
}

enum write_status to_bmp( FILE* out, struct image const* img, struct bmp_header header){
    fwrite(&header, sizeof(struct bmp_header), 1, out);
    for (int i = 0; i < header.biHeight; ++i) {
        for (int j = 0; j < header.biWidth; ++j) {
            fwrite(&img->data[i][j], sizeof(struct pixel), 1, out);
        }
        if( header.biWidth*3 % 4 != 0){
            uint8_t trash = 255;
            int repeat = (int)header.biWidth*3 - ((int)header.biWidth*3)%4 + 4 - (int)header.biWidth*3;
            for(int k=0; k < repeat; ++k)
                fwrite(&trash, 1, 1, out);
        }
    }
    return WRITE_OK;
}

