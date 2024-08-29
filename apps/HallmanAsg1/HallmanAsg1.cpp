//File: HallmanAsg1.cpp
//Author: Jackson Hallman
//Student Num: 00102945
//Email: jhallma5@my.athens.edu

#include <iostream>
#include <cstdlib>   
#include <ctime>     
#include <algorithm> 


void FillWithRandomNumbers(int data[], int size)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < size; ++i)
    {
        data[i] = std::rand() % 100001;
    }
}


void SortTheArray(int data[], int size)
{
    bool swapped;
    for (int i = 0; i < size - 1; ++i)
    {
        swapped = false;
        for (int j = 0; j < size - i - 1; ++j)
        {
            if (data[j] > data[j + 1])
            {
                std::swap(data[j], data[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
}

int main() {
    const int SIZE = 10;
    int data[SIZE];

    FillWithRandomNumbers(data, SIZE);

    std::cout << "Before sorting:\n";
    for (int i = 0; i < SIZE; ++i)
    {
        std::cout << data[i] << " ";
    }

    std::cout << std::endl;

    SortTheArray(data, SIZE);

    std::cout << "After sorting:\n";
    for (int i = 0; i < SIZE; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}