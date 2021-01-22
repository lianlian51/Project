#pragma once 
#include <iostream>
#include <vector>

#include "ctemplate/template.h"

#include "oj_model.hpp"

class OjView
{
  public:
    static void DrawAllQuestions(std::vector<Question>& questions, std::string* html)
    {
      // 1.创建template字典
      ctemplate::TemplateDictionary dict("all_questions");

      // 2.遍历vector就相当于遍历多个试题，每一个试题构造一个子字典
      for(const auto& ques : questions)
      {
        ctemplate::TemplateDictionary* sub_dict = dict.AddSectionDictionary("question");
        // void SetValue(const TemplateString variable, const TemplateString value)
        // variable: 指定的是预定义的html当中的变量名称
        // value：替换的值
        sub_dict->SetValue("id", ques.id_);
        sub_dict->SetValue("id", ques.id_);
        sub_dict->SetValue("title", ques.title_);
        sub_dict->SetValue("star", ques.star_);
        
      }
      // 3.填充
      ctemplate::Template* tl = ctemplate::Template::GetTemplate("./template/all_questions.html", ctemplate::DO_NOT_STRIP);
      // 渲染
      tl->Expand(html, &dict);
    }

    static void DrawOneQuestion(const Question& ques, std::string* html)
    {
      ctemplate::TemplateDictionary dict("question");
      dict.SetValue("id", ques.id_);
      dict.SetValue("tiele", ques.title_);
      dict.SetValue("star", ques.star_);
      dict.SetValue("desc", ques.desc_);
      dict.SetValue("id", ques.id_);
      dict.SetValue("code", ques.header_cpp_);

      ctemplate::Template* tl = ctemplate::Template::GetTemplate("./template/question.html", ctemplate::DO_NOT_STRIP);
      // 渲染
      tl->Expand(html, &dict);
    }
};
