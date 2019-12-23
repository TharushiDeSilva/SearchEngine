//This is a simple prgtram to 
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <map> 
#include <boost/lexical_cast.hpp>

using namespace std; 

static std::map<string, string> index_map; 
static std::map<string, int> keyword_map;  

const std::string index_file_name  ="ind_file.txt"; 
const std::string search_path = "search_space/url"; 
const int dimesion = 2;                                 // number of URL files to read 

std::string ignore_words[11] = {"the", "and", "that", "which", "are", "was", "were", "will", "then", "when", "what"}; 
char ignore_chars[17] = {'&', '.', '>', '<', '?', '#', '@', '~', '!', '$', '%', '*', '(', ')', '[', ']', ','}; 

/*
void write_index_to_file(string keyword, string matching_query){
    //writing the output in a file for test
	
	ofstream offile;
	offile.open("test.txt", ios::app);
	if(offile.is_open()) {
		offile<<"("<<keyword<<",\t{"<<matching_query<<"})"<<std::endl; 
	}
	offile.close();
	
}
*/

/*
void read_file(){
    ifstream ifile;
    ifile.open ("test.txt");
    int count; string message;
    while(ifile >>count>>message){
        std::cout<<count<<"\t"<<message<<std::endl; 
    }
    ifile.close();
}
*/

void generate_inverse_index(){
    
    for(int i=0; i<=dimesion; i++){                                                          // Read each URL in the search space 
        std::string file_name = search_path + boost::lexical_cast<string>(i) + ".txt";      //create the file name
        std::cout<<file_name<<endl; 
        
        ifstream ifile;
        ifile.open (file_name.c_str(), ios::app);

        ifile.close(); 
    }
}

int main(){
    generate_inverse_index(); 
    return 0; 
}
