#include <fstream>
#include <iostream>

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

    std::string possibleResults[9];
    possibleResults[0] = "AXB 2";
    possibleResults[1] = "BXC 3";
    possibleResults[2] = "CXA 1";
    possibleResults[3] = "AYA 4";
    possibleResults[4] = "BYB 5";
    possibleResults[5] = "CYC 6";
    possibleResults[6] = "AZC 9";
    possibleResults[7] = "BZA 7";
    possibleResults[8] = "CZB 8";
    std::string buffer;
    while (getline(in, buffer))
    {
        bool matched = false;
        for (int i = 0; i < 9; i++)
        {
            if (possibleResults[i] == buffer)
            {
                matched = true;
            }
        }
        if (!matched)
        {
            std::cout << buffer << std::endl;
        }
    }

    in.close();
    return 0;
}
