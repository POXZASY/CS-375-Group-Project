#include <iostream>
#include <fstream> //read / write to files
#include <algorithm> //max function
#include <chrono> //time
#include <vector>
#include <string>

using namespace std;

//struct that contains all the information for a single knapsack problem
//the indicies of the weights and values correspond via item. e.g.: weights[1] and values[1] are the respective weight and value for the second item in the problem
struct Problem{
  vector<int> weights;
  vector<int> values;
  int capacity;
};
//struct that contains all information necessary for a complete solution to a knapsack problem
//items are the 1-indexed items that are included in the solution
//weights correspond to the weights of the items i.e. weights[2] is the weight of the third item
//values correspond to the values of the items i.e. values[2] is the value of the third item
struct Solution{
  vector<int> items;
  vector<int> weights;
  vector<int> values;
  vector<vector<int>> knapsackvals; //the solution matrix
  int totalweight; //sum of all the weights of the items in solution
  int totalvalue; //total profit for the solution
  int capacity; //capacity of the problem
  int nanotime; //time spent computing the solution, in nanoseconds
};

//split a string by a space
//takes in a string and splits it up into a vector of strings, where each string in the vector is part of the input string, split by ' '
vector<string> strsplit(string str){
  vector<string> strs; //vector to be returned
  string tempstr = ""; //stores the current string, is pushed back to the vector when a space is encountered or the line ends
  for(unsigned int i = 0; i < str.length(); i++){
    char currentchar = str.at(i); //current character being read. function goes character by character and checks for ' ', adds otherwise
    if(currentchar!=' ') tempstr.append(string(1, currentchar));
    else{
      strs.push_back(tempstr);
      tempstr = "";
    }
  }
  if(tempstr!="" && tempstr!=" ") strs.push_back(tempstr);
  return strs;
}

//returns a vector of all the problems represented by strings in a text file
//filename must be a .txt or similar format, and must have extension
//file must be organized with every 3 lines representing a problem
//lines 1 mod 3 are the weights
//2 mod 3 the values
//0 mod 3 the capacity
vector<Problem> getProblems(string filename){
  vector<Problem> problems; //the problems in the file
  ifstream file; //holds the file object from fstream library
  file.open(filename);
  int counter = 0; //counts line being read
  Problem p; //temp struct for current problem
  string str; //temp string to hold current line content
  while(!file.eof()){
    getline(file, str);
    counter++;
    if(counter%3==1){ //weights
      p.weights={};
      vector<string> weightstrs = strsplit(str); //takes the strings from splitting the input line for weights
      for(unsigned int i = 0; i < weightstrs.size(); i++){
        p.weights.push_back(stoi(weightstrs[i]));
      }
    }
    else if(counter%3==2){ //values
      p.values={};
      vector<string> valuestrs = strsplit(str); //takes the strings from splitting the input line for values
      for(unsigned int i = 0; i < valuestrs.size(); i++){
        p.values.push_back(stoi(valuestrs[i]));
      }
    }
    else{ //capacity
      p.capacity = stoi(str);
      problems.push_back(p);
    }
  }
  return problems;
}

//Bottom-Up Solution to the knapsack problem
//Takes in a problem struct, outputs a solution struct for given problem
Solution knapsack(Problem problem){
  vector<int> weight = problem.weights; //vector to hold the weights for the problem
  vector<int> value = problem.values; //vector to hold the values for the problem
  int capacity = problem.capacity; //the problem capacity
  vector<vector<int>> knapsackvals; //the solution array to be populated
  //initialize knapsackvals
  for(unsigned int i = 0; i <= weight.size(); i++){
    vector<int> temp; //temporary 1D vector to be added as an element of the 2D vector knapsackvals
    for(int j = 0; j <= capacity; j++){
      if(i==0 || j==0) temp.push_back(0);
      else temp.push_back(-1);
    }
    knapsackvals.push_back(temp);
  }

  //bottomup implementation
  int maxi = weight.size(); //number of items total
  for(int i = 0; i <= maxi; i++){
    for(int c = 0; c <= capacity; c++){
      if(i==0||c==0) knapsackvals[i][c]=0;
      else{
        int weighti = weight[i-1]; //weight of last relative item
        int profiti = value[i-1]; //value of last relative item
        if(weighti > c) knapsackvals[i][c]=knapsackvals[i-1][c];
        else knapsackvals[i][c]=max(knapsackvals[i-1][c], knapsackvals[i-1][c-weighti]+profiti);
      }
    }
  }

  //iterate through populated knapsackvals for solution
  vector<int> items; //items in the solution
  vector<int> sweights; //weights of the solution items, corresponding by index
  vector<int> svalues; //values of the solution items, corresponding by index
  int totalweight = 0; //total weight of solution items
  int totalvalue = 0; //total value of solution items
  bool done = false; //boolean to check if search is complete
  int i = weight.size(); //initial number of items to traverse the table
  int c = capacity; //initial capacity to traverse the table
  while(!done){
      int weighti = weight[i-1]; //getting the weight for the last item
      int profiti = value[i-1]; //getting the value for the last item
      if(i==0||c==0) done = true;
      else if(weighti>c) i = i - 1;
      else if(knapsackvals[i-1][c]<knapsackvals[i-1][c-weighti]+profiti){
        items.push_back(i);
        i = i - 1;
        c = c - weighti;
        totalweight+=weighti;
        totalvalue+=profiti;
        sweights.push_back(weighti);
        svalues.push_back(profiti);
      }
      else i = i - 1;
  }
  //creating the solution object
  Solution solution;
  solution.items = items;
  solution.knapsackvals = knapsackvals;
  solution.totalweight = totalweight;
  solution.totalvalue = totalvalue;
  solution.weights = sweights;
  solution.values = svalues;
  solution.capacity = problem.capacity;
  return solution;
}

int main(int argc, char **argv){
  string inputstr = argv[1]; //input filename
  string outputstr = argv[2]; //output filename
  //generate the solutions
  vector<Problem> problems = getProblems(inputstr); //vector of all problems to solve
  vector<Solution> solutions; //vector of solutions to problems, to be populated
  int totalruntime = 0; //increments the runtime for all tests
  for(unsigned int i = 0; i < problems.size(); i++){
    //run the algorithm, and compute the time taken
    chrono::steady_clock::time_point start = chrono::steady_clock::now(); //clock object from chrono library
    Solution solution = knapsack(problems[i]); //get teh solutino for a specific problem
    chrono::steady_clock::time_point end = chrono::steady_clock::now(); //clock object from chrono library
    chrono::nanoseconds time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start); //difference between start and end times
    solution.nanotime = time_taken.count();
    totalruntime+=solution.nanotime;
    solutions.push_back(solution);
  }
  //write solutions to file
  ofstream file; //output stream object
  file.open(outputstr);

  //top of file
  file << "Number of Problems: " << to_string(problems.size()) << endl;
  string totalruntimestr = to_string(totalruntime); //string for the total runtime of the program's knapsack computations
  file << "Total Runtime: " << totalruntimestr << " nanoseconds" << endl;
  string avgruntimestr = to_string(totalruntime/problems.size()); //string for the average runtime of the program's knapsack computations
  file << "Average Runtime: " << avgruntimestr << " nanoseconds" << endl;

  //individual solutions to problems
  for(unsigned int i = 0; i < solutions.size(); i++){
    file << "---------------------------------------" << endl;
    Solution s = solutions[i]; //current solution
    int itemindex = s.items.size()-1; //used to print items in proper order
    file << "Solution to Problem " << i+1 << endl;
    file << "Items: ";
    for(unsigned int j = 0; j < s.items.size(); j++){
      file << s.items[itemindex-j] << " ";
    }
    file << endl;
    file << "Weights: ";
    for(unsigned int j = 0; j < s.items.size(); j++){
      file << s.weights[itemindex-j] << " ";
    }
    file << endl;
    file << "Values: ";
    for(unsigned int j = 0; j < s.items.size(); j++){
      file << s.values[itemindex-j] << " ";
    }
    file << endl;
    file << "Total Weight: " << s.totalweight << endl;
    file << "Total Value: " << s.totalvalue << endl;
    file << "Nanoseconds: " << s.nanotime << endl;
    file << endl;

    //print matrix for first 3 solutions
    unsigned int toti = s.knapsackvals.size(); //number of items i
    int totc = s.capacity; //capacity c
    if(i<3){
      for(unsigned int j = 0; j < toti; j++){
        for(int k = 0; k < totc; k++){
          int tempval = s.knapsackvals[j][k]; //value for specific i, c in matrix
          string aspace, val; //strings for a possible space (if number is only one digit) and value of the element in the matrix
          if(tempval < 0){
            aspace = " ";
            val = "/";
          }
          else if(tempval < 10){
            aspace = " ";
            val = to_string(tempval);
          }
          else{
            aspace = "";
            val = to_string(tempval);
          }

          file << aspace << val << " ";
        }
        file << endl;
      }
    }
  }
  file << endl;
  file.close();
  return 0;
}
