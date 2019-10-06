
#include "LinkedList.h"

#include <iostream>
#include <string>

#define EXIT_SUCCESS    0
#define MAX_PLAYERS 4

void loadMenu();
void startNewGame();
void loadGame();
void showStudentInformation();

int main(void) {

  LinkedList* list = new LinkedList();
  int menuChoice;

  loadMenu();
  std::cin >> menuChoice;

  while ( validMenuChoice(menuChoice) ) {
    std::cout << "Oops! Invalid choice, Try again...\n>";
    std::cin >> menuChoice;
  }

  if ( menuChoice == 1 ) {
    //Start new game
    startNewGame();

  } else if ( menuChoice == 2 ) {
    //Load game
    loadGame();

  } else if ( menuChoice == 3 ) {
    //Show student information
    showStudentInformation();

  } else if ( menuChoice == 4 ) {
    std::cout << "Goodbye!" << std::endl;
    return EXIT_SUCCESS;
  }


  delete list;
  return EXIT_SUCCESS;
}

void loadMenu() {
  std::cout << "Welcome to Qwirkle!\n-------------------" << std::endl;
  std::cout << "Menu\n----\n1. New Game\n2. Load Game\n3. Show student information\n4. Quit\n\n> ";
}

bool validMenuChoice( int choice ) {
  if ( choice < 1 && choice > 4) {
    return true;
  }
  return false;
}

void startNewGame() {
  int totalPlayer;
  std::cout << "Starting a new game!\nEnter number of players [ 2 - 4 ]\n>";

  std::cin >> totalPlayer;
  while ( totalPlayer < 2 || totalPlayer > MAX_PLAYERS ) {
    std::cout << "Invalid number of players.\nEnter number of players [ 2 - 4 ] \n>";
    std::cin << totalPlayer;
  }

  std::string playerName
  std::cin.ignore();

  for ( int x = 0; x < totalPlayer; x++ ) {
    std::cout << "Enter a name for player " << x + 1 << ". ( Uppercase characters only! )\n>";

    std::string inputName;
    getline(std::cin, inputName);
    while ( inputName.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != std::string::npos ) {
      print_str("Name is not valid, enter a valid name:\n> ");
      getline(std::cin, s);
    }

    playerName[x] = inputName;
  }

  std::cout << "Let's play!" << std::endl;

  //Game code

}


void loadGame() {
  std::cin.ignore();
  std::cout << "Enter the filename from which load a game. Type 'Back' to go back to menu.\n>";
  std::string fileName;
  std::cin >> fileName;

  while ( fileName != "Back" ) {
    std::ifstream file( fileName.c_str() );
    while ( !file.good() ) {
      std::cout << "File doesn't exist. Please re-enter filename." << std::endl;
      std::cin >> fileName;
    }
  }
}

void showStudentInformation() {
  std::cout << "---------------------------------- " << std::endl;
  std::cout << "Name:\t" << "Daniel Bound" << std::endl;
  std::cout << "Student ID:\t" << "s3719027" << std::endl;
  std::cout << "Email:\t" << "s3719027@student.rmit.edu.au\n" << std::endl;

  std::cout << "Name:\t" << "Zhiwei Hou" << std::endl;
  std::cout << "Student ID:\t" << "s3699329" << std::endl;
  std::cout << "Email:\t" << "s3699329@student.rmit.edu.au\n" << std::endl;

  std::cout << "Name:\t" << "Hui Alvin Markus" << std::endl;
  std::cout << "Student ID:\t" << "s3677729" << std::endl;
  std::cout << "Email:\t" << "s3677729@student.rmit.edu.au\n" << std::endl;

  std::cout << "Name:\t" << "Zhifeng Rong" << std::endl;
  std::cout << "Student ID:\t" << "s3631999" << std::endl;
  std::cout << "Email:\t" << "s3631999@student.rmit.edu.au" << std::endl;
  std::cout << "---------------------------------- " << std::endl;
}
