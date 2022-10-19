#pragma once
#include "../base64/base64.hpp"
#include "../vigenere/vigenere.hpp"

string globalEncryptKey = "LuWCFZPu3F";

std::string encrypt_const(std::string msg, std::string key) {
	std::string b64_str = base64_encode(msg);
	std::string vigenere_msg = encrypt_vigenere(b64_str, key);
	// std::cout << vigenere_msg << std::endl;
	return vigenere_msg;
}


std::string decrypt_const(std::string encrypted_msg, std::string key) {
	std::string newKey = extend_key(encrypted_msg, key);
	std::string b64_encoded_str = decrypt_vigenere(encrypted_msg, newKey);
	std::string b64_decode_str = base64_decode(b64_encoded_str);
	return b64_decode_str;
}