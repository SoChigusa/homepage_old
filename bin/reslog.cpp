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

#define _UPDATE_CHANGE
// #define _UPLOAD_CHANGE

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
  system("cd ../cv/ && latex cv && bibtex cv && latex cv && latex cv && dvipdfmx cv");
  system("cp ../cv/cv.pdf ../../sochigusa.bitbucket.org/cv/cv.pdf");
#ifdef _UPLOAD_CHANGE
  system(("git commit -a -m \"auto commit by reslog : "+comment+"\" && "
  	  +"git push origin master").c_str());
  system(("cd ../../sochigusa.bitbucket.org/ && git commit -a -m \"auto commit by reslog : "+comment+"\" && "
  	  +"git push origin master").c_str());
#endif
}

void bibtex_info(std::string & arg_title, std::string & arg1, std::string & arg2,
		 const std::string & arg_buf) {
  std::vector<std::string> v, vl, va, vap;
  HTML::split(v, arg_buf, '\n');

  // information should be in order of author < title < eprint
  int nl = 0;
  bool cont = false;
  std::string label[] = {"author", "title", "eprint"};
  std::string res[sizeof(label) / sizeof(label[0])];
  for(int n = 0; n < v.size() && nl < sizeof(label) / sizeof(label[0]); ++n) {
    HTML::split(vl, v[n], '=');
    if(vl.size() == 2 && vl[0].find(label[nl]) != std::string::npos) {
      res[nl] = vl[1];
      auto vlpost1 = res[nl].find("\",");
      auto vlpost2 = res[nl].find("}");
      auto vlpre1  = res[nl].find("{");
      auto vlpre2  = res[nl].find(" \"");
      if(vlpost1 != std::string::npos) res[nl].replace(vlpost1, 2, "");
      else cont = true;
      if(vlpost2 != std::string::npos) res[nl].replace(vlpost2, 1, "");
      if(vlpre1 != std::string::npos) res[nl].replace(vlpre1, 1, "");
      if(vlpre2 != std::string::npos) res[nl].replace(vlpre2, 2, "");
      if(!cont) ++nl;
    } else if(vl.size() == 1 && cont) {
      res[nl] += vl[0];
      auto vlpost1 = res[nl].find("\",");
      auto vlpost2 = res[nl].find("}");
      if(vlpost1 != std::string::npos) {
	res[nl].replace(vlpost1, vlpost1+2, "");
	cont = false;
      }
      if(vlpost2 != std::string::npos) res[nl].replace(vlpost2, 1, "");
      
      auto spsp = res[nl].find("  ");
      while(spsp != std::string::npos) {
	res[nl].replace(spsp, 2, " ");
	spsp = res[nl].find("  ");
      }
      if(!cont) ++nl;
    } else cont = false;
  }

  // author names
  std::string author = "";
  HTML::split(va, res[0], " and ");
  for(int i = 0; i < va.size(); ++i) {
    HTML::split(vap, va[i], ", ");
    author += vap[1];
    author += " ";
    author += vap[0];
    if(i < va.size()-1) author += ", ";
  }

  // info list
  arg_title = res[1]; // title
  arg1 = author; // authors
  arg2 = res[2]; // arXiv number
}

int main(int argc, char** argv) {
  if (argc != 2) {
    errorMessage();
    return -1;
  }
#ifdef _UPLOAD_CHANGE
  system("git pull origin master");
  system("cd ../../sochigusa.bitbucket.org/ && git pull origin master");
#endif

  std::string arg_opt(argv[1]);
  if(arg_opt == "add") {
    std::string arg_type, arg_title, arg1, arg2;
    std::cout << "Research type: [p]aper or [t]alk or [a]ward: ";
    std::getline(std::cin, arg_type);
    if(arg_type == "p") {
      char buffer[2048];
      std::cout << "Copy and paste bibtex and input # and enter: " << std::endl;
      scanf("%2047[^#]", buffer);
      bibtex_info(arg_title, arg1, arg2, std::string(buffer));
#ifdef _UPDATE_CHANGE
      HTML::update_bibtex(buffer);
#endif
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
#ifdef _UPDATE_CHANGE
    add_log(arg_type, arg_title, arg1, arg2);
    update_log("add "+arg_title);
#endif
  } else if(arg_opt == "update") {
#ifdef _UPDATE_CHANGE
    update_log("update");
#endif
  } else {
    errorMessage();
    return -1;
  }

  return 0;
}
