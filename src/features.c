#include <estia-image.h>
#include <stdio.h>

#include "features.h"
#include "utils.h"
#include <stdlib.h>
#include <math.h>
/**
 * @brief Here, you have to code features of the project.
 * Do not forget to commit regurlarly your changes.
 * Your commit messages must contain "#n" with: n = number of the corresponding feature issue.
 * When the feature is totally implemented, your commit message must contain "close #n".
 */

void scale_bilinear(char *source_path,float scale){
    int width = 0;
    int height = 0;
    unsigned char *image_data = NULL;
    int channel_count = 0;  
    if(read_image_data(source_path,&image_data,&width,&height,&channel_count) != 0){
        int out_width = (int)(width * scale);
        int out_height = (int)(height * scale);
        unsigned char *output_data = malloc(out_width * out_height * channel_count);
        for(int y = 0; y < out_height; y++){
            for(int x = 0 ; x< out_width; x++){
                float x_src = x / scale;
                float y_src = y / scale;

                int x0 = (int)floor(x_src);
                int x1 = x0 + 1;
                int y0 = (int)floor(y_src);
                int y1 = y0 + 1;

                if (x1 >= width){
                    x1 = width - 1;
                }
                if (y1 >= height){
                    y1 = height - 1;
                }
                if (x0 < 0){
                    x0 = 0;
                }
                if (y0 < 0){
                    y0 = 0;
                }
                float dx = x_src - x0;
                float dy = y_src - y0;

                int out_index = (y * out_width + x) * channel_count;
                for(int c = 0;c< channel_count; c++){
                    unsigned char pixle00 = image_data[(y0 * width + x0) * channel_count +c];
                    unsigned char pixel10 = image_data[(y0 * width + x1) * channel_count + c];
                    unsigned char pixel01 = image_data[(y1 * width + x0) * channel_count + c];
                    unsigned char pixel11 = image_data[(y1 * width + x1) * channel_count + c];
                
                    float out =(1 - dx) * (1 - dy) * pixle00 +
                            dx * (1 - dy) * pixel10 +
                            (1 - dx) * dy * pixel01 +
                            dx * dy * pixel11;
                    
                    output_data[out_index + c] = (unsigned char)(out + 0.5f);               
                }
            }
        }
        write_image_data("image_out.bmp",output_data,out_width,out_height);
        free_image_data(image_data);
        free(output_data);
    }
    else{
        printf("Read file Error!\n");
    }
}

void scale_nearest(char *source_path,float scale){
    int width = 0;
    int height = 0;
    unsigned char *image_data = NULL;
    int channel_count = 0;

    if(read_image_data(source_path,&image_data,&width,&height,&channel_count) != 0){
        int out_width = (int)width * scale;
        int out_height = (int)height * scale;
        unsigned char *output_data = malloc(out_width * out_height * channel_count);
        for(int y = 0; y < out_height; y++){
            for(int x = 0; x < out_width ;x++){
                int x_src = (x / scale);
                int y_src = (y / scale);
                if(x_src >= width){
                    x_src = width -1 ;
                }
                if(y_src >= height){
                    y_src = height -1;
                }
                int src_index = (y_src * width + x_src) * channel_count;
                int out_index = (y * out_width + x) * channel_count;
                for(int c = 0;c<channel_count;c++){
                    output_data[out_index+c] = image_data[src_index +c];
                }
            }
        }
        write_image_data("image_out.bmp",output_data,out_width,out_height);
        free_image_data(image_data);
        free(output_data);
    }   
    else{
        printf("Read file Error!\n");
    }
}

void scale_crop(char *source_path,int center_x,int center_y,int out_width,int out_height){
    int width = 0;
    int height = 0;
    unsigned char *image_data = NULL;
    int channel_count = 0;
    if(read_image_data(source_path,&image_data,&width,&height,&channel_count) != 0){
        int start_x = center_x - out_width/2;
        int end_x = center_x + out_width/2;
        if(start_x < 0 ){
            start_x = 0;
        }
        if(end_x > width){
            end_x = width;
        }
        int start_y = center_y - out_height/2;
        if(start_y < 0){
            start_y = 0;
        }
        int end_y = center_y + out_height/2;
        if(end_y > height){
            end_y = height;
        }
        int y_pixels = end_y - start_y;
        int x_pixels = end_x - start_x;
        unsigned char *output_data = malloc(y_pixels * x_pixels * channel_count);
        int count = 0;
        for(int y = start_y ; y<end_y; y++){
            for(int x = start_x ; x<end_x ; x++){
                int index = (y*width + x) * channel_count;
                for(int c = 0;c<channel_count;c++){
                    output_data[count +c] = image_data[index];
                }
                count += channel_count;
            }
        }
        write_image_data("image_out.bmp",output_data,x_pixels,y_pixels);
        free_image_data(image_data);
        free(output_data);
    }
    else{
        printf("Read file Error!\n");
    }


    
}

void max_pixel(char *source_path){
    int width = 0;
    int height = 0;
    unsigned char *image_data = NULL;
    int channel_count = 0;
    printf("entering max_pixel");
    if(read_image_data(source_path,&image_data,&width,&height,&channel_count) != 0){
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
    int width = 0;
    int height = 0;
    unsigned char *image_data = NULL;
    int channel_count = 0;
    if(read_image_data(source_path,&image_data,&width,&height,&channel_count) != 0){
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
    if(read_image_data(filename,&image_data,&width,&height,&channel_count) != 0){
        printf("dimension: %d %d\n",width,height);
    }
    else{
        printf("Read file Error!\n");
    }
}
void helloWorld() {
    printf("Hello World !");
}
