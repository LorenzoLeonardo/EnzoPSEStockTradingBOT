#pragma once

#include <string>

#ifndef string_t
    #ifdef UNICODE
        #define string_t std::wstring
    #else
        #define string_t std::string
    #endif
#endif
using namespace std;

class CStock
{
protected:
    string_t        m_sCompanyName;
    string_t        m_sCurrency;
    float           m_fPricePerShare;
    float           m_fPercentChange;
    unsigned long   m_ulVolume;
    string_t        m_sStockSymbol;
    string_t        m_sDate;


public:

    CStock() :m_sCompanyName(_T("")), m_sCurrency(_T("")), m_fPricePerShare(0), m_fPercentChange(0),
        m_ulVolume(0), m_sStockSymbol(_T("")), m_sDate(_T("")){}
    ~CStock() {}

    CStock operator=(const CStock& b)
    {
        this->m_sCompanyName = b.m_sCompanyName;
        this->m_sCurrency = b.m_sCurrency;
        this->m_fPricePerShare = b.m_fPricePerShare;
        this->m_fPercentChange = b.m_fPercentChange;
        this->m_ulVolume = b.m_ulVolume;
        this->m_sStockSymbol = b.m_sStockSymbol;
        this->m_sDate = b.m_sDate;

        return *this;
    }

    void SetCompanyName(string_t sName)
    {
        m_sCompanyName = sName;
    }
    void SetCurrency(string_t sCurrency)
    {
        m_sCurrency = sCurrency;
    }
    void SetPricePerShare(float fPricePerShare)
    {
        m_fPricePerShare = fPricePerShare;
    }
    void SetPercentChange(float fPercentChange)
    {
        m_fPercentChange = fPercentChange;
    }
    void SetVolume(ULONG ulVolume)
    {
        m_ulVolume = ulVolume;
    }
    void SetStockSymbol(string_t sStockSymbol)
    {
        m_sStockSymbol = sStockSymbol;
    }
    void SetDate(string_t sDate)
    {
        m_sDate = sDate;
    }


    string_t GetCompanyName()
    {
        return m_sCompanyName;
    }
    string_t GetCurrency()
    {
        return m_sCurrency;
    }
    float GetPricePerShare()
    {
        return m_fPricePerShare;
    }
    float GetPercentChange()
    {
        return m_fPercentChange;
    }
    ULONG GetVolume()
    {
        return m_ulVolume;
    }
    string_t GetStockSymbol()
    {
        return m_sStockSymbol;
    }
    string_t GetDate()
    {
        return m_sDate;
    }

};