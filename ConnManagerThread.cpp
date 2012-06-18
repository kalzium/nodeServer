#include "ConnManagerThread.h"

ConnManagerThread* ConnManagerThread::m_Self = new ConnManagerThread(*(new io_service()), "127.0.0.1", 50007);

ConnManagerThread::ConnManagerThread(io_service &io, string endpointIP, int endpointPort):
        m_Ios(io),
        m_Acceptor(m_Ios,ip::tcp::endpoint(ip::tcp::v4(),6699)),
        m_ToEndpoint(ip::address::from_string(endpointIP),endpointPort)
{
	m_ChildSocketMap = new map<NodeID, sock_ptr>();
	m_MessageHandler = new MessageHandler();
}


ConnManagerThread::~ConnManagerThread(void)
{
	if(m_ChildSocketMap != NULL)	delete m_ChildSocketMap;
	if(m_MessageHandler != NULL)	delete m_MessageHandler;
}

void ConnManagerThread::operator()()
{
	//connect to the MS
	connect();
	//listen to the clients
	listen();
	m_Ios.run();
}

void ConnManagerThread::connect()
{
    //connect MS async
    sock_ptr sockConnect(new ip::tcp::socket(m_Ios));
    sockConnect->async_connect(m_ToEndpoint,
                               boost::bind(&ConnManagerThread::onConnected,
                                    this,
                                    boost::asio::placeholders::error,
                                    sockConnect));
}

void ConnManagerThread::listen()
{
    //wait client async
	sock_ptr sockAccept(new ip::tcp::socket(m_Ios));
    m_Acceptor.async_accept(*sockAccept,
                          boost::bind(&ConnManagerThread::onAccepted,
                               this,
                               boost::asio::placeholders::error,
                               sockAccept));
}

void ConnManagerThread::onConnected(const system::error_code& ec, sock_ptr sock)
{
    if(ec)
    {
        cout<<"Connect MS error "<<ec<<endl;
        return;
    }
    //TODO
    cout<<"Connect to MS*,"<<endl;
    //call this function to keep accepting the following connection
    m_ParentSocket = sock;
}

void ConnManagerThread::onRead(const system::error_code& ec, char* data,sock_ptr sock)
{
    if(ec)
    {
        return;
    }
    m_MessageHandler->parserData(data);
    //call this function to keep reading the socket

    //notice: the char* data in argument list and the char data[100] in private
    //member list are different. To differ the two 'data', here I use a 'this' pointer
    //to reference the private member 'data'
    sock->async_read_some(buffer(this->m_ReceiveBuffer),
                          boost::bind(&ConnManagerThread::onRead,
                               this,
                               boost::asio::placeholders::error,
                               data,
                               sock));
}

void ConnManagerThread::onAccepted(const system::error_code& ec,sock_ptr sock)
{
   if(ec)
    {
        cout<<ec<<endl;
        return;
    }
    cout<<"DFASDF"<<endl;
    //call these functions to keep accepting the following connection
    sock_ptr sockAccept(new ip::tcp::socket(m_Ios));
    m_Acceptor.async_accept(*sockAccept,
                          boost::bind(&ConnManagerThread::onAccepted,
                               this,
                               boost::asio::placeholders::error,
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
	    boost::shared_ptr<NodeID> temp(new NodeID(nid));
		//NodeID k(nid);
		//m_ChildSocketMap->insert(std::pair<NodeID, sock_ptr>(k, sock));
		m_ChildSocketMap->insert(map<NodeID, sock_ptr>::value_type(*temp,sock));
		boost::shared_ptr<timer> timerTemp(new timer());
		HeartBeatThread::m_Self->m_TimerQueue->insert(std::pair<NodeID, timer_ptr>(*temp, timerTemp));
		//send the connect ack to the client message 
		sock->write_some(buffer("success" + temp->toString()));
    }
    if(nid[0]=='1')
    {
        //generate the NID for client and send it back
        //and store the NID with socket into map

        //generate the NID for client
		boost::shared_ptr<NodeID> temp(new NodeID(nid));
		m_ChildSocketMap->insert(map<NodeID, sock_ptr>::value_type(*temp,sock));
		boost::shared_ptr<timer> timerTemp(new timer());
		HeartBeatThread::m_Self->m_TimerQueue->insert(std::pair<NodeID, timer_ptr>(*temp, timerTemp));
		//send the connect ack to the client message 
		sock->write_some(buffer("success" + temp->toString()));
    }

///when initialize finished
    //begin read data from this sock
    //char data[100];
    sock->async_read_some(buffer(m_ReceiveBuffer),
                          boost::bind(&ConnManagerThread::onRead,
                               this,
                               boost::asio::placeholders::error,
                               m_ReceiveBuffer,
                               sock));
}