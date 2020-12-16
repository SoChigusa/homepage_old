/*
 * Project: gitupdate
 * File: gitupdate.cpp
 * Author: So Chigusa
 *
 * Created on 2018/7/5
 */

#include "html.h"

#define _ENABLE_GIT_UPDATE

int main(int argc, char **argv) {
  std::string comment = "";
  HTML::update_html("../git/index_temp.html", "../git/index.html",
                    "../git/contents.html");
  system("cp ../git/index.html ../../sochigusa.bitbucket.org/git/index.html");
#ifdef _ENABLE_GIT_UPDATE
  system("git pull origin master");
  system("cd ../../sochigusa.bitbucket.org/ && git pull origin master");
  system(("git commit -a -m \"auto commit by gitupdate" + comment + "\" && " +
          "git push origin main")
             .c_str());
  system(("cd ../../sochigusa.bitbucket.org/ && git commit -a -m \"auto commit "
          "by gitupdate" +
          comment + "\" && " + "git push origin master")
             .c_str());
#endif
  return 0;
}
