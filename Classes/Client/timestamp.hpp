#ifndef _Timestamp_hpp_
#define _Timestamp_hpp_

#include<chrono>
using namespace std::chrono;

class Timestamp
{
public:
	Timestamp()
    {
		update();
    }
	~Timestamp()
    {
	}

    void update()
    {
		_begin = high_resolution_clock::now();
    }

    /**
    *   ªÒ»°√Ó
    */
    long long getElapsedTimeInMicroSec()
    {
		return duration_cast<seconds>(high_resolution_clock::now() - _begin).count();
    }
protected:
	time_point<high_resolution_clock> _begin;
};

#endif // !_Timestamp_hpp_