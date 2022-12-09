#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

const int buffer_size = 100000;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return EXIT_SUCCESS;
    }

    std::cout << "Reading from " << argv[1] << '\n';

    std::ifstream file (argv[1]);
    char line_buffer[buffer_size];

    std::vector<char> seen;
    int sum = 0;
    
    file.getline(line_buffer, buffer_size);
    for (int i=4; i<buffer_size && line_buffer[i] != '\0'; i++)
    {
        bool valid = true;
        for (int j=0; j<14; j++)
        {
            for (int k=j+1; k<14; k++)
            {
                if (j == k) continue;
                if (line_buffer[i-j] == line_buffer[i-k])
                {
                    valid = false;
                    break;
                }
            }

            if (!valid) break;
        }

        if (valid)
        {
            std::cout << "valid " << i+1 << "\n";
            break;
        }
    }

    return EXIT_SUCCESS;
}