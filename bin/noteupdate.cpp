/*
 * Project: notelog
 * File: notelog.cpp
 * Author: So Chigusa
 *
 * Created on 2020/5/27
 */

#include "html.h"

// #define _ENABLE_GIT_UPDATE

int main(int argc, char **argv) {
  std::string comment = "";
  HTML::update_html("../note/index_temp.html", "../note/index.html");
  system("cp ../note/index.html ../../sochigusa.bitbucket.org/note/index.html");
#ifdef _ENABLE_GIT_UPDATE
  system("git pull origin master");
  system("cd ../../sochigusa.bitbucket.org/ && git pull origin master");
  system(("git commit -a -m \"auto commit by gitupdate" + comment + "\" && " +
          "git push origin master")
             .c_str());
  system(("cd ../../sochigusa.bitbucket.org/ && git commit -a -m \"auto commit "
          "by gitupdate" +
          comment + "\" && " + "git push origin master")
             .c_str());
#endif
  return 0;
}
