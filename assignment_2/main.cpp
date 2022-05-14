/* Assigment 2 (March 16): 
 * provide a vector<float> map(vector<float>v, int mode, function<float(float)> f, int pardegree) computing in parallel 
 * (using C++ threads or asyncs) the map(f) over v. 
 * Mode is 0 (block) or 1 (cyclic) scheduling.  
 * To be completed by next Tue, March 22 (ideally).
 * 
 */
#include<vector>
#include<functional>
#include<iostream>
#include "map.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	std::vector<float> v = { 7, 5, 16, 8, 14.2 };
	cout<<"Initial vector: \n";
	for (float i: v)
	    std::cout << i << ' ';
	cout<<endl;

	auto f = [](float x){ return x*2; };
	std::vector<float> o = map(v,map_mode::cyclic,f,2);
	cout<<"Final vector: \n";
	for (float i: o)
	    std::cout << i << ' ';
	cout<<endl;



	return 0;
}
