#include "GUIThread.h"

GUIThread* GUIThread::m_Self = new GUIThread();

GUIThread::GUIThread(void)
{
	m_Self = this;
}


GUIThread::~GUIThread(void)
{
}
