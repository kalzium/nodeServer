#include "MessageHandler.h"


MessageHandler::MessageHandler(void)
{
	cout<<"---构造消息分发。"<<endl;
	m_DataParser=new Parser(this);
}


MessageHandler::~MessageHandler(void)
{
	if(m_DataParser!=NULL) delete m_DataParser;
}

void MessageHandler::parserData(char* data)
{
	m_DataParser->feed(data);
}
void MessageHandler::handleTag( Tag *tagMessage )
{
    int type = getType(tagMessage);
    switch(type)
    {
    case 1:
    {
        
        break;
    }
    case 2:
    {
        break;
    }
    default:break;
    }
}


int MessageHandler::getType(Tag* tagMessage)
{
    if(tagMessage->name()=="HeartBeat_c2n")return 1;
    if(tagMessage->name()=="Generate_c2n")return 2;
	return 0;
}
