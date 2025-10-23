//
// Created by Raihan on 10/19/2025.
//
#include "WeatherService.h"
#include "HttpClient.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

const std::string API_KEY = "Add your API"; //Get it from openweathermap.org

WeatherData getWeather(const std::string& cityName) {
    WeatherData result;
     const std::string url = "https://api.openweathermap.org/data/2.5/weather?q=" +
                      cityName + "&appid=" + API_KEY + "&units=metric";

    std::string jsonResponse = makeRequestUrl(url);

    if (jsonResponse.empty()) {
        result.success = false;
        result.errorMessage = "Failed to get weather data";
        return result;
    }

    try {
        json data = json::parse(jsonResponse);

        result.city = data["name"];
        result.temperature = data["main"]["temp"];
        result.condition = data["weather"][0]["description"];
        result.humidity = data["main"]["humidity"];
        result.windSpeed = data["wind"]["speed"];
        result.success = true;
    } catch (const std::exception& e) {
        result.success = false;
        result.errorMessage = "Failed to get weather data" + std::string(e.what());
    }
    return result;
}
