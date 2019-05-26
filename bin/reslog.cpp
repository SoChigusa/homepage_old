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
  if(arg_type == "a") { strType = "Award"; }

  std::ifstream ifs("../research/research.log");
  std::stringstream ss;
  std::string strBufferLine;
  time_t now = std::time(nullptr);
  ss << now << ";" << strType << ";" << arg_title << ";" << arg1;
  if(arg_type == "a") ss << std::endl;
  else ss << ";" << arg2 << std::endl;
  while(std::getline(ifs, strBufferLine)) {
    ss << strBufferLine << std::endl;
  }
  ifs.close();
  
  std::ofstream ofs("../research/research.log");
  ofs << ss.str();
}

void update_log(const std::string &comment) {
  HTML::update_html("../research/index_temp.html", "../research/index.html");
  HTML::update_html("../index_temp.html", "../index.html");
  HTML::update_cv();
  system("cp ../index.html ../../sochigusa.bitbucket.org/index.html");
  system("cp ../research/index.html ../../sochigusa.bitbucket.org/research/index.html");
  system(("cd ../cv/ && latex cv && bibtex cv && latex cv && latex cv && dvipdfmx cv"));
  system("cp ../cv/cv.pdf ../../sochigusa.bitbucket.org/cv/cv.pdf");
  // system(("git commit -a -m \"auto commit by reslog : "+comment+"\" && "
  // 	  +"git push origin master").c_str());
  // system(("cd ../../sochigusa.bitbucket.org/ && git commit -a -m \"auto commit by reslog : "+comment+"\" && "
  // 	  +"git push origin master").c_str());
}

int main(int argc, char** argv) {
  if (argc != 2) {
    errorMessage();
    return -1;
  }
  // system("git pull origin master");
  // system("cd ../../sochigusa.bitbucket.org/ && git pull origin master");

  std::string arg_opt(argv[1]);
  if(arg_opt == "add") {
    std::string arg_type, arg_title, arg1, arg2;
    std::cout << "Research type: [p]aper or [t]alk or [a]ward: ";
    std::getline(std::cin, arg_type);
    if(arg_type == "p") {
      std::cout << "Paper title: ";
      std::getline(std::cin, arg_title);
      std::cout << "Authors: ";
      std::getline(std::cin, arg1);
      std::cout << "arXiv number: ";
      std::getline(std::cin, arg2);

      char buffer[2048];
      std::cout << "Copy and paste bibtex and input # and enter: " << std::endl;
      scanf("%2047[^#]", buffer);
      HTML::update_bibtex(buffer);
    } else if(arg_type == "t") {
      std::cout << "Talk title: ";
      std::getline(std::cin, arg_title);
      std::cout << "Date: ";
      std::getline(std::cin, arg1);
      std::cout << "Conference and Location: ";
      std::getline(std::cin, arg2);
    } else if(arg_type == "a") {
      std::cout << "Award explanation: ";
      std::getline(std::cin, arg_title);
      std::cout << "Date: ";
      std::getline(std::cin, arg1);
    } else {
      std::cout << "Unexpected research type" << std::endl;
      return -1;
    }
    add_log(arg_type, arg_title, arg1, arg2);
    update_log("add "+arg_title);
  } else if(arg_opt == "update") {
    update_log("update");
  } else {
    errorMessage();
    return -1;
  }

  return 0;
}
