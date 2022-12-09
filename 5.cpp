
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <stack>
#include <vector>
#include <string>

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

    std::vector<std::stack<char>> stacks;

    std::stack<char> stack1;
    stack1.push('H');
    stack1.push('R');
    stack1.push('B');
    stack1.push('D');
    stack1.push('Z');
    stack1.push('F');
    stack1.push('L');
    stack1.push('S');
    stacks.push_back(stack1);

    std::stack<char> stack2;
    stack2.push('T');
    stack2.push('B');
    stack2.push('M');
    stack2.push('Z');
    stack2.push('R');
    stacks.push_back(stack2);

    std::stack<char> stack3;
    stack3.push('Z');
    stack3.push('L');
    stack3.push('C');
    stack3.push('H');
    stack3.push('N');
    stack3.push('S');
    stacks.push_back(stack3);

    std::stack<char> stack4;
    stack4.push('S');
    stack4.push('C');
    stack4.push('F');
    stack4.push('J');
    stacks.push_back(stack4);

    std::stack<char> stack5;
    stack5.push('P');
    stack5.push('G');
    stack5.push('H');
    stack5.push('W');
    stack5.push('R');
    stack5.push('Z');
    stack5.push('B');
    stacks.push_back(stack5);

    std::stack<char> stack6;
    stack6.push('V');
    stack6.push('J');
    stack6.push('Z');
    stack6.push('G');
    stack6.push('D');
    stack6.push('N');
    stack6.push('M');
    stack6.push('T');
    stacks.push_back(stack6);

    std::stack<char> stack7;
    stack7.push('G');
    stack7.push('L');
    stack7.push('N');
    stack7.push('W');
    stack7.push('F');
    stack7.push('S');
    stack7.push('P');
    stack7.push('Q');
    stacks.push_back(stack7);

    std::stack<char> stack8;
    stack8.push('M');
    stack8.push('Z');
    stack8.push('R');
    stacks.push_back(stack8);
    
    std::stack<char> stack9;
    stack9.push('M');
    stack9.push('C');
    stack9.push('L');
    stack9.push('G');
    stack9.push('V');
    stack9.push('R');
    stack9.push('T');
    stacks.push_back(stack9);

    int sum = 0;
    while(file.getline(line_buffer, buffer_size))
    {
        std::stringstream s(line_buffer);
        std::string word;
        int count, from, to;
        
        s >> word;
        s >> count;
        s >> word;
        s >> from;
        s >> word;
        s >> to;

        std::stack<char> intrnl;
        for (int i=0; i<count; i++)
        {
            char crate = stacks[from-1].top();
            stacks[from-1].pop();
            intrnl.push(crate);
        }

        for (int i=0; i<count; i++)
        {
            char crate = intrnl.top();
            intrnl.pop();
            stacks[to-1].push(crate);
        }
    }

    std::cout << "stacks: " <<stacks.size() << std::endl;
    for(int i=0; i<9; i++)
    {
        std::cout<< " " << stacks[i].top();
    }

    return EXIT_SUCCESS;
}