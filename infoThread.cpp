/*
 * File:   infoThread.cpp
 * Author: zhangxiaobo
 *
 * Created on 2012.6.5
 */
#include <boost\thread.hpp>
#include <iostream>

using namespace std;
using namespace boost;

typedef boost::posix_time::ptime system_time;
void infoFunc()
{
    //TO DO
    while(true)
    {
        thread::sleep(get_system_time()+posix_time::seconds(8));
        cout<<"the info thread is working.  "<<endl;
    }
}
