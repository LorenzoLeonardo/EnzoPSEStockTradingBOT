#pragma once
#include <string>
#include <functional>
#include <tchar.h>
#include <map>
using namespace std;

#ifndef string_t
#ifdef UNICODE
#define string_t std::wstring
#else
#define string_t std::string
#endif
#endif


class CJSONParser
{
protected:
	string_t m_sJSONstring;
    map<string_t, string_t> m_mapStocks;

    inline string_t& ltrim(string_t& s)
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
    }
    inline string_t& rtrim(string_t& s)
    {
        s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
    }
    inline string_t& trim(string_t& s)
    {
        return ltrim(rtrim(s));
    }
    inline string_t& removespaces(string_t& sMain)
    {
        sMain.erase(std::remove(sMain.begin(), sMain.end(), _T(' ')), sMain.end());
        return sMain;
    }
    void ParseJSON();
public:
    CJSONParser();
    CJSONParser(string_t sJSON);
    ~CJSONParser();
    void SetJSONString(string_t sJSON);
    void GetValue(string_t sTag, unsigned long &data);
    void GetValue(string_t sTag, float& data);
    void GetValue(string_t sTag, string_t& data);
    void GetValue(string_t sJSONstring, string_t sTag, unsigned long& data);
    void GetValue(string_t sJSONstring, string_t sTag, float& data);
    void GetValue(string_t sJSONstring, string_t sTag, string_t& data);
    map<string_t, string_t> GetParsedStrings()
    {
        return m_mapStocks;
    }
};

