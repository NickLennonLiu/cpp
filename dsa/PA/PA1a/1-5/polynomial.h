#pragma once
#include <iostream>
using namespace std;
#define poly Polynomial

#define M 1000000007

#define Plus(a,b) ((a)+(b))%M
#define Multiply(a,b) ((long long)(a)*(long long)(b)) % M
#define Minus(a,b) ((a)-(b)+M)%M
#define max(a,b) (((a) > (b))?(a):(b))
#define min(a,b) (((a) < (b))?(a):(b))

class Polynomial
{
    int c[66];
    //int *c;
    int highest;
    int _type;
public:
    Polynomial()
    : highest(0)
    {}
    Polynomial (int c0,int type=0)
    : _type(type)
    {
        highest = 0;
        if(type==0 || type==1)
        {
            for(int i = 0; i < 66; ++i) c[i] = 0;
            c[0] = c0;
            if(type==1)
            {
                _type = 0;
                c[1] = 1;
                highest = 1;
            }
        } 
    }
    Polynomial operator+(const Polynomial &b);
    Polynomial operator-(const Polynomial &b);
    Polynomial operator*(const Polynomial &b);
    Polynomial(const Polynomial& b)
    {
        _type = b._type;
        highest = b.highest;
        if(_type==0 || _type==1)
        {
            for(int i = 0;i < 66;i++) 
            {
                c[i] = b.c[i];
            }
        }
        
    }
    Polynomial operator^(int pow);
    int coeffecient(int const& pow){return c[pow];}
    int rank() const {return highest;}
    int type() const {return _type;}
};

void Poly_Print(Polynomial C)
{
    cout << "rank:" << C.rank() <<" Coefficients: ";
    for (int i = C.rank(); i >= 0; --i)
    {
        cout << C.coeffecient(i) << " ";
    }
    cout << endl;
}

poly poly::operator+(const poly& b)
{
    poly C(0,0);
    int h = max(highest, b.highest);
    for(int i = 0;i <= h; ++i)
    {
        C.c[i] = Plus(c[i],b.c[i]);
    }
    C.highest = h;
    //cout << "Plus------" << endl;
    //Poly_Print(C);
    return C;
}

poly poly::operator*(const poly & b)
{
    poly C(0,0);
    C.highest = highest + b.highest;
    for(int i = 0; i<= highest; ++i)
    {
        for(int j = 0; j<= b.highest; ++j)
        {
            C.c[i+j] = Plus(C.c[i+j], Multiply(c[i],b.c[j]));
        }
    }
    
    //cout << "Multiply------" << endl;
    //Poly_Print(C);
    return C;
}

poly poly::operator-(const poly & b)
{
    poly C(0,0);
    C.highest = max(highest, b.highest);
    for(int i = 0; i <= C.highest; ++i)
    {
        C.c[i] = Minus(c[i],b.c[i]);
    }
    while(C.highest && !C.c[C.highest]) C.highest--;
    cout << "Minus------" << endl;
    //Poly_Print(C);
    return C;
}

poly poly::operator^(int pow)
{
    Polynomial C = *this;
    while(--pow)
    {
        C = C*(*this);
    }
    cout << "Power------" << endl;
    //Poly_Print(C);
    return C;
}