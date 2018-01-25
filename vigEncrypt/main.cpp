/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: sslt
 *
 * Created on January 13, 2018, 10:22 AM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>

//using namespace std;
std::string plainTextFile = "/tmp/plaintext.txt";
std::string cipherTextFile = "vcipherkey.txt";
//std::string outputTextFile = "/tmp/vigenerecipheroutput.txt";
std::string outputTextFile = "/tmp/blockaffinecipherplaintextoutput.txt";

std::string alphabet_S = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string alphabet_L = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

bool readInPlainText(std::string &sText);
bool readInCipherKey(std::string &sKey);
bool writeOutputFile(std::string output);

bool writeFilesToTMP(void);

std::string trim(const std::string &s);
void removeSpaces(std::string &s);

void encrypt_S(std::string plain, std::string key, std::string &output);
void encrypt_L(std::string plain, std::string key, std::string &output);

/*
 * 
 */
int main(int argc, char** argv) {


    std::string plainText = "this shouldn't be here";
    std::string cipherKey = "neither should this";

    std::string input = "p";
    std::string ess = "S", ell = "L";
    std::string output = "";

    bool check = true;

    if (readInPlainText(plainText)) {
    }//try to read in the plain text
    else {
        std::cout << "could not read file " << plainTextFile << std::endl;
        return -1;
    }

    if (readInCipherKey(cipherKey)) {
    }//try to read in the cipher key
    else {
        std::cout << "could not read file " << cipherTextFile << std::endl;
        return -1;
    }

    std::cout << "Which alphabet will you use? Alphabet 'S' or 'L'?" << '\n' << ">>";
    std::cin >> input;
    trim(input);

    while (check) {
        if (strcmp(ess.c_str(), input.c_str()) == 0) {
            std::cout << "Using alphabet S" << std::endl;
            check = false;

            encrypt_S(plainText, cipherKey, output);
        } else if (strcmp(ell.c_str(), input.c_str()) == 0) {
            std::cout << "Using alphabet L" << std::endl;
            check = false;

            encrypt_L(plainText, cipherKey, output);
        } else {
            std::cout << "Please select S or L." << '\n' << ">>";
            input.clear();
            std::cin >> input;
            trim(input);
        }
    }

    std::cout << "PlainText  : " << plainText << std::endl;
    std::cout << "Encrypted  : " << output << std::endl;

    std::cout << "Writing file " << outputTextFile << std::endl;
    writeOutputFile(output);

    return 0;
}

bool readInPlainText(std::string &sText) {
    std::string out;
    std::ifstream myFile(plainTextFile.c_str());

    if (myFile.is_open()) {
        while (std::getline(myFile, sText)) {
            out += sText;
        }
        myFile.close();
        sText = out;

        return true;
    } else {
        std::cout << "file " << plainTextFile << " didn't open!" << std::endl;
        return false;
    }


    return true;
}

bool readInCipherKey(std::string &sKey) {
    std::string out;
    std::ifstream myFile(cipherTextFile.c_str());

    if (myFile.is_open()) {
        while (std::getline(myFile, sKey)) {
            out += sKey;
        }
        myFile.close();
        sKey = out;

        return true;
    } else {
        std::cout << "file " << cipherTextFile << " didn't open!" << std::endl;
        return false;
    }
    return true;
}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

void removeSpaces(std::string &s)
{
    std::string::iterator endIterator = std::remove(s.begin(),s.end(), ' ');
    s.erase(endIterator, s.end());
}


bool writeOutputFile(std::string output) {
    std::ofstream f;

    f.open(outputTextFile.c_str(), (std::ios::out | std::ios::trunc));

    if (f.is_open()) {
        
        for (std::string::iterator it = output.begin();
                it != output.end();
                ++it) {
            f << *it;
        }

    }
}

void encrypt_S(std::string plain, std::string key, std::string &output) {
    unsigned int keyCount = 0;
    int alphabetSize = alphabet_S.size();
    
    removeSpaces(plain);
    
    for (std::string::iterator it = plain.begin(); it != plain.end(); ++it) {
        if (keyCount == key.size()) keyCount = 0;

        int alphaIndex = ((int) key[keyCount] - 65) + ((int) *it - 65);
        
        if (alphaIndex > (alphabetSize - 1) ) {
            alphaIndex = alphaIndex - alphabetSize;
        }

        output += alphabet_S[alphaIndex];

        keyCount++;
    }
}

void encrypt_L(std::string plain, std::string key, std::string &output) {
    unsigned int keyCount = 0;
    int alphabetSize = alphabet_L.size();
    
    removeSpaces(plain);
    
    for (std::string::iterator it = plain.begin(); it != plain.end(); ++it) {
        if (keyCount == key.size()) keyCount = 0;

        //need to account for lower case numbers!
        //different ASCII values. See a table.
        int alphaIndex = ((int) key[keyCount] - 65) + ((int) *it - 65);

        if (alphaIndex > (alphabetSize - 1) ) {
            alphaIndex = alphaIndex - alphabetSize;
        }

        output += alphabet_L[alphaIndex];

        keyCount++;
    }
}

bool writeFilesToTMP(void)
{
    
    return true;
}
