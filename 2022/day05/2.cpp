#include <fstream>
#include <iostream>
#include <stack>
#include <string>

void printStack(std::stack<char> &s);

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << "<input_file>" << std::endl;
        exit(0);
    }
    std::fstream in;
    in.open(argv[1], std::ios::in);
    if (in.fail())
    {
        std::cout << "Error opening input file" << std::endl;
        exit(0);
    }

    std::fstream in_stacks;
    in_stacks.open("input_stacks.txt", std::ios::in);

    std::string buffer;
    std::stack<char> stacks[9];

    for (int i = 0; getline(in_stacks, buffer); i++)
    {
        while (!buffer.empty())
        {
            stacks[i].push(buffer.back());
            buffer.pop_back();
        }
    }
    /*     for (int i = 0; i < 9; i++)
        {
            std::cout << "stack " << i << " ";
            printStack(stacks[i]);
        } */

    while (in >> buffer)
    {
        int nPieces, from, to;
        in >> buffer;
        nPieces = std::stoi(buffer);
        in >> buffer;
        in >> buffer;
        from = std::stoi(buffer);
        in >> buffer;
        in >> buffer;
        to = std::stoi(buffer);

        std::stack<char> tmp;
        for (int i = 0; i < nPieces; i++)
        {
            tmp.push(stacks[from - 1].top());
            stacks[from - 1].pop();
        }
        while (!tmp.empty())
        {
            stacks[to - 1].push(tmp.top());
            tmp.pop();
        }

        /*         std::cout << std::endl
                          << "move " << nPieces << " from " << from << " to " << to;

                std::cout << std::endl;
                for (int i = 0; i < 9; i++)
                {
                    std::cout << "stack " << i << " ";
                    printStack(stacks[i]);
                } */
    }

    for (int i = 0; i < 9; i++)
    {
        std::cout << stacks[i].top();
    }
    std::cout << std::endl;

    in.close();
    return 0;
}

void printStack(std::stack<char> &s)
{
    std::stack<char> tmp;
    while (!s.empty())
    {
        tmp.push(s.top());
        s.pop();
    }
    while (!tmp.empty())
    {
        std::cout << tmp.top() << " ";
        s.push(tmp.top());
        tmp.pop();
    }
    std::cout << std::endl;
}
