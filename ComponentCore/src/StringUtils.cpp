/*
Written by Nack li <nackli@163.com>
Copyright (c) 2024. All Rights Reserved.
*/

#include "StringUtils.h"
#include <algorithm>
#include <sstream>
#include <iomanip> 
#include <codecvt> 
#include <iostream>
#include <wchar.h>
#include <random>
/**************************************************************************************************************************************/
static const std::string g_strBase64Chars ="ABCDEFGHIJKLMNOPQRSTUVWXYZ""abcdefghijklmnopqrstuvwxyz""0123456789+/";
/**************************************************************************************************************************************/
template <typename T>
/**
 * @brief 
 * @tparam T 
 * @param tData 
 * @param iBase 
 * @param uWidth 
 * @param chFill 
 * @param iPrecision 
 * @return 
*/
static std::string OnDigit2String(T tData, int iBase, unsigned char uWidth = 0, char chFill = '0', int iPrecision = 6)
{
    std::ostringstream ss;
    if (uWidth && chFill)
        ss << std::setw(uWidth) << std::setfill(chFill);

    if (iBase == 8)
        ss <</* std::setiosflags(std::ios::uppercase) <<*/ std::oct;
    else if (iBase == 10)
        ss <</* std::setiosflags(std::ios::uppercase) <<*/ std::dec;
    else if (iBase == 16)
        ss <</* std::setiosflags(std::ios::uppercase) <<*/ std::hex;
    else if (typeid(tData) == typeid(float) || typeid(tData) == typeid(double))
        ss <</* std::setiosflags(std::ios::uppercase) <<*/ std::fixed << std::setprecision(iPrecision);
    ss << tData;
    return std::move(ss.str());
}
/**
 * @brief 
 * @param strUUID 
 * @return 
*/
static std::string str2UUIDFomat(std::string strUUID)
{
    if (strUUID.length() < 32)
        return std::string();
    std::string strResult = strUUID.substr(0, 8);
    for (int i = 0; i < 3; i++)
    {
        strResult += "-";
        strResult += strUUID.substr(strResult.length() - i - 1, 4);
    }
    strResult += "-";
    strResult += strUUID.substr(20);
    return strResult;
}
/**************************************************************************************************************************************/
std::string &StringUtils::trimLeft(std::string &strInput,const std::string strTrim)
{
    if (strInput.empty() || strTrim.empty())
        return strInput;
    strInput.erase(0, strInput.find_first_not_of(strTrim));
    return strInput;
}
/**
 * @brief 
 * @param strInput 
 * @param strTrim 
 * @return 
*/
std::string &StringUtils::trimRight(std::string &strInput, const std::string strTrim) 
{
    //strInput.erase(std::find_if(strInput.rbegin(), strInput.rend(), [](unsigned char c) -> bool { return !isspace(c); }).base(), strInput.end());
    if (strInput.empty() || strTrim.empty())
        return strInput;
    strInput.erase(strInput.find_last_not_of(strTrim) + 1);
    return strInput;
}
/**
 * @brief 
 * @param strInput 
 * @param strTrim 
 * @return 
*/
std::string &StringUtils::trim(std::string& strInput, const std::string  strTrim)
{
    return trimRight(trimLeft(strInput, strTrim), strTrim);
}
/**
 * @brief 
 * @param szLeft 
 * @param szRight 
 * @param bCaseSensitive 
 * @return 
*/
bool StringUtils::equals(const char * szLeft, const char *szRight,bool bCaseSensitive)
{
    if (bCaseSensitive)
#ifdef WIN32    
        return std::strcmp(szLeft, szRight) == 0;
#else
        return strcmp(szLeft, szRight) == 0;
#endif
    else
#ifdef WIN32    
        return _strcmpi(szLeft, szRight) == 0;
#else
        return strcasecmp(szLeft, szRight) == 0;
#endif 
    return false;
}
/**
 * @brief 
 * @param strLeft 
 * @param strRight 
 * @param bCaseSensitive 
 * @return 
*/
bool StringUtils::equals(const std::string& strLeft, const std::string& strRight, bool bCaseSensitive)
{
    return equals(strLeft.c_str(), strRight.c_str(), bCaseSensitive);
}
/**
 * @brief 
 * @param str 
 * @return 
*/
bool StringUtils::toLower(std::string &str)
{
    return std::transform(str.begin(), str.end(), str.begin(), ::tolower) == str.end();
}
/**
 * @brief 
 * @param str 
 * @return 
*/
bool StringUtils::toUpper(std::string &str)
{
    return std::transform(str.begin(), str.end(), str.begin(), ::toupper) == str.end();
}
/**
 * @brief 
 * @param strValue 
 * @param strStart 
 * @param case_sensitive 
 * @return 
*/
bool StringUtils::startsWith(const std::string strValue, const std::string strStart, bool case_sensitive)
{
    if (strStart.length() > strValue.length())
        return false;

    if (case_sensitive) 
        return std::equal(strStart.begin(), strStart.end(), strValue.begin());
  
    return std::equal(strStart.begin(), strStart.end(), strValue.begin(), [](unsigned char lc, unsigned char rc) {return tolower(lc) == tolower(rc); });
}
/**
 * @brief 
 * @param strValue 
 * @param strEnd 
 * @param case_sensitive 
 * @return 
*/
bool StringUtils::endsWith(const std::string strValue, const std::string strEnd, bool case_sensitive) {
    if (strEnd.length() > strValue.length() || strValue.empty() || strEnd.empty())
        return false;

    if (case_sensitive) 
        return std::equal(strEnd.rbegin(), strEnd.rend(), strValue.rbegin());
   
    return std::equal(strEnd.rbegin(), strEnd.rend(), strValue.rbegin(), [](unsigned char lc, unsigned char rc) {return tolower(lc) == tolower(rc); });
}
/**
 * @brief 
 * @param strInput 
 * @param chDelimiter 
 * @return 
*/
std::pair<std::string, std::string> StringUtils::spiltKv(const std::string strInput, char chDelimiter)
{
    if (strInput.empty())
        return {};
    size_t uFirstEqualPos = strInput.find(chDelimiter);
    if (uFirstEqualPos == std::string::npos)
        return {};
    std::string strKey = strInput.substr(0, uFirstEqualPos);
    strKey = trim(strKey);
    if (strKey.empty())
        return {};
    std::string strValue = strInput.substr(uFirstEqualPos + 1);
    strValue = trim(strValue);
    return { strKey, strValue };
}
/**
 * @brief 
 * @param strInput 
 * @param chDelimiter 
 * @return 
*/
std::string StringUtils::spiltLast(const std::string strInput, char chDelimiter)
{
    if (strInput.empty())
        return std::string();
    size_t uFirstEqualPos = strInput.rfind(chDelimiter);
    if (uFirstEqualPos == std::string::npos)
        return std::string();
    std::string strExt = strInput.substr(uFirstEqualPos + 1);
    return std::move(trim(strExt));
}
/**
 * @brief 
 * @param strInput 
 * @return 
*/
bool StringUtils::str2Bool(std::string strInput)
{
    if (strInput.empty())
        return false;
    std::string trimmed = trim(strInput);
    if (equals(trimmed, "true",false) || equals(trimmed, "yes", false) || equals(trimmed, "ok", false))
        return true;

    if (equals(trimmed, "false",false) || equals(trimmed, "no", false) || equals(trimmed, "cancel", false))
        return false;
 
    return false;
}
/**
 * @brief 
 * @param strInput 
 * @param strFrom 
 * @param strTo 
 * @return 
*/
bool StringUtils::replaceOne(std::string& strInput, const std::string& strFrom, const std::string& strTo) 
{
    bool fRet = false;
    if (strInput.empty() || strFrom.empty() || strTo.empty())
        return false;

    std::size_t iStartPot = strInput.find(strFrom);
    if (iStartPot == std::string::npos)
        return fRet;

    if (!strInput.replace(iStartPot, strFrom.length(), strTo).empty())
        fRet = true;
    return fRet;
}
/**
 * @brief 
 * @param strSource 
 * @param strFrom 
 * @param strTo 
*/
void StringUtils::replaceAll(std::string& strSource, const std::string& strFrom, const std::string& strTo) 
{
    if (strSource.empty() || strFrom.empty() || strTo.empty())
        return;
    std::size_t loc = 0;
    std::size_t lastFound;
    while ((lastFound = strSource.find(strFrom, loc)) != std::string::npos) 
    {
        strSource.replace(lastFound, strFrom.size(), strTo);
        loc = lastFound + strTo.size();
        if (strFrom.empty()) 
            loc++;
    }
}
/**
 * @brief 
 * @param strData 
 * @param strFrom 
 * @param strTo 
 * @return 
*/
bool StringUtils::replaceLast(std::string& strData, const std::string& strFrom, const std::string& strTo)
{
    if (strData.empty() || strFrom.empty() || strTo.empty())
        return false;
    size_t start_pos = strData.rfind(strFrom);
    if (start_pos == std::string::npos)
        return false;
    strData.replace(start_pos, strFrom.length(), strTo);
    return true;
}
/**
 * @brief 
 * @param strTypeName 
 * @return 
*/
std::string StringUtils::getTypeName2WithDot(const std::string &strTypeName)
{
    const std::string strClassPrefix = "class ";
    const std::string strStructPrefix = "struct ";
    const std::string strEnumPrefix = "enum ";
    std::string strOlnyTypeName = strTypeName;
    if (startsWith(strOlnyTypeName, strClassPrefix))
        strOlnyTypeName = trimLeft(strOlnyTypeName, strClassPrefix);

    else if (startsWith(strOlnyTypeName, strStructPrefix))
        strOlnyTypeName = trimLeft(strOlnyTypeName, strClassPrefix);

    else if (startsWith(strOlnyTypeName, strEnumPrefix))
        strOlnyTypeName = trimLeft(strOlnyTypeName, strClassPrefix);
    replaceAll(strOlnyTypeName, "::", ".");
    return strOlnyTypeName;
}
/**
 * @brief 
 * @param strInput 
 * @return 
*/
std::string StringUtils::ascii2HexString(const std::string& strInput)
{
    if (strInput.empty())
        return std::string();
    std::string strRetData = "0x";

    for (std::string::const_iterator it = strInput.begin(); it != strInput.end(); it++)
        strRetData += OnDigit2String<int>(*it, 16, 2);

    return strRetData;
}
/**
 * @brief 
 * @param strInput 
 * @return 
*/
std::string StringUtils::hexString2Ascii(const std::string& strInput)
{
    if(strInput.empty())
        return std::string();
    std::string strHex = std::move(strInput.substr(2));//DEL HEAR 0X
    std::stringstream ss;
    do 
    {
        ss.put((char)std::strtol(strHex.substr(0, 2).c_str(), nullptr, 16));
        if(strHex.length() > 2)
            strHex = strHex.substr(2);
        else
            strHex = strHex.substr(strHex.length());
    } while (!strHex.empty());

    return std::move(ss.str());
}
/**
 * @brief 
 * @param iData 
 * @param iBase 
 * @param iWidth 
 * @param chFill 
 * @return 
*/
std::string StringUtils::digit2Str(int iData, const int iBase, const int iWidth, const char chFill)
{
    return OnDigit2String<int>(iData, iBase, iWidth, chFill);
}
/**
 * @brief 
 * @param lData 
 * @param iBase 
 * @param iWidth 
 * @param chFill 
 * @return 
*/
std::string StringUtils::digit2Str(long lData, const int iBase, const int iWidth, const char chFill)
{
    return OnDigit2String<long>(lData, iBase, iWidth, chFill);
}
/**
 * @brief 
 * @param lData 
 * @param iBase 
 * @param iWidth 
 * @param chFill 
 * @return 
*/
std::string StringUtils::digit2Str(unsigned int lData, const int iBase, const int iWidth, const char chFill)
{
    return OnDigit2String<unsigned int>(lData, iBase, iWidth, chFill);
}
/**
 * @brief 
 * @param lData 
 * @param iBase 
 * @param iWidth 
 * @param chFill 
 * @return 
*/
std::string StringUtils::digit2Str(unsigned long lData, const int iBase, const int iWidth, const char chFill)
{
    return OnDigit2String<unsigned long>(lData, iBase, iWidth, chFill);
}
/**
 * @brief 
 * @param lData 
 * @param iBase 
 * @param iWidth 
 * @param chFill 
 * @return 
*/
std::string StringUtils::digit2Str(long long lData, const int iBase, const int iWidth, const char chFill)
{
    return OnDigit2String<long long>(lData, iBase, iWidth, chFill);
}
/**
 * @brief 
 * @param lData 
 * @param iBase 
 * @param iWidth 
 * @param chFill 
 * @return 
*/
std::string StringUtils::digit2Str(unsigned long long lData, const int iBase,  const int iWidth, const char chFill)
{
    return OnDigit2String<unsigned long long>(lData, iBase, iWidth, chFill);
}
/**
 * @brief 
 * @param lData 
 * @param iBase 
 * @param iWidth 
 * @param chFill 
 * @param iPrecision 
 * @return 
*/
std::string StringUtils::digit2Str(double lData, const int iBase, const int iWidth, const char chFill, const int iPrecision)
{
    return OnDigit2String<double>(lData, iBase, iWidth, chFill, iPrecision);
}
/**
 * @brief 
 * @param lData 
 * @param iBase 
 * @param iWidth 
 * @param chFill 
 * @param iPrecision 
 * @return 
*/
std::string StringUtils::digit2Str(float lData, const int iBase, const int iWidth, const char chFill,  const int iPrecision)
{
    return OnDigit2String<float>(lData, iBase, iWidth, chFill, iPrecision);
}
/**
 * @brief 
 * @param strInt 
 * @return 
*/
int StringUtils::str2Int(std::string strInt)
{
    return transFomat<int>(strInt);
}
/**
 * @brief 
 * @param strDigit 
 * @return 
*/
unsigned int StringUtils::str2Uint(std::string strDigit)
{
    return transFomat<unsigned int>(strDigit);
}
/**
 * @brief 
 * @param strDigit 
 * @return 
*/
long StringUtils::str2Long(std::string strDigit)
{
    return transFomat<long>(strDigit);
}
/**
 * @brief 
 * @param strDigit 
 * @return 
*/
unsigned long StringUtils::str2Ulong(std::string strDigit)
{
    return transFomat<unsigned long>(strDigit);
}
/**
 * @brief 
 * @param strDigit 
 * @return 
*/
long long StringUtils::str2LongLong(std::string strDigit)
{
    return transFomat<long long>(strDigit);
}
/**
 * @brief 
 * @param strDigit 
 * @return 
*/
unsigned long long StringUtils::str2ULongLong(std::string strDigit) 
{
    return transFomat<unsigned long long>(strDigit);
}
/**
 * @brief 
 * @param strDigit 
 * @return 
*/
double StringUtils::str2Double(std::string strDigit) 
{
    return transFomat<double>(strDigit);
}
/**
 * @brief 
 * @param strDigit 
 * @return 
*/
float StringUtils::str2Float(std::string strDigit)
{
    return transFomat<float>(strDigit);
}
/**
 * @brief 
 * @param szByteData 
 * @param uLen 
 * @return 
*/
std::string StringUtils::toBase64(const char* szByteData, unsigned int uLen)
{
    std::string ret = std::string();
    if (!szByteData)
        return ret;
    if (!uLen)
        uLen = strlen(szByteData);
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3] = {0};  // store 3 byte of bytes_to_encode
    unsigned char char_array_4[4] = {0};  // store encoded character to 4 bytes

    while (uLen--) 
    {
        char_array_3[i++] = *(szByteData++);  // get three bytes (24 bits)
        if (i == 3) 
        {
            // eg. we have 3 bytes as ( 0100 1101, 0110 0001, 0110 1110) --> (010011, 010110, 000101, 101110)
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2; // get first 6 bits of first byte,
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4); // get last 2 bits of first byte and first 4 bit of second byte
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6); // get last 4 bits of second byte and first 2 bits of third byte
            char_array_4[3] = char_array_3[2] & 0x3f; // get last 6 bits of third byte

            for (i = 0; (i < 4); i++)
                ret += g_strBase64Chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

        for (j = 0; (j < i + 1); j++)
            ret += g_strBase64Chars[char_array_4[j]];

        while ((i++ < 3))
            ret += '=';

    }

    return ret;
}
/**
 * @brief 
 * @param c 
 * @return 
*/
inline bool StringUtils::IsBase64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}
/**
 * @brief 
 * @param strBase64 
 * @return 
*/
std::string StringUtils::fromBase64(const std::string& strBase64)
{
    if (strBase64.empty())
        return std::string();

    size_t iBaseLen = strBase64.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;

    while (iBaseLen-- && (strBase64[in_] != '=') && IsBase64(strBase64[in_]))
    {
        char_array_4[i++] = strBase64[in_]; 
        in_++;
        if (i == 4) 
        {
            for (i = 0; i < 4; i++)
                char_array_4[i] = g_strBase64Chars.find(char_array_4[i]) & 0xff;

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }

    if (i) 
    {
        for (j = 0; j < i; j++)
            char_array_4[j] = g_strBase64Chars.find(char_array_4[j]) & 0xff;

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);

        for (j = 0; (j < i - 1); j++) 
            ret += char_array_3[j];
    }

    return ret;
}
/**
 * @brief 
 * @param strFormat 
 * @param theTime 
 * @return 
*/
std::string StringUtils::time2String(const std::string strFormat, const time_t theTime)
{
    if (strFormat.empty())
        return std::string();
    time_t iTime = theTime;
    if(iTime < 0)
        iTime = time(&iTime);

    struct tm timeinfo = { 0 };
#ifdef WIN32 
    localtime_s(&timeinfo, &iTime);
#else
    struct tm *pTm  = localtime(&iTime);
    memcpy(&timeinfo, pTm, sizeof(timeinfo));
#endif 

    std::ostringstream os;
    os << std::put_time(&timeinfo, strFormat.c_str());
    return os.str();
}
/**
 * @brief 
 * @param strFormat 
 * @param strTimer 
 * @return 
*/
time_t StringUtils::string2Timer(const std::string strFormat, const std::string strTimer)
{
    struct tm timeinfo = { 0 };
    if (strFormat.empty() || strTimer.empty())
        return -1;
    std::istringstream os(strTimer);
    os >> std::get_time(&timeinfo, strFormat.c_str());
    if (os.fail())
        return -1;
    return mktime(&timeinfo);
}
/**
 * @brief 
 * @param str 
 * @return 
*/
std::wstring StringUtils::UTF8ToUnicode(const std::string str)
{
    std::wstring ret;
    try {
        std::wstring_convert< std::codecvt_utf8<wchar_t> > wcv;
        ret = wcv.from_bytes(str);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return ret;
}
/**
 * @brief 
 * @param wstr 
 * @return 
*/
std::string StringUtils::UnicodeToUTF8(const std::wstring wstr)
{
    std::string ret;
    try {
        std::wstring_convert< std::codecvt_utf8<wchar_t> > wcv;
        ret = wcv.to_bytes(wstr);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return ret;
}
/**
 * @brief 
 * @param wstr 
 * @return 
*/
std::string StringUtils::UnicodeToANSI(const std::wstring& wstr)
{
    std::string ret;
#ifdef WIN32 
    std::mbstate_t state = {};
    size_t uRetValue = 0;
    const wchar_t* src = wstr.data();
    errno_t errNo = wcsrtombs_s(&uRetValue, nullptr, 0, &src, wstr.length(), &state);
    if (!errNo)
    {
        uRetValue += 1;
        std::unique_ptr< char[] > buff(new char[uRetValue]);
        errNo = wcsrtombs_s(&uRetValue, buff.get(), uRetValue , &src, uRetValue, &state);

        if (!errNo)
            ret.assign(buff.get(), uRetValue);
    }
#else
    // int errNo = wcsrtombs(&uRetValue, nullptr, 0, &src, wstr.length(), &state);
    // if (!errNo)
    // {
    //     uRetValue += 1;
    //     std::unique_ptr< char[] > buff(new char[uRetValue]);
    //     errNo = wcsrtombs(&uRetValue, buff.get(), uRetValue , &src, uRetValue, &state);

    //     if (!errNo)
    //         ret.assign(buff.get(), uRetValue);
    // }
#endif    
    return ret;
}
/**
 * @brief 
 * @param str 
 * @return 
*/
std::wstring StringUtils::ANSIToUnicode(const std::string& str)
{
    std::wstring ret;
 #ifdef WIN32       
    std::mbstate_t state = {};
    size_t uRetValue = 0;
    const char* src = str.data();
    errno_t errNo = mbsrtowcs_s(&uRetValue, nullptr, 0, &src, str.length(), &state);
    if (!errNo)
    {
        uRetValue += 1;
        std::unique_ptr< wchar_t[] > buff(new wchar_t[uRetValue]);
        errNo = mbsrtowcs_s(&uRetValue, buff.get(), uRetValue, &src, str.length(), &state);

        if (!errNo)
            ret.assign(buff.get(), uRetValue);
    }
#endif
    return ret;
}
/**
 * @brief 
 * @param str 
 * @return 
*/
std::string StringUtils::UTF8ToANSI(const std::string& str)
{
    return UnicodeToANSI(UTF8ToUnicode(str));
}
/**
 * @brief 
 * @param str 
 * @return 
*/
std::string StringUtils::ANSIToUTF8(const std::string& str)
{
    return UnicodeToUTF8(ANSIToUnicode(str));
}
/**
 * @brief 
 * @return 
*/
std::string StringUtils::generateUUID() 
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> disInt;

    uint64_t part1 = disInt(gen);
    uint64_t part2 = disInt(gen);

    std::ostringstream oss;
    oss << /*std::uppercase <<*/ std::hex << part1 << part2;
    std::string strResult = str2UUIDFomat(std::move(oss.str()));
    return strResult.substr(0, 36); 
}