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

void add_log(std::string arg_name) {
  time_t now = std::time(nullptr);
  std::stringstream ss;
  ss << now << ";" << arg_name << std::endl;

  std::ifstream ifs("../tips/tips.log");
  std::string strBufferLine;
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
    std::ifstream test("../tips/source/"+arg_name+".html");
    if(!test.is_open()) {
      std::cout << "File ../tips/source/" << arg_name << ".html isn't found" << std::endl;
      return -1;
    }
    add_log(arg_name);
    HTML::update_tipslog();
  } else if(arg_opt == "update") {
    HTML::update_tipslog();    
  }
  return 0;
}

