#include "CThread.h"


CThread::CThread(void)
{
	m_thread=NULL;
	m_mustStop=false;
}


CThread::~CThread(void)
{
	if (m_thread!=NULL) delete m_thread;
}

// Start the thread
void CThread::Start()
{
	m_thread=new boost::thread(boost::ref(*this));
}

void CThread::operator () (){
	bool mustStop;
 
	do
	{
		this->loop();
 
		// Get the "must stop" state (thread-safe)
		m_mustStopMutex.lock();
		mustStop=m_mustStop;
		m_mustStopMutex.unlock();
	}
	while (mustStop==false);
}

void CThread::Stop()
{
	// Signal the thread to stop (thread-safe)
	m_mustStopMutex.lock();
	m_mustStop=true;
	m_mustStopMutex.unlock();
 
	// Wait for the thread to finish.
	if (m_thread!=NULL) m_thread->join();
}
