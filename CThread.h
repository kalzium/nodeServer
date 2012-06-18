#pragma once
#include <boost/thread.hpp>
#include<iostream>
using namespace std;
class CThread
{
private:
	boost::thread* m_thread;
	// Variable that indicates to stop and the mutex to
	// synchronise "must stop" on (mutex explained later)
protected:
	bool m_mustStop;
	boost::mutex m_mustStopMutex;
public:
	void Start();
	void Stop();
	virtual void operator () ();
	virtual void loop(){};
public:
	CThread(void);
	~CThread(void);
};

