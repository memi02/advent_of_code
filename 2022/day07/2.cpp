#include <fstream>
#include <iostream>
#include <string>
#include "../utilities/tree.hpp"

class data
{
private:
    int size;
    std::string name;

    bool isDir;

public:
    data() {}

    data(const std::string n, const int s, const bool d)
    {
        size = s;
        name = n;
        isDir = d;
    }

    int
    getSize() { return size; }
    void setSize(const int in) { size = in; }

    std::string getName() { return name; }
    void setName(const std::string in) { name = in; }

    bool isaDir() { return isDir; }

    bool operator==(const data &d) const { return (d.name == name && d.isDir == isDir); }

    std::string toString()
    {
        std::string res;
        res += name + " (" + std::to_string(size) + ")";
        return res;
    }
};

void calculateSize(Tree<data> *t);
int findSmallest(Tree<data> *t, int size);

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

    Tree<data> *root = new Tree<data>(new data("/", 0, true));
    Tree<data> *current = root;

    getline(in, buffer);
    while (!in.eof())
    {
        // std::cout << root->toString();
        if (buffer.substr(2, 2) == "cd")
        {
            // this is a command to move around the tree
            std::string address = buffer.substr(5);
            if (address == "/")
            {
                current = root;
            }
            else if (address == "..")
            {
                current = current->getParent();
            }
            else
            {
                current = current->findSon(data(address, 0, true));
            }
            getline(in, buffer);
        }
        else
        {
            // this is a command to list all the items in a folder
            bool cont = true;
            while (cont)
            {
                getline(in, buffer);
                if (in.eof())
                {
                    cont = false;
                }
                if (buffer.front() == '$')
                {
                    cont = false;
                }
                else
                {
                    std::string first = buffer.substr(0, buffer.find(" "));
                    std::string second = buffer.substr(buffer.find(" ") + 1);
                    if (first == "dir")
                        current->insertChild(new Tree<data>(new data(second, 0, true)));
                    else
                        current->insertChild(new Tree<data>(new data(second, stoi(first), false)));
                }
            }
        }
    }
    std::cout << root->toString();
    calculateSize(root);
    std::cout << root->toString();
    std::cout << findSmallest(root, 30000000 - (70000000 - root->read()->getSize()));
    in.close();
    return 0;
}

void calculateSize(Tree<data> *t)
{
    if (t != nullptr)
    {
        int sum = 0;
        Tree<data> *tmp = t->leftMostChild();
        while (tmp != nullptr)
        {
            calculateSize(tmp);
            sum += tmp->read()->getSize();
            tmp = tmp->rightSibiling();
        }
        if (t->read()->isaDir())
        {
            t->read()->setSize(sum);
        }
    }
}

int findSmallest(Tree<data> *t, int size)
{
    int min = INT_MAX;

    if (t != nullptr)
    {
        Tree<data> *tmp = t->leftMostChild();
        while (tmp != nullptr)
        {
            min = std::min(min, findSmallest(tmp, size));
            if (tmp->read()->getSize() < min && tmp->read()->getSize() > size && tmp->read()->isaDir())
            {
                min = tmp->read()->getSize();
            }
            tmp = tmp->rightSibiling();
        }
    }
    return min;
}