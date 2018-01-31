/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: matthew rose
 *
 * Created on January 17, 2018, 2:07 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>

std::string plainTextFile = "/tmp/blockaffinecipherplaintextoutput.txt";
std::string cipherTextFile = "/tmp/vcipherkey.txt";
std::string outputTextFile = "/tmp/secondplaintext.txt";

std::string alphabet_S = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string alphabet_L = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

bool readInPlainText(std::string &sText);
bool readInCipherKey(std::string &sKey);
bool writeOutputFile(std::string output);

std::string trim(const std::string &s);

void removeSpaces(std::string &s);
void removeNonLetters(std::string &s);

void decrypt_S(std::string plain, std::string key, std::string &output);
void decrypt_L(std::string plain, std::string key, std::string &output);

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
        removeSpaces(cipherKey);
        removeNonLetters(cipherKey);
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

            decrypt_S(plainText, cipherKey, output);
        } else if (strcmp(ell.c_str(), input.c_str()) == 0) {
            std::cout << "Using alphabet L" << std::endl;
            check = false;

            decrypt_L(plainText, cipherKey, output);
        } else {
            std::cout << "Please select S or L." << '\n' << ">>";
            input.clear();
            std::cin >> input;
            trim(input);
        }
    }

    std::cout << "PlainText  : " << plainText << std::endl;
    std::cout << "Decrypted  : " << output << std::endl;

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

void removeSpaces(std::string &s) {
    std::string::iterator endIterator = std::remove(s.begin(), s.end(), ' ');
    s.erase(endIterator, s.end());
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

void decrypt_S(std::string plain, std::string key, std::string &output) {
    unsigned int keyCount = 0;
    int alphaIndex = 0;
    removeSpaces(plain);

    for (std::string::iterator it = plain.begin(); it != plain.end(); ++it) {
        if (keyCount == key.size()) keyCount = 0;

        alphaIndex = ((int) *it - 65) - ((int) key[keyCount] - 65);

        if (alphaIndex < 0) {
            alphaIndex = alphaIndex + 26;
        }

        output += alphabet_S[alphaIndex];

        keyCount++;
    }
}

void decrypt_L(std::string plain, std::string key, std::string &output) {
    unsigned int keyCount = 0;
    int alphaIndex = 0;
    //    int alphabetSize = alphabet_L.size();

    removeSpaces(plain);

    for (std::string::iterator it = plain.begin(); it != plain.end(); ++it) {
        if (keyCount == key.size()) keyCount = 0;

        //need to account for lower case numbers!
        //different ASCII values. See a table. 

        int partA = 0;
        int partB = 0;

        if ((int) *it >= 97) {
            partA = (int) *it - 71;
        } else {
            partA = (int) *it - 65;
        }

        if ((int) key[keyCount] >= 97) {
            partB = (int) key[keyCount] - 71;
        } else{
            partB = (int) key[keyCount] - 65;
        }
        
        alphaIndex = partA - partB;


        if (alphaIndex < 0) {
            alphaIndex = alphaIndex + 52;
        }

        output += alphabet_L[alphaIndex];

        keyCount++;
    }
}