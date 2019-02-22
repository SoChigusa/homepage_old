/*
 * Project: tipslog
 * File: tipslog.cpp
 * Author: So Chigusa
 *
 * Created on 2018/7/1
 */

#include "html.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void errorMessage() {
  std::cout << "2-Ways of use:" << std::endl;
  std::cout << "./tiplog add [TipsName]" << std::endl;
  std::cout << "./tiplog update: update files using existing log" << std::endl;
}

void update_log(const std::string &comment) {
  HTML::update_tipslog();
  HTML::update_html("../index_temp.html", "../index.html");
  system("cp ../index.html ../../sochigusa.bitbucket.org/index.html");
  system("cp ../tips/*.html ../../sochigusa.bitbucket.org/tips/");
  system(("git add ../tips/* && git commit -a -m \"auto commit by tipslog : "+comment+"\" && "
  	  +"git push origin master").c_str());
  system(("cd ../../sochigusa.bitbucket.org/ && git add tips/*.html && git commit -a -m \"auto commit by tipslog : "+comment+"\" && "
  	  +"git push origin master").c_str());
}

int add_log(std::string &arg_name, std::ifstream &ifcont) {
  std::string strBufferLine;
  std::vector<std::string> val, val2;
  bool exist_h1 = false;
  while(std::getline(ifcont, strBufferLine)) {
    if((int)strBufferLine.find("</h1>") != -1) {
      exist_h1 = true;
      break;
    }
  }
  if(!exist_h1) return -1;
  HTML::split(val, strBufferLine, '>');
  HTML::split(val2, val[1], '<');
  
  time_t now = std::time(nullptr);
  std::stringstream ss;
  ss << now << ";" << arg_name << ";" << val2[0] << std::endl;

  std::ifstream ifs("../tips/tips.log");
  while(std::getline(ifs, strBufferLine)) {
    ss << strBufferLine << std::endl;
  }
  ifs.close();
  
  std::ofstream ofs("../tips/tips.log");
  ofs << ss.str();
  return 0;
}

int main(int argc, char** argv) {
  if (argc == 1) {
    errorMessage();
    return -1;
  }
  system("git pull origin master");
  system("cd ../../sochigusa.bitbucket.org/ && git pull origin master");
  std::string arg_opt(argv[1]);
  if (!(argc == 2 && arg_opt == "update") &&
      !(argc == 3 && arg_opt == "add")) {
    errorMessage();
    return -1;
  }

  if(arg_opt == "add") {
    std::string arg_name(argv[2]);
    HTML::extract_body("../tips/source/"+arg_name+".html",
		       "../tips/source/"+arg_name+".html");
    std::ifstream ifcont("../tips/source/"+arg_name+".html");
    if(add_log(arg_name, ifcont) == -1) {
      std::cout << "Error: source html should contain <h1>...</h1> block" << std::endl;
      return -1;
    }
    update_log("add "+arg_name);
  } else if(arg_opt == "update") {
    update_log("update");
  }
  return 0;
}

