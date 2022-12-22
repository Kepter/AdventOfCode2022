#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <regex>
#include <map>
#include <deque>
#include <stdexcept>

const int buffer_size = 100000;

struct Monkey
{
    int dep = -1;

    std::string leftDep = "?";
    std::string rightDep = "?";

    long leftVal = -1;
    long rightVal = -1;
    long val = -1;

    char oper = '?';

    std::string name = "?";

    std::deque<Monkey*> dependants;
};

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return EXIT_SUCCESS;
    }

    std::cout << "Reading from " << argv[1] << '\n';

    std::ifstream file (argv[1]);
    char line_buffer[buffer_size];
    std::map<std::string, Monkey*> monkeyMap;
    std::deque<Monkey*> readyMonkeys;
    std::deque<Monkey*> dependantMonkeys;

    while(file.getline(line_buffer, buffer_size))
    {
        std::string line(line_buffer);
        Monkey *m = new Monkey();

        m->name = line.substr(0, 4);
        
        // assume number monkey
        try
        {
            m->val = stoi(line.substr(6));
            m->dep = 0;

            readyMonkeys.push_back(m);
        }
        // Not number monkey
        catch (std::invalid_argument)
        {
            m->leftDep = line.substr(6, 4);
            m->rightDep = line.substr(13, 4);
            m->dep = 2;
            m->oper = line[11];

            dependantMonkeys.push_back(m);
        }

        monkeyMap[m->name] = m;
    }

    // Process depedencies now that all monkeys are known
    while(!dependantMonkeys.empty())
    {
        Monkey *m = dependantMonkeys.front();
        dependantMonkeys.pop_front();

        monkeyMap[m->leftDep]->dependants.push_back(m);
        monkeyMap[m->rightDep]->dependants.push_back(m);
    }

    // Process the monkeys, optimally
    while(!readyMonkeys.empty())
    {
        Monkey *m = readyMonkeys.front();
        readyMonkeys.pop_front();

        // Let the dependant monkeys know about this resolution
        while(!m->dependants.empty())
        {
            Monkey *depMonkey = m->dependants.front();
            m->dependants.pop_front();

            // Is this the Left or right?
            if (m->name.compare(depMonkey->leftDep) == 0)
            {
                depMonkey->leftVal = m->val;
            }
            else
            {
                depMonkey->rightVal = m->val;
            }

            // If the monkey has all its depedencies resolved, calculate it
            if (--depMonkey->dep == 0)
            {
                switch (depMonkey->oper)
                {
                    case '+':
                        depMonkey->val = depMonkey->leftVal + depMonkey->rightVal;
                        break;
                    case '-':
                        depMonkey->val = depMonkey->leftVal - depMonkey->rightVal;
                        break;
                    case '/':
                        depMonkey->val = depMonkey->leftVal / depMonkey->rightVal;
                        break;
                    case '*':
                        depMonkey->val = depMonkey->leftVal * depMonkey->rightVal;
                        break;
                }

                readyMonkeys.push_back(depMonkey);
            }
        }
    }

    
    std::cout << " Root: " << monkeyMap["root"]->val << std::endl;

    return EXIT_SUCCESS;
}