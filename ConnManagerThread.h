#pragma once

#include "CThread.h"
#include "NodeID.h"
#include "MessageHandler.h"
#include "HeartBeatThread.h"

#include <map>
#include <boost/asio.hpp>


using namespace std;
using namespace boost;
using namespace boost::asio;
using namespace gloox;

typedef boost::shared_ptr<ip::tcp::socket> sock_ptr;
typedef boost::shared_ptr<Tag> tag_ptr;
typedef boost::shared_ptr<timer> timer_ptr;

class ConnManagerThread :public CThread
{

public:
	static ConnManagerThread *m_Self;
	map<NodeID, sock_ptr> *m_ChildSocketMap;
	sock_ptr m_ParentSocket;	
private:
	MessageHandler* m_MessageHandler;
	io_service &m_Ios;
    ip::tcp::acceptor m_Acceptor;
    ip::tcp::endpoint m_ToEndpoint;
	char m_ReceiveBuffer[128];
public:
	ConnManagerThread(io_service&, string, int);
	~ConnManagerThread(void);
	void operator()();
	void connect();
	void listen();
	void onConnected(const system::error_code&, sock_ptr);
	void onRead(const system::error_code&, char*, sock_ptr);
	void onAccepted(const system::error_code&,sock_ptr);
};

