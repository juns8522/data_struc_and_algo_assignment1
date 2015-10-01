#include <iostream>
#include <fstream>
#include <cstdlib>
#include <list>

using namespace std;

class isbn
{
   private:
   list <string> isbns;
   int newIsbn[10];
   public:

   isbn()
   {
   }

   isbn(const isbn &other) :
   isbns(other.isbns)
   {
   }

   ~isbn()
   {
   }

   void addIsbn(string number)
   {
      isbns.push_back(number);
   }

   bool isValid(string number)
   {
      if(isTenNumbers(number))
      {
         setNewIsbn(number);
         return isMultiple();
      }
      return false;
   }

   bool isTenNumbers(string number) const
   {
      int count = 0;
      int lastIndex = number.length() - 1;

      if(isdigit(number[0]))
         count++;

      if( isdigit(number[lastIndex]) || number[lastIndex] == 'X')
         count++;

      for(int i = 1; i < (int)lastIndex; i++)
      {
         if(isdigit(number[i]))
            count++;
         else if(number[i] != ' ' && number[i] != '-')
            return false;
      }
      return count == 10;
   }

   bool isMultiple() const
   {
      int weight = 10;
      int sum = 0;

      for(int i = 0; i < 10; i++)
      {
         sum += (newIsbn[i] * weight);
         weight--;
      }
      return sum % 11 == 0;
   }

   isbn& operator = (const isbn &other)
   {
      isbns = other.isbns;
      return *this;
   }

   void setNewIsbn(string number)
   {
      int index = 0;

      for(int i = 0; i < (int)number.length(); i++)
      {
         if(isdigit(number[i]))
         {
            newIsbn[index] = number[i] - '0';
            index++;
         }
         else if(number[i] == 'X')
         {
            newIsbn[index] = 10;
            index++;
         }
      }
   }

   list <string> getIsbns() const
   {
      return isbns;
   }
};

void openFile(char *argv[], isbn &myIsbn);
void printTitle(char *argv[]);
void printError();
void check(isbn myIsbn);

int main(int argc, char *argv[])
{
   isbn myIsbn;

   openFile(argv, myIsbn);
   check(myIsbn);

   return 0;
}

void openFile(char *argv[], isbn &myIsbn)
{
   ifstream fin;
   string number;

   fin.open(argv[1]);

   if(!fin)
   {
      printError();
      exit(0);
   }

   printTitle(argv);

   while(!fin.eof())
   {
      getline(fin, number);

      if(number.size() != 0)
         myIsbn.addIsbn(number);
   }
   fin.close();
}

void printTitle(char *argv[])
{
   cout << "\nISBN file : " << argv[1] <<"\n\n";
}

void printError()
{
   cout << "Program failed with the following message" <<endl;
   cout << "Unable to open file to read" <<endl;
}

void check(isbn myIsbn)
{
   list <string> isbns = myIsbn.getIsbns();
   list<string>::const_iterator itr;

   for (itr = isbns.begin(); itr != isbns.end(); itr++ )
   {
      cout << *itr <<" ";

      if(myIsbn.isValid(*itr))
         cout << "is a valid ISBN" <<endl;
      else
         cout << "is not a valid ISBN" <<endl;
   }
}
