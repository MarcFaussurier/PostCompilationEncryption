#include <iostream>
#include <fstream>
#include <vector>
#include "file_detour/printf.hpp"
using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::vector;
using std::ofstream;
#include <stdio.h>
#include <stdlib.h>
    #include <iostream>
#include <string>

int main(int ac, char **av)
{
    try 
    {

    char byte = 0;


    ofstream output_file("test.tmp", std::ios::binary);

    unsigned int i = 0;

    while (i < ac) {

        char    *s;

        asprintf(&s, "arg=%s\n", av[i]);
        output_file << s;
        
        i += 1;
    }
   



    for (std::string line; std::getline(std::cin, line);) {
        std::cout << line << std::endl;
    }

    output_file.close();
    }
    catch(...)
    {
        printf("Error\n");
    }
    return EXIT_SUCCESS;
}