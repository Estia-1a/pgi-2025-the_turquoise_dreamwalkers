#include <estia-image.h>

#include "utils.h"
#include <stdio.h>
/**
 * @brief Here, you have to define functions of the pixel struct : getPixel and setPixel.
 * 
 */

pixelRGB* getPixel(unsigned char* data, const unsigned int width, const unsigned int height, const unsigned int n, const unsigned int x, const unsigned int y) {
    
    
    unsigned int index = (y * width + x) * n;
    static pixelRGB pixel ;
    
    pixel.R = data[index];
    pixel.G = data[index + 1];
    pixel.B = data[index + 2];
    // printf("%d,%d,%d",pixel.B,pixel.G,pixel.B);
    // free_image_data(data);
    return &pixel;
}

void setPixel(unsigned char* data, const unsigned int width, const unsigned int height, const unsigned int n, const unsigned int x, const unsigned int y, pixelRGB* pixel) {

    unsigned int index = (y * width + x) * n;
    
    data[index] = pixel->R;
    data[index + 1] = pixel->G;
    data[index + 2] = pixel->B;
}
pixelRGB *get_pixel(unsigned char* data, const unsigned int width, const unsigned int height, const unsigned int n, const unsigned int x, const unsigned int y) {
    if (data == NULL) return NULL;
    if (x >= width || y >= height) return NULL;
    int index = (y * width + x) * n;
    return (pixelRGB *) &data[index];
}
