#pragma once

#include "MsgQueue.h"
#include "CThread.h"

class ClientManagerThread:public CThread
{
public:
	static ClientManagerThread *m_Self;
	MsgQueue *m_MessagerQueue;
public:
	ClientManagerThread(void);
	~ClientManagerThread(void);
	void loop();
};

