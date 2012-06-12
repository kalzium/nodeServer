/*
 * File:   heartBeatThread.cpp
 * Author: zhangxiaobo
 *
 * Created on 2012.6.4
 */

#include <iostream>
#include <boost\thread.hpp>

typedef boost::posix_time::ptime system_time;
using namespace std;
using namespace boost;

void heartBeatFunc()
{
    //TO DO
    while(true)
    {
        thread::sleep(get_system_time()+posix_time::seconds(10));
        cout<<"the heart beat thread is working"<<endl;
    }
}
