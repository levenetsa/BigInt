#include "BigInteger.h"
#include <exception>
#include <stdlib.h>


BigInteger::BigInteger ()
{
    a.push_back(0);
    sign = true;
}
BigInteger::BigInteger (int t)
{
    if (t >= 0)
    {
        sign = true;
    }
    else
    {
        sign = false;
        t=-t;
    }
    a.push_back(t);
}

BigInteger::BigInteger (std::string const& st)
{
//string constructor
    std::string str="";
    str+=st;
    if (str[0]!='-')
    {
        sign = true;
    }
    else
    {
        sign = false;
        str=str.substr(1,str.length()-1);

    }
try{
    //incorrect input possible there
    for (int i=0;i<st.length() ;i++ )
        if (!isdigit(st[i]))
                throw "incorrect input";}
                catch(...){
        std::cout << "incorrect input"<<std::endl;
        return ;
    }



    int t;
    while(str.length()>3)
    {
        t=atoi(str.substr(str.length()-4,4).c_str());
        str=str.substr(0,str.length()-4);
        a.push_back(t);
    }
    if (str.length()>0)
    {

        t=atoi(str.c_str());
        a.push_back(t);
    }

}



BigInteger::BigInteger(BigInteger const& right)
{
    for (int i=0; i<right.a.size(); i++)
        a.push_back(right.a[i]);
    sign = right.sign;
}

std::ostream& operator<<(std::ostream& so, const BigInteger& consst)
{
    //out
    so<<toString(consst);
    return so;
}

std::istream& operator>>(std::istream& so, BigInteger& consst)
{
    //in
    std::string str;
    so>>str;
    consst =  BigInteger(str);
    // constructor from string can throw incorrect input

    return so;
}


std::string toString (BigInteger right)
{
    //reducting to string
    std::string current(""),ghj;
    if (!right.sign) current += "-";
    BigInteger d;
    int tk,amz;
    int size=right.a.size();
    for (int i=size-1; i>=0; i--)
    {
        tk=right.a[i];
        ghj=to_string(tk);
        if (i!=size-1)
        {
            amz=get_amz(tk);
            for(int j=0; j<amz; j++)
                current+="0";
        }
        current+=ghj;
    }
    return current;
}
int get_amz (int t)
{
    //get an amount of zeros in block
    if (t<10) return 3;
    if (t<100) return 2;
    if (t<1000) return 1;
    return 0;

}

std::string to_string (int t)
{
    //reducting block to string
    std::string out;
    if (t==0) return "0";
    while(t!=0)
    {
        out = (char)(t%10 + (int)'0') + out;
        t = t / 10;
    }
    return out;

}

BigInteger& BigInteger::operator+=(BigInteger const& right)
{

    BigInteger first(right);
    long check;
    int adding=0;
    int addingN;
    int size = std::max(a.size(),first.a.size());
    //additiont to one length
    if (a.size()<first.a.size())
    {
        for (int i=0; i<=size-a.size()+1; i++)
            a.push_back(0);
    }
    else
    {
        if (a.size()!=first.a.size())
            for (int i=0; i<=size-first.a.size()+1; i++)
                first.a.push_back(0);
    }
// sum cases + & +, - & +, + & -, - & -
    if (first.sign && sign||!first.sign && !sign)
    {
        for (int i=0; i<size; i++)
        {
            check=first.a[i]+a[i]+adding;
            if (check > 9999)
            {
                addingN=1;
                check-=10000;
            }
            else addingN=0;
            a[i]=(int)check;
            adding=addingN;
        }
        if (adding==1) a.push_back(1);
    }
    else
    {
        int comp = compare(*this,first);
        if (comp==0)
        {
            BigInteger c;
            a=c.a;
        }
        else
        {
            if (comp==-1)
            {
                if (sign==false)
                {
                    for (int i=0; i<size; i++)
                    {
                        check=first.a[i]-a[i]+adding;
                        if (check < 0)
                        {
                            addingN=-1;
                            check=10000+check;
                        }
                        else addingN=0;
                        a[i]=(int)check;
                        adding=addingN;
                    }
                    sign = true;
                }
                else
                {
                    for (int i=0; i<size; i++)
                    {
                        check=first.a[i]-a[i]+adding;
                        if (check < 0)
                        {
                            addingN=-1;
                            check=10000+check;
                        }
                        else addingN=0;
                        a[i]=(int)check;
                        adding=addingN;
                    }
                    sign =false;
                }
            }
            else
            {
                if (sign==false)
                {
                    for (int i=0; i<size; i++)
                    {
                        check=-first.a[i]+a[i]+adding;
                        if (check < 0)
                        {
                            addingN=-1;
                            check=10000+check;
                        }
                        else addingN=0;
                        a[i]=(int)check;
                        adding=addingN;
                    }
                    sign = false;
                }
                else
                {
                    for (int i=0; i<size; i++)
                    {
                        check=-first.a[i]+a[i]+adding;
                        if (check < 0)
                        {
                            addingN=-1;
                            check=10000+check;
                        }
                        else addingN=0;
                        a[i]=(int)check;
                        adding=addingN;
                    }
                    sign =true;
                }
            }
        }

    }
    while(a.size()!=1&&a.back()==0)
        a.pop_back();

}

int compare (BigInteger ab,BigInteger bb)
{
    //compare by abs
    int size = std::max(ab.a.size(),bb.a.size());
    for (int i=0; i<size-ab.a.size(); i++)
        ab.a.push_back(0);
    for (int i=0; i<size-bb.a.size(); i++)
        bb.a.push_back(0);
    for (int i=size-1; i>=0; i--)
    {
        if (ab.a[i]>bb.a[i]) return 1;
        if (ab.a[i]<bb.a[i]) return -1;
    }
    return 0;
}

BigInteger operator+(BigInteger l,BigInteger const& right)
{
    BigInteger b(l);
    b+=right;
    return b ;
}

BigInteger operator-(BigInteger l,BigInteger const& right)
{
    BigInteger b(l);
    b-=right;
    return b ;
}

BigInteger& BigInteger::operator=(BigInteger const& right)
{
    BigInteger b(right);

    a=b.a;
    sign=b.sign;
    return b;
}


BigInteger& BigInteger::operator-=(BigInteger const& right)
{
    BigInteger m(right);
    m.sign= !m.sign;
    *this+=m;
}



BigInteger& BigInteger::operator*=(BigInteger const& right)
{
    //multiplication
    BigInteger c;
    c.sign=(sign==right.sign);
    int length=a.size()+right.a.size()+1;
    int buffer,adding;
    for(int i=0; i<=length; i++)
        c.a.push_back(0);
    for (int ix = 0; ix <a.size() ; ix++)
        for (int jx = 0; jx < right.a.size(); jx++)
        {
            buffer=a[ix] * right.a[jx];
            adding=buffer%10000;
            buffer=buffer/10000;
            c.a[ix + jx] += adding;
            int z=ix+jx;
            while (z<length&&c.a[z]>=10000)
            {
                c.a[z+1]=c.a[z]/10000;
                c.a[z]%=10000;
            }
            c.a[ix+jx+1]+=buffer;
            z=ix+jx+1;
            while (z<length&&c.a[z]>=10000)
            {
                c.a[z+1]=c.a[z]/10000;
                c.a[z]%=10000;
            }
        }
    while(c.a.size()!=1&&c.a.back()==0)
        c.a.pop_back();
    *this=c;
}
BigInteger& BigInteger::operator*(BigInteger const& right)
{
    BigInteger t(*this);

    t*=right;
    BigInteger *n = new BigInteger(t);
    return *n;
}











