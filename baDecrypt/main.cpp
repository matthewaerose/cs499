/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: sslt
 *
 * Created on January 20, 2018, 8:00 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <math.h>

#include <cctype>
#include <vector>

//using namespace std;

std::string inputFile = "/tmp/blockaffinecipheroutput.txt";
std::string outputTextFile = "/tmp/blockaffinecipherplaintextoutput.txt";

std::string alphabet_S = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string alphabet_L = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

long long result;
/*
 * 
 */

bool readInInputFile(std::string &sText);
bool writeOutputFile(std::string output);

bool testCoprime(long long a, long long b);

void lettersToNumbers(std::string s, std::vector<std::string> &i, int m);

bool getMultiplier(long long &m);
bool getOffset(long long &o);
bool getAlphabet(int &modulo);

int modInverse(long long a, long long b);

bool checkForNonNumbers(std::string &s);

void decrypt_S(std::vector<std::string> input, long long multiplier, long long offset, std::string &output);
void decrypt_L(std::vector<std::string> input, long long multiplier, long long offset, std::string &output);

int main(int argc, char** argv) {

    std::string inputText = "This should NOT be here";
    std::string outputText = "not here";
    long long offset = -1;
    long long multiplier = -1;
    int modulo = -1;
    result = 0;
    std::vector<std::string> numberVector;

    readInInputFile(inputText);

    if (getAlphabet(modulo)) {
        std::cout << "Your modulo is " << modulo << std::endl;
        lettersToNumbers(inputText, numberVector, modulo);
    }

    if (getMultiplier(multiplier)) {
    }

    if (getOffset(offset)) {
    }

    if (testCoprime(multiplier, modulo)) {
        std::cout << "The multiplier and modulus were co-prime!" << std::endl;
    } else {
        std::cout << "\nERROR ERROR ERROR ERROR\n";
        std::cout << "The multiplier " << multiplier << " is NOT relatively prime to the modulo " << modulo << ".\n";
        std::cout << "Please restart the program and try again with different numbers\n";
        std::cout << "~~~~~~~END ERROR~~~~~~~\n\n";
        return -1;
    }

    std::cout << "Decrypting!" << std::endl;

    if (modulo == 2526) {
        decrypt_S(numberVector, multiplier, offset, outputText);
    } else {
        decrypt_L(numberVector, multiplier, offset, outputText);
    }

    std::cout << "Writing file " << outputTextFile << std::endl;

    if (writeOutputFile(outputText)) {
        std::cout << "File " << outputTextFile << " was written." << std::endl;
    } else {
        std::cout << "File " << outputTextFile << " was NOT written." << std::endl;
    }
    return 0;
}

void lettersToNumbers(std::string s, std::vector<std::string> &i, int mod) {
    std::string build = "";

    for (std::string::iterator t = s.begin(); t != s.end(); ++t) {
        build.append(std::to_string((int) *t - 48));
        //        ++t;
        //        build.append(std::to_string((int) *t - 48));
        if ((build.size()) % 4 == 0) {
            i.push_back(build);
            build.clear();
        }
        //        i.push_back(build);
    }
}

bool getMultiplier(long long &m) {
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
            m = std::stoll(input);
            check = false;
            return true;
        }
    }

    return false;
}

bool getOffset(long long &o) {
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
            o = std::stoll(input);
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
            modulo = 2526;
            check = false;
            return true;
        } else if (strcmp(ell.c_str(), input.c_str()) == 0) {
            modulo = 5152;
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

bool checkForNonNumbers(std::string &s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int modInverse(long long a, long long b) {
    long long t = 0, new_t = 1;
    long long r = b, new_r = a;

    while (new_r != 0) {
        long long quotient = r / new_r;
        long long swap = new_t;
        new_t = t - quotient * swap;
        t = swap;

        swap = new_r;
        new_r = r - quotient * swap;
        r = swap;
    }

    if (r > 1) {
        std::cout << a << " is not invertible." << std::endl;
        return -1;
    }

    if (t < 0) {
        t = t + b;
        std::cout << "the inverse is " << t << "!" << std::endl;
        return t;
    } else {
        std::cout << "the inverse is " << t << "!" << std::endl;
        return t;
    }

    return true;
}

bool testCoprime(long long big, long long small) {

    if (big > small) {
    } else {
        int swap = big;
        big = small;
        small = swap;
    }
    if (big == 1 && small == 0) {
        return true;
    } else if (big != 1 && small == 0) {
        return false;
    } else {
        result = big % small;
        testCoprime(small, result);
    }
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

    } else {
        std::cout << "file " << inputFile << " didn't open!" << std::endl;
        return false;
    }

    return true;
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

void decrypt_S(std::vector<std::string> input, long long multiplier, long long offset, std::string &output) {
    int inverse = modInverse(multiplier, 2526);
    // decrypt the blocks
    // encrypted = (mP + off) mod 2526
    std::string encrypted = "";

    for (unsigned int i = 0; i < input.size(); ++i) {
        long long C = std::stoll(input.at(i)) - offset;
        C = inverse * C;
        int P = C % 2526;

        std::string resu = std::to_string(P);
        std::string sOne = "";
        std::string sTwo = "";

        if (resu.size() == 1) {
            sOne += "0";
            sOne += "0";
            sTwo += "0";
            sTwo += resu[0];
        } else if (resu.size() == 2) {
            sOne += "0";
            sOne += "0";
            sTwo += resu[0];
            sTwo += resu[1];
        } else if (resu.size() == 3) {
            sOne += "0";
            sOne += resu[0];
            sTwo += resu[1];
            sTwo += resu[2];
        } else if (resu.size() == 4) {
            sOne += resu[0];
            sOne += resu[1];
            sTwo += resu[2];
            sTwo += resu[3];
        }
        
        encrypted += alphabet_S[std::stoi(sOne)];
        encrypted += alphabet_S[std::stoi(sTwo)];
    }
    output = encrypted;
}

void decrypt_L(std::vector<std::string> input, long long multiplier, long long offset, std::string &output) {
    int inverse = modInverse(multiplier, 5152);
    // decrypt the blocks
    // encrypted = (mP + off) mod 2526
    std::string encrypted = "";

    for (unsigned int i = 0; i < input.size(); ++i) {
        long long xMINUSb = std::stoll(input.at(i)) - offset;
        long long mult = inverse * xMINUSb;
        int P = mult % 5152;

        std::string resu = std::to_string(P);
        std::string sOne = "";
        std::string sTwo = "";

        if (resu.size() == 1) {
            sOne += "0";
            sOne += "0";
            sTwo += "0";
            sTwo += resu[0];
        } else if (resu.size() == 2) {
            sOne += "0";
            sOne += "0";
            sTwo += resu[0];
            sTwo += resu[1];
        } else if (resu.size() == 3) {
            sOne += "0";
            sOne += resu[0];
            sTwo += resu[1];
            sTwo += resu[2];
        } else if (resu.size() == 4) {
            sOne += resu[0];
            sOne += resu[1];
            sTwo += resu[2];
            sTwo += resu[3];
        }
        
        encrypted += alphabet_L[std::stoi(sOne)];
        encrypted += alphabet_L[std::stoi(sTwo)];
    }
    output = encrypted;

}

