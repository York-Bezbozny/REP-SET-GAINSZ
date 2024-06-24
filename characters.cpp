#include "characters.h"  
#include <ctime>   
#include <cstdlib>  
#include <fstream>
#include <sstream>
#include <cmath>

const string CHARACTERS_FILE = "characters.txt";

// Input validation functions
bool isValidName(const string& name) {
  return all_of(name.begin(), name.end(), [](char c) { return isalpha(c) || isspace(c); });
}

bool isValidGender(const string& gender) {
  return (gender == "male" || gender == "female");
}

bool isValidInteger(const string& input) {
  return all_of(input.begin(), input.end(), ::isdigit);
}

bool isValidPositiveDouble(const string& input) {
  if (input.empty() || (input[0] == '-' && input.size() > 1))
      return false;
  size_t pos;
  try {
      stod(input, &pos);
      return pos == input.size(); // Ensure entire string is parsed
  } catch (const std::exception& e) {
      return false;
  }
}


// Function implementations (createCharacter, removeCharacter, printCharacters, findCharacter)
void createCharacter() {
    string name, gender;
    double height, weight, balance, minutes, seconds, hangtime, pushups, leg_stretch;
    float miles;

    // Input character information with error handling
    while (true) {
        cout << "\nCharacter Creation\n";

        cout << "What is your name, soldier? ";
        cin.ignore();
        getline(cin, name);
        if (!isValidName(name)) {
            cout << "Invalid name. Please use only letters and spaces.\n";
            continue;
        }

        ifstream file(CHARACTERS_FILE);
        string line;
        bool nameExists = false;
        while (getline(file, line)) {
            stringstream ss(line);
            string existingName;
            getline(ss, existingName, ';');
            if (existingName == name) {
                nameExists = true;
                break;
            }
        }
        file.close();
        if (nameExists) {
            cout << "Name already exists. Please choose a different name.\n";
            continue;
        }

        // ... (Input for gender, height, weight with error handling)
        while (true) {
            cout << "What is your gender? (male/female) ";
            getline(cin, gender);
            if (isValidGender(gender)) {
                break;
            }
            cout << "Invalid gender. Please enter 'male' or 'female'.\n";
        }

        while (true) {
            cout << "What is your height in inches? ";
            string input;
            getline(cin, input);
            if (isValidPositiveDouble(input)) {
                height = stod(input);
                break;
            }
            cout << "Invalid height. Please enter a positive number.\n";
        }

        while (true) {
            cout << "What is your weight in pounds? ";
            string input;
            getline(cin, input);
            if (isValidPositiveDouble(input)) {
                weight = stod(input);
                break;
            }
            cout << "Invalid weight. Please enter a positive number.\n";
        }

      while (true) {
        cout << "How long can you balance on one leg with your eyes closed (in seconds)? ";
        string input;
        getline(cin, input);
        if (isValidPositiveDouble(input)) {
            balance = stod(input);
            break;
        }
        cout << "Invalid balance time. Please enter a positive number.\n";
      }

      while (true) {
        cout << "What is your one-mile run time (MM:SS)? ";
        string input;
        getline(cin, input);
        if (input.find(":") != string::npos) {
            try {
                minutes = stoi(input.substr(0, input.find(":")));
                seconds = stoi(input.substr(input.find(":") + 1));
                if (minutes >= 0 && seconds >= 0 && seconds < 60) {
                    break;
                }
            } catch (const invalid_argument& e) {
                // Handle invalid argument exception (non-numeric input)
            }
        }
        cout << "Invalid run time. Please enter in the format MM:SS (e.g., 05:30).\n";
      }

      while (true) {
        cout << "How many miles can you run in an hour? ";
        string input;
        getline(cin, input);
        if (isValidPositiveDouble(input)) {
            miles = stod(input);
            break;
        }
        cout << "Invalid miles. Please enter a positive number.\n";
      }

      while (true) {
        cout << "How long can you hold a dead hang from a pullup bar for (in seconds)? ";
        string input;
        getline(cin, input);
        if (isValidPositiveDouble(input)) {
            hangtime = stod(input);
            break;
        }
        cout << "Invalid hang time. Please enter a positive number.\n";
      }

      while (true) {
        cout << "How many pushups can you do in two minutes? ";
        string input;
        getline(cin, input);
        if (isValidInteger(input) && stoi(input) >= 0) {
            pushups = stoi(input);
            break;
        }
        cout << "Invalid pushups. Please enter a non-negative integer.\n";
      }

      while (true) {
        cout << "What is your leg stretch angle in degrees (180 degrees = splits)? ";
        string input;
        getline(cin, input);
        if (isValidInteger(input) && stoi(input) >= 0) {
            leg_stretch = stoi(input);
            break;
        }
        cout << "Invalid leg stretch. Please enter a non-negative integer.\n";
      }

      // Calculate ability scores 
      int grace = round(10 + (balance - 10) / (60 - 10) * 10);
      int agility = round(10 + ((minutes * 60 + seconds) - 600) / (227 - 600) * 10);
      int iron = round(10 + (hangtime - 30) / (160 - 30) * 10);
      int nourishment = round(10 + (miles - 4) / (12 - 4) * 10);
      int strength = round(10 + (pushups - 34) / (100 - 34) * 10);
      int zen = round(10 + (leg_stretch - 80) / (300 - 80) * 10);
      map<string, vector<string>> class_mappings = {
          {"Grace", {"Phantom Striker", "Zephyr Blade", "Oracle Sage"}},
          {"Agility", {"Phantom Striker", "Zephyr Blade", "Siege Titan"}},
          {"Iron", {"Zenith Guardian", "Nova Harbinger"}},
          {"Nourishment", {"Siege Titan", "Zephyr Blade", "Oracle Sage"}},
          {"Strength", {"Siege Titan", "Nova Harbinger"}},
          {"Zen", {"Zenith Guardian"}}
      };

      // Find the highest-scoring ability and its classes
      map<string, int> ability_scores = {
          {"Grace", grace}, 
          {"Agility", agility}, 
          {"Iron", iron},
          {"Nourishment", nourishment},
          {"Strength", strength},
          {"Zen", zen}
      };

      // Find the highest-scoring ability (handling ties)
      vector<string> topAbilities;
      int maxScore = -1; // Initialize to a value lower than any possible score

      for (const auto& pair : ability_scores) {
          if (pair.second > maxScore) {
              maxScore = pair.second;
              topAbilities.clear(); // Reset the top abilities list
              topAbilities.push_back(pair.first);
          } else if (pair.second == maxScore) {
              topAbilities.push_back(pair.first);
          }
      }

      // Choose a class randomly from the potential classes of the top abilities
      string chosenClass;
      if (topAbilities.size() == 1) {
          vector<string> potentialClasses = class_mappings[topAbilities[0]];
          chosenClass = potentialClasses[rand() % potentialClasses.size()];
      } else { // Handle ties
          int randomIndex = rand() % topAbilities.size();
          string selectedAbility = topAbilities[randomIndex];
          vector<string> potentialClasses = class_mappings[selectedAbility];
          chosenClass = potentialClasses[rand() % potentialClasses.size()];
      }



        // Save character to file
        ofstream outfile(CHARACTERS_FILE, ios::app);
        outfile << name << ";" << gender << ";" << height << ";" << weight << ";"
                << grace << ";" << agility << ";" << iron << ";" 
                << nourishment << ";" << strength << ";" << zen << ";"
                << chosenClass << endl;
        outfile.close();
      cout << "\nYour ability scores are:\n";
        cout << "Grace: " << grace << endl;
        cout << "Agility: " << agility << endl;
        cout << "Iron: " << iron << endl;
        cout << "Nourishment: " << nourishment << endl;
        cout << "Strength: " << strength << endl;
        cout << "Zen: " << zen << endl;
       cout << "Your class is: " << chosenClass << endl;
        cout << "Character created and saved successfully!\n";
        break; // Exit the loop
    }
}

void removeCharacter() {
  string nameToRemove;
  cout << "\nEnter the name of the character to remove: ";
  cin.ignore(); // Clear newline from previous input
  getline(cin, nameToRemove);

  ifstream infile(CHARACTERS_FILE);
  ofstream outfile("temp.txt"); // Temporary file

  string line;
  bool found = false;
  while (getline(infile, line)) {
      stringstream ss(line);
      string name;
      getline(ss, name, ';'); 
      if (name != nameToRemove) {
          outfile << line << endl;
      } else {
          found = true;
      }
  }
  infile.close();
  outfile.close();

  if (found) {
      remove(CHARACTERS_FILE.c_str());    
      rename("temp.txt", CHARACTERS_FILE.c_str()); 
      cout << nameToRemove << " has been removed.\n";
  } else {
      cout << nameToRemove << " not found.\n";
      remove("temp.txt"); 
  }
}

void printCharacters() {
    string sortChoice;
    cout << "\nWould you like to sort characters? (y/n): ";
    cin >> sortChoice;

    ifstream infile(CHARACTERS_FILE);
    vector<vector<string>> characters;
    string line;

    // Read all characters into a vector for sorting
    while (getline(infile, line)) {
        if (line.empty()) {
            continue;
        }
        stringstream ss(line);
        vector<string> characterData;
        string token;
        while (getline(ss, token, ';')) {
            characterData.push_back(token);
        }
        characters.push_back(characterData);
    }
    infile.close();

    vector<string> attributeNames = {"Name", "Gender", "in.", "lbs.", "Grace",
                                    "Agility", "Iron", "Nourishment", "Strength", "Zen", "Class"}; // Attribute names for labels

    int sortIndex = 0; 

    if (sortChoice == "y") {
        char orderChoice;
        cout << "(H)ighest or (L)owest? ";
        cin >> orderChoice;

        cout << "Sort by:\n";
        for (int i = 2; i < attributeNames.size() - 1; ++i) { // Start from 2 to exclude name and gender
            cout << (i - 1) << ". " << attributeNames[i] << endl;
        }
        cout << "Enter your choice: ";
        cin >> sortIndex;

        if (sortIndex < 1 || sortIndex > 8) {
            cout << "Invalid choice. Characters will not be sorted.\n";
        } else {
            sortIndex += 1; // Adjust index to match attributes (starts from 2)

            sort(characters.begin(), characters.end(),
                 [&orderChoice, sortIndex](const vector<string>& a, const vector<string>& b) {
                     // Handle potential invalid_argument exceptions from stod
                     try {
                         double aVal = stod(a[sortIndex]);
                         double bVal = stod(b[sortIndex]);

                         if (orderChoice == 'H') {
                             return aVal > bVal;
                         } else {
                             return aVal < bVal;
                         }
                     } catch (const invalid_argument& e) {
                         cout << "Invalid data in characters file. Cannot sort.\n";
                         return false; // Don't change the order
                     }
                 });
        }
    }

    //Print the characters
    cout << "\nList of Characters:\n";

    // Calculate and print averages before sorting
    if (sortChoice == "y") {
        vector<double> sums(attributeNames.size(), 0.0); 
        int numCharacters = 0; 
        for (const auto& character : characters) {
            numCharacters++;
            for (int i = 2; i < attributeNames.size() - 1; ++i) {  // Exclude Name, Gender, and Class
                try {
                    sums[i] += stod(character[i]);
                } catch (const invalid_argument& e) {
                    // Handle non-numeric values, e.g., set to 0
                    sums[i] += 0.0;
                }
            }
        }

        cout << "\nAverage:" << (sums[sortIndex] / numCharacters) << attributeNames[sortIndex] << "\n" << endl;
        
    }

    for (const auto& character : characters) {
        cout << character[0] << endl;
    }
}








void findCharacter() {
    string nameToFind;
    cout << "\nEnter the name of the character to find: ";
    cin.ignore();
    getline(cin, nameToFind);

    ifstream infile(CHARACTERS_FILE);
    string line;
    bool found = false;
    while (getline(infile, line)) {
        stringstream ss(line);
        string name, gender, classChosen;
        int height, weight, grace, agility, iron, nourishment, strength, zen;
        getline(ss, name, ';');
        if (name == nameToFind) {
            found = true;

            // Read rest of the stats
            getline(ss, gender, ';');
            ss >> height; ss.ignore();  // Ignore semicolon
            ss >> weight; ss.ignore();
            ss >> grace; ss.ignore();
            ss >> agility; ss.ignore();
            ss >> iron; ss.ignore();
            ss >> nourishment; ss.ignore();
            ss >> strength; ss.ignore();
            ss >> zen; ss.ignore();
            getline(ss, classChosen);  // Read the rest as class

            // Display character stats in a readable format
            cout << "\nName: " << name << endl;
            cout << "Gender: " << gender << endl;
            cout << "Height: " << height << " inches" << endl;
            cout << "Weight: " << weight << " lbs" << endl;
            cout << "\nYour ability scores are:\n";
            cout << "Grace: " << grace << endl;
            cout << "Agility: " << agility << endl;
            cout << "Iron: " << iron << endl;
            cout << "Nourishment: " << nourishment << endl;
            cout << "Strength: " << strength << endl;
            cout << "Zen: " << zen << endl;
            cout << "Your class is: " << classChosen << endl;
            break;
        }
    }
    infile.close();

    if (!found) {
        cout << nameToFind << " not found.\n";
    }
}
