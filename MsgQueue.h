/*
 * File:   messageQueue.h
 * Author: chenkexin
 *
 * Created on 2012.6.3
 */
#ifndef MESSAGEQUEUE_H_
#define MESSAGEQUEUE_H_

#include "MessageFactory.h"
#include <list>
#include <boost\thread.hpp>
#include <iostream>

using namespace std;
using namespace boost;
//using namespace gloox;

class MsgQueue
{
private:
	list<Tag> m_MsgList;
	mutex m_Mutex;
public:
	MsgQueue(){}
	~MsgQueue(){}
//options that give others to use this queue

//extract the first Tag in the queue
//and do the process work
	Tag* searchMsg(string name);

//add the message in the list
	void addMsg(Tag &t);

//print the list
//a helper function that will be usefull when debug
	void printList();
};
#endif
