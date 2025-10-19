#ifndef WEATHERSERVICE_H
#define WEATHERSERVICE_H
#include <bits/stdc++.h>

struct WeatherData {
    std::string city;
    double temperature;
    std::string condition;
    int humidity;
    double windSpeed;
    bool success;
    std::string errorMessage;
};

WeatherData getWeather(const std::string& cityName);

#endif