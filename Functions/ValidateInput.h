//
// Created by Paweł Kuźniar on 22/11/2023.
//

#ifndef CURRENCYFLTK_VALIDATEINPUT_H
#define CURRENCYFLTK_VALIDATEINPUT_H

#include <cstring>
#include <FL/fl_ask.H>
#include <iomanip>


// Validate the input
bool ValidateInput(const char* inputValue) {
    // Check if the user entered a value
    if (std::strlen(inputValue) == 0) {
        // Throw an error for not entering a value
        fl_alert("Error: Please enter a value.");
        return false;
    }

    // Check if the user entered a valid numeric value
    char* endptr;
    std::strtod(inputValue, &endptr);
    if (*endptr != '\0') {
        // Throw an error for entering a non-numeric value
        fl_alert("Error: Please enter a valid numeric value.");
        return false;
    }

    return true;
}

#endif //CURRENCYFLTK_VALIDATEINPUT_H
