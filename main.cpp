#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <curl/curl.h>
#include <json/json.h>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <FL/fl_ask.H>

#include "Functions/WriteCallback.h"
#include "Functions/GetExchangeRates.h"
#include "Functions/AddSorted.h"
#include "Functions/ValidateInput.h"
#include "Functions/GetCurrencyIndex.h"
#include "Functions/SetDefaultCurrency.h"

// List of currencies supported by the program
std::vector<std::string> progCurrencies = {"USD", "EUR", "PLN", "GBP", "JPY", "CNY", "CAD", "AUD", "CHF", "CZK", "SEK", "DKK"};

// Calculate positions for centering
int screenWidth = Fl::w();
int screenHeight = Fl::h();
int windowWidth = 400;
int windowHeight = 400;
int windowX = (screenWidth - windowWidth) / 2;
int windowY = (screenHeight - windowHeight) / 2;
int spacing = 35;

std::string defaultInputCurrency = "USD";
std::string defaultOutputCurrency = "PLN";

int main(){
    // Initialize FLTK
    Fl_Window* window = new Fl_Window(windowX, windowY, windowWidth, windowHeight, "Currency Translator");

    // Input field
    Fl_Input* inputField = new Fl_Input(windowWidth / 2 - 50, windowHeight / 10, 100, 30, "Amount");
    inputField->align(FL_ALIGN_TOP);

    // Output field
    Fl_Output* outputField = new Fl_Output(windowWidth / 2 - 50, inputField->y() + inputField->h() + spacing, 100, 30, "Result");
    outputField->color(FL_GRAY);
    outputField->align(FL_ALIGN_TOP);

    // Input currency menu
    Fl_Choice* inputMenu = new Fl_Choice(windowWidth / 2 - 150, outputField->y() + outputField->h() + spacing, 100, 25, "Input currency");
    AddSorted(inputMenu, progCurrencies);
    inputMenu->align(FL_ALIGN_TOP);
    SetDefaultCurrency(inputMenu, defaultInputCurrency, progCurrencies);

    // Output currency menu
    Fl_Choice* outputMenu = new Fl_Choice(windowWidth / 2 + 50, inputMenu->y(), 100, 25, "Output currency");
    AddSorted(outputMenu, progCurrencies);
    outputMenu->align(FL_ALIGN_TOP);
    SetDefaultCurrency(outputMenu, defaultOutputCurrency, progCurrencies);

    // Date of the update
    Fl_Output* dateOutput = new Fl_Output(windowWidth / 2 - 50, windowHeight - 80, 100, 20, nullptr);
    dateOutput->color(FL_GRAY);
    dateOutput->align(FL_ALIGN_TOP);

    Fl_Output* dateNextOutput = new Fl_Output(windowWidth / 2 - 50, windowHeight - 30, 100, 20, nullptr);
    dateNextOutput->color(FL_GRAY);
    dateNextOutput->align(FL_ALIGN_TOP);

    // Convert button
    Fl_Button* convertButton = new Fl_Button(windowWidth / 2 - 50, outputMenu->y() + outputMenu->h() + spacing - 5, 100, 30, "Convert");
    convertButton->callback([](Fl_Widget* widget, void* data) {

        // Get the exchange rates for the selected currencies
        std::string inputCurrency = static_cast<Fl_Choice*>(widget->parent()->child(2))->text();
        std::string outputCurrency = static_cast<Fl_Choice*>(widget->parent()->child(3))->text();
        Fl_Input* inputField = static_cast<Fl_Input*>(widget->parent()->child(0));

        // Validate the input
        const char* inputValue = inputField->value();
        if (!ValidateInput(inputValue)) {
            return;
        }

        std::string exchangeRates = GetExchangeRates(inputCurrency);

        // Parse JSON response
        Json::CharReaderBuilder builder;
        Json::CharReader* reader = builder.newCharReader();
        Json::Value jsonValue;
        std::istringstream jsonStream(exchangeRates);
        reader->parse(jsonStream.str().c_str(), jsonStream.str().c_str() + jsonStream.str().length(), &jsonValue, nullptr);

        if(jsonValue["result"] == "error") {
            fl_alert("Error requesting from the OXR API.");
            return;
        }

        // Get the conversion rate
        double conversionRate = jsonValue["rates"][outputCurrency].asDouble();

        // Perform the conversion
        double inputAmount = std::stod(inputValue);
        double result = inputAmount * conversionRate;
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << result;
        std::string resultRounded = oss.str();

        if (inputAmount != 0.0 && result == 0.0) {
            return;
        }

        // Display the update date
        Fl_Output* outputField = static_cast<Fl_Output*>(widget->parent()->child(1));
        outputField->value(resultRounded.c_str());

        long timestamp = jsonValue["time_last_update_unix"].asLargestInt();
        time_t updateTime = static_cast<time_t>(timestamp);
        char dateBuffer[80];
        strftime(dateBuffer, sizeof(dateBuffer), "%d.%m.%Y %H:%M:%S", localtime(&updateTime));

        Fl_Output* dateOutput = static_cast<Fl_Output*>(widget->parent()->child(4));
        dateOutput->textsize(10);
        dateOutput->color(fl_rgb_color(143, 91, 186));
        dateOutput->textcolor(fl_rgb_color(199, 167, 8));
        dateOutput->label("Data update [UTC+1]:");
        dateOutput->labelsize(12);
        dateOutput->labelfont(FL_ITALIC);
        dateOutput->labelcolor(FL_BLUE);
        dateOutput->value(dateBuffer);

        long timestamp2 = jsonValue["time_next_update_unix"].asLargestInt();
        time_t updateTime2 = static_cast<time_t>(timestamp2);
        char date2Buffer[80];
        strftime(date2Buffer, sizeof(date2Buffer), "%d.%m.%Y %H:%M:%S", localtime(&updateTime2))    ;

        Fl_Output* dateNextOutput = static_cast<Fl_Output*>(widget->parent()->child(5));
        dateNextOutput->textsize(10);
        dateNextOutput->color(fl_rgb_color(125, 52, 75));
        dateNextOutput->textcolor(fl_rgb_color(14, 102, 220));
        dateNextOutput->label("Next update [UTC+1]:");
        dateNextOutput->labelsize(12);
        dateNextOutput->labelfont(FL_ITALIC);
        dateNextOutput->labelcolor(FL_BLUE);
        dateNextOutput->value(date2Buffer);

        outputField->color(FL_WHITE);
    });

    convertButton->color(FL_INACTIVE_COLOR | FL_DARK2);
    convertButton->labelcolor(FL_WHITE);

    // Show the window
    window->color(FL_GRAY);
    window->resizable(window);
    window->end();
    window->show();
    return Fl::run();
}