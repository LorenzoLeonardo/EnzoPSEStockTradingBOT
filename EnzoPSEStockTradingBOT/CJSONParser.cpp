#include "pch.h"
#include "CJSONParser.h"

CJSONParser::CJSONParser()
{
	m_sJSONstring = _T("");
}
CJSONParser::CJSONParser(string_t sJSON) 
{
	m_sJSONstring = trim(sJSON);
}
CJSONParser::~CJSONParser() 
{
}

void CJSONParser::SetJSONString(string_t sJSON)
{
	m_sJSONstring = trim(sJSON);
	ParseJSON();
}

void CJSONParser::GetValue(string_t sTag, unsigned long& data)
{
	string_t str = m_sJSONstring.substr(m_sJSONstring.find(sTag) + sTag.length());
	string_t sStack;
	int nIndex = 0, nStart = 0;
	while (nIndex < str.length())
	{
		if (str[nIndex] == _T(':') && sStack.empty())
		{
			sStack.push_back(str[nIndex]);
			nStart = nIndex + 1;
		}
		else if ((str[nIndex] == _T(',') || str[nIndex] == _T('}')) && !sStack.empty())
		{
			sStack.pop_back();
			nIndex--;
			break;
		}
		nIndex++;
	}
	string_t sTemp = str.substr(nStart, nIndex);
	data = _tcstoul(sTemp.c_str(),NULL,0);
}
void CJSONParser::GetValue(string_t sTag, float& data) 
{
	string_t str = m_sJSONstring.substr(m_sJSONstring.find(sTag) + sTag.length());
	string_t sStack;
	int nIndex = 0, nStart = 0;
	while (nIndex < str.length())
	{
		if (str[nIndex] == _T(':') && sStack.empty())
		{
			sStack.push_back(str[nIndex]);
			nStart = nIndex + 1;
		}
		else if ((str[nIndex] == _T(',') || str[nIndex] == _T('}')) && !sStack.empty())
		{
			sStack.pop_back();
			nIndex--;
			break;
		}
		nIndex++;
	}
	string_t sTemp = str.substr(nStart, nIndex);
	data = _ttof(sTemp.c_str());
}
void CJSONParser::GetValue(string_t sTag, string_t& data)
{
	string_t str = m_sJSONstring.substr(m_sJSONstring.find(sTag)+ sTag.length());
	string_t sStack;
	int nIndex = 0, nStart = 0;
	while (nIndex < str.length())
	{
		if (str[nIndex] == _T('\"') && sStack.empty())
		{
			sStack.push_back(str[nIndex]);
			nStart = nIndex+1;
		}
		else if (str[nIndex] == _T('\"') && !sStack.empty())
		{
			sStack.pop_back();
			nIndex--;
			break;
		}
		nIndex++;
	}
	data = str.substr(nStart, nIndex-1);

}
void CJSONParser::GetValue(string_t sJSONstring, string_t sTag, unsigned long& data)
{
	string_t str = sJSONstring.substr(sJSONstring.find(sTag) + sTag.length());
	string_t sStack;
	int nIndex = 0, nStart = 0;
	while (nIndex < str.length())
	{
		if (str[nIndex] == _T(':') && sStack.empty())
		{
			sStack.push_back(str[nIndex]);
			nStart = nIndex + 1;
		}
		else if ((str[nIndex] == _T(',') || str[nIndex] == _T('}')) && !sStack.empty())
		{
			sStack.pop_back();
			nIndex--;
			break;
		}
		nIndex++;
	}
	string_t sTemp = str.substr(nStart, nIndex);
	data = _tcstoul(sTemp.c_str(), NULL, 0);
}
void CJSONParser::GetValue(string_t sJSONstring, string_t sTag, float& data)
{
	string_t str = sJSONstring.substr(sJSONstring.find(sTag) + sTag.length());
	string_t sStack;
	int nIndex = 0, nStart = 0;
	while (nIndex < str.length())
	{
		if (str[nIndex] == _T(':') && sStack.empty())
		{
			sStack.push_back(str[nIndex]);
			nStart = nIndex + 1;
		}
		else if ((str[nIndex] == _T(',') || str[nIndex] == _T('}')) && !sStack.empty())
		{
			sStack.pop_back();
			nIndex--;
			break;
		}
		nIndex++;
	}
	string_t sTemp = str.substr(nStart, nIndex);
	data = _ttof(sTemp.c_str());
}
void CJSONParser::GetValue(string_t sJSONstring, string_t sTag, string_t& data)
{
	string_t str = sJSONstring.substr(sJSONstring.find(sTag) + sTag.length());
	string_t sStack;
	int nIndex = 0, nStart = 0;
	while (nIndex < str.length())
	{
		if (str[nIndex] == _T('\"') && sStack.empty())
		{
			sStack.push_back(str[nIndex]);
			nStart = nIndex + 1;
		}
		else if (str[nIndex] == _T('\"') && !sStack.empty())
		{
			sStack.pop_back();
			nIndex--;
			break;
		}
		nIndex++;
	}
	data = str.substr(nStart, nIndex - 1);
}
void CJSONParser::ParseJSON()
{
	string_t sBraceStack;
	string_t sParenthesisStack;
	size_t length = m_sJSONstring.length();
	size_t nStartOfStockString = 0;
	size_t nEndOfStockString = 0;
	size_t i = 0;

	while(m_sJSONstring[i] != _T('['))
		i++;

	while(i<length)
	{
		if (m_sJSONstring[i] == _T('['))
			sBraceStack.push_back(m_sJSONstring[i]);
		else if (m_sJSONstring[i] == _T('{'))
		{
			if (sParenthesisStack.empty())
			{
				nStartOfStockString = i;
				nEndOfStockString = 0;
			}
			sParenthesisStack.push_back(m_sJSONstring[i]);
		}
		else if (m_sJSONstring[i] == _T('}'))
		{
			sParenthesisStack.pop_back();
			if (sParenthesisStack.empty())
			{
				string_t sTemp = m_sJSONstring.substr(nStartOfStockString, nEndOfStockString+1);
				string_t sStock;
				GetValue(sTemp, _T("\"symbol\""), sStock);
				m_mapStocks[sStock] = sTemp;
			}
		}
		else if (m_sJSONstring[i] == _T(']'))
		{
			sBraceStack.pop_back();
			if (sBraceStack.empty())
				break;
		}
		i++;
		nEndOfStockString++;
	}
	return;
}