#pragma once

#include "CThread.h"
#include "MsgQueue.h"
#include "NodeID.h"
#include "ConnManagerThread.h"
#include "config.h"
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

typedef boost::shared_ptr<ip::tcp::socket> sock_ptr;

class DealingThread :public CThread
{
public:
	static DealingThread *m_Self;
	MsgQueue *m_MessageQueue;
public:
	DealingThread(void);
	~DealingThread(void);
	void loop();
	//void operator() ();
};

