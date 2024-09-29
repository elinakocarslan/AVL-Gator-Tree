#include <iostream>
#include <sstream>
#include"AVL.h"

/* Note:
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

bool checkIfInputCorrect(std::string input, bool letters) { // checks if the input string has letter or number characters
    if ((!letters && input.length() != 8) && (letters && input.length() > 0)){ // making sure an actual input exists, for search
        return false;
    }
    for (char letter : input) {
        if (letter == ' ') {
            continue;
        }
        if (letters && !std::isalpha(letter)) { // if letters are meant to be in the string and are not return false; taken from Project 1 video
            return false;
        } else if (!letters && !std::isdigit(letter)) { // if letters are meant to be in it and are not return false; taken from Project 1 video
            return false;
        }
    }
    return true;
}
int main() {
    AVLTree *gators = new AVLTree;
    std::string numOfCommands; // code from project 1 video breakdown
    getline(std::cin, numOfCommands);

    std::vector<std::string> functions;
    std::vector<std::string> names;
    std::vector<std::string> ufids;


    for (int i = 0; i < stoi(numOfCommands); i++) { //code from video project 1 breakdown
        std::string line;
        getline(std::cin, line);

        std::istringstream newCin(line);

        std::string function;
        getline(newCin, function, ' ');
        functions.push_back(function);

        if (function == "remove" || function == "removeInorder") {
            names.push_back("");

            std::string ufid;
            getline(newCin, ufid);
            ufids.push_back(ufid);
        }else {
            std::string next;
            getline(newCin, next, '"');

            std::string name;
            getline(newCin, name, '"');
            names.push_back(name);

            std::string next2;
            getline(newCin, next2, ' ');

            std::string ufid;
            getline(newCin, ufid);
            ufids.push_back(ufid);
        }

//        std::cout << function << std::endl;
//        std::cout << name << std::endl;
//        std::cout << ufid << std::endl;
    }

    for (int i = 0; i < functions.size(); i++) {

        bool letters;

        if (functions[i] == "insert") {
            letters = true;
            if (!checkIfInputCorrect(names[i], letters)) {
                std::cout << "unsuccessful" << std::endl;
                return 0;
            }

            letters = false;
            if (!checkIfInputCorrect(ufids[i], letters)) {
                std::cout << "unsuccessful" << std::endl;
                return 0;
            }
            gators->insert(names[i], ufids[i]);
        }
        else if (functions[i] == "remove") {
            letters = false;
            if (!checkIfInputCorrect(ufids[i], letters)) {
                std::cout << "unsuccessful" << std::endl;
                return 0;
            }
            gators->remove(ufids[i]);
        }else if (functions[i] == "removeInorder") {
            for (char letter : ufids[i]) {
                if (!std::isdigit(letter)) { // second input but the name of the var is name
                    std::cout << "unsuccessful" << std::endl;
                    return 0;
                }
            }
            gators->removeInOrder(stoi(ufids[i])); // convert string into int
        }else if (functions[i] == "search"){
            if (ufids[i] != "") {
                letters = false;
                if (!checkIfInputCorrect(ufids[i], letters)){ //had to do it a diff way beacuse there is two things to check for
                    std::cout << "unsuccessful" << std::endl;
                    return 0;
                }
                gators->searchID(ufids[i]);
            }else if (names[i] != ""){
                letters = true;
                if (!checkIfInputCorrect(names[i], letters)) { // checking if letters exist, if not it must be an id input
                    std::cout << "unsuccessful" << std::endl;
                    return 0;
                }
                gators->searchNAME(names[i]);
            }
        }else if (functions[i] == "printInorder") {
            gators->printInOrder();
        }else if (functions[i] == "printPreorder") {
            gators->printPreOrder();
        }else if (functions[i] == "printPostorder") {
            gators->printPostOrder();
        }else if (functions[i] == "printLevelCount") {
            gators->printLevelCount();
        }
    }

    return 0;

}
