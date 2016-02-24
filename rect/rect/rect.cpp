#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <stdlib.h>     // for exit()
#include <iomanip>      // for setw()

using namespace std;

#include "my-input-simple.h"
#include "rectangle-non-class.h"


// These are all of the main menu options.  Note that the numbers:
// 0, 1, 2, etc., show up /nowhere/ in the code, even though the
// user will see them on the screen, and will input them for
// choosing a menu option.
enum menu_option {
	EXIT_MENU,
	SET_NUMBER_OF_RECTANGLES,
	INPUT_RECTANGLE,
	OUTPUT_RECTANGLE,
	WRITE_RECTANGLES_TO_FILE,
	READ_RECTANGLES_FROM_FILE,
	// a neat trick for for-loop initial and final values
	FIRST_MENU_OPTION = EXIT_MENU,
	LAST_MENU_OPTION = READ_RECTANGLES_FROM_FILE
};

// These strings will be seen by the user, on the main menu.  They
// must be kept consistent with the operations of menu_option
// above.
// If this definition was in a header file, then it should be made
// static.
const char * const menu_option_strings[] = {
	"exit",
	"set number of rectangles",
	"input a rectangle",
	"output a rectangle",
	"write rectangles to file",
	"read rectangles from file"
};

// function for getting a menu option from the user
menu_option get_menu_option(void) {
	cout << endl << "Please note the following menu options:" <<
		endl << endl;

	const int menu_indent = 10;

	// The user will see:
	//
	//           0 -- exit
	//           1 -- set number of rectangles
	//           2 -- input a rectangle
	// etc.
	//
	// The (int) cast and static_cast<> are for doing the "++" as
	// an int type, since they are not allowed as a menu_option
	// type.

	for (menu_option menu_option_chosen = FIRST_MENU_OPTION;
		menu_option_chosen <= LAST_MENU_OPTION;
		menu_option_chosen = static_cast<menu_option>((int)menu_option_chosen + 1))
		cout << setw(menu_indent) << " " <<
		menu_option_chosen << " -- " <<
		menu_option_strings[menu_option_chosen] << endl;
	cout << endl;

	int menu_option_chosen_as_int;
	prompted_input(menu_option_chosen_as_int, "Please choose a menu option");
	// After the user has input an int, it is cast to a menu_option variable.
	return static_cast<menu_option>(menu_option_chosen_as_int);
}


int main(void) {
	cout << endl << "Welcome to RectangleCalc!" << endl << endl;

	// I have allowed this file name to be determined by user.
	//     (You're welcome.  ;-) )
	char *rectangles_file_name = 0;

	// the default number of rectangles, unless changed by the user
	unsigned int number_of_rectangles = 10;
	// these represent the array of rectangles
	unsigned int *lengths = 0, *widths = 0;

	cout << "Default number of rectangles: " << number_of_rectangles << endl << endl;
	// performing the initial allocation of array of rectangles
	allocate_rectangles(number_of_rectangles, lengths, widths);

	menu_option menu_option_chosen;

	// Everything happens inside of this do-while loop, until the user
	//     has decided to exit (or an error occurs).
	do {
		menu_option_chosen = get_menu_option();

		unsigned int rectangle_number;

		// Note how the individual cases, match nicely to the
		//     operations they will perform.
		switch (menu_option_chosen) {
		case EXIT_MENU:
			// adios
			cout << "Thanx for using RectangleCalc!" << endl;
			break;

		case SET_NUMBER_OF_RECTANGLES:
			// first, get the desired number of rectangles
			prompted_input(number_of_rectangles,
				"Please input the number of rectangles");
			// note that this will first delete any current array of rectangles
			allocate_rectangles(number_of_rectangles, lengths, widths);
			break;

		case INPUT_RECTANGLE:
			// find out from the user, into which rectangle (of the array of
			//     rectangles) to read the values
			prompted_input(rectangle_number, "Input into rectangle number");
			// make sure such an element exists in the array of rectangles
			if (rectangle_number < number_of_rectangles) {
				input_rectangle(lengths[rectangle_number],
					widths[rectangle_number]);
			}
			else {
				cerr << "Not a valid rectangle number." << endl;
			}
			break;

		case OUTPUT_RECTANGLE:
			// same two comments as for INPUT_RECTANGLE
			prompted_input(rectangle_number, "Output rectangle number");
			if (rectangle_number < number_of_rectangles) {
				output_rectangle(lengths[rectangle_number],
					widths[rectangle_number]);
			}
			else {
				cerr << "Not a valid rectangle number." << endl;
			}
			break;

		case WRITE_RECTANGLES_TO_FILE:
			// first get the filename
			prompted_input(rectangles_file_name,
				"Please input the file name");
			write_rectangles_to_file(rectangles_file_name,
				number_of_rectangles, lengths, widths);
			break;

		case READ_RECTANGLES_FROM_FILE:
			// first get the filename
			prompted_input(rectangles_file_name,
				"Please input the file name");
			read_rectangles_from_file(rectangles_file_name,
				number_of_rectangles, lengths, widths);
			break;

		default:
			cerr << "Sorry, but " << menu_option_chosen <<
				" is not a valid menu option." << endl;
			break;
		}
	} while (menu_option_chosen != EXIT_MENU);

	// clean up
	delete[] widths;
	delete[] lengths;

	delete[] rectangles_file_name;

	return 0;
}
