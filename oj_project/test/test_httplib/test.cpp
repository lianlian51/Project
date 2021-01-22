#include <stdio.h>
#include "httplib.h"

void func(const httplib::Request& req, httplib::Response& resp)
{
  resp.set_content("<html>test</html>", 17, "text/html");
  printf("recv test\n");
}

int main()
{
  // 创建httplib一个server类对象，使用该类对象，模拟创建一个http服务器
  httplib::Server svr;

  svr.Get("/test", func);

  svr.listen("0.0.0.0", 19898);
  return 0;
}
