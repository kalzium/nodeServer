/*
 * File:   snMap.h
 * Author: zhangxiaobo
 *
 * Created on 2012.6.11
 */

#ifndef SNMAP_H_
#define SNMAP_H_

#include <map>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include "NodeID.h"
#include "clientSocketMeg.h"

using namespace std;
/*
 * File:   snMap.h
 * Author: zhangxiaobo
 *
 * Created on 2012.6.11
 */

using namespace boost;
using namespace boost::asio;

typedef boost::shared_ptr<ip::tcp::socket> sock_ptr;
typedef boost::shared_ptr<clientSocketMeg> csm_ptr;

class snMap
{
private:
	map<NodeID, csm_ptr> mapData;
	io_service &ios;
public:
	snMap(io_service &io);
	~snMap();
	bool addPair(NodeID&, sock_ptr&);
	bool deletePair(NodeID, sock_ptr);
	bool modifyPair(NodeID oldid, NodeID newid);
	sock_ptr findPair(NodeID);
};

#endif
