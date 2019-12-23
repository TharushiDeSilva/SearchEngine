//This is a simple prgtram to 
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <map> 

using namespace std; 

static std::map<string, string> index_map; 
static std::map<string, int> keyword_map;  

const std::string index_file_name  ="ind_file.txt"; 
const std::string search_path = "search_space/url"; 
const int dimesion = 2;                                 // number of URL files to read 

void write_index_to_file(string keyword, string matching_query){
    //writing the output in a file for test
	
	ofstream offile;
	offile.open("test.txt", ios::app);
	if(offile.is_open()) {
		offile<<"("<<keyword<<",\t{"<<matching_query<<"})"<<std::endl; 
	}
	offile.close();
	
}

void read_file(){
    ifstream ifile;
    ifile.open ("test.txt");
    int count; string message;
    while(ifile >>count>>message){
        std::cout<<count<<"\t"<<message<<std::endl; 
    }
    ifile.close();
}

int main(){
    
    write_index_to_file("computer", "www.url1.com/index.html"); 
    //read_file(); 
    return 0; 
}
