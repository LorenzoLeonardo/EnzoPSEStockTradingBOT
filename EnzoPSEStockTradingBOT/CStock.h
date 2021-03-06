#pragma once
#include <vector>
#include <string>
using namespace std;

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
    string_t        m_sTime;
    string_t        m_sGMT;
    int             m_nGMT;
    ULONG           m_ulTime;
    vector<CStock>  m_vChangeHistory;

    inline ULONG StringTimeToUlong(string_t sTime)
    {
        TCHAR* stopstring;
        string_t sTemp;

        sTemp = sTime.substr(0, sTime.find(_T(":")));
        ULONG ulHR = wcstoul(sTemp.c_str(), &stopstring, 10);
        sTemp = sTime.substr(sTime.find(_T(":")) + 1, 2);
        ULONG ulMin = wcstoul(sTemp.c_str(), &stopstring, 10);
        sTemp = sTime.substr(sTime.rfind(_T(":")) + 1, 2);
        ULONG ulSec = wcstoul(sTemp.c_str(), &stopstring, 10);
        return (ulHR * 60 * 60) + ulMin * 60 + ulSec;
    }
public:

    CStock() :m_sCompanyName(_T("")), m_sCurrency(_T("")), m_fPricePerShare(0), m_fPercentChange(0),
        m_ulVolume(0), m_sStockSymbol(_T("")), m_sDate(_T("")), m_sTime(_T("")), m_nGMT(0), m_ulTime(0) {}
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
        this->m_sTime = b.m_sTime;
        this->m_sGMT = b.m_sGMT;
        this->m_nGMT = b.m_nGMT;
        this->m_ulTime = b.m_ulTime;
        this->m_vChangeHistory.assign(b.m_vChangeHistory.begin(), b.m_vChangeHistory.end());
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
        //2022-02-21T12:50:00+08:00
        m_sDate = sDate.substr(0,sDate.find(_T("T")));
        m_sTime = sDate.substr(sDate.find(_T("T"))+1, (sDate.find(_T("+")) - sDate.find(_T("T"))-1));
        if(sDate.find(_T("+")) != string_t::npos)
            m_sGMT = sDate.substr(sDate.find(_T("+")), sDate.length() - sDate.find(_T("+")));
        else if(sDate.find(_T("-")) != string_t::npos)
            m_sGMT = sDate.substr(sDate.find(_T("-")), sDate.length() - sDate.find(_T("-")));

        m_nGMT = _ttoi(m_sGMT.c_str());
        m_ulTime = StringTimeToUlong(m_sTime);
    }
    void SetTime(string_t sTime)
    {
        m_sTime = sTime;
    }
    void SetGMT(string_t sGMT)
    {
        m_sGMT = sGMT;
    }
    void SetGMT(int ulGMT)
    {
        m_nGMT = ulGMT;
    }
    void SetTimeUL(ULONG ulTime)
    {
        m_ulTime = ulTime;
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
    string_t GetTime()
    {
        return m_sTime;
    }
    string_t GetGMT()
    {
        return m_sGMT;
    }
    int GetGMTInt()
    {
        return m_nGMT;
    }
    ULONG GetTimeUl()
    {
        return m_ulTime;
    }

    vector<CStock> GetChangeHistory()
    {
        return m_vChangeHistory;
    }
    void AddToChangeHistory(CStock stock)
    {
        m_vChangeHistory.push_back(stock);
    }
    void AddToChangeHistory(vector<CStock> vstock)
    {
        m_vChangeHistory.assign(vstock.begin(), vstock.end());
    }
};