#include <fstream>
#include <iostream>
#include <string>

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

    int max = 0, sum = 0;
    while (!in.eof())
    {
        std::string buffer;
        getline(in, buffer);
        if (buffer == "")
        {
            if (sum > max)
                max = sum;
            sum = 0;
        }
        else
        {
            sum += std::atoi(buffer.c_str());
        }
    }
    std::cout << max << std::endl;
    return 0;
}