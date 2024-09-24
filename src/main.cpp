#include <iostream>
#include"AVL.h"

/* Note:
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

bool checkIfInputCorrect(std::string input, bool letters) { // checks if the input string has letter or number characters
    if (letters && input.find_first_not_of("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMONPQRSTUVWXYZ") != std::string::npos) { // if letters are meant to be in the string and are not return false
        return false;
    }else if (!letters && input.find_first_not_of("0123456789") != std::string::npos) { // if letters are meant to be in it and are not return false
        return false;
    }
    return true;
}
int main(){
    AVLTree* gators = new AVLTree;
    int input; //how many lines there will be
    std::cin >> input;


    //read each line and store them into a vector
    for (int i = 0; i < input; i++) {
        std::string command; //creating variables to keep track of the lines of input
        std::cin >> command;
        bool letters;

        if (command.substr(0,6) == "insert") {
            command.erase(0, 6);
            letters = true;
            std::string name = command.substr(0, command.find(" ") - 1); // taking out the second string left in command, to have name
            if (!checkIfInputCorrect(name, letters)) {
                std::cout << "unsuccessful" << std::endl;
                return 0;
            }

            letters = false;
            command.erase(0, command.find(" ") + 1); // only leaving ufid in command
            std::string ufid = command;
            if (!checkIfInputCorrect(ufid, letters) && ufid.size() != 8) {
                std::cout << "unsuccessful" << std::endl;
                return 0;
            }
            gators->insert(name, ufid);
        }else if (command.substr(0,6) == "remove") {
            command.erase(0, 6);
            letters = false;
            std::string ufid = command.substr(0, command.find(" ") - 1); // leaving the id
            if (!checkIfInputCorrect(ufid, letters)) {
                std::cout << "unsuccessful" << std::endl;
                return 0;
            }
            gators->remove(ufid);
        }else if (command.substr(0,13) == "removeInOrder") {
            command.erase(0, 6); // leaving n index only
            letters = false;
            std::string n = command;
            if (!checkIfInputCorrect(n, letters)) {
                std::cout << "unsuccessful" << std::endl;
                return 0;
            }
            gators->removeInOrder(stoi(n)); // convert string into int
        }else if (command.substr(0, 6) == "search"){
            command.erase(0, 6); // leaving the name or id
            letters = true;
            std::string nameOrID = command;
            if (!checkIfInputCorrect(nameOrID, letters)) { // checking if letters exist, if not it must be an id input
                gators->searchNAME(nameOrID);
            }
            else {
                gators->searchID(nameOrID);
            }
        }else if (command == "printInOrder"){
            gators->printInOrder();
        }else if (command == "printPreOrder"){
            gators->printPreOrder();
        }else if (command == "printPostOrder"){
            gators->printPostOrder();
        }else if (command == "printLevelCount"){
            gators->printLevelCount();
        }
    }
    return 0;
}

