#pragma once

#include <string>
#include "ServerID.h"

using namespace std;

class NodeID
{
private:
	char *idArray;
public:
	NodeID(const NodeID &n);
	NodeID(string nidStr);
	NodeID(ServerID* sid,string pecialStr);
	~NodeID(void);
	string NodeID::toString()const;
	bool operator <(const NodeID &nid)const;
	friend ostream & operator << ( ostream & os , const NodeID &nid );
};

