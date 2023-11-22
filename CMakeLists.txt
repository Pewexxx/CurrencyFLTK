cmake_minimum_required(VERSION 3.26)
project(CurrencyFLTK)

set(CMAKE_CXX_STANDARD 23)

add_executable(CurrencyFLTK main.cpp
        Functions/WriteCallback.h
        Functions/GetExchangeRates.h
        APICredentials.h
        Functions/AddSorted.h
        Functions/ValidateInput.h
        Functions/GetCurrencyIndex.h
        Functions/SetDefaultCurrency.h)

# Link your executable with the FLTK library
# Include FLTK headers
target_include_directories(CurrencyFLTK PRIVATE /opt/homebrew/opt/fltk/include/)
target_include_directories(CurrencyFLTK PRIVATE /opt/homebrew/opt/curl/include)
target_include_directories(CurrencyFLTK PRIVATE /opt/homebrew/opt/jsoncpp/include)


# Link against the FLTK library
target_link_libraries(CurrencyFLTK PRIVATE /opt/homebrew/opt/fltk/lib/libfltk.dylib)
target_link_libraries(CurrencyFLTK PRIVATE /opt/homebrew/opt/curl/lib/libcurl.dylib)
target_link_libraries(CurrencyFLTK PRIVATE /opt/homebrew/opt/jsoncpp/lib/libjsoncpp.dylib)