/*
 * File:   nodeServer.cpp
 * Author: chenkexin
 *
 * Created on 2012.6.5
 */
#include "nodeServer.h"

extern void heartBeatFunc();
extern void infoFunc();

void nodeServer::start()
{
    sock_ptr sockAccept(new ip::tcp::socket(ios));
    //wait client async
    acceptor.async_accept(*sockAccept,
                          bind(&nodeServer::accept_handler,
                               this,
                               placeholders::error,
                               sockAccept));
    //connect MS async
    sock_ptr sockConnect(new ip::tcp::socket(ios));
    sockConnect->async_connect(toEndpoint,
                               bind(&nodeServer::connect_handler,
                                    this,
                                    placeholders::error,
                                    sockConnect));
    //start the working threads
//    cout<<"NOW£Ó£Ô£Á£Ò£Ô"<<endl;
    thread hb_thread(heartBeatFunc);
    thread it_thread(infoFunc);

//    hb_thread.join();
//    it_thread.join();
}

void nodeServer::accept_handler(const system::error_code& ec,sock_ptr sock)
{
    if(ec)
    {
        cout<<ec<<endl;
        return;
    }
    cout<<"DFASDF"<<endl;
    //call these functions to keep accepting the following connection
    sock_ptr sockAccept(new ip::tcp::socket(ios));
    acceptor.async_accept(*sockAccept,
                          bind(&nodeServer::accept_handler,
                               this,
                               placeholders::error,
                               sockAccept));

    //TODO
    cout<<"ACCEPT client connect:  "<<sock->remote_endpoint().address()<<endl;
///initialize work
    //accept unique code or NID
    //all the identifier is of length 128
    char nid[129];
    sock->read_some(buffer(nid));
    cout<<"the nid"<<nid<<endl;
    if(nid[0]=='0')
    {
        //store the NID with socket into map
    shared_ptr<NodeID> temp(new NodeID(nid));
    online->addPair(*temp,sock);
    }
    if(nid[0]='1')
    {
        //generate the NID for client and send it back
        //and store the NID with socket into map

        //generate the NID for client
     shared_ptr<NodeID> temp(new NodeID(nid));
     online->addPair(*temp,sock);
    }

///when initialize finished
    //begin read data from this sock
    //char data[100];
    sock->async_read_some(buffer(data),
                          bind(&nodeServer::read_handler,
                               this,
                               placeholders::error,
                               data,
                               sock));
}
void nodeServer::connect_handler(const system::error_code& ec, sock_ptr sock)
{
    if(ec)
    {
        cout<<"Connect MS error "<<ec<<endl;
        return;
    }
    //TODO
    cout<<"Connect to MS*,"<<endl;
    //call this function to keep accepting the following connection
}

void nodeServer::read_handler(const system::error_code& ec, char* data,sock_ptr sock)
{
    if(ec)
    {
        return;
    }
    p->feed(data);
    //call this function to keep reading the socket

    //notice: the char* data in argument list and the char data[100] in private
    //member list are different. To differ the two 'data', here I use a 'this' pointer
    //to reference the private member 'data'
    sock->async_read_some(buffer(this->data),
                          bind(&nodeServer::read_handler,
                               this,
                               placeholders::error,
                               data,
                               sock));
}


void nodeServer::handleTag( Tag *tag )
{
    //in this function, we shall decide with queue the Tag would go to.
    int type = getType(tag);

    switch(type)
    {
    case 0:
        itQueue->addMsg(*tag);
        break;
    case 1:
    {
        hbQueue->addMsg(*tag);
        break;
    }
    case 2://ignore
        break;
    default:
        break;
    }
}

int nodeServer::getType(Tag* t)
{
    //node server will only receive the messages with
    //suffix like "X2c", and "NID"
    if(t->name()=="NID") return 0;
    if(t->name()=="HeartBeat_c2n") return 1;
    if(t->name()=="Generate_c2n") return 2;
}
