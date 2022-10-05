#include <iostream>
#include <fstream>
#include <vector>
#include "..\crypto\encr.hpp"

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::vector;
using std::ofstream;

int main(int ac, char **av)
{
    try 
    {
    string  input(av[1]);
    string  output(av[2]);
    char byte = 0;
    ifstream input_file(input, std::ios::binary);
    ofstream output_file(output, std::ios::binary);
    if (!input_file.is_open()) {
        cerr << "Could not open the input file" << endl;
        return EXIT_FAILURE;
    }
    unsigned int i = 0;
    while (input_file.get(byte)) {
        output_file << encr(byte, i);// (char)(( byte   - 2 + i) ^ (42 * i));
        i += 1;
    }
    input_file.close();
    output_file.close();
    }
    catch (...)
    {
        printf("error\n");
    }
    return EXIT_SUCCESS;
}