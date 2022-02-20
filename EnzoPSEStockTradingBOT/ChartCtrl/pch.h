// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"
#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <conio.h>
#include <string.h>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include "CStock.h"
#include "CJSONParser.h"

#ifdef _DEBUG
#pragma comment(lib,"cpprest142_2_10d.lib")
#else
#pragma comment(lib,"cpprest142_2_10.lib")
#endif
using namespace std;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

#endif //PCH_H
