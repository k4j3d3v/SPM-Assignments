/***
Assignment 1 (March 9): 

evaluate overhead needed to start/join a thread and to start an async (launch::async policy) and 
get the result of the computed future. 
Measures should be taken as averages of a large number of events. 
Possibly, measure times on your machine AND on the remote virtual machine.
To be completed by next Tue, March 15 (ideally).
*/

#include <thread>
#include <future>
#include <iostream>

using namespace std;

int main(int argc, char * argv[]) {
	if (argc == 1){
		cout<<"Please remeber usage: $./program numoftimestorepeat numofthreads \n";
		exit(1);
	}
	int t = atoi(argv[1]);
	int n = atoi(argv[2]);
	cout<<"Just spawning "<<n<<" workers, for "<<t<<" times \n";
	//return 1;
	auto body = [] (int x) {
		return;
    	};
	
	std::thread *tids = new std::thread[n];
	
	chrono::system_clock::time_point start = chrono::system_clock::now();
	for(int i = 0; i < t; i++){
		// spawing/creating and storing reference
		for(int j=0; j < n; j++)
		{
			tids[j] = std::thread(body,1);
		}
		// joining instanciated threads
		for(int j=0; j < n; j++)
			tids[j].join();
	}
	auto stop = chrono::system_clock::now();
	auto elapsed = stop - start;
    auto musec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout<<"AVG fork/join time: "<<(musec/t/n)<<" usec"<<endl;
	
	std::future<void> *futs = new std::future<void>[n]; 
	// asyncs scenario
	start = chrono::system_clock::now();
	for(int j=0; j<t; j++)
	{
		for(int i=0; i<n; i++) 
			futs[i] = async(launch::async, body, 1);
	    // asycn launched, now wait results
		for(int i=0; i<n; i++)
			try {
				futs[i].get();
		        } catch (const std::exception& e) {
			      cout << "Got " << e.what() << " i= " << i << endl; 
			}
	}
	stop = chrono::system_clock::now();
	musec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout<<"AVG asyncs time: "<<(musec/t/n)<<" usec"<<endl;
	
	return 0;

}

