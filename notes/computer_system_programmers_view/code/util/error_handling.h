#pragma once

/*
Modified from
https://www.cs.cmu.edu/afs/cs/academic/class/15213-f05/code/conc/csapp.h
*/

#include <string_view>

void unix_error(std::string_view msg);
void posix_error(int code, std::string_view msg);
void dns_error(std::string_view msg);
void app_error(std::string_view msg);