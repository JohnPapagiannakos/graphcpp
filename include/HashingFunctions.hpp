#ifndef HASHINGFUNCTIONS_HPP
#define HASHINGFUNCTIONS_HPP

// Quick & Dirty hashing based on Szudzik's function.
int pseudo_hash(const int a, const int b)
{
    return a >= b ? a * a + a + b : a + b * b;
}

#endif