/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Matthew Rose
 *
 * Created on January 13, 2018, 10:22 AM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <math.h>

#include <cctype>

std::string plainTextFile = "/tmp/plaintext.txt";
std::string cipherTextFile = "/tmp/vcipherkey.txt";
std::string outputTextFile = "/tmp/vigenerecipheroutput.txt";

std::string alphabet_S = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string alphabet_L = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

bool readInPlainText(std::string &sText);
bool readInCipherKey(std::string &sKey);
bool writeOutputFile(std::string output);

void removeSpaces(std::string &s);
void removeLowercase(std::string &s);
void removeNonLetters(std::string &s);

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


    while (check) {
        if (strcmp(ess.c_str(), input.c_str()) == 0) {
            std::cout << "Using alphabet S" << std::endl;
            check = false;

            removeLowercase(plainText);

            encrypt_S(plainText, cipherKey, output);
        } else if (strcmp(ell.c_str(), input.c_str()) == 0) {
            std::cout << "Using alphabet L" << std::endl;
            check = false;

            encrypt_L(plainText, cipherKey, output);
        } else {
            std::cout << "Please select S or L." << '\n' << ">>";
            input.clear();
            std::cin >> input;
        }
    }

    std::cout << "PlainText  : " << plainText << std::endl;
    std::cout << "Encrypted  : " << output << std::endl;

    std::cout << "Writing file " << outputTextFile << std::endl;

    if (writeOutputFile(output)) {
        std::cout << "File was written" << std::endl;
    } else {
        std::cout << "File was NOT written" << std::endl;
    }

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

        removeSpaces(sText);
        removeNonLetters(sText);

        if ((sText.size() % 2 == 0)) {
            return true;
        } else {

            sText.append("A");
            return true;
        }
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

void removeSpaces(std::string &s) {
    std::string::iterator endIterator = std::remove(s.begin(), s.end(), ' ');
    s.erase(endIterator, s.end());
    s.erase(std::remove_if(s.begin(),
            s.end(),
            [](unsigned char x) {
                return std::isspace(x);
            }),
    s.end());
}

void removeLowercase(std::string &s) {
    s.erase(std::remove_if(s.begin(),
            s.end(),
            [](unsigned char x) {
                return std::islower(x);
            }),
    s.end());
}

void removeNonLetters(std::string &s) {
    s.erase(std::remove_if(s.begin(),
            s.end(),
            [](unsigned char x) {
                return std::ispunct(x);
            }),
    s.end());

    s.erase(std::remove_if(s.begin(),
            s.end(),
            [](unsigned char x) {
                return std::isdigit(x);
            }),
    s.end());
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
        return true;
    }

    return false;
}

void encrypt_S(std::string plain, std::string key, std::string &output) {
    unsigned int keyCount = 0;
    int alphabetSize = alphabet_S.size();

    for (std::string::iterator it = plain.begin(); it != plain.end(); ++it) {
        if (keyCount == key.size()) keyCount = 0;

        int alphaIndex = ((int) key[keyCount] - 65) + ((int) *it - 65);

        if (alphaIndex > (alphabetSize - 1)) {
            alphaIndex = alphaIndex % 26;
        }

        output += alphabet_S[alphaIndex];

        keyCount++;
    }
}

void encrypt_L(std::string plain, std::string key, std::string &output) {
    unsigned int keyCount = 0;
    int alphabetSize = alphabet_L.size();
    int alphaIndex = 0;

    for (std::string::iterator it = plain.begin(); it != plain.end(); ++it) {
        if (keyCount == key.size()) keyCount = 0;

        //need to account for lower case numbers!
        //different ASCII values. See a table.
        if ((int) *it >= 97) {
            int partA = (int) *it - 71;
            int partB = (int) key[keyCount] - 65;
            alphaIndex = partA + partB;
        } else {
            alphaIndex = ((int) *it - 65) + ((int) key[keyCount] - 65);
        }

        if (alphaIndex > (alphabetSize)) {
            alphaIndex = alphaIndex % 52;
        }

        output += alphabet_L[alphaIndex];

        keyCount++;
    }
}
