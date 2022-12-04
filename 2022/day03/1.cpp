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

    std::string buffer;
    int tot = 0;
    while (getline(in, buffer))
    {
        int comp1[50], comp2[50];
        int l = buffer.length() / 2;
        for (int i = 0; i < l; i++)
        {
            char tmp = buffer.back();
            if ('a' <= tmp && tmp <= 'z')
            {
                comp2[i] = tmp - 'a' + 1;
            }
            else
            {
                comp2[i] = tmp - 'A' + 27;
            }
            buffer.pop_back();
        }
        for (int i = 0; i < l; i++)
        {
            char tmp = buffer.back();
            if ('a' <= tmp && tmp <= 'z')
            {
                comp1[i] = tmp - 'a' + 1;
            }
            else
            {
                comp1[i] = tmp - 'A' + 27;
            }
            buffer.pop_back();
        }
        bool cont = true;
        int value = 0;
        for (int i = 0; i < l && cont; i++)
        {
            for (int j = 0; j < l && cont; j++)
            {
                if (comp1[i] == comp2[j])
                {
                    value = comp1[i];
                    cont = false;
                }
            }
        }
        tot += value;

        // std::cout << value << std::endl;
        // for (int i = 0; i < l; i++)
        // {
        //     std::cout << comp1[i] << " ";
        // }
        // std::cout << std::endl;
        // for (int i = 0; i < l; i++)
        // {
        //     std::cout << comp2[i] << " ";
        // }
        // std::cout << std::endl;
    }
    std::cout << tot << std::endl;
    in.close();
    return 0;
}
