#pragma once
#include<string>

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

using namespace std;
class ServerID
{
private:
	char * idArray;
public:
	string toString()const;
	
	ServerID(string sidStr);
	~ServerID(void);
	bool operator < (const ServerID &sid);
	friend ostream & operator << ( ostream & os , const ServerID &sid );
};

