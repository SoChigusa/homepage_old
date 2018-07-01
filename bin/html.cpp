/*
 * Class: HTML
 * File: html.cpp
 * Author: So Chigusa
 * Description: html operation class
 *
 * Created on 2018/6/30
 */

#include "html.h"

void HTML::split(std::vector<std::string> &v, const std::string &buf, char sep) {
  v.resize(0);
  std::stringstream ss(buf);
  std::string mbuf;
  while(getline(ss, mbuf, sep)) { if(mbuf != "") v.push_back(mbuf); }
}

std::string HTML::getYYYYMMDD(time_t t) {
  struct tm* localTime = std::localtime(&t);
  int yyyy = localTime->tm_year + 1900;
  int mm = localTime->tm_mon + 1;
  int dd = localTime->tm_mday;
  return std::to_string(yyyy) + "/" + std::to_string(mm) + "/" + std::to_string(dd);
}

void HTML::update_index() {
  std::ifstream ifs("../index_temp.html");
  std::ifstream iflog("../research/research.log");
  std::stringstream ss;
  std::string strBufferLine;
  std::vector<std::string> val;

  while(std::getline(ifs, strBufferLine)) {
    ss << strBufferLine << std::endl;

    // add recent activities
    if((int)strBufferLine.find("<!-- Recent Activities below -->") != -1) {
      ss << "<article>" << std::endl;
      for(int i = 0; i < 4; i++) {
	std::getline(iflog, strBufferLine);
	split(val, strBufferLine, ';');
	ss << "  <section>" << std::endl;
	
	if(val[1] == "Paper") {
	  ss << "    <span class=\"date\">" // date
	     << getYYYYMMDD((time_t)stol(val[0])) << "</span>" << std::endl;
	  ss << "    <h1><a href=\"https://arxiv.org/abs/" << val[4] << "\" "
	     << "target=_blank>arXiv:" << val[4] << "</a></h1>" << std::endl; // arXiv #
	  ss << "    <p>" << std::endl;
	  ss << "      " << val[3] << "<br>" << std::endl; // authors
	  ss << "      <i>" << val[2] << "</i>" << std::endl; // title
	  ss << "    </p>" << std::endl;	
	} else if(val[1] == "Talk") {
	  ss << "    <span class=\"date\">" << val[3] << "</span>" << std::endl; // date
	  ss << "    <h1>Talk: " << val[4] << "</a></h1>" << std::endl;
	  ss << "    <p>" << std::endl;
	  ss << "      <i>" << val[2] << "</i>" << std::endl;
	  ss << "    </p>" << std::endl;
	}
	
	ss << "  </section>" << std::endl;
      }
      ss << "</article>" << std::endl;
    }
  }

  std::ofstream ofs("../index.html");
  ofs << ss.str();
}

void HTML::update_reslog() {
  std::ifstream ifs("../research/index_temp.html");
  std::stringstream ss;
  std::string strBufferLine;
  std::vector<std::string> val;

  while(std::getline(ifs, strBufferLine)) {
    ss << strBufferLine << std::endl;

    // add paper info
    if((int)strBufferLine.find("<!-- Papers below -->") != -1) {
      std::ifstream iflog("../research/research.log");
      while(std::getline(iflog, strBufferLine)) {
	split(val, strBufferLine, ';');
	if(val[1] == "Paper") {
	  ss << "    <li>" << val[3] << "<br>" << std::endl; // authors
	  ss << "      <i>" << val[2] << ",</i><br>" << std::endl; // title
	  ss << "      <a href=\"https://arxiv.org/abs/" << val[4] << "\" target=_blank>[arXiv:" << val[4] << "]</a>." << std::endl; // arXiv #
	  ss << "    </li>" << std::endl;
	}
      }
    }

    // add talk info
    if((int)strBufferLine.find("<!-- Talks below -->") != -1) {
      std::ifstream iflog("../research/research.log");
      while(std::getline(iflog, strBufferLine)) {
	split(val, strBufferLine, ';');
	if(val[1] == "Talk") {
	  ss << "    <li><i>" << val[2] << ",</i><br>" << std::endl; // title
	  ss << "      " << val[4] << " (" << val[3] << ").</li>" << std::endl; // location and date
	}
      }
    }
  }
  
  std::ofstream ofs("../research/index.html");
  ofs << ss.str();
}
