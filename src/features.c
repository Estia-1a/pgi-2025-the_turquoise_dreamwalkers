#include <estia-image.h>
#include <stdio.h>

#include "features.h"
#include "utils.h"

/**
 * @brief Here, you have to code features of the project.
 * Do not forget to commit regurlarly your changes.
 * Your commit messages must contain "#n" with: n = number of the corresponding feature issue.
 * When the feature is totally implemented, your commit message must contain "close #n".
 */

void max_pixel(char *source_path){
    int a = 0;
    int width = 0;
    int height = 0;
    unsigned char *image_data = NULL;
    int channel_count = 0;
    printf("entering max_pixel");
    if(a != read_image_data(source_path,&image_data,&width,&height,&channel_count)){
        int rgbSum = 0;
        int maxSum = -1;
        int currentWidth = 0;
        int currentHeight = 0;
        int RGB[] = {0,0,0};
        long long total_bytes = (long long)width * height * channel_count;

        for(int i = 0 ; i < total_bytes; i+=channel_count){
            rgbSum = image_data[i] + image_data[i+1] + image_data[i+2];
            if(maxSum < rgbSum){
                maxSum = rgbSum;
                int pixel_index = i / channel_count;
                currentHeight = pixel_index / width;
                currentWidth = pixel_index % width;
                RGB[0] = image_data[i];
                RGB[1] = image_data[i+1];
                RGB[2] = image_data[i+2];
            }
        }
        printf("max_pixel (%d,%d): %d, %d, %d\n",currentWidth,currentHeight,RGB[0],RGB[1],RGB[2]);
    }
    else{
        printf("Read file Error!\n");
    }
}

void first_pixel(char *source_path){
    int a = 0;
    int width = 0;
    int height = 0;
    unsigned char *image_data = NULL;
    int channel_count = 0;
    if(a != read_image_data(source_path,&image_data,&width,&height,&channel_count)){
        printf("first_pixel: %d, %d, %d\n",image_data[0],image_data[1],image_data[2]);
    }
    else{
        printf("Read file Error!\n");
    }
}
void dimension(const char *filename){
    // unsigned char **data;int *width;int *height;int *channel_count;
    int width = 0;
    int height = 0;
    unsigned char *image_data = NULL;
    int channel_count = 0;
    int a = 0;
    if(a != read_image_data(filename,&image_data,&width,&height,&channel_count)){
        printf("dimension: %d %d\n",width,height);
    }
    else{
        printf("Read file Error!\n");
    }
}
void helloWorld() {
    printf("Hello World !");
}
