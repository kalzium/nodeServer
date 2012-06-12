#include "NodeID.h"
#include "string.h"

NodeID::NodeID(string nidStr)
{
	idArray=new char[128];
	strncpy(idArray, nidStr.c_str(), 128);
}
NodeID::NodeID(ServerID* sid,string pecialStr)
{
	idArray=new char[128];
	//ππ‘ÏNodeID
}

NodeID::NodeID(char* nidc)
{
    idArray = nidc;
}


NodeID::~NodeID(void)
{
	if(idArray!=NULL){
		delete idArray;
	}
}


string NodeID::toString()const
{
	return string(idArray);
}

//inline bool NodeID::operator <(const NodeID &nid)const
bool NodeID::operator <(const NodeID &nid)const
{
	return this->toString()<nid.toString();
}

ostream & operator << ( ostream & os , const NodeID &nid )
{
	os << nid.toString();
	return os;
}
