#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <stdio.h>

using namespace std;

#define MAX_MEMORY_SIZE 22

int deptRunNumber = 0;
int empRunNumber = 0;

vector<string> empTempFiles;
vector<string> deptTempFiles;


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
	deptTempFiles.push_back(tempFile);
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

			if(index % MAX_MEMORY_SIZE == 0){
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
	empTempFiles.push_back(tempFile);
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

			if(index % MAX_MEMORY_SIZE == 0){
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

	for(int i = 0; i < empRunNumber; i++){
		stringstream ss;
		ss << i;
		string tempFile = "Emp_runNumber_" + ss.str();
		remove(tempFile.c_str());
	}
}

void mergeAndJoin() {
	int index = 0;
	int empIndex = 0;
	int deptIndex = 0;
	vector<Dept> deptMergedVector;
	vector<Emp> empMergedVector;
	struct Emp empStruct;
	struct Dept deptStruct;
	string line;
	string delimiter = ",";
	ofstream outFile;
	outFile.open("join.csv", ios::out | ios::trunc);
	//outer loop
	while(empTempFiles.size() > 0 && deptTempFiles.size() > 0) {
		while(empTempFiles.size() != 0) {
			//open each file from both relations
			for(int i = 0; i < empTempFiles.size(); i++){
				int j = -1;
				// read the 'index' file line # from each and read into the vector
				ifstream infile(empTempFiles[i].c_str());
				if(infile.is_open()) {
					while(j != empIndex) {
						getline(infile, line);
						j++;
					}
					// read the elements from line into a struct
					if(!line.empty()) {

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
						line = "";
						empStruct.eid = atoi(holdTokens[0].c_str());
						empStruct.ename = holdTokens[1];
						empStruct.age = atoi(holdTokens[2].c_str());
						empStruct.salary = atof(holdTokens[3].c_str());
						empMergedVector.push_back(empStruct);

					} else {
						// delete this entry from empTempFiles
						empTempFiles.erase(empTempFiles.begin() + i);
					}
					infile.close();
				}
			}
			empIndex++;
		}
		sort(empMergedVector.begin(), empMergedVector.end(), sortByAttributeEmp);

		while(deptTempFiles.size() != 0) {
			//open each file from both relations
			for(int i = 0; i < deptTempFiles.size(); i++){
				int j = -1;
				// read the 'index' file line # from each and read into the vector
				ifstream infile(deptTempFiles[i].c_str());
				if(infile.is_open()) {
					while(j != deptIndex) {
						getline(infile, line);
						j++;
					}
					// read the elements from line into a struct
					if(!line.empty()) {

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
						line = "";
						deptStruct.did = atoi(holdTokens[0].c_str());
						deptStruct.dname = holdTokens[1];
						deptStruct.budget = atof(holdTokens[2].c_str());
						deptStruct.managerid = atoi(holdTokens[3].c_str());
						deptMergedVector.push_back(deptStruct);

					} else {
						// delete this entry from empTempFiles
						deptTempFiles.erase(deptTempFiles.begin() + i);
					}
					infile.close();
				}
			}
			deptIndex++;
		}
		sort(deptMergedVector.begin(), deptMergedVector.end(), sortByAttributeDept);

		if(empMergedVector.size() > 0 && deptMergedVector.size() > 0) {
			//join
			int i = 0;
			int j = 0;
			while(j < empMergedVector.size() && i < deptMergedVector.size()) {
				//equal case
				if(deptMergedVector[i].managerid == empMergedVector[j].eid) {
					outFile << deptMergedVector[i].did << "," << deptMergedVector[i].dname << "," << deptMergedVector[i].budget << "," << deptMergedVector[i].managerid << "," << empMergedVector[j].eid << "," << empMergedVector[j].ename << "," << empMergedVector[j].age << "," << empMergedVector[j].salary << endl;
					i++;
					j++;
				} else if (deptMergedVector[i].managerid > empMergedVector[j].eid) {
					j++;
				} else {
					i++;
				}
			}
		}

		// clear emp/deptMergedVector after done joining
		deptMergedVector.clear();
		empMergedVector.clear();
		index++;
	}
	outFile.close();
}

int main(){
	readRelationDept();
	readRelationEmp();
	mergeAndJoin();
	//cout << empRunNumber << endl << deptRunNumber << endl;
	deleteTempFiles();
	return 0;
}
