//
// Created by Paweł Kuźniar on 22/11/2023.
//

#ifndef CURRENCYFLTK_WRITECALLBACK_H
#define CURRENCYFLTK_WRITECALLBACK_H


#include <string>
#include <curl/curl.h>

// Function to perform HTTP GET request using cURL
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}


#endif //CURRENCYFLTK_WRITECALLBACK_H
