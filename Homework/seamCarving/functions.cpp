#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using std::cout, std::endl, std::string;

void initializeImage(Pixel image[][MAX_HEIGHT]) {
  // iterate through columns
  for (unsigned int col = 0; col < MAX_WIDTH; col++) {
    // iterate through rows
    for (unsigned int row = 0; row < MAX_HEIGHT; row++) {
      // initialize pixel
      image[col][row] = {0, 0, 0};
    }
  }
}

void loadImage(string filename, Pixel image[][MAX_HEIGHT], unsigned int &width, unsigned int &height)
{
    // TODO: implement (part 1)
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open " + filename);
    }

    string fileType;
    file >> fileType;
    if (fileType != "P3" && fileType != "p3")
    {
        throw std::runtime_error("Invalid type " + fileType);
    }

    file >> width >> height;
    if (width <= 0 || height <= 0 || width > MAX_WIDTH || height > MAX_HEIGHT)
    {
        throw std::runtime_error("Invalid dimensions");
    }

    int maxColor;
    file >> maxColor;

    for (unsigned int row = 0; row < height; ++row)
    {
        for (unsigned int col = 0; col < width; ++col)
        {
            short r, g, b;
            if (!(file >> r >> g >> b))
            {
                throw std::runtime_error("Invalid color value");
            }
            if (r < 0 || g < 0 || b < 0 || r > maxColor || g > maxColor || b > maxColor)
            {
                throw std::runtime_error("Invalid color value");
            }
            image[col][row] = {r, g, b};
        }
    }

    string extra;
    if (file >> extra)
    {
        throw std::runtime_error("Too many values");
    }

    file.close();
}

void outputImage(string filename, Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height)
{
    // TODO: implement (part 1)
    std::ofstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open " + filename);
    }

    file << "P3" << endl;
    file << width << " " << height << endl;
    file << "255" << endl;

    for (unsigned int row = 0; row < height; ++row)
    {
        for (unsigned int col = 0; col < width; ++col)
        {
            file << static_cast<int>(image[col][row].r) << " ";
            file << static_cast<int>(image[col][row].g) << " ";
            file << static_cast<int>(image[col][row].b) << " ";
        }
        file << endl;
    }

    file.close();
}

unsigned int energy(Pixel image[][MAX_HEIGHT], unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
  // TODO: implement (part 1)
  unsigned int energy = 0;
  unsigned int deltaR = 0;
  unsigned int deltaG = 0;
  unsigned int deltaB = 0;

  if(x == 0)
  {
    deltaR = pow(image[x+1][y].r - image[width-1][y].r, 2);
    deltaG = pow(image[x+1][y].g - image[width-1][y].g, 2);
    deltaB = pow(image[x+1][y].b - image[width-1][y].b, 2);
    energy = deltaR + deltaG + deltaB;
  }
  else if(x == width - 1)
  {
    deltaR = pow(image[x-1][y].r - image[0][y].r, 2);
    deltaG = pow(image[x-1][y].g - image[0][y].g, 2);
    deltaB = pow(image[x-1][y].b - image[0][y].b, 2);
    energy = deltaR + deltaG + deltaB;
  }
  else
  {
    deltaR = pow(image[x-1][y].r - image[x+1][y].r, 2);
    deltaG = pow(image[x-1][y].g - image[x+1][y].g, 2);
    deltaB = pow(image[x-1][y].b - image[x+1][y].b, 2);
    energy = deltaR + deltaG + deltaB;
  }

  if(y == 0)
  {
    deltaR = pow(image[x][y+1].r - image[x][height-1].r, 2);
    deltaG = pow(image[x][y+1].g - image[x][height-1].g, 2);
    deltaB = pow(image[x][y+1].b - image[x][height-1].b, 2);
    energy = energy + deltaR + deltaG + deltaB;
  }
  else if(y == height - 1)
  {
    deltaR = pow(image[x][y-1].r - image[x][0].r, 2);
    deltaG = pow(image[x][y-1].g - image[x][0].g, 2);
    deltaB = pow(image[x][y-1].b - image[x][0].b, 2);
    energy = energy + deltaR + deltaG + deltaB;
  }
  else
  {
    deltaR = pow(image[x][y-1].r - image[x][y+1].r, 2);
    deltaG = pow(image[x][y-1].g - image[x][y+1].g, 2);
    deltaB = pow(image[x][y-1].b - image[x][y+1].b, 2);
    energy = energy + deltaR + deltaG + deltaB;
  }
  return energy;
}


// uncomment functions as you implement them (part 2)

// unsigned int loadVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_col, unsigned int width, unsigned int height, unsigned int seam[]) {
//   // TODO: implement (part 2)
//   return 0;
// }

// unsigned int loadHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_row, unsigned int width, unsigned int height, unsigned int seam[]) {
//   // TODO: implement (part 2)
//   return 0;
// }

// void findMinVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[]) {
//   // TODO: implement (part 2)
// }

// void findMinHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[]) {
//   // TODO: implement (part 2)
// }

// void removeVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int& width, unsigned int height, unsigned int verticalSeam[]) {
//   // TODO: implement (part 2)
// }

// void removeHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int& height, unsigned int horizontalSeam[]) {
//   // TODO: implement (part 2)
// }
