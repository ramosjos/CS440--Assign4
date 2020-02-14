#include <iostream> 
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>

int runNumber = 0;

using namespace std;

struct Dept {
	int did;
	string dname;
	double budget;
	int managerid;
};

struct Emp {
	int eid;
	string ename;
	int age;
	double salary;
};

void readRelation(){
	int index = 0;
	struct Dept deptStruct;
	vector<Dept> runVector;
	string line;	
	string delimiter = ",";
	ifstream infile ("Dept.csv");
	if(infile.is_open()){
		while(getline(infile, line)){
			index++;
			vector<string> holdTokens;
			size_t pos = 0;
			string token;
			while ((pos = line.find(delimiter)) != std::string::npos) {
				token = line.substr(0, pos);
				holdTokens.push_back(token);
				line.erase(0, pos + delimiter.length());
			}
			token = line.substr(0, pos);
			holdTokens.push_back(token);
			deptStruct.did = atoi(holdTokens[0].c_str());
			deptStruct.dname = holdTokens[1];
			deptStruct.budget = atof(holdTokens[2].c_str());
			deptStruct.managerid = atoi(holdTokens[3].c_str());
			runVector.push_back(deptStruct);
			if(index % 22 == 0){
				// call writeToFile();
				index = 0;
				runVector.clear();
				runNumber++;
			}
		}
	}
}
/*
   stringstream ss;
   ss << runNumber;
   string tempFile = fileName + "_runNumber_" + ss.str();
   ofstream
   */
int main(){
	readRelation();
	return 0;
}
