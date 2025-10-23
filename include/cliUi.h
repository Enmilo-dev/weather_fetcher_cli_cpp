#pragma once
#include "WeatherService.h"

void wellcome();
void printUsage(const std::string& programName);
void displayWeather(const WeatherData& weather);
void displayError(const std::string& error);