#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <vector>


int main(int argc, char * argv[])
{
    for (int i = 1; i < 10'000'000; ++i)
    {
        std::vector<int> vec;

        for (int s = i, k = 1; s != 0; s >>= 1, k <<= 1)
        {
            if (s & 1)
            {
                vec.emplace_back(k);
            }
        }

        if (i != std::reduce(vec.cbegin(), vec.cend(), 0LL))
        {
            std::cout << i << '\n';
            break;
        }
    }

    return EXIT_SUCCESS;
}
