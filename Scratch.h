#ifndef SCRATCH_H
#define SCRATCH_H
#include "CMarkup/Markup.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <memory>

#define PRINT(arg) std::cout << arg << std::endl;


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




#endif // SCRATCH_H
