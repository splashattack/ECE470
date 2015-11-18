//Caleb Gill
//ECE470 HW9

#include <iostream>
using namespace std;

template <typename T1, typename T2, typename T3> T3 dotProduct(const T1& A1, const T2& A2, size_t size, T3 inital);

int main()
{
    //Test 1
    int foo_int[5] = {1, 2, 3, 4, 5};
    int bar_int[5] = {5, 4, 3, 2, 1};
    int result1 = dotProduct(foo_int, bar_int, (size_t)5, (int)0);
    cout << result1 << endl;

    //Test 2
    long foo_long[3] = {3, 2, 1};
    short bar_short[3] = {5, 5, 5};
    long result2 = dotProduct(foo_long, bar_short, (size_t)3, (long)0);
    cout << result2 << endl;

    //Test 3
    double foo_double[10] = { 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
    double bar_double[10] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    double result3 = dotProduct(foo_double, bar_double, (size_t)10, (double)100);
    cout << result3 << endl;

    //Test 4
    double foo_double2[2] = {0.1, 0.2};
    float bar_double2[2] = {0.321, 0.456};
    double result4 = dotProduct(foo_double2, bar_double2, (size_t)2, (double)2);
    cout << result4 << endl;

    return 0;
}


template <typename T1, typename T2, typename T3> T3 dotProduct(const T1& A1, const T2& A2, size_t size, T3 inital)
{
    T3 product = inital;
    for (size_t i = 0; i < size; i++)
    {
        product += (A1[i] * A2[i]);
    }
    return product;
}