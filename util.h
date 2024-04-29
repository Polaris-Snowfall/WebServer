#include <string>
#include <iostream>
#include <cstring>
#include <cassert>

std::ostream errorOstream(std::cout.rdbuf());

void errorExit(const std::string& errorMsg)
{
    errorOstream << strerror(errno) << "\n";
    exit(-1);
}