#pragma once

#include <sys/time.h>
#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <unordered_map>
#include <fstream>

class FileUtil
{
  public:
    // filenam: 读的文件
    // content: 出参
    static bool ReadFile(const std::string& filename, std::string* content)
    {
      content->clear();

      std::ifstream file(filename.c_str());

      if(!file.is_open())
      {
        return false;
      }

      std::string line;
      while(getline(file, line))
      {
        (*content) += line + "\n";
      }

      file.close();
      return true;
    }

    static bool WriteFile(const std::string& filename, const std::string data)
    {
      std::ofstream file(filename.c_str());
      if(!file.is_open())
      {
        return false;
      }

      file.write(data.c_str(), data.size());
      file.close();
      return true;
    }
};


class StringUtil
{
  public:
    static void Split(const std::string& input, const std::string& split_char, std::vector<std::string>* output)
    {
      boost::split(*output, input, boost::is_any_of(split_char), boost::token_compress_off);
    }
};


class UrlUtil
{
  public:

    //body从httplib.h当中的request类的成员变量获得
    //        //  body:
    //        //     key=value&key1=value1   ===> 并且是进行过编码
    //        //  1.先切割
    //        //  2.在对切割之后的结果进行转码


    static unsigned char ToHex(unsigned char x)   
    {   
      return  x > 9 ? x + 55 : x + 48;   
    }  

    static unsigned char FromHex(unsigned char x)   
    {   
      unsigned char y;  
      if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;  
      else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;  
      else if (x >= '0' && x <= '9') y = x - '0';  
      else assert(0);  
      return y;  
    }  

    static std::string UrlEncode(const std::string& str)  
    {  
      std::string strTemp = "";  
      size_t length = str.length();  
      for (size_t i = 0; i < length; i++)  
      {  
        if (isalnum((unsigned char)str[i]) ||   
            (str[i] == '-') ||  
            (str[i] == '_') ||   
            (str[i] == '.') ||   
            (str[i] == '~'))  
          strTemp += str[i];  
        else if (str[i] == ' ')  
          strTemp += "+";  
        else  
        {  
          strTemp += '%';  
          strTemp += ToHex((unsigned char)str[i] >> 4);  
          strTemp += ToHex((unsigned char)str[i] % 16);  
        }  
      }  
      return strTemp;  
    }  

    static std::string UrlDecode(const std::string& str)  
    {  
      std::string strTemp = "";  
      size_t length = str.length();  
      for (size_t i = 0; i < length; i++)  
      {  
        if (str[i] == '+') strTemp += ' ';  
        else if (str[i] == '%')  
        {  
          assert(i + 2 < length);  
          unsigned char high = FromHex((unsigned char)str[++i]);  
          unsigned char low = FromHex((unsigned char)str[++i]);  
          strTemp += high*16 + low;  
        }  
        else strTemp += str[i];  
      }  
      return strTemp;  
    } 


    static void PraseBody(const std::string& body, std::unordered_map<std::string, std::string>* body_kv) 
    {
      std::vector<std::string> kv_vec;
      StringUtil::Split(body, "&", &kv_vec);

      for(const auto& t : kv_vec)
      {
        std::vector<std::string> sig_kv;
        StringUtil::Split(t, "=", &sig_kv);

        if(sig_kv.size() != 2)
        {
          continue;
        }

        // 保存的时候，针对value进行转码
        (*body_kv)[sig_kv[0]] = UrlDecode(sig_kv[1]);
      }
    }
};

class TimeUtil
{
  public:
    static int64_t GetTimeStampMs()
    {
      struct timeval tv;
      gettimeofday(&tv, NULL);
      return tv.tv_sec + tv.tv_usec / 1000;
    }

    static void GetTimeStamp(std::string* TimeStamp)
    {
      time_t st;
      time(&st);

      struct tm* t = localtime(&st);
      
      char buf[30] = {0};
      snprintf(buf, sizeof(buf) - 1, "%04d-%02d-%02d %02d:%02d:%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
      TimeStamp->assign(buf, strlen(buf));
    }
};

enum LogLevel
{
  INFO = 0,
  WARNING,
  ERROR,
  FATAL,
  DEUBG 
};


const char* Level[] = 
{
  "INFO",
  "WARNING",
  "ERROR",
  "FATAL",
  "DEUBG"
};

inline std::ostream& Log(LogLevel lev, const char* file, int line, const std::string& logmsg)
{
  std::string level_info = Level[lev];
  std::string TimeStamp;
  TimeUtil::GetTimeStamp(&TimeStamp);
  
  std::cout << "[" << TimeStamp << " " << level_info << " " << file << ":" << line << "]" << " " << logmsg;
  return std::cout;
}

#define LOG(lev, msg) Log(lev, __FILE__, __LINE__, msg)

