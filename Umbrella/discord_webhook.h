#pragma once
#include <windows.h>
#include <wininet.h>
#include <tchar.h>
#include <string>
#include <iostream>

#pragma comment(lib, "Wininet.lib")

// Webhook Nuked Logs Discord Server AsepppStore
inline void DiscordWebhookSenderNukedLogs1(std::string message) {
    LPCTSTR szUserAgent = _T("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.74 Safari/537.36 Edg/79.0.309.43");
    LPCTSTR szHost = _T("discordapp.com");
    LPCTSTR szUrlPath = _T("/api/webhooks/950034562187132978/-jZyRUxKxl8u2qZS2v5JkhPfaVUe-q2crI4FD0yWwK1ds97eOeSeW-cdUa1Ul1NsMsgz");
    LPCTSTR szAcceptTypes[] = { _T("application/json"), NULL };
    LPCTSTR szContentTypeHeader = _T("Content-Type: application/json");
    LPCSTR szPostData = ("{ \"username\": \"Nuked Logs\", \"embeds\":  \[{\"description\": \"<:nuke:950741971448778833> " + message + "\", \"color\": \"65535\", \"footer\": \{\"text\": \"Nuked Logs By @Dr. Aseppp Of Beban#8307\", \"icon_url\": \"https://cdn.discordapp.com/avatars/493311232070123520/6b2016d46fbf0fc2c7759da7dcedb72f.png?size=1024\"}}]}").c_str();

    const DWORD dwPostDataLength = strlen(szPostData);
    HINTERNET hIntSession = InternetOpen(szUserAgent, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hIntSession) {
        HINTERNET hHttpSession = InternetConnect(hIntSession, szHost, INTERNET_DEFAULT_HTTPS_PORT, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);
        if (hHttpSession) {
            HINTERNET hHttpRequest = HttpOpenRequest(hHttpSession, _T("POST"), szUrlPath, NULL, NULL, szAcceptTypes,
                (INTERNET_FLAG_NO_COOKIES | INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE), 0);
            if (hHttpRequest) {
                if (HttpSendRequest(hHttpRequest, szContentTypeHeader, -1, (LPVOID)szPostData, dwPostDataLength)) {
                    DWORD dwStatusCode = 0;
                    {
                        TCHAR szStatusCode[32] = { 0 };
                        DWORD dwStatusCodeSize = sizeof(szStatusCode) / sizeof(TCHAR);
                        if (HttpQueryInfo(hHttpRequest, HTTP_QUERY_STATUS_CODE, szStatusCode, &dwStatusCodeSize, NULL)) {
                            dwStatusCode = _ttoi(szStatusCode);
                        }
                    }
                    unsigned char* lpResponse = NULL;
                    DWORD dwTotalSize = 0;
                    {
                        unsigned char* lpBuffer = (unsigned char*)malloc(2048);
                        DWORD dwRead = 0;
                        while (InternetReadFile(hHttpRequest, lpBuffer, sizeof(lpBuffer), &dwRead) && dwRead) {
                            unsigned char* lpTmp = (unsigned char*)realloc(lpResponse, dwTotalSize + dwRead);
                            if (lpTmp) {
                                lpResponse = lpTmp;
                                memcpy(&lpResponse[dwTotalSize], lpBuffer, dwRead);
                                dwTotalSize += dwRead;
                            }
                            dwRead = 0;
                        }
                        free(lpBuffer);
                    }
                    if (lpResponse) {
                        free(lpResponse);
                    }
                }
                InternetCloseHandle(hHttpRequest);
            }
            InternetCloseHandle(hHttpSession);
        }
        InternetCloseHandle(hIntSession);
    }
}

// Webhook Nuked Logs Discord Server Petani X
inline void DiscordWebhookSenderNukedLogs2(std::string message) {
    LPCTSTR szUserAgent = _T("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.74 Safari/537.36 Edg/79.0.309.43");
    LPCTSTR szHost = _T("discordapp.com");
    LPCTSTR szUrlPath = _T("/api/webhooks/950709916400750613/wFffXf6tkEBwy1SINe9rYArJNgZr0iMYA607ib4hAVmmQgVC1rqPLN0_-DmDlByCawq3");
    LPCTSTR szAcceptTypes[] = { _T("application/json"), NULL };
    LPCTSTR szContentTypeHeader = _T("Content-Type: application/json");
    LPCSTR szPostData = ("{ \"username\": \"Nuked Logs\", \"embeds\":  \[{\"description\": \"<:nuke:950741971448778833> " + message + "\", \"color\": \"65535\", \"footer\": \{\"text\": \"Nuked Logs By @Dr. Aseppp Of Beban#8307\", \"icon_url\": \"https://cdn.discordapp.com/avatars/493311232070123520/6b2016d46fbf0fc2c7759da7dcedb72f.png?size=1024\"}}]}").c_str();

    const DWORD dwPostDataLength = strlen(szPostData);
    HINTERNET hIntSession = InternetOpen(szUserAgent, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hIntSession) {
        HINTERNET hHttpSession = InternetConnect(hIntSession, szHost, INTERNET_DEFAULT_HTTPS_PORT, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);
        if (hHttpSession) {
            HINTERNET hHttpRequest = HttpOpenRequest(hHttpSession, _T("POST"), szUrlPath, NULL, NULL, szAcceptTypes,
                (INTERNET_FLAG_NO_COOKIES | INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE), 0);
            if (hHttpRequest) {
                if (HttpSendRequest(hHttpRequest, szContentTypeHeader, -1, (LPVOID)szPostData, dwPostDataLength)) {
                    DWORD dwStatusCode = 0;
                    {
                        TCHAR szStatusCode[32] = { 0 };
                        DWORD dwStatusCodeSize = sizeof(szStatusCode) / sizeof(TCHAR);
                        if (HttpQueryInfo(hHttpRequest, HTTP_QUERY_STATUS_CODE, szStatusCode, &dwStatusCodeSize, NULL)) {
                            dwStatusCode = _ttoi(szStatusCode);
                        }
                    }
                    unsigned char* lpResponse = NULL;
                    DWORD dwTotalSize = 0;
                    {
                        unsigned char* lpBuffer = (unsigned char*)malloc(2048);
                        DWORD dwRead = 0;
                        while (InternetReadFile(hHttpRequest, lpBuffer, sizeof(lpBuffer), &dwRead) && dwRead) {
                            unsigned char* lpTmp = (unsigned char*)realloc(lpResponse, dwTotalSize + dwRead);
                            if (lpTmp) {
                                lpResponse = lpTmp;
                                memcpy(&lpResponse[dwTotalSize], lpBuffer, dwRead);
                                dwTotalSize += dwRead;
                            }
                            dwRead = 0;
                        }
                        free(lpBuffer);
                    }
                    if (lpResponse) {
                        free(lpResponse);
                    }
                }
                InternetCloseHandle(hHttpRequest);
            }
            InternetCloseHandle(hHttpSession);
        }
        InternetCloseHandle(hIntSession);
    }
}

// Webhook Nuked Logs Discord Server Growtopia Logs
inline void DiscordWebhookSenderNukedLogs3(std::string message) {
    LPCTSTR szUserAgent = _T("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.74 Safari/537.36 Edg/79.0.309.43");
    LPCTSTR szHost = _T("discordapp.com");
    LPCTSTR szUrlPath = _T("api/webhooks/953983755247321098/L2qJCFdq4yjdgxgbtsSAxjwAHv6oUOV1E4KYWKzEbv1qeI_8V40l6AtjtNQDPPh5au8X");
    LPCTSTR szAcceptTypes[] = { _T("application/json"), NULL };
    LPCTSTR szContentTypeHeader = _T("Content-Type: application/json");
    LPCSTR szPostData = ("{ \"username\": \"Nuked Logs\", \"embeds\":  \[{\"description\": \"<:nuke:950741971448778833> " + message + "\", \"color\": \"65535\"}]}").c_str();

    const DWORD dwPostDataLength = strlen(szPostData);
    HINTERNET hIntSession = InternetOpen(szUserAgent, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hIntSession) {
        HINTERNET hHttpSession = InternetConnect(hIntSession, szHost, INTERNET_DEFAULT_HTTPS_PORT, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);
        if (hHttpSession) {
            HINTERNET hHttpRequest = HttpOpenRequest(hHttpSession, _T("POST"), szUrlPath, NULL, NULL, szAcceptTypes,
                (INTERNET_FLAG_NO_COOKIES | INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE), 0);
            if (hHttpRequest) {
                if (HttpSendRequest(hHttpRequest, szContentTypeHeader, -1, (LPVOID)szPostData, dwPostDataLength)) {
                    DWORD dwStatusCode = 0;
                    {
                        TCHAR szStatusCode[32] = { 0 };
                        DWORD dwStatusCodeSize = sizeof(szStatusCode) / sizeof(TCHAR);
                        if (HttpQueryInfo(hHttpRequest, HTTP_QUERY_STATUS_CODE, szStatusCode, &dwStatusCodeSize, NULL)) {
                            dwStatusCode = _ttoi(szStatusCode);
                        }
                    }
                    unsigned char* lpResponse = NULL;
                    DWORD dwTotalSize = 0;
                    {
                        unsigned char* lpBuffer = (unsigned char*)malloc(2048);
                        DWORD dwRead = 0;
                        while (InternetReadFile(hHttpRequest, lpBuffer, sizeof(lpBuffer), &dwRead) && dwRead) {
                            unsigned char* lpTmp = (unsigned char*)realloc(lpResponse, dwTotalSize + dwRead);
                            if (lpTmp) {
                                lpResponse = lpTmp;
                                memcpy(&lpResponse[dwTotalSize], lpBuffer, dwRead);
                                dwTotalSize += dwRead;
                            }
                            dwRead = 0;
                        }
                        free(lpBuffer);
                    }
                    if (lpResponse) {
                        free(lpResponse);
                    }
                }
                InternetCloseHandle(hHttpRequest);
            }
            InternetCloseHandle(hHttpSession);
        }
        InternetCloseHandle(hIntSession);
    }
}

// Webhook Ban System Logs Discord Server AsepppStore
inline void DiscordWebhookSender3(std::string message) {
    LPCTSTR szUserAgent = _T("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.74 Safari/537.36 Edg/79.0.309.43");
    LPCTSTR szHost = _T("discordapp.com");
    LPCTSTR szUrlPath = _T("api/webhooks/953173915717496892/hj5Bcn1oIv4fNEqJxvwopJ-DV871HJ7qfu8BaUgfxcz7qY1_I0hIM-kLgJiv0_eBMRpz");
    LPCTSTR szAcceptTypes[] = { _T("application/json"), NULL };
    LPCTSTR szContentTypeHeader = _T("Content-Type: application/json");
    LPCSTR szPostData = ("{ \"username\": \"System Logs\", \"embeds\":  \[{\"description\": \"<:mengbanned:952109216779366410> " + message + "\", \"color\": \"65535\"}]}").c_str();

    const DWORD dwPostDataLength = strlen(szPostData);
    HINTERNET hIntSession = InternetOpen(szUserAgent, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hIntSession) {
        HINTERNET hHttpSession = InternetConnect(hIntSession, szHost, INTERNET_DEFAULT_HTTPS_PORT, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);
        if (hHttpSession) {
            HINTERNET hHttpRequest = HttpOpenRequest(hHttpSession, _T("POST"), szUrlPath, NULL, NULL, szAcceptTypes,
                (INTERNET_FLAG_NO_COOKIES | INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE), 0);
            if (hHttpRequest) {
                if (HttpSendRequest(hHttpRequest, szContentTypeHeader, -1, (LPVOID)szPostData, dwPostDataLength)) {
                    DWORD dwStatusCode = 0;
                    {
                        TCHAR szStatusCode[32] = { 0 };
                        DWORD dwStatusCodeSize = sizeof(szStatusCode) / sizeof(TCHAR);
                        if (HttpQueryInfo(hHttpRequest, HTTP_QUERY_STATUS_CODE, szStatusCode, &dwStatusCodeSize, NULL)) {
                            dwStatusCode = _ttoi(szStatusCode);
                        }
                    }
                    unsigned char* lpResponse = NULL;
                    DWORD dwTotalSize = 0;
                    {
                        unsigned char* lpBuffer = (unsigned char*)malloc(2048);
                        DWORD dwRead = 0;
                        while (InternetReadFile(hHttpRequest, lpBuffer, sizeof(lpBuffer), &dwRead) && dwRead) {
                            unsigned char* lpTmp = (unsigned char*)realloc(lpResponse, dwTotalSize + dwRead);
                            if (lpTmp) {
                                lpResponse = lpTmp;
                                memcpy(&lpResponse[dwTotalSize], lpBuffer, dwRead);
                                dwTotalSize += dwRead;
                            }
                            dwRead = 0;
                        }
                        free(lpBuffer);
                    }
                    if (lpResponse) {
                        free(lpResponse);
                    }
                }
                InternetCloseHandle(hHttpRequest);
            }
            InternetCloseHandle(hHttpSession);
        }
        InternetCloseHandle(hIntSession);
    }
}

// Webhook Donate Logs Discord Server EL Store's
inline void DiscordWebhookSender4(std::string message) {
    LPCTSTR szUserAgent = _T("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.74 Safari/537.36 Edg/79.0.309.43");
    LPCTSTR szHost = _T("discordapp.com");
    LPCTSTR szUrlPath = _T("api/webhooks/953530192146624523/ArvJPNf9oDs5JJ6mSbVzXqN20wbdptGErDEPqQJB5bxJpC-cZhKghVVJCWNX8ex8cXM8");
    LPCTSTR szAcceptTypes[] = { _T("application/json"), NULL };
    LPCTSTR szContentTypeHeader = _T("Content-Type: application/json");
    LPCSTR szPostData = ("{ \"username\": \"Donate Logs\", \"embeds\":  \[{\"description\": \"" + message + "\", \"color\": \"65535\"}]}").c_str();

    const DWORD dwPostDataLength = strlen(szPostData);
    HINTERNET hIntSession = InternetOpen(szUserAgent, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hIntSession) {
        HINTERNET hHttpSession = InternetConnect(hIntSession, szHost, INTERNET_DEFAULT_HTTPS_PORT, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);
        if (hHttpSession) {
            HINTERNET hHttpRequest = HttpOpenRequest(hHttpSession, _T("POST"), szUrlPath, NULL, NULL, szAcceptTypes,
                (INTERNET_FLAG_NO_COOKIES | INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE), 0);
            if (hHttpRequest) {
                if (HttpSendRequest(hHttpRequest, szContentTypeHeader, -1, (LPVOID)szPostData, dwPostDataLength)) {
                    DWORD dwStatusCode = 0;
                    {
                        TCHAR szStatusCode[32] = { 0 };
                        DWORD dwStatusCodeSize = sizeof(szStatusCode) / sizeof(TCHAR);
                        if (HttpQueryInfo(hHttpRequest, HTTP_QUERY_STATUS_CODE, szStatusCode, &dwStatusCodeSize, NULL)) {
                            dwStatusCode = _ttoi(szStatusCode);
                        }
                    }
                    unsigned char* lpResponse = NULL;
                    DWORD dwTotalSize = 0;
                    {
                        unsigned char* lpBuffer = (unsigned char*)malloc(2048);
                        DWORD dwRead = 0;
                        while (InternetReadFile(hHttpRequest, lpBuffer, sizeof(lpBuffer), &dwRead) && dwRead) {
                            unsigned char* lpTmp = (unsigned char*)realloc(lpResponse, dwTotalSize + dwRead);
                            if (lpTmp) {
                                lpResponse = lpTmp;
                                memcpy(&lpResponse[dwTotalSize], lpBuffer, dwRead);
                                dwTotalSize += dwRead;
                            }
                            dwRead = 0;
                        }
                        free(lpBuffer);
                    }
                    if (lpResponse) {
                        free(lpResponse);
                    }
                }
                InternetCloseHandle(hHttpRequest);
            }
            InternetCloseHandle(hHttpSession);
        }
        InternetCloseHandle(hIntSession);
    }
}

// Webhook Donate Logs Discord Server Xco Store
inline void DiscordWebhookSender5(std::string message) {
    LPCTSTR szUserAgent = _T("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.74 Safari/537.36 Edg/79.0.309.43");
    LPCTSTR szHost = _T("discordapp.com");
    LPCTSTR szUrlPath = _T("api/webhooks/953530697698660412/D_YB9IjIcPFIi8fo4Yg33q7ph2BB_OYIs8L1KSy4PwvLYlYy3HSexMOzlW7DC7m65f_y");
    LPCTSTR szAcceptTypes[] = { _T("application/json"), NULL };
    LPCTSTR szContentTypeHeader = _T("Content-Type: application/json");
    LPCSTR szPostData = ("{ \"username\": \"Donate Logs\", \"embeds\":  \[{\"description\": \"" + message + "\", \"color\": \"65535\"}]}").c_str();

    const DWORD dwPostDataLength = strlen(szPostData);
    HINTERNET hIntSession = InternetOpen(szUserAgent, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hIntSession) {
        HINTERNET hHttpSession = InternetConnect(hIntSession, szHost, INTERNET_DEFAULT_HTTPS_PORT, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);
        if (hHttpSession) {
            HINTERNET hHttpRequest = HttpOpenRequest(hHttpSession, _T("POST"), szUrlPath, NULL, NULL, szAcceptTypes,
                (INTERNET_FLAG_NO_COOKIES | INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE), 0);
            if (hHttpRequest) {
                if (HttpSendRequest(hHttpRequest, szContentTypeHeader, -1, (LPVOID)szPostData, dwPostDataLength)) {
                    DWORD dwStatusCode = 0;
                    {
                        TCHAR szStatusCode[32] = { 0 };
                        DWORD dwStatusCodeSize = sizeof(szStatusCode) / sizeof(TCHAR);
                        if (HttpQueryInfo(hHttpRequest, HTTP_QUERY_STATUS_CODE, szStatusCode, &dwStatusCodeSize, NULL)) {
                            dwStatusCode = _ttoi(szStatusCode);
                        }
                    }
                    unsigned char* lpResponse = NULL;
                    DWORD dwTotalSize = 0;
                    {
                        unsigned char* lpBuffer = (unsigned char*)malloc(2048);
                        DWORD dwRead = 0;
                        while (InternetReadFile(hHttpRequest, lpBuffer, sizeof(lpBuffer), &dwRead) && dwRead) {
                            unsigned char* lpTmp = (unsigned char*)realloc(lpResponse, dwTotalSize + dwRead);
                            if (lpTmp) {
                                lpResponse = lpTmp;
                                memcpy(&lpResponse[dwTotalSize], lpBuffer, dwRead);
                                dwTotalSize += dwRead;
                            }
                            dwRead = 0;
                        }
                        free(lpBuffer);
                    }
                    if (lpResponse) {
                        free(lpResponse);
                    }
                }
                InternetCloseHandle(hHttpRequest);
            }
            InternetCloseHandle(hHttpSession);
        }
        InternetCloseHandle(hIntSession);
    }
}

// Webhook Donate Logs Discord Server -KuzStore-
inline void DiscordWebhookSender6(std::string message) {
    LPCTSTR szUserAgent = _T("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.74 Safari/537.36 Edg/79.0.309.43");
    LPCTSTR szHost = _T("discordapp.com");
    LPCTSTR szUrlPath = _T("api/webhooks/953536667325722674/MmGjYlAOg6De1UmoPAo319xUXW8aG6kdoQrF2WzJULOkRhexQhuTR-GCwh9Dl2OjOYK3");
    LPCTSTR szAcceptTypes[] = { _T("application/json"), NULL };
    LPCTSTR szContentTypeHeader = _T("Content-Type: application/json");
    LPCSTR szPostData = ("{ \"username\": \"Donate Logs\", \"embeds\":  \[{\"description\": \"" + message + "\", \"color\": \"65535\"}]}").c_str();

    const DWORD dwPostDataLength = strlen(szPostData);
    HINTERNET hIntSession = InternetOpen(szUserAgent, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hIntSession) {
        HINTERNET hHttpSession = InternetConnect(hIntSession, szHost, INTERNET_DEFAULT_HTTPS_PORT, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);
        if (hHttpSession) {
            HINTERNET hHttpRequest = HttpOpenRequest(hHttpSession, _T("POST"), szUrlPath, NULL, NULL, szAcceptTypes,
                (INTERNET_FLAG_NO_COOKIES | INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE), 0);
            if (hHttpRequest) {
                if (HttpSendRequest(hHttpRequest, szContentTypeHeader, -1, (LPVOID)szPostData, dwPostDataLength)) {
                    DWORD dwStatusCode = 0;
                    {
                        TCHAR szStatusCode[32] = { 0 };
                        DWORD dwStatusCodeSize = sizeof(szStatusCode) / sizeof(TCHAR);
                        if (HttpQueryInfo(hHttpRequest, HTTP_QUERY_STATUS_CODE, szStatusCode, &dwStatusCodeSize, NULL)) {
                            dwStatusCode = _ttoi(szStatusCode);
                        }
                    }
                    unsigned char* lpResponse = NULL;
                    DWORD dwTotalSize = 0;
                    {
                        unsigned char* lpBuffer = (unsigned char*)malloc(2048);
                        DWORD dwRead = 0;
                        while (InternetReadFile(hHttpRequest, lpBuffer, sizeof(lpBuffer), &dwRead) && dwRead) {
                            unsigned char* lpTmp = (unsigned char*)realloc(lpResponse, dwTotalSize + dwRead);
                            if (lpTmp) {
                                lpResponse = lpTmp;
                                memcpy(&lpResponse[dwTotalSize], lpBuffer, dwRead);
                                dwTotalSize += dwRead;
                            }
                            dwRead = 0;
                        }
                        free(lpBuffer);
                    }
                    if (lpResponse) {
                        free(lpResponse);
                    }
                }
                InternetCloseHandle(hHttpRequest);
            }
            InternetCloseHandle(hHttpSession);
        }
        InternetCloseHandle(hIntSession);
    }
}

// Webhook Donate Logs Discord Server Q STORE
inline void DiscordWebhookSender7(std::string message) {
    LPCTSTR szUserAgent = _T("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.74 Safari/537.36 Edg/79.0.309.43");
    LPCTSTR szHost = _T("discordapp.com");
    LPCTSTR szUrlPath = _T("api/webhooks/953638597054066750/_PC5hnMUYNBRna4QxeN9cO30EX6nCPlCaWahYOXzWvVjnk-M4gSUyyyji90xBe_xXHNU");
    LPCTSTR szAcceptTypes[] = { _T("application/json"), NULL };
    LPCTSTR szContentTypeHeader = _T("Content-Type: application/json");
    LPCSTR szPostData = ("{ \"username\": \"Donate Logs\", \"embeds\":  \[{\"description\": \"" + message + "\", \"color\": \"65535\"}]}").c_str();

    const DWORD dwPostDataLength = strlen(szPostData);
    HINTERNET hIntSession = InternetOpen(szUserAgent, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hIntSession) {
        HINTERNET hHttpSession = InternetConnect(hIntSession, szHost, INTERNET_DEFAULT_HTTPS_PORT, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);
        if (hHttpSession) {
            HINTERNET hHttpRequest = HttpOpenRequest(hHttpSession, _T("POST"), szUrlPath, NULL, NULL, szAcceptTypes,
                (INTERNET_FLAG_NO_COOKIES | INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE), 0);
            if (hHttpRequest) {
                if (HttpSendRequest(hHttpRequest, szContentTypeHeader, -1, (LPVOID)szPostData, dwPostDataLength)) {
                    DWORD dwStatusCode = 0;
                    {
                        TCHAR szStatusCode[32] = { 0 };
                        DWORD dwStatusCodeSize = sizeof(szStatusCode) / sizeof(TCHAR);
                        if (HttpQueryInfo(hHttpRequest, HTTP_QUERY_STATUS_CODE, szStatusCode, &dwStatusCodeSize, NULL)) {
                            dwStatusCode = _ttoi(szStatusCode);
                        }
                    }
                    unsigned char* lpResponse = NULL;
                    DWORD dwTotalSize = 0;
                    {
                        unsigned char* lpBuffer = (unsigned char*)malloc(2048);
                        DWORD dwRead = 0;
                        while (InternetReadFile(hHttpRequest, lpBuffer, sizeof(lpBuffer), &dwRead) && dwRead) {
                            unsigned char* lpTmp = (unsigned char*)realloc(lpResponse, dwTotalSize + dwRead);
                            if (lpTmp) {
                                lpResponse = lpTmp;
                                memcpy(&lpResponse[dwTotalSize], lpBuffer, dwRead);
                                dwTotalSize += dwRead;
                            }
                            dwRead = 0;
                        }
                        free(lpBuffer);
                    }
                    if (lpResponse) {
                        free(lpResponse);
                    }
                }
                InternetCloseHandle(hHttpRequest);
            }
            InternetCloseHandle(hHttpSession);
        }
        InternetCloseHandle(hIntSession);
    }
}

// Webhook Donate Logs Discord Server Bling Store
inline void DiscordWebhookSender8(std::string message) {
    LPCTSTR szUserAgent = _T("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.74 Safari/537.36 Edg/79.0.309.43");
    LPCTSTR szHost = _T("discordapp.com");
    LPCTSTR szUrlPath = _T("api/webhooks/953845901443624990/pAymq0lhuM0Tvz6mC_1TCZF6cCoVTu2dT2_gNnmEeO9oY9YkanH3Y3gEf5aCf-cj0-Pa");
    LPCTSTR szAcceptTypes[] = { _T("application/json"), NULL };
    LPCTSTR szContentTypeHeader = _T("Content-Type: application/json");
    LPCSTR szPostData = ("{ \"username\": \"Donate Logs\", \"embeds\":  \[{\"description\": \"" + message + "\", \"color\": \"65535\"}]}").c_str();

    const DWORD dwPostDataLength = strlen(szPostData);
    HINTERNET hIntSession = InternetOpen(szUserAgent, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hIntSession) {
        HINTERNET hHttpSession = InternetConnect(hIntSession, szHost, INTERNET_DEFAULT_HTTPS_PORT, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);
        if (hHttpSession) {
            HINTERNET hHttpRequest = HttpOpenRequest(hHttpSession, _T("POST"), szUrlPath, NULL, NULL, szAcceptTypes,
                (INTERNET_FLAG_NO_COOKIES | INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE), 0);
            if (hHttpRequest) {
                if (HttpSendRequest(hHttpRequest, szContentTypeHeader, -1, (LPVOID)szPostData, dwPostDataLength)) {
                    DWORD dwStatusCode = 0;
                    {
                        TCHAR szStatusCode[32] = { 0 };
                        DWORD dwStatusCodeSize = sizeof(szStatusCode) / sizeof(TCHAR);
                        if (HttpQueryInfo(hHttpRequest, HTTP_QUERY_STATUS_CODE, szStatusCode, &dwStatusCodeSize, NULL)) {
                            dwStatusCode = _ttoi(szStatusCode);
                        }
                    }
                    unsigned char* lpResponse = NULL;
                    DWORD dwTotalSize = 0;
                    {
                        unsigned char* lpBuffer = (unsigned char*)malloc(2048);
                        DWORD dwRead = 0;
                        while (InternetReadFile(hHttpRequest, lpBuffer, sizeof(lpBuffer), &dwRead) && dwRead) {
                            unsigned char* lpTmp = (unsigned char*)realloc(lpResponse, dwTotalSize + dwRead);
                            if (lpTmp) {
                                lpResponse = lpTmp;
                                memcpy(&lpResponse[dwTotalSize], lpBuffer, dwRead);
                                dwTotalSize += dwRead;
                            }
                            dwRead = 0;
                        }
                        free(lpBuffer);
                    }
                    if (lpResponse) {
                        free(lpResponse);
                    }
                }
                InternetCloseHandle(hHttpRequest);
            }
            InternetCloseHandle(hHttpSession);
        }
        InternetCloseHandle(hIntSession);
    }
}

// Webhook Donate Logs Discord Server Create ID by SIHAM
inline void DiscordWebhookSender9(std::string message) {
    LPCTSTR szUserAgent = _T("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.74 Safari/537.36 Edg/79.0.309.43");
    LPCTSTR szHost = _T("discordapp.com");
    LPCTSTR szUrlPath = _T("api/webhooks/954351823836291124/wRjYsizMvsJOU2BCUiyHE20pcRYOaayoQ3G20_-r_3xOdXR8JgmkSqQk7wxkAqde0xU6");
    LPCTSTR szAcceptTypes[] = { _T("application/json"), NULL };
    LPCTSTR szContentTypeHeader = _T("Content-Type: application/json");
    LPCSTR szPostData = ("{ \"username\": \"Donate Logs\", \"embeds\":  \[{\"description\": \"" + message + "\", \"color\": \"65535\"}]}").c_str();

    const DWORD dwPostDataLength = strlen(szPostData);
    HINTERNET hIntSession = InternetOpen(szUserAgent, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hIntSession) {
        HINTERNET hHttpSession = InternetConnect(hIntSession, szHost, INTERNET_DEFAULT_HTTPS_PORT, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);
        if (hHttpSession) {
            HINTERNET hHttpRequest = HttpOpenRequest(hHttpSession, _T("POST"), szUrlPath, NULL, NULL, szAcceptTypes,
                (INTERNET_FLAG_NO_COOKIES | INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE), 0);
            if (hHttpRequest) {
                if (HttpSendRequest(hHttpRequest, szContentTypeHeader, -1, (LPVOID)szPostData, dwPostDataLength)) {
                    DWORD dwStatusCode = 0;
                    {
                        TCHAR szStatusCode[32] = { 0 };
                        DWORD dwStatusCodeSize = sizeof(szStatusCode) / sizeof(TCHAR);
                        if (HttpQueryInfo(hHttpRequest, HTTP_QUERY_STATUS_CODE, szStatusCode, &dwStatusCodeSize, NULL)) {
                            dwStatusCode = _ttoi(szStatusCode);
                        }
                    }
                    unsigned char* lpResponse = NULL;
                    DWORD dwTotalSize = 0;
                    {
                        unsigned char* lpBuffer = (unsigned char*)malloc(2048);
                        DWORD dwRead = 0;
                        while (InternetReadFile(hHttpRequest, lpBuffer, sizeof(lpBuffer), &dwRead) && dwRead) {
                            unsigned char* lpTmp = (unsigned char*)realloc(lpResponse, dwTotalSize + dwRead);
                            if (lpTmp) {
                                lpResponse = lpTmp;
                                memcpy(&lpResponse[dwTotalSize], lpBuffer, dwRead);
                                dwTotalSize += dwRead;
                            }
                            dwRead = 0;
                        }
                        free(lpBuffer);
                    }
                    if (lpResponse) {
                        free(lpResponse);
                    }
                }
                InternetCloseHandle(hHttpRequest);
            }
            InternetCloseHandle(hHttpSession);
        }
        InternetCloseHandle(hIntSession);
    }
}