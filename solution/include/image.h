//
// Created by beregom on 04.01.23.
//

#ifndef LABA1_IMAGE_H
#define LABA1_IMAGE_H

#include <stdint.h>

struct pixel { uint8_t b, g, r; };

struct image {
    uint64_t width, height;
    struct pixel** data;
};

#endif //LABA1_IMAGE_H
