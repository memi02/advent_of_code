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
    int tot = 0;
    std::string buffer;

    while (getline(in, buffer))
    {
        int start1, end1, start2, end2;

        start1 = std::stoi(buffer.substr(0, buffer.find_first_of('-')));
        end1 = std::stoi(buffer.substr(buffer.find_first_of('-') + 1, buffer.find_first_of('-') - buffer.find_first_of(',')));
        start2 = std::stoi(buffer.substr(buffer.find_first_of(',') + 1, buffer.find_first_of(',') - buffer.find_last_of('-')));
        end2 = std::stoi(buffer.substr(buffer.find_last_of('-') + 1, buffer.find_first_of('-') - buffer.size()));

        // std::cout << start1 << " " << end1 << " " << start2 << " " << end2 << " " << buffer << std::endl;
        if (start1 <= start2 && end1 >= end2)
        {
            tot++;
            // std::cout << start1 << " " << end1 << " " << start2 << " " << end2 << " " << buffer << std::endl;
        }
        else if (start1 >= start2 && end1 <= end2)
        {
            tot++;
            // std::cout << start1 << " " << end1 << " " << start2 << " " << end2 << " " << buffer << std::endl;
        }
    }
    std::cout << tot << std::endl;
    /*
    std::fstream out;
    out.open("output.txt", std::ios::out);
    */

    in.close();
    return 0;
}
