#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <deque>
#include <string>
#include <regex>
#include <algorithm>

//#define DEBUG 0
//#define DEBUG2 0

const int buffer_size = 100000;
const int num_monkey = 8;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return EXIT_SUCCESS;
    }

    std::cout << "Reading from " << argv[1] << '\n';

    std::ifstream file (argv[1]);
    char line_buffer[buffer_size];

    std::deque<int> monkeys[num_monkey];
    int inspections[num_monkey];

    std::regex int_regex("([0-9][0-9]*)");

    // Parse file
    for (int m=0; m<num_monkey; m++)
    {
        // Ignore first line
        file.getline(line_buffer, buffer_size); 

        // Starting items: 96, 60, 68, 91, 83, 57, 85
        file.getline(line_buffer, buffer_size);
        std::string line(line_buffer);

        // Extract items
        std::smatch match;
        while (std::regex_search(line, match, int_regex))
        {
            monkeys[m].push_back(std::stoi(match[0].str()));
            line = match.suffix().str();
        }
        // Ignore other lines, we code these
        file.getline(line_buffer, buffer_size); 
        file.getline(line_buffer, buffer_size); 
        file.getline(line_buffer, buffer_size); 
        file.getline(line_buffer, buffer_size); 
        file.getline(line_buffer, buffer_size);

        // Initalize inspections count
        inspections[m] = 0;
    }
    

    for (int r=0; r<20; r++)
    {
        for (int m=0; m<num_monkey; m++)
        {
            inspections[m] += monkeys[m].size();
            while (monkeys[m].size() > 0)
            {
                int x = monkeys[m].front();
                monkeys[m].pop_front();

                // Monkey specific actions
                switch(m)
                {
                    case 0:
                        x *= 2;
                        break;
                    case 1:
                        x += 3;
                        break;
                    case 2:
                        x += 6;
                        break;
                    case 3:
                        x += 5;
                        break;
                    case 4:
                        x += 8;
                        break;
                    case 5:
                        x *= 5;
                        break;
                    case 6:
                        x *= x;
                        break;
                    case 7:
                        x += 4;
                        break;
                }

                x = x / 3;

                // Monkey specific passes
                switch(m)
                {
                    case 0:
                        if (x % 17 == 0)
                            monkeys[2].push_back(x);
                        else
                            monkeys[5].push_back(x);
                        break;
                    case 1:
                        if (x % 13 == 0)
                            monkeys[7].push_back(x);
                        else
                            monkeys[4].push_back(x);
                        break;
                    case 2:
                        if (x % 19 == 0)
                            monkeys[6].push_back(x);
                        else
                            monkeys[5].push_back(x);
                        break;
                    case 3:
                        if (x % 7 == 0)
                            monkeys[7].push_back(x);
                        else
                            monkeys[1].push_back(x);
                        break;
                    case 4:
                        if (x % 11 == 0)
                            monkeys[0].push_back(x);
                        else
                            monkeys[2].push_back(x);
                        break;
                    case 5:
                        if (x % 3 == 0)
                            monkeys[6].push_back(x);
                        else
                            monkeys[3].push_back(x);
                        break;
                    case 6:
                        if (x % 2 == 0)
                            monkeys[3].push_back(x);
                        else
                            monkeys[1].push_back(x);
                        break;
                    case 7:
                        if (x % 5 == 0)
                            monkeys[4].push_back(x);
                        else
                            monkeys[0].push_back(x);
                        break;
                }
            }
        }
    }

    std::cout << "Monkey inspections: " << std::endl;
    int max1, max2; max1 = max2 = 0;
    for(int m=0; m<num_monkey; m++)
    {
        std::cout << "  M" << m << " | " << inspections[m] << std::endl;
        if (inspections[m] > max2)
        {
            max1 = max2;
            max2 = inspections[m];
        }
        else if (inspections[m] > max1)
        {
            max1 = inspections[m];
        }
    }
    std::cout << " Monkey shenangians: " << (max1 * max2) << std::endl;

    return EXIT_SUCCESS;
}