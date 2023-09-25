#include <iostream>
#include <cmath>
#include "bits.h"
#include "limits"

using namespace std;

float Q_rsqrt( float number )
{
    const float x2 = number * 0.5F;
    const float threehalfs = 1.5F;

    union {
        float f;
        uint32_t i;
    } conv = {number}; // member 'f' set to value of 'number'.
    conv.i = 0x5f3759df - ( conv.i >> 1 );
    conv.f *= threehalfs - x2 * conv.f * conv.f;
    return conv.f;
}
/*float Q_rsqrt( float number )
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;                       // evil floating point bit level hacking
    i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
    y  = * ( float * ) &i;
    y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

    return y;
}*/

int main() {
    float x;
    cin >> x;
    cout << Q_rsqrt(x) << endl;
    cout << 1 / Q_rsqrt(x) << endl;
    cout << sqrtf(x) << endl;
    cout << 1/ sqrtf(x);
}