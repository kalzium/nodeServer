#pragma once

#include <gloox.h>
#include <parser.h>
#include <taghandler.h>
#include <tag.h>
#include<iostream>

using namespace std;
using namespace gloox;

class MessageHandler:public TagHandler
{
public:
	//parser to parse the XML data
    Parser* m_DataParser;
public:
	MessageHandler(void);
	virtual~MessageHandler(void);

	void parserData(char* data);
	virtual void handleTag(Tag* tagMessage);
	int MessageHandler::getType(Tag* tagMessage);
};

