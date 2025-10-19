#include <bits/stdc++.h>
#include <curl/curl.h>

size_t WriteCallBack(void* contents, size_t size, size_t nmemb, void* userp);

std::string makeRequestUrl(const std::string& url);