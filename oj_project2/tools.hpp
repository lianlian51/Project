#pragma once

#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <vector>

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
};


class StringUtil
{
  public:
    static void Split(const std::string& input, const std::string& split_char, std::vector<std::string>* output)
    {
      boost::split(*output, input, boost::is_any_of(split_char), boost::token_compress_off);
    }
};
