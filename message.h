/*
 * File:   message.h
 * Author: chenkexin
 *
 * Created on 2012.6.3
 */
#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "tag.h"

using namespace std;
using namespace gloox;

//enum Message_Type
//{
//    //sending and receiving heart beat message
//    HeartBeat_n2m = 901,
//    HeartBeat_c2n = 902,
//
//    //receiving the unique code
//    Generate_c2n = 903,
//
//    //sending NS's basic info to MS
//    Information_n2m = 904,
//
//    //sending NID to client
//    NID_n2c = 905
//};

class MESSAGE
{
    public:
//如果使用Tag作为载体就不需要length字段了。
//<HeartBeat_n2m></HeartBeat_n2m>
    Tag* N_HEARTBEAT()
    {
        Tag* t = new Tag("HeartBeat_n2m");
        return t;
    }

    Tag* C_HEARTBEAT()
    {
        Tag* t = new Tag("HeartBeat_c2n");
        return t;
    }

    Tag* C_UNIQUE(string unicode)
    {
        Tag* t = new Tag("Generate_c2n");
        Tag* code = new Tag("UniCode");
        code->setCData(unicode);
        t->addChild(code);
        return t;
    }

    Tag*  N_NID(string clientNID)
    {
        Tag* t = new Tag("NID_n2c");
        Tag* nid = new Tag("NID");
        nid->setCData(clientNID);
        t->addChild(nid);
        return t;
    }

/// //store the info that passed from NS to MS
///
///    //the number of clients holds in the NS;
///    int clientNum;
///    //the NodeServer's NID;
///    string NID;
///    //the max number of clients that the NS can hold
///    int maxClient;

    Tag* N_INFO(int clientNum, string NID, int maxClient)
    {
        Tag* t = new Tag("Information_n2m");
        Tag* cn = new Tag("clientNum");

        //change the int type into char[]
        char strNum[10];
        itoa(clientNum,strNum,10);
        cn->setCData(strNum);

        Tag* ni = new Tag("NID");
        ni->setCData(NID);

        char strMax[10];
        itoa(maxClient,strMax,10);
        Tag* max = new Tag("maxClient");
        max->setCData(strMax);

        t->addChild(cn);
        t->addChild(ni);
        t->addChild(max);
        return t;
    }
};
#endif
