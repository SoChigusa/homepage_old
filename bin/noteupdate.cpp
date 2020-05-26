/*
 * Project: notelog
 * File: notelog.cpp
 * Author: So Chigusa
 *
 * Created on 2020/5/27
 */

#include "html.h"
#include <fstream>

#define _ENABLE_GIT_UPDATE

void errorMessage() {
  std::cout << "Usage: noteupdate [notename]" << std::endl;
}

void errorMessage2() {
  std::cout << "Error: input existing file name" << std::endl;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    errorMessage();
    return -1;
  }
  std::string notename(argv[1]);
  std::ifstream ifs("../note/" + notename + ".html");
  if (!ifs.is_open()) {
    errorMessage2();
    return -2;
  }
  HTML::update_html("../note/index_temp.html", "../note/index.html");
  system("cp ../note/index.html ../../sochigusa.bitbucket.org/note/index.html");
  system(
      ("cp ../note/" + notename + ".html ../../sochigusa.bitbucket.org/note/")
          .c_str());
#ifdef _ENABLE_GIT_UPDATE
  system("git pull origin master");
  system("cd ../../sochigusa.bitbucket.org/ && git pull origin master");
  system("git add note/" + notename + ".html");
  system(("git commit -a -m \"auto commit by gitupdate " + notename + "\" && " +
          "git push origin master")
             .c_str());
  system(("cd ../../sochigusa.bitbucket.org/ && git add note/" + notename +
          ".html && git commit -a -m \"auto commit "
          "by noteupdate " +
          notename + "\" && " + "git push origin master")
             .c_str());
#endif
  return 0;
}
