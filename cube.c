#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#define clrscr() printf("\e[1;1H\e[eJ")

int main() {
  char output_char = '.';  

  const int x_size = 150; 
  const int y_size = 50; 
  const int output_size = x_size * y_size; 

  char output_buffer[output_size]; 
  float z_buffer[output_size]; 
  
  // starting positions 
  const float x_starter = -4; 
  const float y_starter = -4; 
  const float z_starter = -4; 

  // dimensions of the cube
  const float x_dimensions = 8; 
  const float y_dimensions = 8; 
  const float z_dimensions = 8; 

  // rotation angles
  float a = 0; 
  float a_updater = 0.03; 

  float b = 0; 
  float b_updater = 0.07;

  // 3d-2d projection 
  float distance_z = 50.; 
  
  for (;;) {
    memset(&output_buffer, 0x20, output_size * sizeof(char)); 
    memset(&z_buffer, 0x00, output_size * sizeof(float)); 

    for (float x = x_starter; x <= x_dimensions; x++) {
      for (float y = y_starter; y <= y_dimensions; y++) {
        for (float z = z_starter; z <= z_dimensions; z++) {
          
          // rotate around the x axis 
          float r1_x = x; 
          float r1_y = (y * cos(a)) + (z * sin(a)); 
          float r1_z = (y * -sin(a)) + (z * cos(a)); 
          float ooz = 1/r1_z; 

          // rotate around the y axis 
          float r2_x = (r1_x * cos(b)) - (r1_z * sin(b)); 
          float r2_y = r1_y; 
          float r2_z = (r1_x * sin(b)) + (r1_z * cos(b)); 

          // distance the z 
          r2_z -= distance_z;

          // project the 3d point to a 2d terminal
          int x_projected = (int) (r2_x / (r2_z / distance_z)); 
          int y_projected = (int) (r2_y / (r2_z / distance_z)); 

          // calculate the position in the buffer
          int position = (y_projected * x_size) + x_projected; 
          position += x_size/2; 
          position += y_size/2 * x_size; 

          output_buffer[position] = '.';
        }
      }
    }

    for (int i = 0; i < output_size; i++) {
      int character = i % x_size ? output_buffer[i] : 10; 
      putchar(character); 
    }

    usleep(20000); 
    clrscr();

    a += a_updater;
    b += b_updater; 

  }

  putchar(10);
} 
