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

  for (;;) {
    memset(&output_buffer, 0x20, output_size * sizeof(char)); 
    memset(&z_buffer, 0x00, output_size * sizeof(float)); 

    for (float x = x_starter; x <= x_dimensions; x++) {
      for (float y = y_starter; y <= y_dimensions; y++) {
        for (float z = z_starter; z <= z_dimensions; z++) {
          
          // rotate around the x axis 
          int r1_x = x; 
          int r1_y = (y * cos(a)) + (z * sin(a)); 
          int r1_z = (y * -sin(a)) + (z * cos(a)); 
          int ooz = 1/r1_z; 

          int position = (r1_y * x_size) + r1_x; 
          position += x_size/2; 
          position += y_size/2 * x_size; 

          // float L = cosphi*costheta*sinB - cosA*costheta*sinphi - sinA*sintheta + cosB*(cosA*sintheta - costheta*sinA*sinphi);

          // if (L > 0) {
          //   if (ooz > z_buffer[position]) {
          //     z_buffer[position] = ooz; 
          //     int luminance_index = L*8; 
          //     output_buffer[position] = ".,-~:;=!*#$@"[luminance_index]; 
          //   }
          // }
        }
      }
    }

    for (int i = 0; i < output_size; i++) {
      int character = i % x_size ? output_buffer[i] : 10; 
      putchar(character); 
    }

    usleep(10000); 
    clrscr();

    a += a_updater;

  }

  putchar(10);
} 
