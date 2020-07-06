/*
 * Project: reslog
 * File: reslog.cpp
 * Author: So Chigusa
 *
 * Created on 2018/6/30
 */

#include "html.h"
#include "inspire.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// #define _UPLOAD_CHANGE

void errorMessage() {
  std::cout << "Accepts 1 option:" << std::endl;
  std::cout << "option add: add information and update files" << std::endl;
  std::cout << "option update: update files using existing log" << std::endl;
}

void add_log(std::string arg_type, std::string arg_title, std::string arg1,
             std::string arg2, std::string arg3) {
  std::string strType;
  if (arg_type == "s")
    strType = "Seminar";
  if (arg_type == "io")
    strType = "IO";
  if (arg_type == "ip")
    strType = "IP";
  if (arg_type == "do")
    strType = "DO";
  if (arg_type == "dp")
    strType = "DP";
  if (arg_type == "a")
    strType = "Award";

  std::ifstream ifs("../research/research.log");
  std::stringstream ss;
  std::string strBufferLine;
  time_t now = std::time(nullptr);
  ss << now << ";" << strType << ";" << arg_title << ";" << arg1;
  if (arg_type == "a")
    ss << std::endl;
  else {
    ss << ";" << arg2;
    if (arg_type != "s")
      ss << ";" << arg3;
    ss << std::endl;
  }
  while (std::getline(ifs, strBufferLine)) {
    ss << strBufferLine << std::endl;
  }
  ifs.close();

  std::ofstream ofs("../research/research.log");
  ofs << ss.str();
}

void bibtex_info(std::string &arg_title, std::string &arg1, std::string &arg2,
                 const std::string &arg_buf) {
  std::vector<std::string> v, vl, va, vap;
  HTML::split(v, arg_buf, '\n');

  // information should be in order of author < title < eprint
  int nl = 0;
  bool cont = false;
  std::string label[] = {"author", "title", "eprint"};
  std::string res[sizeof(label) / sizeof(label[0])];
  for (int n = 0; n < v.size() && nl < sizeof(label) / sizeof(label[0]); ++n) {
    HTML::split(vl, v[n], '=');
    if (vl.size() == 2 && vl[0].find(label[nl]) != std::string::npos) {
      res[nl] = vl[1];
      auto vlpost1 = res[nl].find("\",");
      auto vlpost2 = res[nl].find("}");
      auto vlpre1 = res[nl].find("{");
      auto vlpre2 = res[nl].find(" \"");
      if (vlpost1 != std::string::npos)
        res[nl].replace(vlpost1, 2, "");
      else
        cont = true;
      if (vlpost2 != std::string::npos)
        res[nl].replace(vlpost2, 1, "");
      if (vlpre1 != std::string::npos)
        res[nl].replace(vlpre1, 1, "");
      if (vlpre2 != std::string::npos)
        res[nl].replace(vlpre2, 2, "");
      if (!cont)
        ++nl;
    } else if (vl.size() == 1 && cont) {
      res[nl] += vl[0];
      auto vlpost1 = res[nl].find("\",");
      auto vlpost2 = res[nl].find("}");
      if (vlpost1 != std::string::npos) {
        res[nl].replace(vlpost1, vlpost1 + 2, "");
        cont = false;
      }
      if (vlpost2 != std::string::npos)
        res[nl].replace(vlpost2, 1, "");

      auto spsp = res[nl].find("  ");
      while (spsp != std::string::npos) {
        res[nl].replace(spsp, 2, " ");
        spsp = res[nl].find("  ");
      }
      if (!cont)
        ++nl;
    } else
      cont = false;
  }

  // author names
  std::string author = "";
  HTML::split(va, res[0], " and ");
  for (int i = 0; i < va.size(); ++i) {
    HTML::split(vap, va[i], ", ");
    author += vap[1];
    author += " ";
    author += vap[0];
    if (i < va.size() - 1)
      author += ", ";
  }

  // info list
  arg_title = res[1]; // title
  arg1 = author;      // authors
  arg2 = res[2];      // arXiv number
}

void update_log(const std::string &comment) {
  // update paper log
  if (comment == "update") {

    // obtain information from iNSPIRE
    // Inspire my_inspire("S.Chigusa.1", "../cv/cv.bib");
    // my_inspire.get();

    // generate paper log from bibtex
    std::ifstream ifs("../cv/cv.bib");
    std::ofstream ofs("../research/paper.log");
    std::string buf((std::istreambuf_iterator<char>(ifs)),
                    std::istreambuf_iterator<char>());
    std::vector<std::string> v;
    std::string title, author, preprint;
    HTML::split(v, buf, "\n\n");
    for (int i = 0; i < v.size(); ++i) {
      bibtex_info(title, author, preprint, v[i]);
      double num = stod(preprint);
      int y = 2000 + (int)(num / 100.);    // year
      int m = (int)num - (y - 2000) * 100; // month
      struct tm date = {0, 0, 0, 1, m - 1, y - 1900};
      ofs << std::mktime(&date) << ";"
          << "Paper;" << title << ";" << author << ";" << preprint << std::endl;
    }
  }

  // pick up most recent 6 activities
  std::ifstream ifs_p("../research/paper.log");
  std::ifstream ifs_r("../research/research.log");
  std::ofstream ofs_r("../research/recent.log");
  std::vector<std::string> v1, v2;
  std::string buf1, buf2;
  getline(ifs_p, buf1);
  getline(ifs_r, buf2);
  for (int i = 0; i < 6; ++i) {
    HTML::split(v1, buf1, ';');
    HTML::split(v2, buf2, ';');
    if (stoi(v1[0]) >= stoi(v2[0])) {
      ofs_r << buf1 << std::endl;
      if (!getline(ifs_p, buf1))
        break;
    } else {
      ofs_r << buf2 << std::endl;
      if (!getline(ifs_r, buf2))
        break;
    }
  }

  // html and pdf files update
  HTML::update_html("../research/index_temp.html", "../research/index.html");
  HTML::update_html("../index_temp.html", "../index.html");
  HTML::update_cv();
  system("cp ../index.html ../../sochigusa.bitbucket.org/index.html");
  system("cp ../research/index.html "
         "../../sochigusa.bitbucket.org/research/index.html");
  system("cd ../cv/ && uplatex cv && bibtex cv && uplatex cv && uplatex cv && "
         "dvipdfmx cv");
  system("cp ../cv/cv.pdf ../../sochigusa.bitbucket.org/cv/cv.pdf");

  // upload
#ifdef _UPLOAD_CHANGE
  system(("git commit -a -m \"auto commit by reslog : " + comment + "\" && " +
          "git push origin master")
             .c_str());
  system(("cd ../../sochigusa.bitbucket.org/ && git commit -a -m \"auto commit "
          "by reslog : " +
          comment + "\" && " + "git push origin master")
             .c_str());
#endif
}

int main(int argc, char **argv) {
  if (argc != 2) {
    errorMessage();
    return -1;
  }
#ifdef _UPLOAD_CHANGE
  system("git pull origin master");
  system("cd ../../sochigusa.bitbucket.org/ && git pull origin master");
#endif

  std::string arg_opt(argv[1]);
  if (arg_opt == "add") {
    std::string arg_type, arg_title, arg1, arg2, arg3;
    std::cout << "Research type: [s]eminar, [io]=international oral, "
                 "[ip]=poster, [do]=domestic, [dp], or [a]ward: ";
    std::getline(std::cin, arg_type);
    if (arg_type == "s") {
      std::cout << "Seminar title: ";
      std::getline(std::cin, arg_title);
      std::cout << "Date: ";
      std::getline(std::cin, arg1);
      std::cout << "Institute name: ";
      std::getline(std::cin, arg2);
    } else if (arg_type == "io" || arg_type == "ip" || arg_type == "do" ||
               arg_type == "dp") {
      std::cout << "Talk title: ";
      std::getline(std::cin, arg_title);
      std::cout << "Date: ";
      std::getline(std::cin, arg1);
      std::cout << "Conference name: ";
      std::getline(std::cin, arg2);
      std::cout << "Location: ";
      std::getline(std::cin, arg3);
    } else if (arg_type == "a") {
      std::cout << "Award explanation: ";
      std::getline(std::cin, arg_title);
      std::cout << "Date: ";
      std::getline(std::cin, arg1);
    } else {
      std::cout << "Unexpected research type" << std::endl;
      return -1;
    }
    add_log(arg_type, arg_title, arg1, arg2, arg3);
    update_log("add " + arg_title);
  } else if (arg_opt == "update") {
    update_log("update");
  } else {
    errorMessage();
    return -1;
  }

  return 0;
}
