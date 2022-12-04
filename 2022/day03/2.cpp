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
        int comp1[50], comp2[50], comp3[50];
        int l1, l2, l3;

        l1 = buffer.length();
        for (int i = 0; i < l1; i++)
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

        getline(in, buffer);
        l2 = buffer.length();
        for (int i = 0; i < l2; i++)
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

        getline(in, buffer);
        l3 = buffer.length();
        for (int i = 0; i < l3; i++)
        {
            char tmp = buffer.back();
            if ('a' <= tmp && tmp <= 'z')
            {
                comp3[i] = tmp - 'a' + 1;
            }
            else
            {
                comp3[i] = tmp - 'A' + 27;
            }
            buffer.pop_back();
        }
        bool cont = true;
        int value = 0;
        for (int i = 0; i < l1 && cont; i++)
        {
            for (int j = 0; j < l2 && cont; j++)
            {
                if (comp1[i] == comp2[j])
                {
                    for (int k = 0; k < l3 && cont; k++)
                    {
                        if (comp2[j] == comp3[k])
                        {
                            value = comp3[k];
                            cont = false;
                        }
                    }
                }
            }
        }
        tot += value;

        // std::cout << value << std::endl;
    }
    std::cout << tot << std::endl;
    in.close();
    return 0;
}
