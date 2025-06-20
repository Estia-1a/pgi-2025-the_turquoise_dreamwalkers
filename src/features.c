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
void mirror_vertical(char*sourcepath) {
    unsigned char *data;
    int w,h,ch_count;
    int result = read_image_data(sourcepath, &data, &w, &h, &ch_count);
    if (result !=0){
        unsigned char*mirror_vertical_data=(unsigned char *) malloc(w * h * ch_count);
        if (!mirror_vertical_data) {
            fprintf(stderr,"Problème de réservation de mémoire\n");
            return;
        }
        for (int y=0;y < h;y++){
            for(int x=0 ;x<w;x++){
                for(int i=0;i<ch_count;i++){
                    mirror_vertical_data[((h-1-y)*w+x)*ch_count+i]=data[(y*w +x)*ch_count+i];
                }
            }
        }
        write_image_data("image_out.bmp",mirror_vertical_data,w,h);
        free_image_data(mirror_vertical_data);
        
    }
    free_image_data(data);
}
void mirror_horizontal(char*sourcepath) {
    unsigned char *data;
    int w,h,ch_count;
    int result = read_image_data(sourcepath, &data, &w, &h, &ch_count);
    if (result !=0){
        unsigned char*mirror_horizontal_data=(unsigned char *) malloc(w* h * ch_count);
        if (!mirror_horizontal_data) {
            fprintf(stderr,"Problème de réservation de mémoire\n");
            return;
        }
        for (int y=0;y < h;y++){
            for(int x=0 ;x<w;x++){
                for(int i=0;i<ch_count;i++){
                    mirror_horizontal_data[(y*w+(w-x-1))*ch_count+i]=data[(y*w +x)*ch_count+i];
                }
            }
        }
        write_image_data("image_out.bmp", mirror_horizontal_data,w,h);
        free_image_data(mirror_horizontal_data);
    }
    free_image_data(data);
}
void rotate_acw(char* source_path) {
    unsigned char *data;
    int width, height, channel_count;
    int result = read_image_data(source_path, &data, &width, &height, &channel_count);
    if (result != 0) {
        unsigned char *rotated_data = (unsigned char *)malloc(width * height * channel_count);
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                for (int c = 0; c < channel_count; c++) {
                    rotated_data[((width - x - 1) * height + y) * channel_count + c] = data[(y * width + x) * channel_count + c];
                }
            }
        }
        write_image_data("image_out.bmp", rotated_data, height, width); 
        free_image_data(rotated_data);
    }
    
    free_image_data(data);
}
void min_component(char* source_path, char component) {
    unsigned char *data = NULL;
    int width, height, channel_count;
    int min_value = 256;  
    int min_x = 0, min_y = 0;

    if (read_image_data(source_path, &data, &width, &height, &channel_count)) {
        int component_index;

        switch (component) {
            case 'R':
                component_index = 0;
                break;
            case 'G':
                component_index = 1;
                break;
            case 'B':
                component_index = 2;
                break;
            default:
                fprintf(stderr, "Invalid component: %c\n", component);
                free_image_data(data);
                return;
        }

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int index = (y * width + x) * channel_count + component_index;
                int value = data[index];

                if (value < min_value) {
                    min_value = value;
                    min_x = x;
                    min_y = y;
                }
            }
        }

        printf("min_component %c (%d, %d): %d\n", component, min_x, min_y, min_value);
        free_image_data(data);
    } else {
        fprintf(stderr, "Failed to read image data from %s\n", source_path);
    }
}
void max_component(char* source_path, char component) {
    unsigned char *data = NULL;
    int width, height, channel_count;
    int max_value = -1; 
    int max_x = 0, max_y = 0;

    if (read_image_data(source_path, &data, &width, &height, &channel_count)) {
        int component_index;

        switch (component) {
            case 'R':
                component_index = 0;
                break;
            case 'G':
                component_index = 1;
                break;
            case 'B':
                component_index = 2;
                break;
            default:
                fprintf(stderr, "Invalid component: %c\n", component);
                free_image_data(data);
                return;
        }

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int index = (y * width + x) * channel_count + component_index;
                int value = data[index];

                if (value > max_value) {
                    max_value = value;
                    max_x = x;
                    max_y = y;
                }
            }
        }

        printf("max_component %c (%d, %d): %d\n", component, max_x, max_y, max_value);
        free_image_data(data);
    } else {
        fprintf(stderr, "Failed to read image data from %s\n", source_path);
    }
}
void second_line(char* source_path) {
    unsigned char *data;
    int width, height, channel_count;
    int result = read_image_data(source_path, &data, &width, &height, &channel_count);
    if (result != 0) {
        int index = width * channel_count; 
        unsigned char R = data[index];
        unsigned char G = data[index + 1];
        unsigned char B = data[index + 2];
        printf("second_line: %d, %d, %d\n", R, G, B);
    }
    free_image_data(data);
}


void helloWorld() {
    printf("Hello World !");
}


void tenth_pixel (char *source_path){
    unsigned char *data=NULL;
    int width;
    int height;
    int channel_count;

    int Status = read_image_data( source_path ,&data,&width,&height,&channel_count);
    if(Status == 0){
        printf("Here is some error: %s\n",source_path);
        return;
    }

    if(width*height*channel_count <= (9 * channel_count + (channel_count - 1))){
        printf("Here is no tenth_pixel\n");
        free_image_data(data);
        return;
    }

    unsigned char R = data[9*channel_count];
    unsigned char G = data[9*channel_count+ 1];
    unsigned char B = data[9*channel_count+ 2];

    printf("tenth_pixel: %d,%d,%d\n",R,G,B);
    free_image_data(data);
    return;
    
}

void color_blue(char *source_path) {
    int width = 0;
    int height = 0;
    unsigned char *image_data = NULL;
    int channel_count = 0;

    if (read_image_data(source_path, &image_data, &width, &height, &channel_count) != 0) {
        unsigned char *output_data = malloc(width * height * channel_count);
        if (!output_data) {
            fprintf(stderr, "Memory allocation error\n");
            free_image_data(image_data);
            return;
        }

        for (int i = 0; i < width * height; i++) {
            output_data[i * channel_count + 0] = 0;
            output_data[i * channel_count + 1] = 0;
            output_data[i * channel_count + 2] = image_data[i * channel_count + 2]; 
            if (channel_count == 4) {
                output_data[i * channel_count + 3] = image_data[i * channel_count + 3];
            }
        }

        write_image_data("image_out.bmp", output_data, width, height);
        free_image_data(image_data);
        free(output_data);
    } else {
        printf("Read file Error!\n");
    }
}
void min_pixel (char *source_path){
    //printf("[DEBUG] >>> Entering min_pixel()\n");
    unsigned char *data=NULL;
    int width;
    int height;
    int channel_count;
    int min_sum=256*3,min_i=0,min_j=0;
    pixelRGB pixel1={0,0,0};

    int Status = read_image_data( source_path ,&data,&width,&height,&channel_count);
    if(Status == 0){
        printf("Here is some error: %s\n",source_path);
        return;
    }
    //printf("[DEBUG] Image load result: status=%d, data=%p, width=%d, height=%d, channels=%d\n",
    //Status, data, width, height, channel_count);

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            // printf("%d",i);
            pixelRGB* p=getPixel(data,width,height,channel_count,j,i);
            // printf("%d",p->B);
            int sum=p->R+p->G+p->B;
            if(sum<min_sum){
                min_sum=sum;
                min_i=i;
                min_j=j;
                pixel1=*p;
            }
        }

    }

    printf("min_pixel (%d,%d): %d, %d, %d",min_j,min_i,pixel1.R,pixel1.G,pixel1.B);
    free_image_data(data);
    return;
}

void color_red(char *source_path) {
    int width = 0;
    int height = 0;
    unsigned char *image_data = NULL;
    int channel_count = 0;

    if (read_image_data(source_path, &image_data, &width, &height, &channel_count) != 0) {
        unsigned char *output_data = malloc(width * height * channel_count);
        if (!output_data) {
            fprintf(stderr, "Memory allocation error\n");
            free_image_data(image_data);
            return;
        }

        for (int i = 0; i < width * height; i++) {
            output_data[i * channel_count + 0] = image_data[i * channel_count + 0]; // Red conservé
            output_data[i * channel_count + 1] = 0; 
            output_data[i * channel_count + 2] = 0; 
            if (channel_count == 4) { 
                output_data[i * channel_count + 3] = image_data[i * channel_count + 3];
            }
        }

        write_image_data("image_out.bmp", output_data, width, height);
        free_image_data(image_data);
        free(output_data);
    } else {
        printf("Read file Error!\n");
    }}

void color_invert(char *source_path){
    unsigned char *data=NULL;
    int width;
    int height;
    int channel_count;

//printf("[DEBUG] >>> Entering color_invert()\n");
    int Status = read_image_data( source_path ,&data,&width,&height,&channel_count);
    if(Status == 0){
        printf("Here is some error: %s\n",source_path);
        return;
    }

//printf("[DEBUG] >>33 Entering color_invert()\n");

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            pixelRGB* p=getPixel(data,width,height,channel_count,j,i);
            p->R=255-p->R;
            p->G=255-p->G;
            p->B=255-p->B;
            setPixel(data,width,height,channel_count,j,i,p);
        }
    }
    
//printf("[DEBUG] >>> Image data written successfully to image_out.bmp\n");
    
    if (write_image_data("image_out1.bmp", data, width, height) == 0) {
        printf("Error writing image data to file.\n");
    } else {
        printf("Image data written successfully to image_out.bmp\n");
    }

//printf("[DEBUG] >>> Image data written successfully to image_out.bmp\n");
    
    free_image_data(data);  
    return;
}

void color_gray(char *source_path) {
    int width = 0;
    int height = 0;
    unsigned char *image_data = NULL;
    int channel_count = 0;
    if (read_image_data(source_path, &image_data, &width, &height, &channel_count) != 0) {
        unsigned char *output_data = malloc(width * height * channel_count);
        if (!output_data) {
            fprintf(stderr, "Memory allocation error\n");
            free_image_data(image_data);
            return;
        }
        for (int i = 0; i < width * height; i++) {
            unsigned char r = image_data[i * channel_count + 0];
            unsigned char g = image_data[i * channel_count + 1];
            unsigned char b = image_data[i * channel_count + 2];
            unsigned char gray = (r + g + b) / 3;
            output_data[i * channel_count + 0] = gray;
            output_data[i * channel_count + 1] = gray;
            output_data[i * channel_count + 2] = gray;
            if (channel_count == 4) {
                output_data[i * channel_count + 3] = image_data[i * channel_count + 3]; // copie alpha si présent
            }
        }
        write_image_data("image_out.bmp", output_data, width, height);
        free_image_data(image_data);
        free(output_data);
    } else {
        printf("Read file Error!\n");
    }
}
void stat_report(char *source_path){
    int width = 0;
    int height = 0;
    int channel_count = 0;
    unsigned char *image_data = NULL;

    FILE *file = fopen("stat_report.txt", "w");
    if (!file) {
        printf("Error: Could not create stat_report.txt\n");
        return;
    }
    if (read_image_data(source_path, &image_data, &width, &height, &channel_count) == 0) {
        fprintf(file, "Error: Could not read image data\n");
        fclose(file);
        return;
    }
    int max_sum = -1, max_x = 0, max_y = 0, maxR = 0, maxG = 0, maxB = 0;
    int min_sum = 256*3, min_x = 0, min_y = 0, minR = 0, minG = 0, minB = 0;
    int maxR_val = -1, maxG_val = -1, maxB_val = -1;
    int minR_val = 256, minG_val = 256, minB_val = 256;
    int maxR_x = 0, maxR_y = 0, maxG_x = 0, maxG_y = 0, maxB_x = 0, maxB_y = 0;
    int minR_x = 0, minR_y = 0, minG_x = 0, minG_y = 0, minB_x = 0, minB_y = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int idx = (y * width + x) * channel_count;
            int r = image_data[idx];
            int g = image_data[idx + 1];
            int b = image_data[idx + 2];
            int sum = r + g + b;
            if (sum > max_sum) {
                max_sum = sum;
                max_x = x;
                max_y = y;
                maxR = r;
                maxG = g;
                maxB = b;
            }
            if (sum < min_sum) {
                min_sum = sum;
                min_x = x;
                min_y = y;
                minR = r;
                minG = g;
                minB = b;
            }
            if (r > maxR_val) { maxR_val = r; maxR_x = x; maxR_y = y; }
            if (g > maxG_val) { maxG_val = g; maxG_x = x; maxG_y = y; }
            if (b > maxB_val) { maxB_val = b; maxB_x = x; maxB_y = y; }
            if (r < minR_val) { minR_val = r; minR_x = x; minR_y = y; }
            if (g < minG_val) { minG_val = g; minG_x = x; minG_y = y; }
            if (b < minB_val) { minB_val = b; minB_x = x; minB_y = y; }
        }
    }
    fprintf(file, "max_pixel (%d,%d): %d, %d, %d\n\n", max_x, max_y, maxR, maxG, maxB);
    fprintf(file, "min_pixel (%d,%d): %d, %d, %d\n\n", min_x, min_y, minR, minG, minB);
    fprintf(file, "max_component R (%d,%d): %d\n\n", maxR_x, maxR_y, maxR_val);
    fprintf(file, "max_component G (%d,%d): %d\n\n", maxG_x, maxG_y, maxG_val);
    fprintf(file, "max_component B (%d,%d): %d\n\n", maxB_x, maxB_y, maxB_val);
    fprintf(file, "min_component R (%d,%d): %d\n\n", minR_x, minR_y, minR_val);
    fprintf(file, "min_component G (%d,%d): %d\n\n", minG_x, minG_y, minG_val);
    fprintf(file, "min_component B (%d,%d): %d\n\n", minB_x, minB_y, minB_val);

    fclose(file);
    free_image_data(image_data);
}
void mirror_total(char *source_path){
    int width = 0, height = 0, channel_count = 0;
    unsigned char *image_data = NULL;
    if (read_image_data(source_path, &image_data, &width, &height, &channel_count) != 0) {
        unsigned char *output_data = malloc(width * height * channel_count);
        if (!output_data) {
            fprintf(stderr, "Memory allocation error\n");
            free_image_data(image_data);
            return;
        }
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++){
                int src_index = (y * width + x) * channel_count;
                int dst_index = ((height - 1 - y) * width + (width - 1 - x)) * channel_count;
                for (int c = 0; c < channel_count; c++) {
                    output_data[dst_index + c] = image_data[src_index + c];
                }
            }
        }
        write_image_data("image_out.bmp", output_data, width, height);
        free_image_data(image_data);
        free(output_data);
    } else {
        printf("Read file Error!\n");
    }
}
void color_gray_luminance(char *source_path){
    int width = 0;
    int height = 0;
    unsigned char *image_data = NULL;
    int channel_count = 0;

    if (read_image_data(source_path, &image_data, &width, &height, &channel_count) != 0) {
        unsigned char *output_data = malloc(width * height * channel_count);
        if (!output_data) {
            fprintf(stderr, "Memory allocation error\n");
            free_image_data(image_data);
            return;
        }

        for (int i = 0; i < width * height; i++) {
            unsigned char r = image_data[i * channel_count + 0];
            unsigned char g = image_data[i * channel_count + 1];
            unsigned char b = image_data[i * channel_count + 2];
            unsigned char gray = (unsigned char)(0.299f * r + 0.587f * g + 0.114f * b);
            output_data[i * channel_count + 0] = gray;
            output_data[i * channel_count + 1] = gray;
            output_data[i * channel_count + 2] = gray;
            if (channel_count == 4) {
                output_data[i * channel_count + 3] = image_data[i * channel_count + 3]; // copie alpha si présent
            }
        }

        write_image_data("image_out.bmp", output_data, width, height);
        free_image_data(image_data);
        free(output_data);
    } else {
        printf("Read file Error!\n");
    }
}
void print_pixel(char *filename, int x, int y) {
    unsigned char *data = NULL;
    int width, height, channel_count;
    if (read_image_data(filename, &data, &width, &height, &channel_count) != 0) {
        pixelRGB *p = get_pixel(data, width, height, channel_count, x, y);
        if (p) {
            printf("print_pixel (%d, %d): %d, %d, %d\n", x, y, p->R, p->G, p->B);
        } else {
            printf("Invalid pixel coordinates\n");
        }
        free_image_data(data);
    } else {
        printf("Read file Error!\n");
    }
}

void rotate_cw(char *source_path){
    unsigned char *data=NULL;
    int width;
    int height;
    int channel_count;

    int Status = read_image_data(source_path,&data,&width,&height,&channel_count);
    if(Status == 0){    
        printf("Here is some error: %s\n","image.bmp");
        return;
    }

    int new_width  = height;
    int new_height = width;
    unsigned char *rotated = malloc(new_width * new_height * channel_count);
    if (!rotated) {
        fprintf(stderr, "failed!\n");
        free_image_data(data);
        return;
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int src_idx = (y * width + x) * channel_count;
            int dst_x   = y;
            int dst_y   = (new_height - 1) - x;
            int dst_idx = (dst_y * new_width + dst_x) * channel_count;
            for (int c = 0; c < channel_count; c++) {
                rotated[dst_idx + c] = data[src_idx + c];
            }
        }
    }


    if (write_image_data("image_out.bmp",rotated, new_height, new_height) == 0) {
        printf("Error writing image data to file.\n");
    } else {
        printf("Image data written successfully to image_out.bmp\n");
    }

    free_image_data(data);
    return;

}
void color_green(char *source_path){
    int width = 0;
    int height = 0;

    unsigned char *image_data = NULL;
    int channel_count = 0;
    if (read_image_data(source_path, &image_data, &width, &height, &channel_count) != 0) {
        unsigned char *output_data = malloc(width * height * channel_count);
        if (!output_data) {
            fprintf(stderr, "Memory allocation error\n");
            free_image_data(image_data);
            return;
        }
        for (int i = 0; i < width * height; i++) {
            output_data[i * channel_count + 0] = 0; 
            output_data[i * channel_count + 1] = image_data[i * channel_count + 1]; 
            output_data[i * channel_count + 2] = 0; 
            if (channel_count == 4) { 
                output_data[i * channel_count + 3] = image_data[i * channel_count + 3];
            }
        }
        write_image_data("image_out.bmp", output_data, width, height);
        free_image_data(image_data);
        free(output_data);
    } else {
        printf("Read file Error!\n");
    }
}
