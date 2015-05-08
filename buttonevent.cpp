#include "buttonevent.h"

namespace  GUI
{

void ICallBackEventHandler :: AttachHandle(EventHandler * _handle )
{
    handle  = _handle;
}

ICallBackEventHandler :: ~ICallBackEventHandler()
{
   flag = false;
   if(handle) handle->CallBack(this);
}


//Take this out****************************************
TestEventClass :: TestEventClass(std::string bar) : foo(bar) {}

void TestEventClass :: Print()
{

    std::cout << "Print Event......" << std::endl;
    std::cout << "Name : " << foo << std::endl;
}
//******************************************************


EventHandler :: ~EventHandler()
{
    for(IEvent * event : eventList ) if( event ) delete event;
}

void EventHandler :: CallBack(ICallBackEventHandler * CallingObject)
{
    if ( !CallingObject ) return;
    if ( CallingObject->isAlive() ) return;
    for( IEvent * event : eventList ) if ( CallingObject == event->getObject() ) event->Reset();
}


void EventHandler :: FireEvents()
{
    for(IEvent * event : eventList ) if ( event->set ) event->FireEvent();
}



}//EON
