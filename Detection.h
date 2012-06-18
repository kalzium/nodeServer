#pragma once
#include "CThread.h"
class Detection :public CThread
{
public:
	Detection(void);
	~Detection(void);
	void operator() ();
	void loop();
};

