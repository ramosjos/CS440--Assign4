#include <iostream> 
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <stdio.h>

using namespace std;

int deptRunNumber = 0;
int empRunNumber = 0;

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

float sortByAttributeDept(const Dept &d1, const Dept &d2){
	return d1.managerid < d2.managerid;
} 

void writeToTempDept(vector<Dept> runVector, int runNumber){
	stringstream ss;
	ss << runNumber;
	string tempFile = "Dept_runNumber_" + ss.str();
	sort(runVector.begin(), runVector.end(), sortByAttributeDept);
	ofstream outfile;
	outfile.open(tempFile.c_str(), ios::out | ios::trunc);
	deptRunNumber++;
	for(int i = 0; i < runVector.size(); i++){
		outfile << runVector[i].did << "," << runVector[i].dname << "," << runVector[i].budget << "," << runVector[i].managerid << endl;
	}
}

void readRelationDept(){
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
				writeToTempDept(runVector, runNumber);
				index = 0;
				runVector.clear();
				runNumber++;
			}
		}
		if(runVector.size() > 0){
			writeToTempDept(runVector, runNumber);
		}
	
	}
}

float sortByAttributeEmp(const Emp &e1, const Emp &e2){
	return e1.eid < e2.eid;
} 

void writeToTempEmp(vector<Emp> runVector, int runNumber){
	stringstream ss;
	ss << runNumber;
	string tempFile = "Emp_runNumber_" + ss.str();
	sort(runVector.begin(), runVector.end(), sortByAttributeEmp);
	ofstream outfile;
	outfile.open(tempFile.c_str(), ios::out | ios::trunc);
	empRunNumber++;
	for(int i = 0; i < runVector.size(); i++){
		outfile << runVector[i].eid << "," << runVector[i].ename << "," << runVector[i].age << "," << runVector[i].salary << endl;
	}
}

void readRelationEmp(){
	int index = 0;
	int runNumber = 0;
	struct Emp empStruct;
	vector<Emp> runVector;
	string line;
	string delimiter = ",";
	ifstream infile ("Emp.csv");
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
			empStruct.eid = atoi(holdTokens[0].c_str());
			empStruct.ename = holdTokens[1];
			empStruct.age = atoi(holdTokens[2].c_str());
			empStruct.salary = atof(holdTokens[3].c_str());
			runVector.push_back(empStruct);

			if(index % 22 == 0){
				writeToTempEmp(runVector, runNumber);
				index = 0;
				runVector.clear();
				runNumber++;
			}
		}
		if(runVector.size() > 0){
			writeToTempEmp(runVector, runNumber);
		}
	
	}
}

void deleteTempFiles(){
	for(int i = 0; i < deptRunNumber; i++){
		stringstream ss;
		ss << i;
		string tempFile = "Dept_runNumber_" + ss.str();
		remove(tempFile.c_str());
	}
}


int main(){
	readRelationDept();	
	readRelationEmp();	
	cout << empRunNumber << endl << deptRunNumber << endl;
	return 0;
}
