#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <estia-image.h>
#include <getopt.h>

#include "features.h"
#include "utils.h"
#include "argsparse.h"
#include "features.h"
int main(int argc, char **argv) {
  /*To use debug mode: 
   - add --debug: freud.exe --debug -f images/input/image.jpeg
   or 
   - Simply run your compiled project with start button on the blue menu bar at the bottom of the VS Code window.
   */

  /*DO NOT EDIT THIS PART*/
  Config configuration ;
  parse_arguments( argc, argv, &configuration ) ;
  check_debug_mode(configuration);
  check_file();
  /* END */

  /* Use "if ( strncmp( command, <commandname>, 9 ) == 0 )" to check if your <commandname> is called by program.*/
  /* Example with helloworld command
   * If helloworld is a called command: freud.exe -f images/input/image.jpeg -c helloworld 
   */
  if ( strncmp( configuration.command, "helloworld", 10 ) == 0 ) {
    /* helloworld() function is defined in feature.h and implemented in feature.c */
    helloWorld();
  }

  if( strncmp(configuration.command, "dimension", 9 ) == 0 ){
    dimension(configuration.filenames[0]);
  }

  if ( strncmp( configuration.command, "first_pixel", 11 ) == 0 ) {
      first_pixel(configuration.filenames[0]);
  }
  if ( strncmp( configuration.command, "max_pixel", 9 ) == 0 ) {
      max_pixel(configuration.filenames[0]);
  }
  if ( strncmp( configuration.command, "scale_crop", 10 ) == 0 ) {
      scale_crop(configuration.filenames[0],
        atoi(configuration.arguments[0]),
        atoi(configuration.arguments[1]),
        atoi(configuration.arguments[2]),
        atoi(configuration.arguments[3]));
  }
  if ( strncmp( configuration.command, "scale_nearest", 13 ) == 0 ) {
      scale_nearest(configuration.filenames[0],
        atof(configuration.arguments[0]));
  } 
  if ( strncmp( configuration.command, "scale_bilinear", 14 ) == 0 ) {
      scale_nearest(configuration.filenames[0],
        atof(configuration.arguments[0]));
  }   
  if (strncmp(configuration.command,"mirror_vertical", 15)==0){
    mirror_vertical(configuration.filenames[0]);
  }
  if (strncmp(configuration.command,"mirror_horizontal", 17)==0){
        mirror_horizontal(configuration.filenames[0]);
  }
  if (strncmp(configuration.command, "rotate_acw", 10) == 0) {
        rotate_acw(configuration.filenames[0]);
  }
    if (strncmp(configuration.command, "min_component", 13) == 0) {
        if (configuration.arguments[0] != NULL) {
            char component = configuration.arguments[0][0];
            min_component(configuration.filenames[0], component);
        }
    }
  if (strncmp(configuration.command, "max_component", 13) == 0) {
        if (configuration.arguments[0] != NULL) {
            char component = configuration.arguments[0][0];
            max_component(configuration.filenames[0], component);
        } 
    }
  if (strncmp(configuration.command, "second_line", 11) == 0) {
    second_line(configuration.filenames[0]);
  }
  
  if(strncmp(configuration.command,"tenth_pixel",11)==0){
      tenth_pixel(configuration.filenames[0]);
  }
 if (strncmp(configuration.command, "color_blue", 10) == 0) {
    color_blue(configuration.filenames[0]);
 }
  if(strncmp(configuration.command,"min_pixel",9)==0){
      min_pixel(configuration.filenames[0]);
  }

  if(strncmp(configuration.command,"color_invert",12)==0){
      color_invert(configuration.filenames[0]);
  }
  if (strncmp(configuration.command, "color_red",9) == 0) {
    color_red(configuration.filenames[0]);
 }
 if (strncmp(configuration.command, "color_gray", 10) == 0) {
    color_gray(configuration.filenames[0]);
}
if (strncmp(configuration.command, "stat_report", 11) == 0) {
    stat_report(configuration.filenames[0]);
}
if (strncmp(configuration.command, "mirror_total", 12) == 0) {
    mirror_total(configuration.filenames[0]);
}
if (strncmp(configuration.command, "print_pixel", 11) == 0) {
    if (configuration.arguments[0] && configuration.arguments[1]) {
        int x = atoi(configuration.arguments[0]);
        int y = atoi(configuration.arguments[1]);
        print_pixel(configuration.filenames[0], x, y);
    }
}



if ((strncmp(configuration.command, "color_gray_luminance",20) == 0)) {
    color_gray_luminance(configuration.filenames[0]);
}
{
  /* code */
}

  /*
   * TO COMPLETE
   */
  
  return 0;
}
