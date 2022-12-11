#pragma once

template <typename data>
Tree<data>::Tree(data *in)
{
    sibling = nullptr;
    child = nullptr;
    parent = nullptr;
    d = in;
}

template <typename data>
Tree<data>::~Tree()
{
    delete d;
}

template <typename data>
data *Tree<data>::read()
{
    return d;
}

template <typename data>
void Tree<data>::write(const data *in)
{
    d = in;
}

template <typename data>
Tree<data> *Tree<data>::getParent()
{
    return parent;
}

template <typename data>
Tree<data> *Tree<data>::leftMostChild()
{
    return child;
}

template <typename data>
Tree<data> *Tree<data>::rightSibiling()
{
    return sibling;
}

template <typename data>
void Tree<data>::insertChild(Tree<data> *t)
{
    t->parent = this;
    t->sibling = child;
    child = t;
}

template <typename data>
void Tree<data>::insertSibling(Tree<data> *t)
{
    t->parent = parent;
    t->sibling = sibling;
    sibling = t;
}

template <typename data>
void Tree<data>::deleteChild()
{
    Tree<data> newChild = child->rightSibling();
    delete child;
    child = newChild;
}

template <typename data>
void Tree<data>::deleteSibling()
{
    Tree newSibling = sibling->rightSibling();
    delete sibling();
    sibling = newSibling();
}

template <typename data>
Tree<data> *Tree<data>::findSon(data d)
{
    Tree<data> *tmp = child;
    while (tmp != nullptr)
    {
        if (d == *tmp->read())
            return tmp;
        tmp = tmp->rightSibiling();
    }
    return nullptr;
}

template <typename data>
std::string Tree<data>::toString(int spacing)
{
    std::string res;
    for (int i = 0; i < spacing; i++)
    {
        res += " ";
    }
    res += read()->toString() += '\n';

    Tree *current = leftMostChild();
    while (current != nullptr)
    {
        res += current->toString(spacing + 1);
        current = current->rightSibiling();
    }

    return res;
}