#include "DealingThread.h"

DealingThread* DealingThread::m_Self = new DealingThread();


DealingThread::DealingThread(void)
{
	
	m_MessageQueue = new MsgQueue();
}


DealingThread::~DealingThread(void)
{
	delete m_MessageQueue;
}

void DealingThread::loop()
{
	sock_ptr sockMS = ConnManagerThread::m_Self->m_ParentSocket;
	map<NodeID, sock_ptr> *sockCL = ConnManagerThread::m_Self->m_ChildSocketMap;
	if(sockMS != nullptr)
	{
		char nid[128] = "1";
		boost::shared_ptr<NodeID> temp(new NodeID(nid));
		MessageFactory mesg;
		Tag * t= mesg.Information_n2m(sockCL->size(), "101010", 10);
		sockMS->write_some(buffer(t->xml()));
		cout << "heartbeat has sent to the manage server" << endl;
		thread::sleep(get_system_time()+posix_time::seconds(INFOSEND_TIME));
	//cout<<"the info thread is working.  "<<endl;
	}
}
//
//void DealingThread::operator() ()
//{
//	bool mustStop;
//	do
//	{
//		this->loop();
//		// Get the "must stop" state (thread-safe)
//		m_mustStopMutex.lock();
//		mustStop=m_mustStop;
//		m_mustStopMutex.unlock();
//	}
//	while (mustStop==false);
//}