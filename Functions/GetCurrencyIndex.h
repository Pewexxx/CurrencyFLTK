//
// Created by Paweł Kuźniar on 22/11/2023.
//

#ifndef CURRENCYFLTK_GETCURRENCYINDEX_H
#define CURRENCYFLTK_GETCURRENCYINDEX_H

#include <string>
#include <vector>
#include <algorithm>


int getCurrencyIndex(const std::string& currency, std::vector<std::string>& progCurrencies) {
    std::sort(progCurrencies.begin(), progCurrencies.end());
    auto loc = std::find(progCurrencies.begin(), progCurrencies.end(), currency);
    if (loc != progCurrencies.end() || currency == progCurrencies.back()) {
        return (std::distance(progCurrencies.begin(), loc));
    }
    return -1; // Not found
}


#endif //CURRENCYFLTK_GETCURRENCYINDEX_H
