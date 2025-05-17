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
void first_pixel(char *source_path){
    int a = 0;
    int width = 0;
    int height = 0;
    unsigned char *image_data = NULL;
    int channel_count = 0;
    if(a != read_image_data(source_path,&image_data,&width,&height,&channel_count)){
        printf("first_pixel: %d, %d, %d",image_data[0],image_data[1],image_data[2]);
    }
    else{
        printf("Read file Error!");
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
        printf("dimension: %d %d",width,height);
    }
    else{
        printf("Read file Error!");
    }
}
void helloWorld() {
    printf("Hello World !");
}
