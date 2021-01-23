#include "helpers.h"
#include <math.h>

int cap(int a);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    int halfwidth = width / 2;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < halfwidth; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float nterms;
    int rsum;
    int bsum;
    int gsum;
    RGBTRIPLE tempimage[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            nterms = 0.00;
            rsum = 0;
            gsum = 0;
            bsum = 0;
            for (int k = -1; k <= 1; k++)
            {
                if (i + k < 0 || i + k >= height)
                {
                    continue;
                }

                for (int l = -1; l <= 1; l++)
                {
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }

                    rsum += image[i + k][j + l].rgbtRed;
                    gsum += image[i + k][j + l].rgbtGreen;
                    bsum += image[i + k][j + l].rgbtBlue;
                    nterms++;
                }
            }
            tempimage[i][j].rgbtRed = round(rsum / nterms);
            tempimage[i][j].rgbtGreen = round(gsum / nterms);
            tempimage[i][j].rgbtBlue = round(bsum / nterms);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tempimage[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int x[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
    int y[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };
    float Gx[3];
    float Gy[3];
    RGBTRIPLE tempimage[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = 0; k <= 2; k++)
            {
                Gx[k] = 0.00;
                Gy[k] = 0.00;
            }

            for (int k = -1; k <= 1; k++)
            {
                if (i + k < 0 || i + k >= height)
                {
                    continue;
                }

                for (int l = -1; l <= 1; l++)
                {
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }

                    Gx[0] += x[k + 1][l + 1] * image[i + k][j + l].rgbtRed;
                    Gx[1] += x[k + 1][l + 1] * image[i + k][j + l].rgbtGreen;
                    Gx[2] += x[k + 1][l + 1] * image[i + k][j + l].rgbtBlue;
                    Gy[0] += y[k + 1][l + 1] * image[i + k][j + l].rgbtRed;
                    Gy[1] += y[k + 1][l + 1] * image[i + k][j + l].rgbtGreen;
                    Gy[2] += y[k + 1][l + 1] * image[i + k][j + l].rgbtBlue;
                }
            }
            tempimage[i][j].rgbtRed = cap(round(sqrt(Gx[0] * Gx[0] + Gy[0] * Gy[0])));
            tempimage[i][j].rgbtGreen = cap(round(sqrt(Gx[1] * Gx[1] + Gy[1] * Gy[1])));
            tempimage[i][j].rgbtBlue = cap(round(sqrt(Gx[2] * Gx[2] + Gy[2] * Gy[2])));
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tempimage[i][j];
        }
    }
    return;
}

int cap(int a)
{
    if (a < 255)
    {
        return a;
    }
    return 255;
}