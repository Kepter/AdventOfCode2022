#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <regex>

const int buffer_size = 100000;

#define FLOW 3
#define SNAD 2
#define ROCK 1
#define AIR 0

#define SHOW_FLOW 0

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return EXIT_SUCCESS;
    }

    std::cout << "Reading from " << argv[1] << '\n';

    std::ifstream file (argv[1]);
    char line_buffer[buffer_size];

    int map[200][1200];
    int negmap[200][1200];
    for(int i=0; i<200; i++)
        for(int j=0; j<1200; j++)
        {
            map[i][j] = AIR;
            negmap[i][j] = AIR;
        }
            
    
    std::regex coord_regex("([0-9][0-9]*),([0-9][0-9]*)");
    int floor = 0;
    while(file.getline(line_buffer, buffer_size))
    {
        int lx, ly; lx = ly = -1;
        std::string line(line_buffer);

        // Process coordinates
        std::smatch match;
        while (std::regex_search(line, match, coord_regex))
        {
            int x = std::stoi(match[1].str()) + 300;
            int y = std::stoi(match[2].str());
            floor = std::max(floor, y);

            if (!(lx == ly == -1))
            {
                int base, dist, i;
                switch (lx == x)
                {
                    case true:
                        dist = std::abs(ly - y);
                        base = std::min(ly, y);

                        for (i=0; i<=dist; i++)
                        {
                            map[base+i][lx] = ROCK;
                        }

                        break;

                    case false:
                        dist = std::abs(lx - x);
                        base = std::min(lx, x);
                        
                        for (i=0; i<=dist; i++)
                        {
                            map[ly][base+i] = ROCK;
                        }

                        break;
                }
            }
            
            lx = x;
            ly = y;
            line = match.suffix().str();
        }
    }

    // Add floor
    for (int i=0; i<1200; i++)
    {
        map[floor+2][i] = ROCK;
    }

    std::cout << "FLOOR " << floor << std::endl;

    for (int r=0; r<=floor+2; r++)
    {
        for (int c=470; c<=530; c++)
        {
            if (map[r][c] == ROCK)
                std::cout << "#";
            else if (map[r][c] == AIR)
                std::cout << ".";
            else if (map[r][c] == SNAD)
                std::cout << "o";
            else if (map[r][c] == FLOW)
                std::cout << "~";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << " ================================================ " << std::endl;
    std::cout << std::endl;

    int snad_count = 0;

    // Simulate
    bool isDestroyed = false;
    while(!isDestroyed)
    {
        // Create SNAD
        int sx, sy;
        sx = 800; sy = 0;

        // Sweep away flowing SNAD
        if (SHOW_FLOW)
        {
            for (int r=0; r<200; r++)
            {
                for (int c=0; c<1200; c++)
                {
                    if (map[r][c] == FLOW)
                        map[r][c] = AIR;
                }
            }
        }

        // Simulate
        int iter = 0;
        while(true)
        {
            // Fall to the ground
            while(sy < 199 && map[sy+1][sx] == AIR)
                sy++;

            if (SHOW_FLOW)
                map[sy][sx] = FLOW;

            // Try shift left
            if (sx > 0 && map[sy+1][sx-1] == AIR)
            {
                sx -= 1;
                sy += 1;
                continue;
            }

            // Try shift right
            if (sx < 1199 && map[sy+1][sx+1] == AIR)
            {
                sx += 1;
                sy += 1;
                continue;
            }

            // Can't move
            map[sy][sx] = SNAD;
            snad_count++;

            if (sx == 800 && sy == 0)
                isDestroyed = true;
            
            break;
        }
    }

    for (int r=0; r<=floor+2; r++)
    {
        for (int c=700; c<=899; c++)
        {
            if (map[r][c] == ROCK)
                std::cout << "#";
            else if (map[r][c] == AIR)
                std::cout << ".";
            else if (map[r][c] == SNAD)
                std::cout << "o";
            else if (map[r][c] == FLOW)
                std::cout << "~";
        }
        std::cout << std::endl;
    }

    std::cout << "SNAD COUNT " << snad_count << std::endl;

    return EXIT_SUCCESS;
}