#include "Menu.h"

Menu::Menu()
{
  //
}
Menu::~Menu()
{
  //
}

void Menu::showMenu()
{
  std::cout<<"Menu"<<std::endl;
  std::cout<<"-------------"<<std::endl;
  std::cout<<"1. New Game"<<std::endl;;
  std::cout<<"2. Load Game"<<std::endl;
  std::cout<<"3. Show Stydent Information"<std::endl;
  std::cout<<"Quit"<<std::endl;

  std::cout<<"<";
  char input=' ';
  std::cin>>input;
  if(input=='1')
  {
    StartGame* sg=new StartGame();
    sg->SetUpGame();
  }
  if(input=='2')
  {
    std::cout<<"----------"<<std::endl;
  }
  if(input=='3')
  {
    char buffer[256];
    std::ifstream read("StudentInfo.txt",std::ios::in);
    while(!read.eof())
   {
      read.getline(buffer,256);
      std::cout<<buffer<<std::endl;
    }
    read.close();
    showMenu();

  }
  if(input=='4')
  {
    std::cout<<"GoodBye"<<std::endl;
  }
}
