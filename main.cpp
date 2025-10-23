#include <iostream>
#include "ThreadPool.h"
#include "cliUI.h"
#include <curl/curl.h>

std::mutex displayMtx;

int main(int argc, char* argv[]) {
    CURLcode res = curl_global_init(CURL_GLOBAL_ALL);
    if (res != CURLE_OK) {
        std::cerr << "curl_global_init() failed: " << curl_easy_strerror(res) << std::endl;
        return 1;
    }

    std::vector<std::string> cityName;
    wellcome();

    std::string input;
    std::getline(std::cin, input);

    if (input.empty()) {
        std::cerr << "Please enter a valid input." << std::endl;
        return 1;
    }

    std::stringstream ss(input);
    std::string city;

    while (ss >> city) {
        if (!city.empty() && city.back() == ',') {
            city.pop_back();
        }
        cityName.push_back(city);
    }

    if (cityName.size() == 1) {
        std::cout << "\n🔍 Fetching weather data for " << cityName[0] << "...\n";

        WeatherData weather = getWeather(cityName[0]);

        if (!weather.success) {
            displayError(weather.errorMessage);
            return 1;
        }

        displayWeather(weather);
    } else {
        std::cout << "\n🔍 Fetching weather data for " << cityName.size() << " cities...\n";
        {
            ThreadPool pool(std::thread::hardware_concurrency());

            for (size_t i = 0; i < cityName.size(); i++) {
                pool.enqueue([city = cityName[i]]() {
                    const WeatherData weather = getWeather(city);
                    {
                        std::lock_guard<std::mutex> lock(displayMtx);
                        if (weather.success) {
                            displayWeather(weather);
                        } else {
                            displayError(weather.errorMessage);
                        }
                    }
                });
            }
        }
    }
    curl_global_cleanup();
    return 0;
}