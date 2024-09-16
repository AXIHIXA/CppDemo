#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <set>
#include <vector>


void conv2d(const float * __restrict__ in,
            int inSizeX,
            int inSizeY,
            const float * __restrict__ kernel,
            int kSizeX,
            int kSizeY,
            float * __restrict__ out)
{
    // Check validity of params.
    assert(in && out && kernel && 0 < inSizeX && 0 < inSizeY);

    // Find center position of kernel (half of kernel size).
    int kCenterX = kSizeX >> 1;
    int kCenterY = kSizeY >> 1;

    // Init working pointers.
    const float * __restrict__ in1 = &in[inSizeX * kCenterY + kCenterX];
    const float * __restrict__ in2 = in1;
    float * __restrict__ o = out;
    const float * __restrict__ k = kernel;

    // Start convolution.
    for (int i = 0, rowMin, rowMax; i < inSizeY; ++i)
    {
        rowMin = i - inSizeY + kCenterY;
        rowMax = i + kCenterY;

        for (int j = 0, colMin, colMax; j < inSizeX; ++j)
        {
            colMax = j + kCenterX;
            colMin = j - inSizeX + kCenterX;

            // Zero target before accumulation.
            *o = 0;

            // Flip the kernel and traverse all the kernel values.
            // Multiply each kernel value with underlying input data.
            for (int m = 0; m < kSizeY; ++m)
            {
                // check if the index is out of bound of input array
                if (rowMin < m && m <= rowMax)
                {
                    for (int n = 0; n < kSizeX; ++n)
                    {
                        // check the boundary of array
                        if (colMin < n && n <= colMax)
                        {
                            *o += *(in1 - n) * (*k);
                        }

                        // next kernel
                        ++k;
                    }
                }
                else
                {
                    // Out of bound, move to next row of kernel.
                    k += kSizeX;
                }

                // Move input data 1 row up.
                in1 -= inSizeX;
            }

            k = kernel;   // Reset kernel to (0, 0).
            in1 = ++in2;  // Next input.
            ++o;          // Next output.
        }
    }
}


int main(int argc, char * argv[])
{
    std::vector<float> in(6 * 6, 1.0f);
    std::vector<float> out(6 * 6);
    std::vector<float> kernel = {0.0f, 1.0f, 0.0f, 1.0f, -4.0f, 1.0f, 0.0f, 1.0f, 0.0f};
    conv2d(in.data(), 6, 6, kernel.data(), 3, 3, out.data());

    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            std::printf("%+.1f ", out[i * 6 + j]);
        }

        std::cout << '\n';
    }

    std::cout << '\n';

    return EXIT_SUCCESS;
}