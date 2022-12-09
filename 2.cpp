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

    int sum = 0;

    while(file.getline(line_buffer, buffer_size))
    {
        switch(line_buffer[2])
        {
            case 'X':
                sum += 1;
                
                switch(line_buffer[0])
                {
                    case 'A':
                        sum += 3;
                        break;
                    
                    case 'C':
                        sum += 6;
                        break;
                }
                
                break;

            case 'Y':
                sum += 2;
                
                switch(line_buffer[0])
                {
                    case 'B':
                        sum += 3;
                        break;
                    
                    case 'A':
                        sum += 6;
                        break;
                }
                break;

            case 'Z':
                sum += 3;
                
                switch(line_buffer[0])
                {
                    case 'C':
                        sum += 3;
                        break;
                    
                    case 'B':
                        sum += 6;
                        break;
                }
                break;
        }
    }

    std::cout << "Score: " << sum << '\n' << std::endl;

    return EXIT_SUCCESS;
}