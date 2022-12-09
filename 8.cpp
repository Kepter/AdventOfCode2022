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

    std::vector<std::vector<bool>> isVisible;
    std::vector<std::vector<int>> height;
    
    while(file.getline(line_buffer, buffer_size))
    {
        isVisible.resize(isVisible.size() + 1);
        height.resize(height.size() + 1);

        for (int i=0; line_buffer[i] >= '0' && line_buffer[i] <= '9'; i++)
        {
            isVisible[isVisible.size() - 1].push_back(false);
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

    std::cout << "rows: " << rowCount << "  cols: " << colCount << "\n";

    // Count columns up/down
    for (int col=0; col<colCount; col++)
    {
        int lastUp = -1;
        int lastDown = -1;

        for (int row = 0; row<rowCount; row++)
        {
            //std::cout << "r: " << row << "c: " << col << std::endl;
            // Checking 0 to n
            if (height[row][col] > lastUp)
            {
                if (!isVisible[row][col])
                {
                    totalVisible++;
                }

                isVisible[row][col] = true;
            }

            // Checking n to 0
            if (height[rowCount - row - 1][col] > lastDown)
            {
                if (!isVisible[rowCount - row - 1][col])
                {
                    totalVisible++;
                }

                isVisible[rowCount - row - 1][col] = true;
            }

            lastUp = std::max(height[row][col], lastUp);
            lastDown =  std::max(height[rowCount - row - 1][col], lastDown);
        }
    }
    
    for (int row=0; row<rowCount; row++)
    {
        int lastLeft = -1;
        int lastRight = -1;

        for (int col = 0; col<colCount; col++)
        {
            // Checking 0 to n
            if (height[row][col] > lastLeft)
            {
                if (!isVisible[row][col])
                {
                    totalVisible++;
                }

                isVisible[row][col] = true;
            }

            // Checking n to 0
            if (height[row][colCount - col - 1] > lastRight)
            {
                if (!isVisible[row][colCount - col - 1])
                {
                    totalVisible++;
                }

                isVisible[row][colCount - col - 1] = true;
            }

            lastLeft =  std::max(height[row][col], lastLeft);
            lastRight =  std::max(height[row][colCount - col - 1], lastRight);
        }
    }

    std::cout << "visible " << totalVisible << "\n";
    return EXIT_SUCCESS;
}