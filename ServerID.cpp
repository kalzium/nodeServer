#include "ServerID.h"


ServerID::ServerID(string sidStr)
{
	idArray = new char[sidStr.length() + 1];
	strncpy(idArray, sidStr.c_str(), sidStr.length() + 1);
}

string ServerID::toString()const
{
	return string(idArray); 
}

inline bool ServerID::operator <(const ServerID &sid)
{
	return this->toString()<sid.toString();
} 

ostream & operator << ( ostream & os , const ServerID &sid )
{
	os << sid.toString();
	return os;
}

ServerID::~ServerID(void)
{
	if(this->idArray!=NULL) delete this->idArray;
}
