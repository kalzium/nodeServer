/*
 * File:   messageQueue.cpp
 * Author: chenkexin
 *
 * Created on 2012.6.3
 */

#include "messageQueue.h"
#include <string>

//find the tag with the passing name
//return a pointer that points to the first suitable tag, and remove the oringinal one
//if there aren't any one that match the name, return a null tag.
Tag* msgQueue::searchMsg(string name)
{
    std::list<Tag>::iterator iter;
    //iter = msgList.begin();
        mutex::scoped_lock lock(m);
        for(iter = msgList.begin(); iter != msgList.end() ; iter++)
        {
            if(name==iter->findAttribute("to"))
            {

                Tag *t = iter->clone();
                msgList.erase(iter);
//                m.unlock();
                return t;
            }
        }
    Tag *t = NULL;
    return t;
}

void msgQueue::addMsg(Tag &t)
{
    mutex::scoped_lock lock(m);
    msgList.push_back(t);
}

void msgQueue::printList()
{
    cout<<"THE LIST IS:"<<endl;
    mutex::scoped_lock lock(m);
    if(msgList.size()==0) cout<<"NULLLLLL"<<endl;
    else
    {
        list<Tag>::iterator iter;
        for( iter = msgList.begin(); iter != msgList.end(); iter++)
        {
            cout<<"@@@  ";
            cout<<iter->xml()<<endl;
        }
    }
//    m.unlock();
}
