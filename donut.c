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

  float a = 0; // x axis rotation angle 
  float a_updater = 0.03; // updater for the a angle  

  for (;;) { 
    memset(&output_buffer, 0x20, output_size * sizeof(char));

    for (float theta = 0; theta < 6.28; theta += 0.01) {
      for (float phi = 0; phi < 6.28; phi += 0.07) {

        // calculate circle coordinates 
        int x = r2 + (r1 * cos(theta)); 
        int y = r2 + (r1 * sin(theta));
        int z = 0; 

        // rotate around the y axis (calculate the donut coordinates)
        int r1_x = x * cos(phi); 
        int r1_y = y; 
        int r1_z = x * -sin(phi);

        // rotate around the x axis (rotate the donut) 
        int r2_x = r1_x; 
        int r2_y = (r1_y * cos(a) + (r1_z * sin(a)));
        int r2_z = (r1_y * -sin(a) + (r1_z * cos(a)));

        // calculate position, center it and output to the array
        int position = (r2_y * x_size) + r2_x; 
        position += x_size/2; 
        position += y_size/2 * x_size;

        output_buffer[position] = output_char;
      }
    }


    // output to terminal
    for (int i = 0; i < output_size; i++) {
      int character = i % 150 ? output_buffer[i] : 10; 
      putchar(character);
    }

    // update the rotation angle 
    a += a_updater; 

    usleep (5000); 
    clrscr();
  }

  putchar(10);
}
