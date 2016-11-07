#ifndef MRPRIME_H
#define MRPRIME_H

#include <cstdlib>

int modMultiply(int a, int b, int m)
{
    return a * b % m;
}

int modPow(int a, int b, int m)
{
    int v = 1;
    for (int p = a % m; b > 0; b >>= 1, p = modMultiply(p, p, m))
        if (b & 1)
            v = modMultiply(v, p, m);
    return v;
}

bool witness(int a, int n)
{
    int n1 = n - 1, s2 = n1 & -n1, x = modPow(a, n1 / s2, n);
    if (x == 1 || x == n1) return false;
    for (; s2 > 1; s2 >>= 1)
    {
        x = modMultiply(x, x, n);
        if (x == 1)
            return true;
        if (x == n1)
            return false;
    }
    return true;
}

int random(int high)
{
    return (int)(high * (rand() / (double)RAND_MAX));
}

bool probablyPrime(int n, int k)
{
    if (n == 2 || n == 3)
        return true;
    if (n < 2 || n % 2 == 0)
        return false;
    while (k-- > 0)
        if (witness(random(n - 3) + 2, n))
            return false;
    return true;
}

int nextPrime(int x)
{
   int i = x;
   while(1)
   {
       if(probablyPrime(++i,2))
       {
          break;
       }
   }
   return i;
}

#endif // MRPRIME_H
