/*
 * File:   snMap.cpp
 * Author: zhangxiaobo
 *
 * Created on 2012.6.11
 */

#include "snMap.h"


snMap::snMap(io_service &io):ios(io)
{}

snMap::~snMap()
{
}

bool snMap::addPair( NodeID& nodeid,  sock_ptr& sock)
{
	boost::shared_ptr<clientSocketMeg> csm(new clientSocketMeg(sock));
	//csm->setSock(sock);
	mapData.insert(map<NodeID, csm_ptr>::value_type(nodeid, csm));
	//mapData.insert(std::pair<NodeID, clientSocketMeg>(nodeid, csm));
	return true;
}

bool snMap::deletePair(NodeID nodeid, sock_ptr sock)
{
	mapData.erase(mapData.find(nodeid));
	return true;
}

sock_ptr snMap::findPair(NodeID nodeid)
{
	return (mapData.find(nodeid)->second)->getSock();
}

bool snMap::modifyPair(NodeID oldid, NodeID newid)
{
	sock_ptr temp = (mapData.find(oldid)->second)->getSock();
	deletePair(oldid, temp);
	addPair(newid, temp);
	return true;
}