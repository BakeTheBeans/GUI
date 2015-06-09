#ifndef BUTTONEVENT_H
#define BUTTONEVENT_H
#include <iostream>
#include <vector>

namespace GUI
{

class  EventHandler;

class ICallBackEventHandler
{
    friend class EventHandler;
    bool flag;
    EventHandler * handle;
private:
    bool isAlive() { return flag; }
    void AttachHandle(EventHandler * _handle );

public:
    ICallBackEventHandler() : flag(true) {}
    virtual ~ICallBackEventHandler();

};


//Take this out****************************************
class TestEventClass : public ICallBackEventHandler
{
public:
    std::string foo;

public:
    TestEventClass(std::string bar);
    void  Print();
};
//******************************************************



struct IEvent
{

    bool set;
public:
    IEvent() : set(true) {}
    virtual ~IEvent() {}
    virtual void FireEvent()=0;
    virtual void Reset() {}
    virtual ICallBackEventHandler * getObject() { return 0; }
};



class EventHandler
{

private:
    template<typename T>
    struct Event : public IEvent
    {

        typedef void ( T::* vFptrv)() ;

        T * object;
        vFptrv funcPtr;

        Event( T * _obj, vFptrv _funcPtr  ) : object(_obj)
        {
            funcPtr = _funcPtr;
        }

        void FireEvent()
        {            
            (object->*funcPtr)();
        }

        void Reset()
        {
            set = false;
            object  = 0;
        }

        virtual ICallBackEventHandler * getObject()
        {
            return object;
        }

        ~Event()
        {
            Reset();
        }

    };


    std::vector<IEvent*> eventList;

public:
    EventHandler() : eventList() {}
    ~EventHandler();
    void CallBack(ICallBackEventHandler * CallingObject);
    void FireEvents();

    template<typename T> void AddEvent(T * _obj, typename Event<T>::vFptrv _funcPtr)
    {
        ICallBackEventHandler * check = static_cast<ICallBackEventHandler*>(_obj);

        if ( _obj )
        {
         IEvent* event = new Event<T>(_obj, _funcPtr);
         static_cast<ICallBackEventHandler*>(_obj)->AttachHandle(this);
         eventList.push_back(event);

        }

    }

};




}//EON
#endif // BUTTONEvent_H
