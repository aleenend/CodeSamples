/*  Aleene Dupuy

    This file contains the permute class and its function implementations.
    This file was written by me.
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <string>

using namespace std;

class permute {
  private:
    //original number sequence
    vector<string> numberSequence;
    //final permutation
    vector<string> permutation;
    int permutationCount;
  public:
    permute(vector<string> data);
    void print_permutation();
    void quick_permute();
    void stack_permute();
    void random_comparison_permute();

};

/*
  This is the constructor for the permute class. It just puts the values from
  the data vector into a new vector and sets permutationCount to 0.
*/
permute::permute(vector<string> data){
  for(unsigned int i = 0; i < data.size(); i++){
    numberSequence.push_back(data.at(i));
  }

  permutationCount = 0;
}

/*
    This function keeps track of how many permutations were performed and uses
    a different function for each new permutation. Then it prints the
    permutation.
*/
void permute::print_permutation(){
  permutationCount++;
  vector<string>::iterator iter;

  //switch statement to use different permutation functions
  switch(permutationCount){
    case 1:
      quick_permute();
      break;
    case 2:
      stack_permute();
      break;
    case 3:
      random_comparison_permute();
      break;
  }

  //prints permutation
  for(iter = permutation.begin(); iter != permutation.end(); iter++){
    cout << *iter;
  }
  cout << endl;
  //clears permutation for next one
  permutation.clear();
}

/*
    This function is called quick permute only because the beginning was
    inspired by the beginning of quicksort. It generates a random number between
    0 and the size of the numberSequence. It then checks if each value in
    numberSequence is greater or less than the value at the random point and
    puts each value in the corresponding vector.

    It then generates another random number - either a 1 or a 0 and puts the
    values in the final permutation vector depending on the random number. If
    the  number is 1, the smaller values are put in the vector first in reverse
    order and then the larger values are put in in order. If the number is 0,
    the larger values are put in the vector first in reverse order and then the
    smaller values are put in in order.
*/
void permute::quick_permute(){
  //variables
  vector<string> lessThanPoint;
  vector<string> pointOrGreater;
  unsigned int i;
  srand(time(NULL));
  int randomPoint;

  for(i = 0; i < numberSequence.size(); i++){
    randomPoint = rand() % numberSequence.size();
    if(numberSequence.at(i) > numberSequence.at(randomPoint)){
      pointOrGreater.push_back(numberSequence.at(i));
    }
    else{
      lessThanPoint.push_back(numberSequence.at(i));
    }
  }

  //if random number is 1
  if((rand() % 2) > 0){
    //puts smaller numbers in vector backwards
    for(i = lessThanPoint.size(); i > 0; i--){
      permutation.push_back(lessThanPoint.at(i - 1));
    }
    //puts larger numbers in vector forwards
    for(i = 0; i < pointOrGreater.size(); i++){
      permutation.push_back(pointOrGreater.at(i));
    }
  }
  //random number is 0
  else{
    //puts larger numbers in vector backwards
    for(i = pointOrGreater.size(); i > 0; i--){
      permutation.push_back(pointOrGreater.at(i - 1));
    }
    //puts smalelr numbers in vector forwards
    for(i = 0; i < lessThanPoint.size(); i++){
      permutation.push_back(lessThanPoint.at(i));
    }
  }
}

/*
    This function is called stack permute because it uses stacks. It loops
    through the original number sequence and puts the value in stack2 if it is
    greater than a random number, otherwise it puts the value in stack1.

    Then it generates another random number - either a 1 or a 0 and puts the
    values in the final permutation vector based on that number. If it's 1, it
    alternates between putting stack1 and stack2 in permutation with stack1
    first. If it's 0, it alternates between putting stack1 and stack2 in
    permutation with stack2 first.

    Then another random number is generated and if it's 1, the final permutation
    gets reversed.
*/
void permute::stack_permute(){
  //variables
  stack<string> stack1;
  stack<string> stack2;
  vector<string> reverse;
  unsigned int i;
  srand(time(NULL));

  for(i = 0; i < numberSequence.size(); i++){
    //if value greater than random number
    if((rand() % 30) / 2 < stoi(numberSequence.at(i))){
      stack2.push(numberSequence.at(i));
    }
    //if value less than random number
    else{
      stack1.push(numberSequence.at(i));
    }
  }
  while(permutation.size() != numberSequence.size()){
    //if random number is 1
    if(rand() % 2 > 0){
      //puts value from stack1 in permutation stack
      if(!stack1.empty()){
        permutation.push_back(stack1.top());
        stack1.pop();
      }
      //then puts value from stack2 in permutation stack
      if(!stack2.empty()){
        permutation.push_back(stack2.top());
        stack2.pop();
      }
    }
    //if random number is 0
    else{
      //puts value from stack2 in permutation stack
      if(!stack2.empty()){
        permutation.push_back(stack2.top());
        stack2.pop();
      }
      //then puts value from stack1 in permutation stack
      if(!stack1.empty()){
        permutation.push_back(stack1.top());
        stack1.pop();
      }
    }
  }

  //if 1, reverses final permutation
  if(rand() % 2 > 0){
    //puts permutation in another vector backwards
    for(i = permutation.size(); i > 0; i--){
      reverse.push_back(permutation.at(i - 1));
    }
    permutation.clear();
    //puts the reverse back in permutation
    for(i = 0; i < reverse.size(); i++){
      permutation.push_back(reverse.at(i));
    }
  }
}

/*
    This function is called random comparison permute because it compares a
    value to a random value. If the value is greater than the random value, it
    puts it in the final permutation vector and makes the value 0 so it cannot
    be used again. This only works because it is the final permutation. It keeps
    going until each value has been put in the final permutation vector.
*/
void permute::random_comparison_permute(){
  unsigned int i;
  srand(time(NULL));

  while(permutation.size() != numberSequence.size()){
    for(i = 0; i < numberSequence.size(); i++){
      //if value is greater than random number divided by 3
      if((rand() % 100) / 3 < stoi(numberSequence.at(i))){
        //add value to vector and set it to 0 in original vector
        permutation.push_back(numberSequence.at(i));
        numberSequence.at(i) = "0";
      }
    }
  }
}
