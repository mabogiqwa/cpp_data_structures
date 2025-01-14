#include <algorithm>

template <typename Object> //Allows for use of multiple data types
class Vector
{
public:
    explicit Vector(int initSize = 0) : theSize(initSize), theCapacity(initSize + SPARE_CAPACITY)
    {
        objects = new Object[theCapacity];
    } //Makes sure that instantiations of a vector object are in the form: Vector v(10)

    Vector(const Vector & rhs) : theSize(rhs.theSize), theCapacity(rhs.theCapacity), objects(nullptr)
    {
        objects = new Object[theCapacity];
        for (int k = 0; k < theSize; ++k)
            objects[k] = rhs.objects[k];
    }

    Vector & operator=(const Vector & rhs)
    {
        Vector copy = rhs;
        std::swap( *this, copy);
        return *this;
    }

    ~Vector( )
    { delete [ ] objects; }

    Vector(Vector && rhs) : theSize(rhs.theSize), theCapacity(rhs.theCapacity), objects(rhs.objects)
    {
        rhs.objects = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }

    Vector * operator = (Vector && rhs)
    {
        std::swap(theSize, rhs.theSize);
        std::swap(theCapacity, rhs.theCapacity);
        std::swap(objects, rhs.objects);

        return *this;
    }

    void resize(int newSize)
    {
        if (newSize > theCapacity)
            reserve(newSize * 2)
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
        delete [ ] newArray;
    }

private:
    int theSize;
    int theCapacity;
    Object * objects;
};