#ifndef SCRATCH_H
#define SCRATCH_H
#include "CMarkup/Markup.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <memory>

#include "interfaces.h"

#define PRINT(arg) std::cout << arg << std::endl;


class Wolf;
class Tiger;
class Lion;




template<typename T>
struct HasPrintTrait
{
static const bool value = true;
};

template<>
struct HasPrintTrait<Wolf>
{
static const bool value = false;
};

template<>
struct HasPrintTrait<Tiger>
{
static const bool value = false;
};

template<>
struct HasPrintTrait<Lion>
{
static const bool value=false;
};







//Cat, Dog and COw are the means to access resources and are 3rd party classes.
class Dog
{
private:
private:
    int legs;
public:
    Dog(int n) : legs(n) {}
    void Print() { std::cout << "I AM A DOG and I have " << legs << "legs" << std::endl; }
};


class Cat
{
private:
private:
    int legs;
public:
    Cat(int n) : legs(n) {}
    void Print() { std::cout << "I AM A DOG and I have " << legs << "legs" << std::endl; }
};

class Cow
{
private:
    int legs;
public:
    Cow(int n) : legs(n) {}
    void Print() { std::cout << "I AM A COW and I have " << legs << "legs" << std::endl; }
};


class Wolf
{
private:
    int legs;
public:
    Wolf(int n) : legs(n) {}

};

class Tiger
{
private:
    int legs;
public:
    Tiger(int n) : legs(n) {}

};



class Lion
{
private:
    int legs;
public:
    Lion(int n) : legs(n) {}

};






//Canine, Feline, Bovine are my definitions
struct IResource
{
virtual ~IResource() {}
};


struct Canine : public IResource
{
    typedef Dog* ReturnType;
    std::unique_ptr<Dog> res;
public:
    Canine(Dog * _dog) : res(_dog) {}
    ReturnType getResource() { return res.get();}
};

struct Feline : public IResource
{
    typedef Cat* ReturnType;
    std::unique_ptr<Cat> res;
public:
    Feline(Cat * _cat) : res(_cat) {}
    ReturnType getResource() { return res.get(); }

};

struct Bovine : public IResource
{
    typedef Cow* ReturnType;
    std::unique_ptr<Cow> res;
public:
    Bovine(Cow * _cow) : res(_cow) {}
    ReturnType getResource() { return res.get(); }
};


typedef IResource * ResourcePtr;

class Foo
{
private:
    std::vector<ResourcePtr>  bar;

public:
    //template<typename T>
    Foo & Add(ResourcePtr bean)
    {
        bar.push_back(bean);
        return *this;
    }

    template<typename T>
    typename T::ReturnType getResource(int index)
    {
        return (*static_cast<T*>(bar[index])).getResource();
    }

};



class BakeTheBeans : public GUI::EnclosingBox
{
private:
    virtual void SetSize()
    {

    }

    virtual void SetPosition()
    {

    }

public:

    BakeTheBeans() : EnclosingBox() {}

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        this->EnclosingBox::draw(target,states);
    }

};

template<typename T>
void Print(T & obj)
{
    obj.Print();
}


template<typename T>
void TraitTest()
{
    T obj(4);

    if ( HasPrintTrait<T>::value )
    {
        std::cout << typeid(T).name() << "  has HasPrint " << std::endl;
       Print<T>(obj);
    }
    else
        std::cout << typeid(T).name() << " does not have HasPrint " << std::endl;
}




class Factory
{


private:
    Factory()
    {
        std::cout << "Constructed" << std::endl;
    }



    Factory(const Factory & _obj);
    Factory & operator=(const Factory & _obj);

public:
    static Factory &  getFactory()
    {
        static Factory obj;
        return obj;
    }


};


#endif // SCRATCH_H
