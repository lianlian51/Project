include <iostream>
#include <cstdio>

#include "httplib.h"

#include "oj_model.hpp"
#include "oj_view.hpp"
#include "compile.hpp"

int main()
{
  using namespace httplib;
  OjModel model;
  // 1.初始化httplib库的server对象
  Server svr;

  // 2.1 获取整个试题列表，get 
  svr.Get("/all_questions", [&model](const Request& req, Response& resp){
      // 1.返回试题列表
      std::vector<Question> questions;
      model.GetAllQuestion(&questions);

      std::string html;
      OjView::DrawAllQuestions(questions, &html);
      resp.set_content(html, "text/html");
      });
      // 2.2 获取单个试题
      //  如果标识浏览器想要获取的是哪一个试题？？
      //  浏览器提交的资源路径是  /question/[试题编号] 
      //                          /question/[\d+[0, 正无穷]]
      //  \d : 表示一个数字， [0,9]
      //  \d+ : 表示多位数字
  svr.Get(R"(/question/(\d+))", [&model](const Request& req, Response& resp){
      // 1.获取url当中关于试题的数字&获取单个试题的信息
      // std::cout << req.matches[0] << " " << req.matches[1] << std::endl;
      std::cout << req.version << " " << req.method << std::endl;
      std::cout << req.path << std::endl;

      Question ques;
      model.GetOneQuestion(req.matches[1].str(), &ques);

      // 2.渲染模板的html文件
      std::string html;
      OjView::DrawOneQuestion(ques, &html);
      resp.set_content(html, "text/html");
      });
  // 2.3 编译运行
  // 目前还没有区分到底是提交的哪一个试题
  svr.Post(R"(/compile/(\d+))", [&model](const Request& req, Response& resp){
      // 1.获取试题编号 & 获取试题内容
      Question ques;
      model.GetOneQuestion(req.matches[1].str(), &ques);

      // ques.tail_cpp_ ----> main函数调用+测试用例
      
      // post 方法在提交代码的时候，是经过encode的，要想获取浏览器提交的内容，需要进行decode完成的代码和tail.cpp进行合并，产生待编译的源码
      // key:value
      //   code : axamxksmaxkam
      // std::cout << UrlDecode(req.body) << std::endl;
      

      std::unordered_map<std::string, std::string> body_kv;
      UrlUtil::PraseBody(req.body, &body_kv);

      std::string user_code = body_kv["code"];
      // 构造json对象，交给编译运行模块
      Json::Value req_json;
      req_json["code"] = user_code + ques.tail_cpp_;
      req_json["stdin"] = "";

      std::cout << req_json["code"].asString() << std::endl;

      Json::Value resp_json;
      Compiler::CompileAndRun(req_json, &resp_json);
      });

  svr.listen("0.0.0.0", 18888);
  return 0;
}
