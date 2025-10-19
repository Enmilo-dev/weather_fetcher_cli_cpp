//
// Created by Raihan on 10/19/2025.
//
#include <iostream>
#include "HttpClient.h"
#include <curl/curl.h>

size_t WriteCallBack(void* contents, size_t size, size_t nmemb, void* userp) {
    static_cast<std::string *>(userp)->append(static_cast<char *>(contents), size * nmemb);
    return size * nmemb;
}

std::string makeRequestUrl(const std::string& url) {
    CURL *handle = curl_easy_init();
    std::string response;

    if (!handle) {
        std::cerr << "Failed to start session!" << std::endl;
        return "";
    }

    curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, WriteCallBack);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(handle);

    if (res != CURLE_OK) {
        std::cerr << "CURL Error: " << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(handle);
        return "";
    }

    curl_easy_cleanup(handle);
    return response;
}