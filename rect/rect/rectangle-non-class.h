#ifndef RECTANGLE_NON_CLASS_H
#define RECTANGLE_NON_CLASS_H

#include <stdlib.h>     // for exit()
#include <iostream>
#include <fstream>      // for writing to/reading from files
using namespace std;


#include "my-input-simple.h"
#include "allocate-objects.h"


/*
This function dynamically allocates (with verification) the necessary two
(int) arrays, lengths and widths, representing an array of rectangles.

E.g.:

    unsigned int number_of_rectangles = 10;
    unsigned int *lengths = 0, *widths = 0;

    allocate_rectangles(number_of_rectangles, lengths, widths);

*/

// number_of_rectangles is a const reference, for speed.
// lengths and widths are /references/ to pointers, as their values
// are changed here in the function, and must be reflected in the
// invoking function as well.
inline void allocate_rectangles(const unsigned int &number_of_rectangles,
        unsigned int *&lengths, unsigned int *&widths) {
    allocate_objects(number_of_rectangles, lengths);
    allocate_objects(number_of_rectangles, widths);

    if (!lengths || !widths) {
        cerr << "Free store allocation for rectangle arrays failed.";
        exit(-1);
    }

    return;
}

/*
This function writes out an existing array of rectangles (lengths and
widths) to a new file, whose name is in the first argument.  E.g.:

    char *rectangles_file_name = 0;
    prompted_input(rectangles_file_name, "Please input the file name");

    write_rectangles_to_file(rectangles_file_name,
            number_of_rectangles, lengths, widths);

The file's format will start with the number of rectangles, e.g., if
there are 10:

10
34 22
2 19
... (eight more)
*/

inline void write_rectangles_to_file(const char *file_name,
        const unsigned int &number_of_rectangles,
        const unsigned int *lengths, const unsigned int *widths) {
    // opening the new file, for writing
    ofstream outfile(file_name, ios::out);
    if (!outfile) {
        cerr << "No success on opening output." << endl;
        exit(-1);
    }

    outfile << number_of_rectangles << endl;

    unsigned int rectangle;
    for (rectangle = 0; rectangle < number_of_rectangles; rectangle ++)
        outfile <<
                lengths[rectangle] << ' ' <<
                widths[rectangle] <<
                endl;

    outfile.close();

    return;
}

/*
This function reads in an array of rectangles (lengths and
widths) from a file, whose name is in the first argument.  E.g.:

    char *rectangles_file_name = 0;
    prompted_input(rectangles_file_name, "Please input the file name");

    read_rectangles_from_file(rectangles_file_name,
            number_of_rectangles, lengths, widths);

The file's format is as written by write_rectangles_to_file() above.

Note that number_of_rectangles is also set here, and therefore sent by
reference.  This function invokes allocate_rectangles().
*/

inline void read_rectangles_from_file(const char *file_name,
        unsigned int &number_of_rectangles,
        unsigned int *&lengths, unsigned int *&widths) {
    // opening the file, for reading
    ifstream infile(file_name, ios::in);
    if (!infile) {
        cerr << "No success on opening input." << endl;
        exit(-1);
    }

    infile >> number_of_rectangles;

    allocate_rectangles(number_of_rectangles, lengths, widths);

    unsigned int rectangle;
    for (rectangle = 0; rectangle < number_of_rectangles; rectangle ++)
        infile >> lengths[rectangle] >> widths[rectangle];

    infile.close();

    return;
}

/*
This function is for reading in a single rectangle from the user.
*/

inline void input_rectangle(unsigned int& length, unsigned int& width) {
    prompted_input(length, "Please input the length (int)");
    prompted_input(width, "Please input the width (int)");

    return;
}

/*
This function is for pretty-printing out a single rectangle to the
screen.
*/

inline void output_rectangle(const unsigned int& length,
        const unsigned int& width) {
    cout << "the rectangle: (" <<
                   length << ", " <<
                   width << ")" <<
                   endl;

    return;
}

#endif
