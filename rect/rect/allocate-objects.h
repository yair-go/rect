#ifndef ALLOCATE_OBJECTS_H
#define ALLOCATE_OBJECTS_H

#include <stdlib.h>     // for exit()
#include <iostream>
using namespace std;


/*
This function template is for dynamically allocating (with verification)
an array of objects T.

The template aspect will help later on, for allocating an array of
subclass objects, polymorphically.  (Huh??  ;-) )

Note: cannot remove second argument, and have this /return/ the pointer
      value, since the template argument T /must/ be in the argument list.

E.g.:

    unsigned int number_of_objects = 10;
    long long *objects = 0;

    allocate_objects(number_of_objects, objects);

*/

// number_of_objects is a const reference, for speed.
// objects is a /references/ to a pointer, as its value
// is changed here in the function, and must be reflected in the
// invoking function as well.
template <class T>
inline void allocate_objects(const unsigned int &number_of_objects,
        T *&objects) {
    delete [] objects;

    objects = 0;

    objects = new T[number_of_objects];

    if (!objects) {
        cerr << "Free store allocation for object array failed.";
        exit(-1);
    } else    // if okay, let's zero out the array
        for (int object = 0; object < number_of_objects; object++)
            objects[object] = (T) 0;    // note the typecast

    return;
}

#endif
