#pragma once 


#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <iostream>
#include <string>
#include <atomic>
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
      std::string file_nameheader = WriteTmpFile(code);

      if(file_nameheader == "")
      {
        (*Resp)["errorno"] = INTERNAL_ERROR;
        (*Resp)["reson"] = "file write filed";

        return;
      }
      // 3.编译
      if(!Compile(file_nameheader))
      {
        (*Resp)["errorno"] = COMPILE_ERROR;
        std::string reason;
        FileUtil::ReadFile(CompileErrorPath(file_nameheader), &reason);
        (*Resp)["reson"] = reason;

        return;
      }
      
       
      // 4.运行
      int ret = Run(file_nameheader);
      if(ret != 0)
      {
        (*Resp)["errorno"] = RUN_ERROR;
        (*Resp)["reason"] = "program exit by sig: " + std::to_string(ret);

        return;
      }
      // 5.构造响应
      (*Resp)["errorno"] = OK;
      (*Resp)["reason"] = "Compile and Run ok";

      std::string stdout_str;
      FileUtil::ReadFile(stdoutPath(file_nameheader), &stdout_str);
      std::cout << stdout_str << std::endl;
      (*Resp)["stdout"] = stdout_str;

      std::string stderr_str;
      FileUtil::ReadFile(stderrPath(file_nameheader), &stderr_str);
      std::cout << stderr_str << std::endl;
      (*Resp)["stderr"] = stderr_str;


      // 6.删除临时文件
      Clean(file_nameheader);
      return;
    }



  private:
    static void Clean(const std::string& file_name)
    {
      unlink(SrcPath(file_name).c_str());
      unlink(ExePath(file_name).c_str());
      unlink(stdoutPath(file_name).c_str());
      unlink(stderrPath(file_name).c_str());
      unlink(CompileErrorPath(file_name).c_str());
    }

    static int Run(const std::string& file_name)
    {
      int pid = fork();
      if(pid < 0)
      {
        return -1;
      }
      else if(pid > 0)
      {
        int status = 0;
        waitpid(pid, &status, 0);

        return status & 0x7f;
      }
      else if(pid == 0)
      {
        int fd_stdout = open(stdoutPath(file_name).c_str(), O_CREAT | O_WRONLY, 0666);
        if(fd_stdout < 0)
          return -2;

        dup2(fd_stdout, 1);

        int fd_stderr = open(stderrPath(file_name).c_str(), O_CREAT | O_WRONLY, 0666);

        if(fd_stderr < 0)
          return -2;

        dup2(fd_stderr, 2);

        execl(ExePath(file_name).c_str(), ExePath(file_name).c_str(), NULL);

        exit(0);

      }
      return 0;
    }



    static bool Compile(const std::string& file_name)
    {
      // 进程程序替换
      int pid = fork();
      if(pid > 0)
      {
        // 父进程等待
        waitpid(pid, NULL, 0);
      }
      else if(pid == 0)
      {
        // 子进程程序替换
        int fd = open(CompileErrorPath(file_name).c_str(), O_CREAT | O_WRONLY, 0666);
        if(fd < 0)
        {
          return false;
        }

        dup2(fd, 2);

        execlp("g++", "g++", SrcPath(file_name).c_str(), "-o", ExePath(file_name).c_str(), "-std=c++11", "-D", "CompileOnline",NULL);
        exit(0);
      }
      else 
        return false;

      struct stat st;
      int ret = stat(ExePath(file_name).c_str(), &st);

      if(ret < 0)
        return false;

      return true;
    }

    static std::string stdoutPath(const std::string& filename)
    {
      return "./tmp_file/" + filename + ".out";
    }

    static std::string stderrPath(const std::string& filename)
    {
      return "./tmp_file/" + filename + ".err";
    }

    static std::string CompileErrorPath(const std::string& filename)
    {
      return "./tmp_file/" + filename + ".Compilerr";
    }

    static std::string ExePath(const std::string& filename)
    {
      return "./tmp_file/" + filename + ".executable";
    }

    static std::string SrcPath(const std::string& filename)
    {
      return "./tmp_file/" + filename + ".cpp";
    }

    static std::string WriteTmpFile(const std::string& code)
    {
      // 1.组织文件名称，区分源码文件，以及后面生成的可执行程序
      static std::atomic_uint id(0);
      std::string tmp_filename = "tmp_" + std::to_string(TimeUtil::GetTimeStampMs()) + "." + std::to_string(id);
      id++;

      FileUtil::WriteFile(SrcPath(tmp_filename), code);

      return tmp_filename;
    }
};
