#include <iostream>
#include <memory>
#include "vect.h"
#include <string>
#include <cmath>
#include <utility>

std::allocator<double> Vect::alloc;

Vect::Vect(size_t n, double v, std::string const & vec_name) : ime(vec_name), mdata(nullptr),
                                                                mfirst_free(nullptr), mend(nullptr)
{
            std::cerr << "Ctor"<<std::endl;
            if(n > 0) {
                 mdata = alloc.allocate(n);
                 for(size_t i=0; i<n; ++i) alloc.construct(mdata+i, v);
                 mfirst_free = mend = mdata+n;
            }
}

void  Vect::print(std::ostream& out) const
{
    out<< ime << ": (" << size() << "," << capacity()<<") ";
    for(size_t i=0; i < size(); ++i) {
        out << mdata[i];
        if(i+1 < size()) out << ",";
    }
}

void Vect::push_back(double x){
    if( !has_space() )
        reallocate();
    alloc.construct(mfirst_free++, x);
}

void Vect::reallocate()
{
    //ako je vektor prazan
    if(capacity()==0)
    {
        mdata=alloc.allocate(1);
        mfirst_free=mdata;
        mend=mdata+1;
    }
    else
    {
        double* ptr;
        int n=capacity();
        ptr=alloc.allocate(2*n);
        std::uninitialized_copy(mdata, mfirst_free, ptr);
        free();
        mdata=ptr;
        mfirst_free=mdata+n;
        mend=mdata+2*n;
    }
}

void Vect::free()
{
    for(unsigned int i=0; i<size(); ++i) alloc.destroy(mdata+i);
    alloc.deallocate(mdata, capacity());
}

double Vect::norm2() const
{
    double d=0;
    for(unsigned int i=0; i<size(); ++i) d+=mdata[i]*mdata[i];
    return sqrt(d);
}


Vect& Vect::scale(double alpha)
{
    for (unsigned int i=0; i<size(); ++i)
        mdata[i]*=alpha;
    return *this;
}

Vect::Vect(const Vect& v)
{
    std::cout << "Pozvao se CCtor" << std::endl;
    mdata=alloc.allocate(v.capacity());   //alociramo novu memoriju
    std::uninitialized_copy(v.mdata, v.mfirst_free, mdata);  //prekopiramo podatke
    mfirst_free=mdata+v.size();
    mend=mdata+v.capacity();
    ime=v.ime;
}

Vect::Vect(Vect && v) noexcept
{
    std::cout << "pozvao se MCtor" << std::endl;
    ime=std::move(v.ime);
    v.ime.clear();
    mdata=v.mdata;
    mfirst_free=v.mfirst_free;
    mend=v.mend;
    v.mend=nullptr;
    v.mfirst_free=nullptr;
    v.mdata=nullptr;
}

Vect& Vect::operator=(const Vect& v)
{
    std::cout << "pozvao se operator pridruzivanja kopiranjem" << std::endl;
    if(this!=&v)   //samopridruzivanje
    {
        free();  //oslobodimo ono na sto je vektor pokazivao
        mdata=alloc.allocate(v.capacity());   //alociramo memoriju velicine tocno koliko je v
        std::uninitialized_copy(v.mdata, v.mfirst_free, mdata);   //kopiramo podatke
        mfirst_free=mdata+v.size();
        mend=mdata+v.capacity();
        ime=v.ime;
    }
    return *this;
}

Vect& Vect::operator=(Vect && v) noexcept
{

    std::cout << "pozvao se operator pridruzivanja premjestanjem" << std::endl;
    if(this!=&v)
    {
        free();
        mdata=v.mdata;
        mfirst_free=v.mfirst_free;
        mend=v.mend;
        ime=std::move(v.ime);
        v.mdata=nullptr;
        v.mfirst_free=nullptr;
        v.mend=nullptr;
        v.ime.clear();
    }
    return *this;
}
