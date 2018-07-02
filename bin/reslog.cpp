/*
 * Project: reslog
 * File: reslog.cpp
 * Author: So Chigusa
 *
 * Created on 2018/6/30
 */

#include "html.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void errorMessage() {
  std::cout << "Accepts 1 option:" << std::endl;
  std::cout << "option add: add information and update files" << std::endl;
  std::cout << "option update: update files using existing log" << std::endl;
}

void add_log(std::string arg_type, std::string arg_title, std::string arg1, std::string arg2) {
  std::string strType;
  if(arg_type == "p") { strType = "Paper"; }
  if(arg_type == "t") { strType = "Talk"; }

  std::ifstream ifs("../research/research.log");
  std::stringstream ss;
  std::string strBufferLine;
  time_t now = std::time(nullptr);
  ss << now << ";" << strType << ";"
     << arg_title << ";" << arg1 << ";" << arg2 << std::endl;
  while(std::getline(ifs, strBufferLine)) {
    ss << strBufferLine << std::endl;
  }
  ifs.close();
  
  std::ofstream ofs("../research/research.log");
  ofs << ss.str();
}

int main(int argc, char** argv) {
  if (argc != 2) {
    errorMessage();
    return -1;
  }

  std::string arg_opt(argv[1]);
  if(arg_opt == "add") {
    std::string arg_type, arg_title, arg1, arg2;

    std::cout << "Research type: [p]aper or [t]alk: ";
    std::getline(std::cin, arg_type);
    if(arg_type == "p") {
      std::cout << "Paper title: ";
      std::getline(std::cin, arg_title);
      std::cout << "Authors: ";
      std::getline(std::cin, arg1);
      std::cout << "arXiv number: ";
      std::getline(std::cin, arg2);
    } else if(arg_type == "t") {
      std::cout << "Talk title: ";
      std::getline(std::cin, arg_title);
      std::cout << "Date: ";
      std::getline(std::cin, arg1);
      std::cout << "Conference and Location: ";
      std::getline(std::cin, arg2);
    } else {
      std::cout << "Unexpected research type" << std::endl;
      return -1;
    }
    add_log(arg_type, arg_title, arg1, arg2);
    HTML::update_html("../research/index_temp.html", "../research/index.html");
    HTML::update_html("../index_temp.html", "../index.html");
  } else if(arg_opt == "update") {
    HTML::update_html("../research/index_temp.html", "../research/index.html");
    HTML::update_html("../index_temp.html", "../index.html");
  } else {
    errorMessage();
    return -1;
  }

  return 0;
}
