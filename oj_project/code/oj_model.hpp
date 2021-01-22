#pragma once


#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <vector>

#include "tools.hpp"

struct Question{
  std::string id_;
  std::string title_;
  std::string star_;
  std::string path_;
  
  std::string desc_; // 题目的描述
  std::string header_cpp_;  // 预定义的头
  std::string tail_cpp_;    // 题目的尾，包含测试用例和调用逻辑
};


class OjModel
{
  public:
    OjModel()
    {
      Load("./oj_data/oj_config.cfg");
    }

    // 从文件中获取题目
    bool Load(const std::string& filename)
    {
      // fopen open c++ fstream
      // 读
      std::ifstream file(filename.c_str());
      if(!file.is_open())
      {
        std::cout << "configi file open failed!" << std::endl;
        return false;
      }

      // 1.打开文件成功的情况
      //   1.1 从文件当中获取每一行信息
      //      1.1.1 对于每一行信息，还需要获取题号，题目名称，题目难易，题目路径
      //      1.1.2 保存在结构体当中
      // 2.把多个question，组织成map当中

      std::string line;
      while(std::getline(file, line))
      {
        std::vector<std::string> vec;
        StringUtil::Split(line, "\t", &vec);

        // is_any_of：支持多个字符作为分隔符
        // token_compress_off：是否将多个分割字符看做是一个
        // boost::split(vec, line, boost::is_any_of(" "), boost::token_compress_off);
        Question ques;
        ques.id_ = vec[0];
        ques.title_ = vec[1];
        ques.star_ = vec[2];
        ques.path_ = vec[3];

        std::string dir = vec[3];
        FileUtil::ReadFile(dir + "/desc.txt", &ques.desc_);
        FileUtil::ReadFile(dir + "/header.cpp", &ques.header_cpp_);
        FileUtil::ReadFile(dir + "/tail.cpp", &ques.tail_cpp_);

        ques_map_[ques.id_] = ques;
      }
      file.close();
      return true;
    }

    bool GetAllQuestion(std::vector<Question>* questions)
    {
      // 遍历无序的map，将试题信息返回给调用者
      // 对于每一个试题，都是一个Question结构体对象
      for(const auto &kv : ques_map_)
      {
        questions->push_back(kv.second);
      }
      std::sort(questions->begin(), questions->end(), [](const Question& l, const Question& r){
          return std::stoi(l.id_) < std::stoi(r.id_);
          return true;
          });
    }

    bool GetOneQuestion(const std::string& id, Question* ques)
    {
      auto it = ques_map_.find(id);
      if(it == ques_map_.end())
      {
        return false;
      }
      *ques = it->second;
      return true;
    }

    ~OjModel()
    {

    }


  private:
    std::unordered_map<std::string, Question> ques_map_;
};
