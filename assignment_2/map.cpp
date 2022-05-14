#include "map.hpp"

std::vector<float> map(const std::vector<float> v, map_mode mode, std::function<float(float)> f, int pardegree)
{
	int size = v.size();
	std::thread *thrs = new std::thread[pardegree];
	vector<float> out(size);
	std::mutex g_display_mutex;
	if(mode==map_mode::chunk)
	{
		// BLOCK MODE
		// starting with chunk version
		int chunk = size/pardegree;
		cout<<"Running info\n\t Vector size: "<<size<<"\n\t pardegree: "<<pardegree<<"\n\t chunk's size: "<<chunk<<endl;
		auto apply = [&](int st, int end){
			g_display_mutex.lock();
			cout<<"thread spawned "<<std::this_thread::get_id()<<"\n\t";
			cout<<"array start: "<<st<<"\n\tend: "<<end<<endl;
			g_display_mutex.unlock();
			for(int j=st; j<end; j++) 
			{
				g_display_mutex.lock();
				cout<<"Before: arr["<<j<<"]="<<v[j]<<"\n";
				g_display_mutex.unlock();
				out[j]=f(v[j]);
				g_display_mutex.lock();
				cout<<"After: arr["<<j<<"]="<<v[j]<<"\n";
				cout<<endl<<endl;
				g_display_mutex.unlock();
			}
		};

		for(int i = 0; i < pardegree; i++)
		{
			int start=i*chunk;
			int end=(i+1)*chunk;
			if(i == pardegree -1)
				end = size;
			thrs[i]= std::thread(apply,start,end);
		}

		for(int i = 0; i < pardegree; i++)
			thrs[i].join();
	}
	if(mode==map_mode::cyclic)	
	{
		auto apply = [&](int st){
				g_display_mutex.lock();
				cout<<"thread spawned "<<std::this_thread::get_id()<<"\n\t";
				cout<<"array start: "<<st<<endl;
				g_display_mutex.unlock();
				for(int j=st; j<size; j+=pardegree) 
				{
					g_display_mutex.lock();
					cout<<"Before: arr["<<j<<"]="<<v[j]<<"\n";
					g_display_mutex.unlock();
					out[j]=f(v[j]);
					g_display_mutex.lock();
					cout<<"After: arr["<<j<<"]="<<v[j]<<"\n";
					cout<<endl<<endl;
					g_display_mutex.unlock();
				}
			};


		//CYCLIC VERSION
		for(int i=0; i < pardegree; i++)
			thrs[i]=std::thread(apply,i);

		for(int i = 0; i < pardegree; i++)
			thrs[i].join();

	}
	return out;
}
