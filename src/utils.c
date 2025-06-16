#include <estia-image.h>

#include "utils.h"
#include <stdio.h>
/**
 * @brief Here, you have to define functions of the pixel struct : getPixel and setPixel.
 * 
 */

pixelRGB* getPixel(unsigned char* data, const unsigned int width, const unsigned int height, const unsigned int n, const unsigned int x, const unsigned int y) {
    if (x >= width || y >= height || n < 0) {
        return NULL; // Out of bounds
    }
    
    unsigned int index = (y * width + x) * n;
    static pixelRGB* pixel ;
    
    pixel->R = data[index];
    pixel->G = data[index + 1];
    pixel->B = data[index + 2];

    return pixel;
}

void setPixel(unsigned char* data, const unsigned int width, const unsigned int height, const unsigned int n, const unsigned int x, const unsigned int y, pixelRGB* pixel) {
    if (x >= width || y >= height || n < 0) {
        return NULL; // Out of bounds
    }
    
    unsigned int index = (y * width + x) * n;
    
    data[index] = pixel->R;
    data[index + 1] = pixel->G;
    data[index + 2] = pixel->B;
}
