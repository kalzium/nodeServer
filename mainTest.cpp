#include <iostream>
#include "ConnManagerThread.h"
#include "HeartBeatThread.h"
#include "DealingThread.h"

using namespace std;

int main()
{
	ConnManagerThread::m_Self->Start();
	HeartBeatThread::m_Self->Start();
	DealingThread::m_Self->Start();
	std::system("pause");
	return 0;
}