//
// Created by Paweł Kuźniar on 22/11/2023.
//

#ifndef CURRENCYFLTK_GETEXCHANGERATES_H
#define CURRENCYFLTK_GETEXCHANGERATES_H

#include "../APICredentials.h"

// Function to get exchange rates from Open Exchange Rates
std::string GetExchangeRates(const std::string& base_currency) {
    CURL* curl = curl_easy_init();
    if (curl) {
        // For USD and EUR, use the base currency as the selected currency (e.g. USD or EUR
        std::string url = API_URL + base_currency + "?apikey=" + API_KEY;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);

        return response;
    }

    return "";
}

#endif //CURRENCYFLTK_GETEXCHANGERATES_H
