#ifndef FEATURES_H
#define FEATURES_H


void helloWorld();
void dimension(const char *filename);
void first_pixel(char *source_path);
void max_pixel(char *source_path);
void scale_crop(char *source_path,int center_x,int center_y,int width,int height);
void scale_nearest(char *source_path,float scale);
void scale_bilinear(char *source_path,float scale);
void mirror_vertical(char*sourcepath);
void mirror_horizontal(char*sourcepath);
void rotate_acw(char *source_path);
void min_component(char *source_path, char component);
void max_component(char *source_path, char component);
void second_line(char *source_path);

//void yifei

void tenth_pixel (char *source_path);


void color_blue(char *source_path);
void color_red(char* source_path);
void min_pixel (char *source_path);
void color_invert (char *source_path);
void color_green(char *source_path);
void color_gray(char *source_path);


#endif
