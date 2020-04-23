#include <iostream>
#include <fstream> //read / write to files
#include <algorithm> //max function
#include <chrono> //time
#include <vector>
#include <thread>
#include <string>


using namespace std;

static unsigned int itemthreshold = 5;
static int capacitythreshold = 30;

struct Problem{
  vector<int> weights;
  vector<int> values;
  int capacity;
};
struct Solution{
  vector<int> items;
  vector<int> weights;
  vector<int> values;
  vector<vector<int>> knapsackvals;
  int totalweight;
  int totalvalue;
  int capacity;
  int nanotime;
};

//split a string by a space
vector<string> strsplit(string str){
  vector<string> strs;
  string tempstr = "";
  for(unsigned int i = 0; i < str.length(); i++){
    char currentchar = str.at(i);
    if(currentchar!=' ') tempstr.append(string(1, currentchar));
    else{
      strs.push_back(tempstr);
      tempstr = "";
    }
  }
  if(tempstr!="" && tempstr!=" ") strs.push_back(tempstr);
  return strs;
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
      p.weights={};
      vector<string> weightstrs = strsplit(str);
      for(unsigned int i = 0; i < weightstrs.size(); i++){
        p.weights.push_back(stoi(weightstrs[i]));
      }
    }
    else if(counter%3==2){ //values
      p.values={};
      vector<string> valuestrs = strsplit(str);
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

//populates the array and then returns the necessary value
int getKnapsackVal(vector<vector<int>> & knapsack, int i, int c, Problem problem){
  int wi = problem.weights[i-1];
  int pi = problem.values[i-1];
  if(knapsack[i][c]>=0) return knapsack[i][c];
  else if(wi > c){
    knapsack[i][c] = getKnapsackVal(knapsack, i-1, c, problem);
    return knapsack[i][c];
  }
  else{
    int k1 = getKnapsackVal(knapsack, i-1, c, problem);
    int k2 = getKnapsackVal(knapsack, i-1, c-wi, problem);
    knapsack[i][c] = max(k1, k2+pi);
    return knapsack[i][c];
  }
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
  for(unsigned int i = 0; i <= weight.size(); i++){
    vector<int> temp; //temporary 1D vector to be added as an element of the 2D vector knapsackvals
    for(int j = 0; j <= capacity; j++){
      if(i==0 || j==0) temp.push_back(0);
      else temp.push_back(-1);
    }
    knapsackvals.push_back(temp);
  }


  //populate the array
  getKnapsackVal(knapsackvals, weight.size(), capacity, problem);


  //iterate through populated knapsackvals for solution
  vector<int> items;
  vector<int> sweights;
  vector<int> svalues;
  int totalweight = 0;
  int totalvalue = 0;
  bool done = false;
  int i = weight.size();
  int c = capacity;
  while(!done){
      int weighti = weight[i-1];
      int profiti = value[i-1];
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

  Solution solution;
  solution.items = items;
  if(value.size()<=itemthreshold&&capacity<=capacitythreshold){
    solution.knapsackvals = knapsackvals;
  }
  solution.totalweight = totalweight;
  solution.totalvalue = totalvalue;
  solution.weights = sweights;
  solution.values = svalues;
  solution.capacity = problem.capacity;
  return solution;
}

int main(int argc, char **argv){
  string inputstr = argv[1];
  string outputstr = argv[2];
  //generate the solutions
  vector<Problem> problems = getProblems(inputstr);
  vector<Solution> solutions;
  int totalruntime = 0;
  for(unsigned int i = 0; i < problems.size(); i++){
    //run the algorithm, and compute the time taken
    chrono::steady_clock::time_point start = chrono::steady_clock::now(); //clock object from chrono library
    Solution solution = knapsack(problems[i]);
    chrono::steady_clock::time_point end = chrono::steady_clock::now(); //clock object from chrono library
    chrono::nanoseconds time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start); //difference between start and end times
    solution.nanotime = time_taken.count();
    totalruntime+=solution.nanotime;
    solutions.push_back(solution);
  }
  //write solutions to file
  ofstream file;
  file.open(outputstr);

  //top of file
  file << "Number of Problems: " << to_string(problems.size()) << endl;
  string totalruntimestr = to_string(totalruntime);
  file << "Total Runtime: " << totalruntimestr << " nanoseconds" << endl;
  string avgruntimestr = to_string(totalruntime/problems.size());
  file << "Average Runtime: " << avgruntimestr << " nanoseconds" << endl;

  //individual solutions to problems
  for(unsigned int i = 0; i < solutions.size(); i++){
    file << "---------------------------------------" << endl;
    Solution s = solutions[i];
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

    //if item & capacity values below threshold, print matrix
    unsigned int toti = s.knapsackvals.size();
    int totc = s.capacity;
    if(toti <= itemthreshold && totc <= capacitythreshold){
      for(unsigned int j = 0; j < toti; j++){
        for(int k = 0; k < totc; k++){
          int tempval = s.knapsackvals[j][k];
          string aspace, val;
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
