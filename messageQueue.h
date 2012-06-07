/*
 * File:   messageQueue.h
 * Author: chenkexin
 *
 * Created on 2012.6.3
 */
#ifndef MESSAGEQUEUE_H_
#define MESSAGEQUEUE_H_

#include "message.h"
#include <list>
#include <boost\thread.hpp>
#include <iostream>
using namespace std;
using namespace boost;
//using namespace gloox;

class msgQueue
{
private:
list<Tag> msgList;
mutex m;

public:
msgQueue(){}
~msgQueue(){}
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
