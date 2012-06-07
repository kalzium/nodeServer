/*
 * File:   heartBeatThread.h
 * Author: chenkexin
 *
 * Created on 2012.6.4
 */

#ifndef _HEARTBEATTHREAD_h_
#define _HEARTBEATTHREAD_H_

#include "message.h"
#include "messageQueue.h"

class heartBeatThread
{
    public:
    heartBeatThread()
    {
        mq = new msgQueue();
    }
    ~heartBeatThread()
    {
        delete mq;
    }
    //the message queue of the thread
    msgQueue *mq;
    //the heart beat should run this function
    void heartBeatFunc();
};
#endif
