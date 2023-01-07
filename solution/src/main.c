#include "bmp_format.h"
#include "image.h"
#include "rotate.h"
#include "stdint.h"
#include <stdio.h>



int main(int argc, char** argv){ // arg_value - ["main.c","asdsa", "asdsad"]
    char* source = "/home/beregom/Загрузки/img1.bmp";
    char* src_out = "/home/beregom/Загрузки/img2.bmp";
    if ( argc == 3 ) {
        // main.c
        // input
        // output
        source = argv[1];
        src_out = argv[2];
    }
    FILE* in = fopen(source, "rb");
    struct image myimg;
    struct bmp_header header;
    from_bmp(in, &myimg, &header);
    struct image iout = rotate(myimg);
    uint32_t c = header.biWidth;
    header.biWidth = header.biHeight;
    header.biHeight = c;
    FILE* out = fopen(src_out, "wb");
    to_bmp(out, &iout, header);
    fclose(in);
    fclose(out);
    return 0;
}
