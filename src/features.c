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

void helloWorld() {
    printf("Hello World !");
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
