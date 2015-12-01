//* Homework Rotarry Buffer for short term and long term moving averages *


/*
* CALEB GILL
* ECE470
* HW 0x0A
*/
#ifndef _RotaryBuffer
#define _RotaryBuffer

#include <cstddef>
#include <cmath>

template <typename T, std::size_t nLongAv, std::size_t nShortAv>
class RotaryBuffer
{
public:
    RotaryBuffer() : myBack(0), mySize(0) { }

    bool        empty() const { return(mySize == 0); }

    void        store(const T & value); //store (push) a new item, forget the oldest if necessary
    void        clear();                //discard all (pop all) data quickly
    bool        ready() const;          //check if at least myShortCapacity elements are held
    T           ShortAverage() const;   //average the last myShortCapacity elements
    T           LongAverage()  const;   //average all RotaryBuffer elements
private:
    static const std::size_t myCapacity = nLongAv;
    static const std::size_t myShortCapacity = nShortAv;
    T myArray[myCapacity];
    std::size_t myBack;
    std::size_t mySize;
    // additional variables might be needed for the sake of averaging operation efficiency
};

template <typename T, std::size_t nLongAv, std::size_t nShortAv>
void RotaryBuffer<T, nLongAv, nShortAv>::store(const T & value)
{
    myArray[myBack] = value;
    myBack = (myBack + 1) % myCapacity;
    if (mySize < myCapacity)
    {
        mySize++;
    }
}

template <typename T, std::size_t nLongAv, std::size_t nShortAv>
inline void RotaryBuffer<T, nLongAv, nShortAv>::clear()
{
    myBack = 0;
    mySize = 0;
}

template <typename T, std::size_t nLongAv, std::size_t nShortAv>
bool RotaryBuffer<T, nLongAv, nShortAv>::ready() const
{
    return (mySize >= myShortCapacity);
}

template <typename T, std::size_t nLongAv, std::size_t nShortAv>
T RotaryBuffer<T, nLongAv, nShortAv>::ShortAverage() const
{
    if (this->ready())
    {
        T sum = 0;

        size_t pos = (myBack==0) ? mySize - 1 : myBack - 1;
        
        for (size_t iter = myShortCapacity; iter > 0; iter--)
        {
            sum += myArray[pos];
            if (pos == 0)
            {
                pos = mySize - 1;
            }
            else
            {
                pos--;
            }
        }
        
        return sum / myShortCapacity;
    }
    else
    {
        cout << "Cannot compute short average; the buffer is not ready yet!" << endl;
    }
}

template <typename T, std::size_t nLongAv, std::size_t nShortAv>
T RotaryBuffer<T, nLongAv, nShortAv>::LongAverage() const
{
    T sum = 0;
    for (size_t iter = 0; iter < mySize; iter++)
    {
        sum += myArray[iter];
    }
    return sum / mySize;
}

#endif
