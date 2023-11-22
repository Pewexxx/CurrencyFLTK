//
// Created by Paweł Kuźniar on 22/11/2023.
//

#ifndef CURRENCYFLTK_SETDEFAULTCURRENCY_H
#define CURRENCYFLTK_SETDEFAULTCURRENCY_H

#include <FL/Fl_Choice.H>
#include <string>
#include "AddSorted.h"
#include "GetCurrencyIndex.h"


void SetDefaultCurrency(Fl_Choice*& theMenu, std::string& choosenCurrency, std::vector<std::string>& progCurrencies) {
    int index = getCurrencyIndex(choosenCurrency, progCurrencies);
    if (index != -1) {
        theMenu->value(index);
    }
}

#endif //CURRENCYFLTK_SETDEFAULTCURRENCY_H
