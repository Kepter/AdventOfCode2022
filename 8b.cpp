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

    std::vector<std::vector<int>> isVisible;
    std::vector<std::vector<int>> height;
    
    while(file.getline(line_buffer, buffer_size))
    {
        isVisible.resize(isVisible.size() + 1);
        height.resize(height.size() + 1);

        for (int i=0; line_buffer[i] >= '0' && line_buffer[i] <= '9'; i++)
        {
            isVisible[isVisible.size() - 1].push_back(1);
            height[isVisible.size() - 1].push_back((int)(line_buffer[i] - '0'));
        }

        if (isVisible[isVisible.size() - 1].size() == 0)
        {
            isVisible.resize(isVisible.size() - 1);
            height.resize(height.size() - 1);
            break;
        }
    }

    int totalVisible = 0;
    int rowCount = isVisible.size();
    int colCount = isVisible[0].size();
    int max = -1;

    std::cout << "rows: " << rowCount << "  cols: " << colCount << "\n";

    // Count columns up/down
    for (int row=0; row<rowCount; row++)
    {
        for (int col = 0; col<colCount; col++)
        {
            bool a, b, c, d;
            a = b = c = d = false;

            std::cout << "{" << row << ","<<col<<"} ";
            for (int i=1; !a || !b || !c || !d; i++)
            {
                if (!a)
                {
                    if (col - i - 1 < 0 || height[row][col] <= height[row][col-i])
                    {
                        isVisible[row][col] *= i;
                        a = true;
                        std::cout << "a="<< i;
                    }
                }

                if (!b)
                {
                    if (col + i + 1 >= colCount || height[row][col] <= height[row][col+i])
                    {
                        isVisible[row][col] *= i;
                        b = true;
                        std::cout << "b="<< i<<" ";
                    }
                }

                if (!c)
                {
                    if (row - i - 1 < 0 || height[row][col] <= height[row - i][col])
                    {
                        isVisible[row][col] *= i;
                        c = true;
                        std::cout << "c="<< i<<" ";
                    }
                }

                if (!d)
                {
                    if (row + i + 1 >= rowCount || height[row][col] <= height[row+i][col])
                    {
                        isVisible[row][col] *= i;
                        d = true;
                        std::cout << "d="<< i<<" ";
                    }
                }
            }

            std::cout << "(" << isVisible[row][col] << ")";
            max = std::max(isVisible[row][col], max);
        }
        std::cout << "\n";
    }

    std::cout << "Best " << max << "\n";
    return EXIT_SUCCESS;
}