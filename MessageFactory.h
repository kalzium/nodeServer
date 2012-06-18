/*
 * File:   message.h
 * Author: chenkexin
 *
 * Created on 2012.6.3
 *
 * Modified on 2012.6.14 by zhangxiaobo
 * just modified the name to be standard  
 */

#ifndef _MESSAGEFACTORY_H
#define _MESSAGEFACTORY_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <../../gloox-0.9.9.12/src/tag.h>

using namespace std;
using namespace gloox;

class MessageFactory
{
    public:
//如果使用Tag作为载体就不需要length字段了。
//<HeartBeat_n2m></HeartBeat_n2m>
    static Tag* HeartBeat_n2m(string NID)
    {
        Tag* t = new Tag("HeartBeat_n2m");
        t->addAttribute("nid",NID);
        return t;
    }

    static Tag* HeartBeat_c2n(string NID)
    {
        Tag* t = new Tag("HeartBeat_c2n");
        t->addAttribute("nid",NID);
        return t;
    }

    static Tag* Generate_c2n(string unicode)
    {
        Tag* t = new Tag("Generate_c2n");
        Tag* code = new Tag("UniCode");
        code->setCData(unicode);
        t->addChild(code);
        return t;
    }

    //the NID when initializing the XML connect
    static Tag*  NID(string yourNID)
    {
        Tag* t = new Tag("NID");
        t->addAttribute("nid",yourNID);
        return t;
    }

    //the NID generated for client
    static Tag* BackNID(string clientNID)
    {
        Tag* t = new Tag("BackNID");
        t->setCData(clientNID);
        return t;
    }

    static Tag* Information_n2m(int clientNum, string NID, int maxClient)
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
