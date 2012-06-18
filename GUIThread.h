#pragma once
class GUIThread
{
public:
	static GUIThread *m_Self;
public:
	GUIThread(void);
	~GUIThread(void);
};

