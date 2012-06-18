/*
 * File:   messageQueue.cpp
 * Author: chenkexin
 *
 * Created on 2012.6.3
 */

#include "MsgQueue.h"
#include <string>

//find the tag with the passing name
//return a pointer that points to the first suitable tag, and remove the oringinal one
//if there aren't any one that match the name, return a null tag.
Tag* MsgQueue::searchMsg(string name)
{
    std::list<Tag>::iterator iter;
    //iter = msgList.begin();
        mutex::scoped_lock lock(m_Mutex);
        for(iter = m_MsgList.begin(); iter != m_MsgList.end() ; iter++)
        {
            if(name==iter->findAttribute("to"))
            {

                Tag *t = iter->clone();
                m_MsgList.erase(iter);
//                m.unlock();
                return t;
            }
        }
    Tag *t = nullptr;
    return t;
}

void MsgQueue::addMsg(Tag &t)
{
    mutex::scoped_lock lock(m_Mutex);
    m_MsgList.push_back(t);
}

void MsgQueue::printList()
{
    cout<<"THE LIST IS:"<<endl;
    mutex::scoped_lock lock(m_Mutex);
    if(m_MsgList.size()==0) cout<<"NULLLLLL"<<endl;
    else
    {
        list<Tag>::iterator iter;
        for( iter = m_MsgList.begin(); iter != m_MsgList.end(); iter++)
        {
            cout<<"@@@  ";
            cout<<iter->xml()<<endl;
        }
    }
//    m.unlock();
}
