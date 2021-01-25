#pragma once 

#include <iostream>
#include <string>
#include "json/json.h"
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
    static void CompileAndRun(Json::Value Req, Json::Value* Resp)
    {
      // 1.判断参数是否错误，json串中的code是否为空
      if(Req["code"].empty())
      {
        (*Resp)["errorno"] = PRAM_ERROR;
        (*Resp)["reason"] = "pram error";
          return ;
      }
      // 2.将文件写到代码中去
      std::string code = Req["code"].asString();
      WriteTmpFile(code);
      // 3.编译
      // 4.运行
      // 5.构造响应
    }

    static std::string SrcPath(const std::string& filename)
    {
      return filename + ".cpp";
    }

    static std::string WriteTmpFile(const std::string& code)
    {
      // 1.组织文件名称，区分源码文件，以及后面生成的可执行程序
      std::string tmp_filename = "tmp_" + std::to_string(TimeUtil::GetTimeStampMs());

      FileUtil::WriteFile(SrcPath(tmp_filename), code);

      return tmp_filename;
    }
};
