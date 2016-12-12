#include <iostream>
#include "BT.h"
using iterator = GridLeafIterator;
void Segment::refine()
{
    if(isLeaf())
    {
        Segment* i1 = new Segment(mpt_l, (mpt_l+mpt_r)/2, this);
        Segment* i2= new Segment((mpt_l+mpt_r)/2, mpt_r,  this);
        mseg_l.reset(i1);
        mseg_r.reset(i2);
    }
}

void Segment::coarse()
{
    Segment *l, *d;
    l=getLeft();
    d=getRight();
    try
    {
        if(!(l->isLeaf() || d->isLeaf()))
            throw std::runtime_error("ne mozemo okrupniti segment");
        mseg_l.release();
        mseg_r.release();
    }
    catch(std::runtime_error const & e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

/*void popuni_stog(Segment *pocetak)
{
    if(pocetak==nullptr)return;
    popuni_stog(pocetak->getLeft());
    stog.push(pocetak);
    popuni_stog(pocetak->getRight());



}*/
iterator Grid::begin()
{
    Segment *tmp=&root;
    while(tmp->getLeft()!=nullptr)
        tmp=tmp->getLeft();
    iterator it(&root, tmp);
    return it;

    //popuni_stog(&root);

}
iterator Grid::end()
{
    iterator it(&root, nullptr);
    return it;
}

GridLeafIterator& GridLeafIterator::operator++()
{
    Segment *roditelj=mCurrent->parent();
    if(roditelj==nullptr)
    {
        mCurrent=roditelj;
        return *this;
    }
    while(mCurrent==roditelj->getRight())
    {
        mCurrent=roditelj;
        roditelj=roditelj->parent();
        if(roditelj==nullptr)break;
    }
    if(roditelj==nullptr)
    {
        mCurrent=nullptr;
        return *this;
    }
    mCurrent=roditelj->getRight();
    while(mCurrent->getLeft()!=nullptr)
        mCurrent=mCurrent->getLeft();
    return *this;
}

bool operator==(GridLeafIterator const & lhs, GridLeafIterator const & rhs)
{
    if(lhs.mRoot==rhs.mRoot && lhs.mCurrent==rhs.mCurrent) return  true;
    return false;
}

bool operator!=(GridLeafIterator const & lhs, GridLeafIterator const & rhs)
{
    if(lhs.mRoot!=rhs.mRoot || lhs.mCurrent!=rhs.mCurrent) return  true;
    return false;
}


void Grid::print()
{
    for(iterator it=begin(); it!=end(); ++it)
        it->print();

}

void Grid::uniform_refine()
{
    for(iterator it=begin(); it!=end(); ++it)
        it->refine();
}

int  Grid::nOfSegments()
{
    int k=0;
    for(iterator it=begin(); it!=end(); ++it)
        ++k;
    return k;
}

void Grid::refine_selected(int noSeg)
{
    try
    {
        int k=0;
        if(nOfSegments()<=noSeg)
            throw std::runtime_error("zadani segment ne postoji");
        for(iterator it=begin(); it!=end(); ++it)
        {
            if(k==noSeg)
            {
                it->refine();
                break;
            }
            else ++k;
        }
    }
    catch(std::runtime_error const & e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
}


void Grid::coarse_selected(int noSeg)
{
    try
    {
        int k=0;
        if(nOfSegments()<=noSeg)
            throw std::runtime_error("zadani segment ne postoji");
        for(iterator it=begin(); it!=end(); ++it)
        {
            if(k==noSeg)
            {
                Segment* roditelj=it->parent();
                roditelj->coarse();
                break;
            }
            else ++k;
        }
    }
    catch(std::runtime_error const & e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
