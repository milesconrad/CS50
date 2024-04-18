#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = 0;
            average += image[i][j].rgbtRed;
            average += image[i][j].rgbtGreen;
            average += image[i][j].rgbtBlue;
            average = round((float) average / 3);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_clone[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_clone[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_clone[i][width - 1 - j];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_clone[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_clone[i][j] = image[i][j];
        }
    }

    // index 0 is red, index 1 is green, index 2 is blue
    int averages[3] = {0, 0, 0};
    int pixel_count = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if ((k >= 0 && k < height) && (l >= 0 && l < width))
                    {
                        averages[0] += image_clone[k][l].rgbtRed;
                        averages[1] += image_clone[k][l].rgbtGreen;
                        averages[2] += image_clone[k][l].rgbtBlue;
                        pixel_count++;
                    }
                }
            }

            for (int k = 0; k < 3; k++)
            {
                averages[k] = round((float) averages[k] / pixel_count);
            }
            image[i][j].rgbtRed = averages[0];
            image[i][j].rgbtGreen = averages[1];
            image[i][j].rgbtBlue = averages[2];

            for (int k = 0; k < 3; k++)
            {
                averages[k] = 0;
            }
            pixel_count = 0;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_clone[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_clone[i][j] = image[i][j];
        }
    }

    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int Gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    int gx_sums[3] = {0, 0, 0};
    int gy_sums[3] = {0, 0, 0};
    int final_values[3] = {0, 0, 0};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if ((k >= 0 && k < height) && (l >= 0 && l < width))
                    {
                        gx_sums[0] += image_clone[k][l].rgbtRed * Gx[k - (i - 1)][l - (j - 1)];
                        gx_sums[1] += image_clone[k][l].rgbtGreen * Gx[k - (i - 1)][l - (j - 1)];
                        gx_sums[2] += image_clone[k][l].rgbtBlue * Gx[k - (i - 1)][l - (j - 1)];

                        gy_sums[0] += image_clone[k][l].rgbtRed * Gy[k - (i - 1)][l - (j - 1)];
                        gy_sums[1] += image_clone[k][l].rgbtGreen * Gy[k - (i - 1)][l - (j - 1)];
                        gy_sums[2] += image_clone[k][l].rgbtBlue * Gy[k - (i - 1)][l - (j - 1)];
                    }
                }
            }

            for (int k = 0; k < 3; k++)
            {
                final_values[k] = round(sqrt(pow(gx_sums[k], 2) + pow(gy_sums[k], 2)));
                if (final_values[k] > 255)
                {
                    final_values[k] = 255;
                }
            }

            image[i][j].rgbtRed = final_values[0];
            image[i][j].rgbtGreen = final_values[1];
            image[i][j].rgbtBlue = final_values[2];

            for (int k = 0; k < 3; k++)
            {
                gx_sums[k] = 0;
                gy_sums[k] = 0;
                final_values[k] = 0;
            }
        }
    }

    return;
}