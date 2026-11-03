#include "uincampus/version.hpp"

#include <iostream>

int main()
{
    std::cout << "UIN-Campus - Systeme de gestion academique" << std::endl;
    std::cout << "Version : " << uin::version() << std::endl;

    return 0;
}