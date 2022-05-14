/***
Assignment 1 (March 9): 

evaluate overhead needed to start/join a thread and to start an async (launch::async policy) and 
get the result of the computed future. 
Measures should be taken as averages of a large number of events. 
Possibly, measure times on your machine AND on the remote virtual machine.
To be completed by next Tue, March 15 (ideally).
*/

#include <thread>
#include <iostream>

using namespace std;

int main(int argc, char * argv[]) {
	if (argc == 1){
		cout<<"Please remeber usage: $./program numoftimestorepeat numofthreads \n";
		exit(1);
	}
	int t = atoi(argv[1]);
	int n = atoi(argv[2]);
	cout<<"The experiment will be executed "<<t<<" times and for "<<n<<" threads \n";
	//return 1;
	auto body = [] (int x) {
		cout<<"Thread n: "<<this_thread::get_id()<<endl;
		return;
    	};
	
	std::thread *tids = new std::thread[n];

	chrono::system_clock::time_point start = chrono::system_clock::now();
	for(int i = 0; i < t; t++){
		for(int j=0; j < n; j++)
			tids[j] = std::thread(body,j);

	//for(int i = 0; i < t; t++)
		for(int j=0; j < n; j++)
			tids[j].join();
	}
	auto stop = chrono::system_clock::now();
	auto elapsed = stop - start;
    auto musec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout<<"Fork/join time: "<<musec<<" usec"<<endl;
	

	return 0;

}

