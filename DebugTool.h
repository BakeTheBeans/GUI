#ifndef DEBUGTOOL_H
#define DEBUGTOOL_H
#include <thread>
#include <iostream>

class Tracker
{

    int & bug;
    //std::thread t;
public:
    Tracker(int & num) : bug(num)
    {
    }

    void Track()
    {
        std::cout << " Initial Value of TRacked Object " << bug << std::endl;
        std::thread t(&Tracker::StartTracking, this );
        t.detach();

    }

    ~Tracker()
    {
        //t.join();
    }

private:
    void StartTracking()
    {

        while(true)
        {
            std::cout << " Tracking ............ Value og bug : " << bug << std::endl;
            if (bug == 0 ) break;
        }

        std::cerr << "WARNING VALUE HAS CHANGED >>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
    }


};


#endif // DEBUGTOOL_H
