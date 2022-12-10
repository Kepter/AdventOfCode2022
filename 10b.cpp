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
    char screen[6][40];

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

                if (std::abs(x - (cycle%40)) < 2)
                {
                    screen[cycle/40][cycle%40] = '#';
                }
                else
                {
                    screen[cycle/40][cycle%40] = '.';
                }

                cycle++;

                if (std::abs(x - (cycle%40)) < 2)
                {
                    screen[cycle/40][cycle%40] = '#';
                }
                else
                {
                    screen[cycle/40][cycle%40] = '.';
                }

                cycle++;
                x += val;
#ifdef DEBUG2
                std::cout << "Increment: " << screen[(cycle-2)/40][(cycle-2)%40] << " " << screen[(cycle-1)/40][(cycle-1)%40] << std::endl;
#endif
                break;

            // Noop
            case 'n':

                if (std::abs(x - (cycle%40)) < 2)
                {
                    screen[cycle/40][cycle%40] = '#';
                }
                else
                {
                    screen[cycle/40][cycle%40] = '.';
                }

                cycle++;
#ifdef DEBUG2
                std::cout << "Noop: " << screen[(cycle-1)/40][(cycle-1)%40] << " at "<< ((cycle-1)/40) << "," << ((cycle-1)%40) << std::endl;
#endif
                break;

            default:
                std::cout << "Unknown operation: " << word << std::endl;
                break;
        }
    }

    std::cout << "---------------- SCREEN ----------------\n";
    for (int r=0; r<6; r++)
    {
        for (int c=0; c<40; c++)
        {
            std::cout << screen[r][c];
        }
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}