/*
 * File:   main.cpp
 * Author: chenkexin
 *
 * Created on 2012.6.3
 */

#include <iostream>
#include "message.h"

#include <fstream>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <../../gloox-0.9.9.12/src/tag.h>
#include "message.h"
#include "messageQueue.h"
#include "nodeServer.h"

////////////////////////////////////////
using namespace gloox;
using namespace boost::asio;
using namespace boost;
using namespace std;

extern void heartBeatFunc();
int main()
{

//each thread holds the same message queue,
//all the threads do is selecting message from the public message queue
//and do the real process work, and send back the result to the client.
    io_service s;
    nodeServer* ns = new nodeServer(s);
    s.run();

    return 0;
}
