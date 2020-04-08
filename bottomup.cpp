#include <iostream>
#include <fstream> //read / write to files
#include <algorithm> //max function
#include <chrono> //time
#include <vector>
#include <thread>
#include <string>


using namespace std;

static itemthreshold = 5;
static capacitythreshold = 5;

struct Problem{
  vector<int> weights;
  vector<int> values;
  int capacity;
};
struct Solution{
  vector<int> items;
  vector<vector<int>> knapsackvals;
  int totalweight;
  int totalvalue;
  int nanotime;
}

//split a string by a space
vector<string> strsplit(string str){
  istringstream iss(str);
  return vector<string> results((istream_iterator<string>(iss)), istream_iterator<string>());
}

//returns the string for the first line of a text file
//filename must be a .txt or similar format, and must have extension
vector<Problem> getProblems(string filename){
  vector<Problem> problems;
  ifstream file; //holds the file object from fstream library
  file.open(filename);
  int counter = 0; //counts line being read
  Problem p; //temp struct for current problem
  string str; //temp string to hold current line content
  while(!file.eof()){
    getline(file, str);
    counter++;
    if(counter%3==1){ //weights
      p.weights={}
      vector<string> weightstrs = strsplit(str);
      for(int i = 0; i < weightstrs.length(); i++){
        p.weights.push_back(stoi(str));
      }
    }
    else if(counter%3==2){ //values
      p.values={}
      vector<string> valuestrs = strsplit(str);
      for(int i = 0; i < valuestrs.length(); i++){
        p.values.push_back(stoi(str));
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
//outputs the length of the knapsack of the two strings as an integer
//Takes in the two input strings, can be any length including 0
Solution knapsack(Problem problem){
  vector<int> weight = problem.weights;
  vector<int> value = problem.values;
  int capacity = problem.capacity;
  vector<vector<int>> knapsackvals;
  //initialize knapsackvals
  for(unsigned int i = 0; i <= weight.length(); i++){
    vector<int> temp; //temporary 1D vector to be added as an element of the 2D vector knapsackvals
    for(unsigned int j = 0; j <= capacity; j++){
      temp.push_back(-1);
    }
    knapsackvals.push_back(temp);
  }
  int maxi = weight.length(); //number of items
  for(int i = 0; i <= maxi; i++){
    for(int c = 0; c <= capacity; c++){
      if(i==0||c==0) knapsackvals[i][c]=0;
      else{
        int weighti = weight[i-1];
        int profiti = value[i-1];
        if(weighti > c) knapsackvals[i][c]=knapsackvals[i-1][c];
        else knapsackvals[i][c]=max(knapsackvals[i-1][c], knapsackvals[i-1][c-weighti]+profiti);
      }
    }
  }
  //iterate through populated knapsackvals for solution
  vector<int> items;
  int totalweight = 0;
  int totalvalue = 0;
  bool done = false;
  int i = weight.length();
  int c = capacity;
  while(!done)
      int weighti = weight[i-1]
      int profiti = value[i-1]
      if(i==0||c==0) done = true
      else if(weighti>c) i = i - 1;
      else if(knapsackvals[i-1][c]<knapsackvals[i-1][c-weighti]+profiti){
        items.push_back(i);
        i = i - 1;
        c = c - weighti;
        totalweight+=weighti;
        totalvalue+=profiti;
      else i = i - 1;
  }
  Solution solution;
  solution.items = items;
  if(value.length()<=itemthreshold&&capacity<=capacitythreshold){
    solution.knapsackvals = knapsackvals;
  }
  solution.totalweight = totalweight;
  solution.totalvalue = totalvalue;
  return solution;
}

int main(int argc, char **argv){
  //generate the solutions
  vector<Problem> problems = getProblems("items.txt");
  vector<Solution> solutions;
  int totalruntime;
  for(int i = 0; i < problems.length(); i++){
    //run the algorithm, and compute the time taken
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now(); //clock object from chrono library
    Solution solution = knapsack(problems[i]);
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now(); //clock object from chrono library
    auto time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start); //difference between start and end times
    solution.nanotime = time_taken.count();
    totalruntime+=solution.nanotime;
    solutions.push_back(solution);
  }
  //write solutions to file
  ofstream file;
  file.open("solutions_bottomup");
  file << "Number of Problems: " << to_string();
  string totalruntimestr = to_string(totalruntime);
  file << "Total Runtime: " << totalruntimestr << endl;
  string avgruntimestr = to_string(totalruntime)

  for(int i = 0; i < solutions.length(); i++){

  }




  //write to output2.txt
  ofstream file; //output file object
  file.open(output);
  //Output case for strings <= size 10
  if(strx.length()<=10 and stry.length()<=10){
    for(unsigned int i = 0; i <= strx.length(); i++){
      string s; //temp string for a line of the table to display
      for(unsigned int j = 0; j <= stry.length(); j++){
        s.append(to_string(knapsackvals[i][j])+" ");
      }
      file << s << endl;
    }
    file << knapsack(strx, stry) << endl;
  }
  //knapsack length
  else file << substrlen << endl;
  //Running time
  if(time_taken.count()==0) file << "Less than 100 nanoseconds" << endl;
  else file << time_taken.count() << " nanoseconds"<< endl;
  file.close();
  return 0;
}
