#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#define clrscr() printf("\e[1;1H\e[eJ")

int main() {
  char output_char = '.';  

  const int x_size = 200; 
  const int y_size = 100; 
  const int output_size = x_size * y_size; 

  char output_buffer[output_size]; 
  float z_buffer[output_size]; 
  
  // dimensions of the cube
  const float x_dimensions = 10; 
  const float y_dimensions = 10; 
  const float z_dimensions = 10; 

  // starting positions 
  const float x_starter = -x_dimensions/2; 
  const float y_starter = -y_dimensions/2; 
  const float z_starter = -z_dimensions/2; 


  // rotation angles
  float a = 0; 
  float a_updater = 0.05; 

  float b = 0; 
  float b_updater = 0.02;

  // 3d-2d projection 
  float distance_z = 70.; 
  
  for (;;) {
    memset(&output_buffer, 0x20, output_size * sizeof(char)); 
    memset(&z_buffer, 0x0, output_size * sizeof(float)); 

    for (float x = 0; x <= x_dimensions; x++) {
      for (float y = 0; y <= y_dimensions; y++) {
        for (float z = 0; z <= z_dimensions; z++) {

          float x_location = x_starter + x; 
          float y_location = y_starter + y; 
          float z_location = z_starter + z; 
          
          // rotate around the x axis 
          float r1_x = x_location;
          float r1_y = (y_location * cos(a)) + (z_location * sin(a)); 
          float r1_z = (y_location * -sin(a)) + (z_location * cos(a)); 

          // rotate around the y axis 
          float r2_x = (r1_x * cos(b)) - (r1_z * sin(b)); 
          float r2_y = r1_y; 
          float r2_z = (r1_x * sin(b)) + (r1_z * cos(b)); 

          // distance the z 
          // r2_z -= distance_z;
          r2_z += 20;
          float ooz = 1/r2_z; 
          ooz += 20;

          // project the 3d point to a 2d terminal
          int x_projected = (int) (r2_x / (r2_z / distance_z)); 
          int y_projected = (int) (r2_y / (r2_z / distance_z)); 

          // calculate the position in the buffer
          int position = (y_projected * x_size) + x_projected; 
          position += x_size/2; 
          position += y_size/2 * x_size; 

          float nx = -1 + (2/(x_dimensions)) * x; 
          float ny = -1 + (2/(y_dimensions)) * y; 
          float nz = -1 + (2/(z_dimensions)) * z; 

          // printf("X unit -> %f, Y unit -> %f, Z unit -> %f\n", nx, ny, nz);

          float nx_1 = nx; 
          float ny_1 = (ny * cos(a)) + (nz * sin(a));
          float nz_1 = (ny * -sin(a)) + (nz * cos(a));

          float nx_2 = (nx_1 * cos(b)) - (nz_1 * sin(b));
          float ny_2 = ny_1; 
          float nz_2 = (nx_1 * sin(b)) + (nz_1 * cos(b));

          float L = ny_2 * -1 - nz_2;

          if (L < 0) 
            L = 0;

          if (ooz > z_buffer[position]) {
            int luminance_index = L * 6; 
            if (luminance_index > 11)
              luminance_index = 11;
            output_buffer[position] = ".,-~:;=!*#$@"[luminance_index];
            z_buffer[position] = ooz; 
          }
        }
      }
    }

    for (int i = 0; i < output_size; i++) {
      int character = i % x_size ? output_buffer[i] : 10; 
      putchar(character); 
    }

    usleep(20000); 
    // getchar();
    clrscr();

    a += a_updater;
    b += b_updater; 

  }

  putchar(10);
} 
