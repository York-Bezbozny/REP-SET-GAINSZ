#ifndef CHARACTERS_H // Include guard to prevent multiple inclusions
#define CHARACTERS_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm> 

using namespace std;

// Function prototypes (declarations)
void createCharacter();
void removeCharacter();
void printCharacters();
void findCharacter();

bool isValidName(const string& name);
bool isValidGender(const string& gender);
bool isValidInteger(const string& input);
bool isValidPositiveDouble(const string& input);

extern const string CHARACTERS_FILE;

#endif // CHARACTERS_H
