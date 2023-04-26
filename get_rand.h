#pragma once
#include <iostream>
#include <string>

using namespace std;

int GetRandomNumber(int min, int max){
    srand(time(NULL));
    int num = min + rand() % (max - min + 1);
    return num;
}