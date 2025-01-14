#include <algorithm>
#include <stdexcept>
#include <utility>
#include <iostream>

template <typename Object> //Allows for use of multiple data types
class Vector
{
public:
    static constexpr int SPARE_CAPACITY = 16;

    explicit Vector(int initSize = 0) : theSize(initSize), theCapacity(initSize + SPARE_CAPACITY)
    {
        objects = new Object[theCapacity];
    } //Makes sure that instantiations of a vector object are in the form: Vector v(10)

    //The code below defines as deep copy constructor
    Vector(const Vector & rhs) : theSize(rhs.theSize), theCapacity(rhs.theCapacity), objects(nullptr)
    {
        objects = new Object[theCapacity];
        for (int k = 0; k < theSize; ++k)
            objects[k] = rhs.objects[k]; //copies the contents of the Vector object onto the new Vector object
    }

    //Overloaded = which functions as a deep copy constructor
    Vector & operator=(const Vector & rhs)
    {
        Vector copy = rhs;
        std::swap( *this, copy); //Copies the contents of the Vector object on the right onto the one on the left
        return *this;
    }

    ~Vector( ) //Destructor
    { delete [] objects; } //Releases dynamically allocates memory

    //Definition of a move constructor
    //Transfers resources from one Vector object onto another
    //'&&' allows functions to transfer resources onto new objects
    Vector(Vector && rhs) : theSize(rhs.theSize), theCapacity(rhs.theCapacity), objects(rhs.objects)
    {
        rhs.objects = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }

    Vector & operator =(Vector && rhs)
    {
        if (this != &rhs) {
            std::swap(theSize, rhs.theSize);
            std::swap(theCapacity, rhs.theCapacity);
            std::swap(objects, rhs.objects);
        }

        return *this;
    }

    //Enlarges the capacity of a vector
    void resize(int newSize)
    {
        if (newSize > theCapacity)
        { reserve(newSize * 2); }
        theSize = newSize;
    }


    void reserve(int newCapacity)
    {
        if (newCapacity < theSize)
            return;

        Object *newArray = new Object[newCapacity];
        for(int k = 0; k < theSize; ++k)
            newArray[k] = std::move(objects[k]);

        theCapacity = newCapacity;
        std::swap(objects, newArray);
        delete [] newArray;
    }

    Object & operator[](int index)
    { return objects[index]; }

    const Object & operator[](int index) const
    { return objects[index]; }

    bool empty() const
    { return size() == 0; }

    int size() const
    { return theSize; }

    int capacity() const
    { return theCapacity; }

    void push_back(const Object & x)
    {
        if (theSize == theCapacity)
            reserve(2 * theCapacity + 1);
        objects[theSize++] = x;
    }

    void push_back(Object && x)
    {
        if (theSize == theCapacity)
            reserve(2 * theCapacity + 1);
        objects[theSize++] = std::move(x);
    }

    void pop_back()
    { --theSize; }

    const Object & back () const
    { return objects[ theSize - 1 ]; }

    typedef Object * iterator;
    typedef const Object * const_iterator;

    iterator begin()
    { return &objects[0]; }

    const_iterator begin() const
    { return &objects[0]; }

    iterator end()
    { return &objects[size()]; }

    const_iterator end() const
    { return &objects[size()]; }

private:
    int theSize;
    int theCapacity;
    Object * objects;
};

int main()
{
    Vector<int> v(5);

    return 0;
}
