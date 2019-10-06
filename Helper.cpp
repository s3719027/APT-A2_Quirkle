#include "Helper.h"
std::string rowsLetter(int rowNumber)
{
  std::string s="";
  if (rowNumber == 0)
    s = "A";
  else if (rowNumber == 1)
    s = "B";
  else if (rowNumber == 2)
    s = "C";
  else if (rowNumber == 3)
    s = "D";
  else if (rowNumber == 4)
    s = "E";
  else if (rowNumber == 5)
    s = "F";
  else if (rowNumber == 6)
    s = "G";
  else if (rowNumber == 7)
    s = "H";
  else if (rowNumber == 8)
    s = "I";
  else if (rowNumber == 9)
    s = "J";
  else if (rowNumber == 10)
    s = "K";
  else if (rowNumber == 11)
    s = "L";
  else if (rowNumber == 12)
    s = "M";
  else if (rowNumber == 13)
    s = "N";
  else if (rowNumber == 14)
    s = "O";
  else if (rowNumber == 15)
    s = "P";
  else if (rowNumber == 16)
    s = "Q";
  else if (rowNumber == 17)
    s = "R";
  else if (rowNumber == 18)
    s = "S";
  else if (rowNumber == 19)
    s = "T";
  else if (rowNumber == 20)
    s = "U";
  else if (rowNumber == 21)
    s = "V";
  else if (rowNumber == 22)
    s = "W";
  else if (rowNumber == 23)
    s = "X";
  else if (rowNumber == 24)
    s = "Y";
  else if (rowNumber == 25)
    s = "Z";

  return s;
}
int changeletterToInt(std::string rowLetter){
   int n = 0;

   if (rowLetter == "A")
     n = 0;
   else if (rowLetter == "B")
     n = 1;
   else if (rowLetter == "C")
     n = 2;
   else if (rowLetter == "D")
     n = 3;
   else if (rowLetter == "E")
     n = 4;
   else if (rowLetter == "F")
     n = 5;
   else if (rowLetter == "G")
     n = 6;
   else if (rowLetter == "H")
     n = 7;
   else if (rowLetter == "I")
     n = 8;
   else if (rowLetter == "J")
     n = 9;
   else if (rowLetter == "K")
     n = 10;
   else if (rowLetter == "L")
     n = 11;
   else if (rowLetter == "M")
     n = 12;
   else if (rowLetter == "N")
     n = 13;
   else if (rowLetter == "O")
     n = 14;
   else if (rowLetter == "P")
     n = 15;
   else if (rowLetter == "Q")
     n = 16;
   else if (rowLetter == "R")
     n = 17;
   else if (rowLetter == "S")
     n = 18;
   else if (rowLetter == "T")
     n = 19;
   else if (rowLetter == "U")
     n = 20;
   else if (rowLetter == "V")
     n = 21;
   else if (rowLetter == "W")
     n = 22;
   else if (rowLetter == "X")
     n = 23;
   else if (rowLetter == "Y")
     n = 24;
   else if (rowLetter == "Z")
     n = 25;

   return n;
}
std::string getInput(std::string word, int begin, int end)
{
  std::string usefulPath="";
  for（int i=begin;i<end; ++i)
  {
     usefulPath+=word[i];
  }
  return usefulPath;
}
char changeLetterToColor(int a)
{
  char color=' ';
  if(a==1)
  {
    color=RED;
  }
  else if(a==2)
  {
    color=ORANGE;
  }
  else if(a==3)
  {
    color=YELLOW;
  }
  else if(a==4)
  {
    color=GREEN;
  }
  else if(a==5)
  {
    color=BLUE;
  }
  else if(a==6)
  {
    color=PURPLE;
  }
  return color;
}
/*std::vector<int> randomNumber(int begin, int end)
{

  srand((unsigned)time(0));
  std::vector<int>b;
  int a[end];
  for(int i=0; i<end;++i)
  {
    a[i]=(rand()%(end-begin+1))+begin;
    for(int j=0; j<i;++j)
    {
      if(a[i]==a[j])
      {
        a[i]=(rand()%(end-begin+1))+begin;
        std::cout<<"Repeat"<<Std::endl;
      }
    }
  }
  for(int i=0; i<end;++i)
  {
    b.push_back(a[i]);
  }
  return b;
}*/
