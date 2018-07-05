/*
 * Project: gitupdate
 * File: git.cpp
 * Author: So Chigusa
 *
 * Created on 2018/7/5
 */

#include "html.h"

int main(int argc, char** argv) {
  std::string comment="";
  HTML::update_html("../git/index_temp.html", "../git/index.html",
		    "../git/contents.html");
  system("cp ../git/index.html ../../sochigusa.bitbucket.org/git/index.html");
  system(("git commit -a -m \"auto commit by gitupdate"+comment+"\" && "
  	  +"git push origin master").c_str());
  system(("cd ../../sochigusa.bitbucket.org/ && git commit -a -m \"auto commit by gitupdate"+comment+"\" && "
  	  +"git push origin master").c_str());
  return 0;
}
