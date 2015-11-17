#include <iostream>
#include <cstdlib>
#include <ctime>        // header when generate different random values per each compilation
#include <fstream>     // header file for files
#include <limits>     //  header file needed when validating user input using cin.fail()
#include<windows.h>
using namespace std;

struct node  // this will help us implement doubly linked list
{
    int data;
    node *next, *prev;
  // next will point to the next element
    // prev will point to the previous element

};
node *bighead,*tail;
static int setValue = 0; // this will change depending on the data set being tested

void display()
{
    node *curPtr = bighead;
    while(curPtr!=NULL)
    {
        cout<<curPtr->data<<" ";

        curPtr=curPtr->next;
    }
  cout<<endl;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void add(node *head,int item)
{
    if(head==NULL) //list empty
    {
        node *newPtr = new node;
        newPtr->data = item;
        bighead = newPtr;
        tail = newPtr;
        newPtr->prev = NULL;
        newPtr->next= NULL;

    }

    else
    {
        node *newPtr = new node;
        newPtr->data = item;
        tail->next = newPtr;
        newPtr->prev = tail;  // prev now points to the previous element or node
        tail = newPtr;
        newPtr->next = NULL;

    }
}
void outFile()
{
     int maxsize;
     int value;
     int user;
     bool bFail;
    srand(time(0)); // this is to generate different numbers at every runtime

              do{
                    cout<<"\nEnter the data set you wish to sort:<greater than zero (0)> ";
                    cin>>maxsize;  // number of digits to be generated

                   try{
                            if(maxsize < 0){
                            throw -1;
                        }
                            else if(cin.fail()){ //if input = "letters"
                            throw 'a';
                        }

                    } catch(int a) {
                        cout<<"\nDo not enter negative number...\n" <<endl;
                        cin.clear();
                        cin.ignore();
                        //system("pause");

                    } catch(...) {
                        cout<<"\nPlease only enter other number greater than zero...\n"<< endl;
                        cin.clear();
                        cin.ignore();
                        //system("pause");

                    }

                }while(maxsize<=0);

                 setValue = maxsize;
                 ofstream output;
                 output.open("output.txt");
                if(output.fail())
                {
                  cerr<<"Error while opening file";
                  exit(1);
                }
             for(int i=0;i < maxsize;i++) // enter data set..20..0r 200..or 2000
               {
                value = (1 +rand()% 10); // generate random numbers from 1 to 10
                output<<value<<" ";
               }
              output.close();
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void inputFile()
{
    bighead = NULL;
     ifstream input;
      input.open("output.txt");
      if(input.fail())
      {
          cerr<<"Error while opening file"<<endl;
          exit(1);
      }

      while(true)
      {   int x;
          input>>x;
          if(input.eof()) break;

          add(bighead,x);
      }

      input.close();
}
void InsertSort()
{
     inputFile();
      display();
      node *head = bighead;
      node *endPtr =head;
    node *curPtr = endPtr->next;
    int val;


    while(curPtr !=NULL)
    {
        val =curPtr->data;
          while(curPtr !=head && curPtr->prev->data > val)
         {
           curPtr->data = curPtr->prev->data;
           curPtr = curPtr->prev;
         }
          curPtr->data = val;

              if(setValue <=20) display();

          endPtr = endPtr->next;
          curPtr = endPtr->next;
    }
    cout<<endl;
    display();

}
void menu()
{
    char val;

     do{

            InsertSort();
            cout<<"Do you wish to sort again bubble sort..<y/n>: ";
            cin>>val;
             outFile();


     }while(val== 'y');

}
int main()
{


    outFile();  // generate random values and store them to a textfile
     menu();
    cout<<endl;

    cout<<"System Exiting...Thank You...."<<endl;
    return 0;
}
