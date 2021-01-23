#include <iostream>
#include <cstdio>

#include "httplib.h"
#include "oj_model.hpp"

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

      resp.set_content("<html>oj2</html>", 16, "text/html");

      });

  svr.Get("/sig_question", [](const Request& req, Response& resp){

      });

  svr.Post("/test_to", [](const Request& req, Response& resp){

      });

  svr.listen("0.0.0.0", 17878);
  return 0;
}
