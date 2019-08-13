/*
 * Class: HTML
 * File: html.h
 * Author: So Chigusa
 * Description: html operation class
 *
 * Created on 2018/6/30
 */

#ifndef HTML_H
#define HTML_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class HTML {
 private:
  HTML();
 public:
  static void split(std::vector<std::string> &, const std::string &buf, char sep);
  static void split(std::vector<std::string> &, const std::string &buf, const std::string &sep);
  static std::string getYYYYMMDD(time_t);
  static void insertFromFile(std::stringstream &, std::string &);
  static int extract_body(const std::string &, const std::string &);
  static void update_html(const std::string &, const std::string &,
			  const std::string &cname = "");
  static void update_cv();
  static void update_bibtex(const char *);
  static void update_tipslog();
  static void update_diarylog();
};

#endif
