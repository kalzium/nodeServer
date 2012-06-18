#include "NodeID.h"


NodeID::NodeID(const NodeID &n)
{
	idArray = new char[129];
	strncpy(idArray, n.toString().c_str(), 128);
	idArray[n.toString().size()] = '\0';
};

NodeID::NodeID(string nidStr)
{
	idArray=new char[129];
	strncpy(idArray, nidStr.c_str(), 128);
	idArray[nidStr.size()] = '\0';
}
NodeID::NodeID(ServerID* sid,string pecialStr)
{
	idArray=new char[129];
	//ππ‘ÏNodeID
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