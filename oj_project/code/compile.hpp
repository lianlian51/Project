#pragma once 

#include <iostream>
#include <string>
#include <json/json.h>

#include "tools.hpp"

enum ErrorNo
{
  OK = 0,
  PRAM_ERROR,
  INTERNAL_ERROR,
  COMPILE_ERROR,
  RUN_ERROR
};

class Compiler 
{
  public:
    /*
     * Json::Value Req : 请求的json
     *     {"code":"xxx", "stdin":"xxxx"}
     * Json::Value* Resp:出参，返回给调用者
     *     {"errorno":"xx", "reason":"xxxx"}
     */
    static void CompileAndRun(Json::Value Req, Json::Value* Resp)
    {
      // 1.参数是否错误，json串当中的code是否为空
      if(Req["code"].empty())
      {
        (*Resp)["errorno"] = PRAM_ERROR;
        (*Resp)["reason"] = "Pram error";
        return ;
      }
      // 2.将代码写到文件中去
      std::string code = Req["code"].asString();
      // 文件命名约定的时候，tmp_时间戳_src.cpp
      WriteTmpFile(code);
      // 3.编译
      // 4.运行
      // 5.构造响应
    }

    static std::string SrcPath(const std::string& file_name)
    {
      return file_name + ".cpp";
    }

    static std::string WriteTmpFile(const std::string& code)
    {
      // 1.组织文件名称，区分源码文件，以及后面生成的可执行程序文件
      std::string tmp_filename = "tmp_" + std::to_string(TimeUtil::GetTimeStampMs());
      // 2.code写到文档中去
      // tmp_stamp.cpp
      FileUtil::WriteFile(SrcPath(tmp_filename), code);
      return tmp_filename;
    }
};
