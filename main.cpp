#include <iostream> 
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>

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

float sortByAttribute(const Dept &d1, const Dept &d2){
	return d1.managerid < d2.managerid;
} 

void writeToTemp(vector<Dept> runVector, int runNumber){
	stringstream ss;
	ss << runNumber;
	string tempFile = "Dept_runNumber_" + ss.str();
	sort(runVector.begin(), runVector.end(), sortByAttribute);
	ofstream outfile;
	outfile.open(tempFile.c_str(), ios::out | ios::trunc);
	for(int i = 0; i < runVector.size(); i++){
		outfile << runVector[i].did << "," << runVector[i].dname << "," << runVector[i].budget << "," << runVector[i].managerid << endl;
	}
}

void readRelation(){
	int index = 0;
	int runNumber = 0;
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
				writeToTemp(runVector, runNumber);
				index = 0;
				runVector.clear();
				runNumber++;
			}
		}
		if(runVector.size() > 0){
			writeToTemp(runVector, runNumber);
		}
	}
}

int main(){
	readRelation();
	return 0;
}
