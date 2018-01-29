/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: sslt
 *
 * Created on January 20, 2018, 7:59 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <math.h>

#include <cctype>
#include <array>

/*
 * 
 */

void testCoprime(int a, int b);
std::string inputFile = "/tmp/vigenerecipheroutput.txt";
//std::string cipherTextFile = "/tmp/vcipherkey.txt";
//std::string outputTextFile = "/tmp/vigenerecipheroutput.txt";
std::string outputTextFile = "/tmp/blockaffinecipherplaintextoutput.txt";

std::string alphabet_S = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string alphabet_L = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

std::array<int> primeOfMultiplier;
std::array<int> primeOfOffset;

bool readInInputFile(std::string &sText);
bool readInCipherKey(std::string &sKey);
bool writeOutputFile(std::string output);

int getPrimeFactors(int count);
int
bool getMultiplier(int &m);
bool getOffset(int &o);
bool getAlphabet(int &modulo);

bool checkForNonNumbers(std::string &s);

bool checkIfRelativelyPrime(int mult, int mod);

void removeSpaces(std::string &s);
void removeLowercase(std::string &s);
void removeNonLetters(std::string &s);

void encrypt_S(std::string plain, std::string key, std::string &output);
void encrypt_L(std::string plain, std::string key, std::string &output);

int main(int argc, char** argv) {

    std::string inputText = "This should NOT be here";
    int offset = -1;
    int multiplier = -1;
    int modulo = -1;

    readInInputFile(inputText);

    if (getAlphabet(modulo)) {
        std::cout << "Your modulo is " << modulo << std::endl;
    }
    if (getMultiplier(multiplier)) {
        std::cout << "Thanks for the multiplier of " << multiplier << "!" << std::endl;
    }
    if (getOffset(offset)) {
        std::cout << "Thanks for the offset of " << offset << "!" << std::endl;
    }

    if (checkIfRelativelyPrime(multiplier, modulo)) {

    }

    int counter = 1;
    getPrimeFactors(counter);

    testCoprime(multiplier, offset);

    return 0;
}

int getPrimeFactors(int count) {
    ++count;

    int multiplyTheArray = 0;
    for (unsigned int i = 0; i < primeOfMultiplier.size(); ++i) {

    }

    if (primeOfMultiplier.size() != 0) {

    }
}

bool getMultiplier(int &m) {
    std::string input = "p";
    bool check = true;

    std::cout << "Please input multiplier for Block Affine cipher" << '\n' << ">>";
    std::cin >> input;

    while (check) {
        if (!checkForNonNumbers(input)) {
            std::cout << "Please select an integer\n" << ">>";
            input.clear();
            std::cin >> input;
        } else {
            m = std::stoi(input);
            check = false;
            return true;
        }
    }

    return false;
}

bool getOffset(int &o) {
    std::string input = "p";
    bool check = true;

    std::cout << "Please input offset for Block Affine cipher" << '\n' << ">>";
    std::cin >> input;

    while (check) {
        if (!checkForNonNumbers(input)) {
            std::cout << "Please select an integer\n" << ">>";
            input.clear();
            std::cin >> input;
        } else {
            o = std::stoi(input);
            check = false;
            return true;
        }
    }

    return false;
}

bool getAlphabet(int &modulo) {
    bool check = true;
    std::string input = "p";
    std::string ess = "S", ell = "L";

    std::cout << "Which alphabet will you use? Alphabet 'S' or 'L'?" << '\n' << ">>";
    std::cin >> input;


    while (check) {
        if (strcmp(ess.c_str(), input.c_str()) == 0) {
            modulo = 26;
            check = false;
            return true;
        } else if (strcmp(ell.c_str(), input.c_str()) == 0) {
            modulo = 52;
            check = false;
            return true;
        } else {
            std::cout << "Please select S or L." << '\n' << ">>";
            input.clear();
            std::cin >> input;
        }
    }

    return false;
}

bool checkIfRelativelyPrime(int mult, int mod) {

    std::cout << "\nERROR ERROR ERROR ERROR\n";
    std::cout << "The multiplier " << mult << " is NOT relatively prime to the modulo " << mod << ".\n";
    std::cout << "Please restart the program and try again with different numbers\n";
    std::cout << "~~~~~~~END ERROR~~~~~~~\n\n";
    return false;
}

bool checkForNonNumbers(std::string &s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void testCoprime(int big, int small) {
    float sqr = std::sqrt((float) big);
    float flr = std::floor(sqr);

    std::cout << "sqr : " << sqr <<
            "\nflr : " << flr <<
            "\nbig : " << big << std::endl;

}

bool readInInputFile(std::string &sText) {
    std::string out;
    std::ifstream myFile(inputFile.c_str());

    if (myFile.is_open()) {
        while (std::getline(myFile, sText)) {

            out += sText;
        }
        myFile.close();
        sText = out;

        removeSpaces(sText);
        removeNonLetters(sText);

        if ((sText.size() % 2)) {
            return true;
        } else {

            sText.append("A");
            return true;
        }
    } else {
        std::cout << "file " << inputFile << " didn't open!" << std::endl;
        return false;
    }

    return true;
}

bool readInCipherKey(std::string &sKey) {
    //    std::string out;
    //    std::ifstream myFile(cipherTextFile.c_str());
    //
    //    if (myFile.is_open()) {
    //        while (std::getline(myFile, sKey)) {
    //            out += sKey;
    //        }
    //        myFile.close();
    //        sKey = out;
    //
    //        return true;
    //    } else {
    //        std::cout << "file " << cipherTextFile << " didn't open!" << std::endl;
    //        return false;
    //    }
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
