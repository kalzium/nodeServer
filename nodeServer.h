/*
 * File:   nodeServer.h
 * Author: chenkexin
 *
 * Created on 2012.6.5
 */

#ifndef NODESERVER_H_
#define NODESERVER_H_

#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <../../gloox-0.9.9.12/src/tag.h>
#include <../../gloox-0.9.9.12/src/parser.h>
#include <../../gloox-0.9.9.12/src/taghandler.h>
#include "messageQueue.h"
#include "snMap.h"

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

    //holds the online client infos
    snMap* online;

public:
    nodeServer(io_service &io):
        ios(io),
        acceptor(ios,ip::tcp::endpoint(ip::tcp::v4(),6699)),
        toEndpoint(ip::address::from_string("127.0.0.1"),6628)
    {
        //toEndpoint(ip::address::from_string("127.0.0.1"),6628);

//        it= new infoThread();
//        hb = new heartBeatThread();
        hbQueue = new msgQueue();
        itQueue = new msgQueue();
        p = new Parser(this);
        online = new snMap(ios);
//        isInitial = false;
        start();
    }
    virtual ~nodeServer()
    {
        if(hbQueue!=NULL)delete hbQueue;
        if(itQueue!=NULL)delete itQueue;
        if(p!=NULL)delete p;
    }
    void start();
    void accept_handler(const system::error_code& ec,sock_ptr sock);
    void connect_handler(const system::error_code& ec, sock_ptr sock);
    void read_handler(const system::error_code& ec, char* data,sock_ptr sock);
    virtual void handleTag(Tag* t);
    int getType(Tag* t);
};
#endif
