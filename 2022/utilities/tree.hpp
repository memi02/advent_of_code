#pragma once
#include <__nullptr>
#include <string>

template <typename data>
class Tree
{
private:
    data *d;
    Tree *sibling;
    Tree *child;
    Tree *parent;

public:
    Tree(data *in);
    ~Tree();

    data *read();
    void write(const data *in);

    Tree *getParent();
    Tree *leftMostChild();
    Tree *rightSibiling();

    void insertChild(Tree *t);
    void insertSibling(Tree *t);
    void deleteChild();
    void deleteSibling();

    Tree *findSon(data d);

    std::string toString(int spacing = 0);
};

#include "tree.inl"