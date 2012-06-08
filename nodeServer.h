/*
 * File:   nodeServer.h
 * Author: chenkexin
 *
 * Created on 2012.6.5
 */

///
///main class function:
///1.waiting the clients to connect
///2.start connect to MS
///3.srart working threads
///
#ifndef NODESERVER_H_
#define NODESERVER_H_

#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <../../gloox-0.9.9.12/src/tag.h>
#include <../../gloox-0.9.9.12/src/parser.h>
#include <../../gloox-0.9.9.12/src/taghandler.h>
#include "heartBeatThread.h"
#include "infoThread.h"

using namespace std;
using namespace boost::asio;
using namespace boost;
using namespace gloox;

extern void heartBeatFunc();
extern void infoFunc();

class nodeServer:public TagHandler
{
    io_service &ios;
    ip::tcp::acceptor acceptor;
    ip::tcp::endpoint toEndpoint;
    typedef shared_ptr<ip::tcp::socket> sock_ptr;
    typedef shared_ptr<Tag> tag_ptr;

    //private member: the function thread message queue
    msgQueue* hbQueue;
    msgQueue* itQueue;

    //parser to parse the XML data
    Parser* p;

    //the receive data buffer
    char data[100];

    //a control sign
    //to state if the socket has been initialized correctly.
    //namely, possess a NID or generate a unique code to get a NID
    bool isInitial;

public:
    nodeServer(io_service &io):
        ios(io),
        acceptor(ios,ip::tcp::endpoint(ip::tcp::v4(),6688)),
        toEndpoint(ip::address::from_string("127.0.0.1"),6628)
    {
        //toEndpoint(ip::address::from_string("127.0.0.1"),6628);

//        it= new infoThread();
//        hb = new heartBeatThread();
        hbQueue = new msgQueue();
        itQueue = new msgQueue();
        p = new Parser(this);
        isInitial = false;
        start();
    }
    virtual ~nodeServer()
    {
        delete hbQueue;
        delete itQueue;
        delete p;
    }
    void start();
    void accept_handler(const system::error_code& ec,sock_ptr sock);
    void connect_handler(const system::error_code& ec, sock_ptr sock);
    void read_handler(const system::error_code& ec, char* data,sock_ptr sock);
    virtual void handleTag(Tag* t);
    int getType(Tag* t);
};
#endif
