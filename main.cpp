#include <iostream>
#include "cliUI.h"

int main(int argc, char* argv[]) {
    std::string cityName;

    if (argc < 2) {
        std::cout << "Enter city name: ";
        std::getline(std::cin, cityName);

        if (cityName.empty()) {
            displayError("City name cannot be empty");
            return 1;
        }
    } else {
        // Get from command line
        cityName = argv[1];
        for (int i = 2; i < argc; i++) {
            cityName += " ";
            cityName += argv[i];
        }
    }

    std::cout << "\n🔍 Fetching weather data for " << cityName << "...\n";

    WeatherData weather = getWeather(cityName);

    if (!weather.success) {
        displayError(weather.errorMessage);
        return 1;
    }

    displayWeather(weather);
    return 0;
}