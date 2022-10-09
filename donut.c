#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#define clrscr() printf("\e[1;1H\e[2J")

int main() {
  char output_char = '.';

  // dimensions of the output
  int x_size = 150; 
  int y_size = 50; 
  const int output_size = x_size * y_size; 

  // circle positioning: r1 = radius, r2 = x location of the circle 
  float r1 = 5;
  float r2 = 10;  

  // output buffers
  char output_buffer[output_size];
  float z_buffer[output_size];

  float a = 0; // x axis rotation angle 
  float a_updater = 0.03; // updater for the a angle  

  for (;;) { 
    memset(&output_buffer, 0x20, output_size * sizeof(char));
    memset(&z_buffer, 0x00, output_size * sizeof(float)); 

    for (float theta = 0; theta < 6.28; theta += 0.01) {
      for (float phi = 0; phi < 6.28; phi += 0.02) {

        // calculate circle coordinates 
        float x = r2 + (r1 * cos(theta)); 
        float y = r2 + (r1 * sin(theta));
        float z = 0; 

        // rotate around the y axis (calculate the donut coordinates)
        float r1_x = x * cos(phi); 
        float r1_y = y; 
        float r1_z = x * -sin(phi);

        // rotate around the x axis (rotate the donut) 
        float r2_x = r1_x; 
        float r2_y = (r1_y * cos(a) + (r1_z * sin(a)));
        float r2_z = (r1_y * -sin(a) + (r1_z * cos(a)));

        // project the 3D coordinates to 2D coordinates        
        // int x_projected = 
        float distance_z = 100; 
        r2_z = r2_z - distance_z; 

        int x_projected = (int) (r2_x / (r2_z / distance_z));
        int y_projected = (int) (r2_y / (r2_z / distance_z));

        // calculate position, center it and output to the array
        int position = (y_projected * x_size) + x_projected; 
        position += x_size/2; 
        position += y_size/2 * x_size;

        if (r2_z < z_buffer[position]) {
          output_buffer[position] = output_char;
          z_buffer[position] = r2_z;
        }
      }
    }


    // output to terminal
    for (int i = 0; i < output_size; i++) {
      int character = i % 150 ? output_buffer[i] : 10; 
      putchar(character);
    }

    // update the rotation angle 
    a += a_updater; 

    usleep (1000); 
    clrscr();
  }

  putchar(10);
}
