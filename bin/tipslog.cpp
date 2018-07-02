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

void add_log(std::string &arg_name, std::ifstream &ifcont) {
  std::string strBufferLine;
  std::vector<std::string> val, val2;
  std::getline(ifcont, strBufferLine);
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
    std::ifstream ifcont("../tips/source/"+arg_name+".html");
    if(!ifcont.is_open()) {
      std::cout << "File ../tips/source/" << arg_name << ".html isn't found" << std::endl;
      return -1;
    }
    add_log(arg_name, ifcont);
    HTML::update_tipslog();
    HTML::update_html("../index_temp.html", "../index.html");
  } else if(arg_opt == "update") {
    HTML::update_tipslog();
    HTML::update_html("../index_temp.html", "../index.html");
  }
  return 0;
}

