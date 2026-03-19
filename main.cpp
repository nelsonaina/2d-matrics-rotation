#include <iostream>
#include <cmath>
#include "Display.h"

using namespace std;

const int N = 180;
const int HALF = (N - 1) / 2;

// Colors
const short COLOR_GREY = 200;
const short COLOR_GREY_LIGHT = 150;
const short COLOR_WHITE = 255;

void normalizeImageColors(int sinogram[][N]);

void rotateImage(short pixels[][N], short newPixels[][N], double angle);
void clearImage(short pixels[][N]);

void fillRectangle(short pixels[][N], int row0, int col0, int size,
                   int x1, int y1, int x2, int y2);
void fillCircle(short pixels[][N], int row0, int col0, int size,
                int xc, int yc, int R);

int main() {
  short Pixels[N][N];
  int sinogram[N][N] = {};

  clearImage(Pixels);

  fillCircle(Pixels, 0, 0, HALF, 45, 45, 15);
  fillRectangle(Pixels, HALF, HALF, HALF, 15, 15, 62, 62);

  for (int i = 0; i < N; i++) {
    short newPixels[N][N];

    clearImage(newPixels);
    rotateImage(Pixels, newPixels, (-1) * i);

    for (int row = 0; row < N; row++) {
      for (int col = 0; col < N; col++) {
        sinogram[i][col] += newPixels[row][col];
      }
    }
  }

  normalizeImageColors(sinogram);

  short sinogramShort[N][N];
  for (int r = 0; r < N; r++)
    for (int c = 0; c < N; c++)
      sinogramShort[r][c] = (short)sinogram[r][c];

  Display imagePixels(Pixels, "./output/output-pixels");
  Display imageSinogram(sinogramShort, "./output/output-sinogram");
  return 0;
}

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
        pixels[row][col] = COLOR_WHITE;
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
        pixels[row][col] = COLOR_WHITE;
    }
}

void normalizeImageColors(int sinogram[][N]) {
  // Find max value for normalization to 0-255
  int maxVal = 0;
  for (int row = 0; row < N; row++)
    for (int col = 0; col < N; col++)
      if (sinogram[row][col] > maxVal) maxVal = sinogram[row][col];

  for (int row = 0; row < N; row++)
    for (int col = 0; col < N; col++)
      sinogram[row][col] = sinogram[row][col] * 255 / maxVal;
}

/**
 * URL = https://www.geeksforgeeks.org/maths/rotation-matrix/
 * Section of page = 2D Rotation Matrix
 */
void rotateImage(short pixels[][N], short newPixels[][N], double angle) {
  double delta = angle * M_PI / 180.0;

  // Inverse mapping: for each destination pixel, find source pixel
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      double x = j - HALF;
      double y = i - HALF;

      double srcX = x * cos(delta) + y * sin(delta);
      double srcY = -x * sin(delta) + y * cos(delta);

      int sj = round(srcX + HALF);
      int si = round(srcY + HALF);

      if(sj >= 0 && sj < N && si >= 0 && si < N) {
        newPixels[i][j] = pixels[si][sj];
      }
    }
  }
}
