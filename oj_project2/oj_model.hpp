#pragma once 

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

#include <boost/algorithm/string.hpp>


#include "tools.hpp"

struct Question{
  std::string id_;
  std::string title_;
  std::string star_;
  std::string path_;

  std::string desc_;  // 题目描述信息
  std::string header_cpp_;  // 题目预定义的头
  std::string tail_cpp_;    // 题目的尾以及测试用例
};


class OjModel
{
  public:
    OjModel()
    {
      Load("./oj_data/oj_config.cfg");
    }

    ~OjModel()
    {

    }

    bool Load(const std::string& filename)
    {
      // 将文件读出来，进行处理
      std::ifstream file(filename.c_str());
      // 文件是否读取成功
      if(!file.is_open())
      {
        std::cout << "file read failed" << std::endl;
        return false;
      }

      // 文件读取成功，将每一行的数据保存到结构体当中，最后保存到私有变量map中
      std::string line;
      while(getline(file, line))
      {
        // 切割
        // is_any_of : 支持多个字符切割
        // token_compress_off : 是否压缩，将多个字符看成一个
        std::vector<std::string> vec;
        // StringUtil::Split(line, "\t", &vec);
        boost::split(vec, line, boost::is_any_of(" "), boost::token_compress_off);

        Question ques;
        ques.id_ = vec[0];
        ques.title_ = vec[1];
        ques.star_ = vec[2];
        ques.path_ = vec[3];

        std::string dir = vec[3];
        FileUtil::ReadFile(dir + "desc.txt", &ques.desc_);
        FileUtil::ReadFile(dir + "header.cpp", &ques.header_cpp_);
        FileUtil::ReadFile(dir + "tail.cpp", &ques.tail_cpp_);
        
        ques_map_[ques.id_] = ques;
      }

      file.close();
      return true;
    }

    bool GetAllQuestion(std::vector<Question>* questions)
    {
      // 调用这个函数，将试题返回给调用者
      // 遍历ques_map，每一个都是Question结构体对象
      for(const auto &kv : ques_map_)
      {
        questions->push_back(kv.second);
      }

      // 此时的vector是无序的，需要排序
      std::sort(questions->begin(), questions->end(), [](const Question& l, const Question& r){
          return std::stoi(l.id_) < std::stoi(r.id_);
          });
      return true;
    }

    bool GetOneQuestion()
    {

    }
  private:
    std::unordered_map<std::string, Question> ques_map_;
};
