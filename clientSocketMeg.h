/*
 * File:   clientSocketMeg.h
 * Author: zhangxiaobo
 *
 * Created on 2012.6.12
 */

#ifndef CLIENTSOCKETMEG_H_
#define CLIENTSOCKETMEG_H_

#include <boost/timer.hpp>
#include <boost/asio.hpp>

using namespace boost::asio;
using namespace boost;

typedef boost::shared_ptr<ip::tcp::socket> sock_ptr;

const double CONNECT_FAIL_TIME = 10.0;

class clientSocketMeg
{
private:
	timer t;
	sock_ptr sock;

public:
	clientSocketMeg(sock_ptr);
	~clientSocketMeg();
	double getTime();
	void setSock(sock_ptr &_sock);
	sock_ptr getSock();
};

#endif