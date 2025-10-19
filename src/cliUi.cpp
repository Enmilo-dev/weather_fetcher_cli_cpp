//
// Created by Raihan on 10/19/2025.
//
#include "cliUi.h"

void printUsage(const std::string& programName) {
    std::cout << "\n=== Weather CLI ===\n";
    std::cout << "Usage: " << programName << " <city_name>\n\n";
    std::cout << "Examples:\n";
    std::cout << "  " << programName << " Dhaka\n";
    std::cout << "  " << programName << " London\n";
    std::cout << "  " << programName << " \"New York\"\n\n";
    std::cout << "Note: Use quotes for city names with spaces\n";
}

void displayWeather(const WeatherData& weather) {
    std::cout << "\n========================================\n";
    std::cout << "  Weather in " << weather.city << "\n";
    std::cout << "========================================\n";
    std::cout << "  Temperature:  " << weather.temperature << " C\n";
    std::cout << "  Condition:    " << weather.condition << "\n";
    std::cout << "  Humidity:     " << weather.humidity << "%\n";
    std::cout << "  Wind Speed:   " << weather.windSpeed << " m/s\n";
    std::cout << "========================================\n\n";
}

void displayError(const std::string& error) {
    std::cerr << "\n❌ Error: " << error << "\n\n";
}