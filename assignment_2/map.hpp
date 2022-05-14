#include<vector>
#include<functional>
#include<thread>
#include<iostream>
#include<mutex>

using namespace std;


enum class map_mode {
    chunk,
    cyclic
};

std::vector<float> map(const std::vector<float> v, map_mode mode, std::function<float(float)> f, int pardegree);
