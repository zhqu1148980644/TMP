#ifndef FACTORIAL
#define FACTORIAL


#ifndef TEST
#define TEST
#define TEST_FACTORIAL
#endif

#include <iostream>


// factorial ///////////////////////////////////////////////////////////////////////////////////////////       
// linear iteration 
long long factorial(size_t n)
{
    long long result = 1;
    while (n)
        result *= n--;
    return result;
}
// recursion
long long factorial(size_t n)
{
    if (n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}
// big number   base is 10  approximate result
#define MAX_N 10000000000
#define MAX_MANTISA (1e308/MAX_N)
struct bignum
{
    double n1;
    size_t n2;
};

bignum & factorial(size_t n)
{
    double MAX_POW10_LOG = floor(log10(1e308/MAX_N));
    double MAX_POW10 = pow(10, MAX_POW10_LOG);
    bignum p;
    p->n1 = 1;
    p->n2 = 0;
    for (size_t i = 1; i <= n; ++i)
    {
        if (p->n1 >= MAX_MANTISA)
        {
            p->n1 /= MAX_POW10;
            P->n2 += MAX_POW10_LOG;
        }
        p->n1 *= (double) i;
    }
} 
// big number base is 2  approximate result
typedef unsigned short word;
struct bignum
{
    double n1;
    size_t n2;
};

short get_exp_base(doube a) // get exp 
{
    word * pword = (word *)(&a) + 3;
    word rank = ((*pword & 0x7fff) >> 4);
    return (short)(rank - 0x3ff);
}

double get_mantissa(double a)  // get tail
{
    word * pword = (word *)(&a) + 3;
    *pword &= 0x800f;
    *pword |= 0x3ff0;
    return a;
}

bignum factorial(size_t n)
{
    bignum p = {1, 0};
    for (size_t i = 1; i <= n; ++i)
    {
        if (p->n1 >= MAX_MANTISA)
        {
            p->n2 = get_exp_base(p->n1);
            p->n1 = get_mantissa(p->n1);
        }
        p->n1 *= (double) i;
    }
    return p;
}

// real number
char * factorial(size_t n)
{
    size_t len = (n*log10((n + 1) / 2)) + 4;
    char * array = (char *)malloc(sizeof(char) * len);
    memset(array, 0, sizeof(char) * len);
    if (n < 2)
    {
        array[len - 1] = 1;
        return array;
    }
    size_t tail = len - 1;
    size_t head = len - 1;
    array[tail] = 1;
    for (size_t i = 2; i <= n; ++i)
    {
        size_t add = 0;
        for ( j = tail; j >= head; --j )
        {
            size_t pro = array[j] * i + add;
            array[j] = (char)(pro % 10);
            add = pro / 10; 
        }
        while ( add > 0 )
        {
            array[--head] = (char)(add % 10);
            add /= 10;
        }
    }
}

void print_fac(char * s)
{
    for (size_t len = strlen(s); s[len]; --len)
        cout << s[len];
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef TEST_FACTORIAL
int main()
{


}

#endif



#endif