/*
 * Project: gitupdate
 * File: git.cpp
 * Author: So Chigusa
 *
 * Created on 2018/7/5
 */

#include "html.h"

int main(int argc, char** argv) {
  HTML::update_html("../git/index_temp.html", "../git/index.html",
		    "../git/contents.html");
  return 0;
}
