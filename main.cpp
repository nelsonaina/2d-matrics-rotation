#include <iostream>
#include "Display.h"
using namespace std;

const int N = 180;
const int HALF = N / 2;
const short COLOR_GREY = 200;
const short COLOR_GREY_LIGHT = 150;

void clearImage(short pixels[][N]) {
  for (int row = 0; row < N; row++)
    for (int col = 0; col < N; col++)
      pixels[row][col] = 0;
}

void fillRectangle(short pixels[][N], int row0, int col0, int size,
                   int x1, int y1, int x2, int y2) {
  // (x-x1)(x-x2) <= 0  and  (y-y1)(y-y2) <= 0
  for (int row = row0; row < row0 + size; row++)
    for (int col = col0; col < col0 + size; col++) {
      int x = col - col0, y = row - row0;
      if ((x - x1) * (x - x2) <= 0 && (y - y1) * (y - y2) <= 0)
        pixels[row][col] = COLOR_GREY;
    }
}

void fillCircle(short pixels[][N], int row0, int col0, int size,
                int xc, int yc, int R) {
  // (x-xc)^2 + (y-yc)^2 <= R^2
  for (int row = row0; row < row0 + size; row++)
    for (int col = col0; col < col0 + size; col++) {
      int x = col - col0, y = row - row0;
      int dx = x - xc, dy = y - yc;
      if (dx * dx + dy * dy <= R * R)
        pixels[row][col] = COLOR_GREY_LIGHT;
    }
}

/**
 * URL = https://www.geeksforgeeks.org/maths/rotation-matrix/
 */
void rotateImage(short pixels[][N], short newPixels[][N], double degrees) {
    double cos_a = cos(degrees);
    double sin_a = sin(degrees);
    
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            int x = col - HALF;
            int y = row - HALF;
            
            int newCol = (int)(x * cos_a - y * sin_a) + HALF;
            int newRow = (int)(x * sin_a + y * cos_a) + HALF;
            
            if (newRow >= 0 && newRow < N && newCol >= 0 && newCol < N) {
                newPixels[newRow][newCol] = pixels[row][col];
            }
        }
    }
}

int main() {
  short Pixels[N][N];
  short newPixels[N][N

  clearImage(Pixels);
  clearImage(newPixels);

  fillRectangle(Pixels, 0, 0, HALF, 10, 10, 80, 80);
  fillCircle(Pixels, HALF, HALF, HALF, 45, 45, 40);

  rotateImage(Pixels, newPixels, 90.0 * M_PI / 180.0);

  Display image(newPixels, "output");
  return 0;
}
