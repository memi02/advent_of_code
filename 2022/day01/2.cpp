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

    int max[3], sum = 0;
    for (int i = 0; i < 3; i++)
        max[i] = 0;

    while (!in.eof())
    {
        std::string buffer;
        getline(in, buffer);
        if (buffer == "")
        {
            int temp = sum;
            for (int i = 0; i < 3; i++)
                if (temp > max[i])
                    std::swap(temp, max[i]);
            sum = 0;
        }
        else
        {
            sum += std::atoi(buffer.c_str());
        }
    }
    int res = 0;
    for (int i = 0; i < 3; i++)
        res += max[i];
    std::cout << res << std::endl;
    return 0;
}