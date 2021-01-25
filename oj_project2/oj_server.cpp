#include <iostream>
#include <cstdio>

#include "json/json.h"
#include "httplib.h"
#include "oj_model.hpp"
#include "oj_view.hpp"
#include "compile.hpp"

int main()
{
  using namespace httplib;

  OjModel model;
  Server svr;

  svr.Get("/all_questions", [&model](const Request& req, Response& resp){
      std::vector<Question> questions;
      model.GetAllQuestion(&questions);

      for(int i = 0; i < questions.size(); i++)
      {
         std::cout << questions[i].id_ << std::endl;
      }

      std::string html;
      OjView::DrawAllQuestions(questions, &html);

      resp.set_content(html, "text/html");
      });

  svr.Get(R"(/question/(\d+))", [&model](const Request& req, Response& resp){
      // 获取单个试题
      Question ques;
      model.GetOneQuestion(req.matches[1].str(), &ques);

      // 渲染
      std::string html;
      OjView::DrawOneQuestion(ques, &html);

      resp.set_content(html, "text/html");
      });

  svr.Post(R"(/compile/(\d+))", [&model](const Request& req, Response& resp){
      // 获取试题编号 & 获取试题内容
      Question ques;
      model.GetOneQuestion(req.matches[1].str(), &ques);
      // std::cout << req.body << std::endl;
      // std::cout << UrlUtil::UrlDecode(req.body) << std::endl;
      // std::vector<std::string> vec;
      // StringUtil::Split(UrlUtil::UrlDecode(req.body), ":", &vec);

      std::unordered_map<std::string, std::string> body_kv;
      UrlUtil::PraseBody(req.body, &body_kv);
      // std::cout << body_kv["code"] << std::endl;
      // for(int i = 0; i < vec.size(); i++)
      // {
      //   std::cout << vec[i] << std::endl;
      // }
      

      // 构造json对象，交给编译运行模块
      Json::Value req_json;
      std::string user_code = body_kv["code"];
      req_json["code"] = user_code + ques.tail_cpp_;
      req_json["stdin"] = "";

      std::cout << req_json["code"].asString() << std::endl;


      Json::Value resp_json;
      Compiler::CompileAndRun(req_json, &resp_json);

      });

  svr.listen("0.0.0.0", 17878);
  return 0;
}
