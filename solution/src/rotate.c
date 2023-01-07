//
// Created by beregom on 04.01.23.
//

#include "rotate.h"
#include <malloc.h>

struct image rotate( struct image const source ){
    struct image rotate_img;
    rotate_img.width = source.height;
    rotate_img.height = source.width;
    rotate_img.data = malloc(sizeof(struct pixel*)*rotate_img.height);
    for (int i = 0; i < rotate_img.height; ++i)
        rotate_img.data[i] = malloc(sizeof(struct pixel) * rotate_img.width);
    for(int i = 0; i < rotate_img.height; ++i){
        for(int j = 0; j < rotate_img.width; ++j){
            rotate_img.data[i][j] = source.data[rotate_img.width-1-j][i];
        }
    }
    return rotate_img;
}

