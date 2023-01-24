#include "encrypt_const.hpp"

int main(int ac, char** av)
{
    if (ac != 2)
        return !!printf("expected string as first arg\n");

    string s = av[1];
    string encr = encrypt_const(s, globalEncryptKey);
    cout << "Encr: " << encr << endl;
    string decr = decrypt_const(encr, globalEncryptKey);
    cout << "Decr: " << decr << endl;
}