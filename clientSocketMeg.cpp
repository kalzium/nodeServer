/*
 * File:   clientSocketMeg.cpp
 * Author: zhangxiaobo
 *
 * Created on 2012.6.12
 */
#include "clientSocketMeg.h"

typedef boost::shared_ptr<ip::tcp::socket> sock_ptr;

clientSocketMeg::clientSocketMeg(sock_ptr _sock)
{
	sock = _sock;
}

clientSocketMeg::~clientSocketMeg()
{
}

double clientSocketMeg::getTime()
{
	double temp = t.elapsed();
	t.restart();
	return temp;
}

void clientSocketMeg::setSock(sock_ptr &_sock)
{
	sock = _sock;
}

sock_ptr clientSocketMeg::getSock()
{
	return sock;
}