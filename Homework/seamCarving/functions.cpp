#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using std::cout, std::endl, std::string;

void initializeImage(Pixel image[][MAX_HEIGHT])
{
    // iterate through columns
    for (unsigned int col = 0; col < MAX_WIDTH; col++)
    {
        // iterate through rows
        for (unsigned int row = 0; row < MAX_HEIGHT; row++)
        {
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

    if (x == 0)
    {
        deltaR = pow(image[x + 1][y].r - image[width - 1][y].r, 2);
        deltaG = pow(image[x + 1][y].g - image[width - 1][y].g, 2);
        deltaB = pow(image[x + 1][y].b - image[width - 1][y].b, 2);
        energy = deltaR + deltaG + deltaB;
    }
    else if (x == width - 1)
    {
        deltaR = pow(image[x - 1][y].r - image[0][y].r, 2);
        deltaG = pow(image[x - 1][y].g - image[0][y].g, 2);
        deltaB = pow(image[x - 1][y].b - image[0][y].b, 2);
        energy = deltaR + deltaG + deltaB;
    }
    else
    {
        deltaR = pow(image[x - 1][y].r - image[x + 1][y].r, 2);
        deltaG = pow(image[x - 1][y].g - image[x + 1][y].g, 2);
        deltaB = pow(image[x - 1][y].b - image[x + 1][y].b, 2);
        energy = deltaR + deltaG + deltaB;
    }

    if (y == 0)
    {
        deltaR = pow(image[x][y + 1].r - image[x][height - 1].r, 2);
        deltaG = pow(image[x][y + 1].g - image[x][height - 1].g, 2);
        deltaB = pow(image[x][y + 1].b - image[x][height - 1].b, 2);
        energy = energy + deltaR + deltaG + deltaB;
    }
    else if (y == height - 1)
    {
        deltaR = pow(image[x][y - 1].r - image[x][0].r, 2);
        deltaG = pow(image[x][y - 1].g - image[x][0].g, 2);
        deltaB = pow(image[x][y - 1].b - image[x][0].b, 2);
        energy = energy + deltaR + deltaG + deltaB;
    }
    else
    {
        deltaR = pow(image[x][y - 1].r - image[x][y + 1].r, 2);
        deltaG = pow(image[x][y - 1].g - image[x][y + 1].g, 2);
        deltaB = pow(image[x][y - 1].b - image[x][y + 1].b, 2);
        energy = energy + deltaR + deltaG + deltaB;
    }
    return energy;
}

// uncomment functions as you implement them (part 2)

unsigned int loadVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_col, unsigned int width, unsigned int height, unsigned int seam[])
{
    unsigned int totalEnergy = 0;
    seam[0] = start_col;
    totalEnergy += energy(image, start_col, 0, width, height);

    for (unsigned int col = 1; col < height; ++col)
    {
        int middleEnergy = energy(image, start_col, col, width, height);
        int rightEnergy = (start_col > 0) ? energy(image, start_col - 1, col, width, height) : middleEnergy + 1;
        int leftEnergy = (start_col < width - 1) ? energy(image, start_col + 1, col, width, height) : middleEnergy + 1;

        if (middleEnergy <= leftEnergy && middleEnergy <= rightEnergy)
        {
            totalEnergy = totalEnergy + middleEnergy;
        }
        else if (leftEnergy <= rightEnergy && leftEnergy < middleEnergy)
        {
            start_col++;
            totalEnergy = totalEnergy + leftEnergy;
        }
        else
        {
            start_col--;
            totalEnergy = totalEnergy + rightEnergy;
        }

        seam[col] = start_col;
    }

    return totalEnergy;
}

// unsigned int loadHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_row, unsigned int width, unsigned int height, unsigned int seam[])
// {
//     // TODO: implement (part 2)

// }

void findMinVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[])
{
    unsigned int tempSeam[MAX_HEIGHT];
    unsigned int minEnergy = loadVerticalSeam(image, 0, width, height, tempSeam);

    for (unsigned int i = 0; i < height; ++i)
    {
        seam[i] = tempSeam[i];
    }

    for (unsigned int col = 1; col < width; ++col)
    {
        unsigned int currentSeamResult = loadVerticalSeam(image, col, width, height, tempSeam);

        if (currentSeamResult < minEnergy)
        {
            minEnergy = currentSeamResult;
            for (unsigned int i = 0; i < height; ++i)
            {
                seam[i] = tempSeam[i];
            }
        }
    }
}

// void findMinHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[])
// {
//     // TODO: implement (part 2)
// }

void removeVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int &width, unsigned int height, unsigned int verticalSeam[])
{
    for (unsigned int row = 0; row < height; ++row)
    {
        for (unsigned int column = verticalSeam[row]; column < width - 1; ++column)
        {
            image[column][row] = image[column + 1][row];
        }
    }

    width--;
}

// void removeHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int &height, unsigned int horizontalSeam[])
// {
//     // TODO: implement (part 2)

// }

unsigned int loadHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_row, unsigned int width, unsigned int height, unsigned int seam[])
{
    unsigned int totalEnergy = 0;
    seam[0] = start_row;
    totalEnergy += energy(image, 0, start_row, width, height);

    for (unsigned int row = 1; row < width; ++row)
    {
        int middleEnergy = energy(image, row, start_row, width, height);
        int upEnergy = (start_row > 0) ? energy(image, row, start_row - 1, width, height) : middleEnergy + 1;
        int downEnergy = (start_row < height - 1) ? energy(image, row, start_row + 1, width, height) : middleEnergy + 1;

        if (middleEnergy <= upEnergy && middleEnergy <= downEnergy)
        {
            totalEnergy = totalEnergy + middleEnergy;
        }
        else if (upEnergy <= downEnergy && upEnergy < middleEnergy)
        {
            start_row--;
            totalEnergy = totalEnergy + upEnergy;
        }
        else
        {
            start_row++;
            totalEnergy = totalEnergy + downEnergy;
        }

        seam[row] = start_row;
    }

    return totalEnergy;
}

void findMinHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[])
{
    unsigned int tempSeam[MAX_WIDTH];
    unsigned int minEnergy = loadHorizontalSeam(image, 0, width, height, tempSeam);

    for (unsigned int i = 0; i < width; ++i)
    {
        seam[i] = tempSeam[i];
    }

    for (unsigned int row = 1; row < height; ++row)
    {
        unsigned int currentSeamResult = loadHorizontalSeam(image, row, width, height, tempSeam);

        if (currentSeamResult < minEnergy)
        {
            minEnergy = currentSeamResult;
            for (unsigned int i = 0; i < width; ++i)
            {
                seam[i] = tempSeam[i];
            }
        }
    }
}

void removeHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int &height, unsigned int horizontalSeam[])
{
    for (unsigned int col = 0; col < width; ++col)
    {
        for (unsigned int row = horizontalSeam[col]; row < height - 1; ++row)
        {
            image[col][row] = image[col][row + 1];
        }
    }

    height--;
}
