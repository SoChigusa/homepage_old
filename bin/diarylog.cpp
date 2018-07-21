/*
 * Project: diarylog
 * File: diarylog.cpp
 * Author: So Chigusa
 *
 * Created on 2018/7/14
 */

#include "html.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void errorMessage() {
  std::cout << "2-Ways of use:" << std::endl;
  std::cout << "./diarylog add [Date]" << std::endl;
  std::cout << "./diarylog update: update files using existing log" << std::endl;
}

void update_log(const std::string &comment) {
  HTML::update_diarylog();
  system("cp ../diary/index.html ../../sochigusa.bitbucket.org/diary/index.html");
  system(("git add ../diary/page-* && git commit -a -m \"auto commit by diarylog : "+comment+"\" && "
  	  +"git push origin master").c_str());
  system(("cd ../../sochigusa.bitbucket.org/ && git add diary/page-* && git commit -a -m \"auto commit by diarylog : "+comment+"\" && "
  	  +"git push origin master").c_str());
}

void add_log(std::string &arg_name, std::ifstream &ifcont) {
  time_t now = std::time(nullptr);
  std::stringstream ss;
  ss << now << ";" << arg_name << std::endl;

  std::ifstream ifs("../diary/diary.log");
  std::string strBufferLine;
  while(std::getline(ifs, strBufferLine)) {
    ss << strBufferLine << std::endl;
  }
  ifs.close();
  
  std::ofstream ofs("../diary/diary.log");
  ofs << ss.str();
}

int main(int argc, char** argv) {
  if (argc == 1) {
    errorMessage();
    return -1;
  }
  std::string arg_opt(argv[1]);
  if (!(argc == 2 && arg_opt == "update") &&
      !(argc == 3 && arg_opt == "add")) {
    errorMessage();
    return -1;
  }

  if(arg_opt == "add") {
    std::string arg_name(argv[2]);
    std::ifstream ifcont("../diary/source/"+arg_name+".html");
    if(!ifcont.is_open()) {
      std::cout << "File ../diary/source/" << arg_name << ".html isn't found" << std::endl;
      return -1;
    }
    HTML::extract_body("../diary/source/"+arg_name+".html",
		       "../diary/source/"+arg_name+".html");
    add_log(arg_name, ifcont);
    update_log("add "+arg_name);
  } else if(arg_opt == "update") {
    update_log("update");
  }
  return 0;
}

