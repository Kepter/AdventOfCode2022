#include <iostream>
#include <fstream>
#include <cstdlib>

const int buffer_size = 256;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return EXIT_SUCCESS;
    }

    std::cout << "Reading from " << argv[1] << '\n';

    std::ifstream file (argv[1]);
    char line_buffer[buffer_size];

    int maxSums[3] = {};
    int sum = 0;

    while(file.getline(line_buffer, buffer_size))
    {
        try
        {
            sum += std::stoi(line_buffer);
        }
        catch (std::invalid_argument)
        {
            for (int i=2; i>=0; i--)
            {
                if (sum > maxSums[i])
                {
                    for(int j=i-1; j>=0; j--)
                    {
                        maxSums[j] = maxSums[j+1];
                    }
                    maxSums[i] = sum;
                    break;
                }
            }

            sum = 0;
        }
    }

    std::cout << "Max sums: " << maxSums[0] + maxSums[1] + maxSums[2] << '\n' << std::endl;

    return EXIT_SUCCESS;
}