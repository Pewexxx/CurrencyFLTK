//
// Created by Paweł Kuźniar on 22/11/2023.
//

#ifndef CURRENCYFLTK_ADDSORTED_H
#define CURRENCYFLTK_ADDSORTED_H

#include <FL/Fl_Choice.H>
#include <algorithm>
#include <vector>
#include <string>

// Function to add items to a Fl_Choice in sorted order
void AddSorted(Fl_Choice* choice, const std::vector<std::string>& items) {
    std::vector<const char*> sortedItems;
    for (const auto& item : items) {
        sortedItems.push_back(item.c_str());
    }
    std::sort(sortedItems.begin(), sortedItems.end(), [](const char* a, const char* b) {
        return strcmp(a, b) < 0;
    });

    for (const auto& item : sortedItems) {
        choice->add(item);
    }
}

#endif //CURRENCYFLTK_ADDSORTED_H
