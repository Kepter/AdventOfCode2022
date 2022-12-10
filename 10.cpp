#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <sstream>

//#define DEBUG 0
//#define DEBUG2 0

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

    int x = 1;
    int cycle = 0;

    int capture[6] = {20, 60, 100, 140, 180, 220};
    int capIdx = 0;
    int sum = 0;
    
    while(file.getline(line_buffer, buffer_size))
    {
        std::stringstream line(line_buffer);
        std::string word;

        line >> word;

        switch(word[0])
        {
            // Addx
            case 'a':
                int val; line >> val;

                cycle += 2;

                if (capIdx < 6 && cycle >= capture[capIdx])
                {
#ifdef DEBUG
                    std::cout << "Signal " << x << "*" << capture[capIdx] << "=" <<(x*capture[capIdx]) << " at " << cycle << std::endl;
#endif
                    sum += x*capture[capIdx++];
                }
#ifdef DEBUG2
                std::cout << "Increment: " << x << " " << cycle << std::endl;
#endif
                x += val;
                break;

            // Noop
            case 'n':
                cycle++;

                if (capIdx < 6 && cycle == capture[capIdx])
                {
#ifdef DEBUG
                    std::cout << "Signal " << x << "*" << cycle << "=" <<(x*cycle) << " at " << cycle << std::endl;
#endif
                    sum += x*capture[capIdx++];
                }
#ifdef DEBUG2
                std::cout << "Noop: " << cycle << std::endl;
#endif
                break;

            default:
                std::cout << "Unknown operation: " << word << std::endl;
                break;
        }
    }
    std::cout << "Sum " << sum << "\n";
    return EXIT_SUCCESS;
}