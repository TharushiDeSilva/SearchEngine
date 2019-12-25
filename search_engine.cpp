//This is a simple prgtram to 
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <map> 
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <ctime>

using namespace std; 

static std::map<string, string> inverse_index; 

const std::string index_file_name  ="inv_index.txt"; 
const std::string answers_file_name  ="answer.txt";
const std::string queries_file_name  ="queries.txt"; 
const int query_file_length = 1000; 
std::string ignore_words[11] = {"the", "and", "that", "which", "are", "was", "were", "will", "then", "when", "what"}; 
char ignore_chars[21] = {'&', '.', '>', '<', '?', '#', '@', '~', '!', '$', '%', '*', '(', ')', '[', ']', ',', '{', '}', ':', ';'}; 

void load_inverse_index_to_memory(std::string file){
    std::ifstream ifile; 
    ifile.open(file.c_str(), ios::app); 
    if(ifile.is_open()) {
        std::string line;                                                              
        while (std::getline(ifile, line)) {
            line.erase(line.find_last_not_of(" \n\r\t")+1); //trim the edges 
            string keyword = ""; string url_set = ""; int url_start_point = 0; 
            for(int i=0; i<line.size(); i++){
                if(line[i] =='\t'){
                    url_start_point = i+1; 
                    break; 
                }
            }
            keyword = line.substr(0, url_start_point-1); 
            url_set = line.substr(url_start_point); 
            inverse_index.insert(std::pair<string, string>(keyword, url_set));
        }
    }
    ifile.close();
}

void write_output_to_file(std::string filename, std::string content){
    std::ofstream ofile; 
    ofile.open(filename.c_str(), ios::app); 

    if(ofile.is_open()) {
        ofile<<content<<endl;
    }
    ofile.close(); 
}

void read_queries_file(std::string filename){
    std::ifstream ifile; 
    ifile.open(filename.c_str(), ios::app); 

    if(ifile.is_open()) {
        std::string line;                       // each new line is a search query                                                            
        bool firstline = true; 
        while (std::getline(ifile, line)) {
              
            boost::to_lower(line); 
    
            std::string search_query[5] = {"", "", "", "", ""};                     // search words 

            line.erase(line.find_last_not_of(" \n\r\t")+1);
            line.erase(0, line.find_first_not_of("-& \'\"\t.><?#@~!$%*()[],"));
            write_output_to_file(answers_file_name, line); 
            //std::cout<<line<<std::endl; //------------------------------------------------------------------
            std::string word = "";  
            int word_count = 0; 
            for(int i=0; i<line.size(); i++){
                if(line[i] == ' '){
                    word.erase(0, word.find_first_not_of("-& \'\"\t.><?#@~!$%*()[],"));
                    search_query[word_count] = word;
                    word = "";
                    word_count +=1;  
                }else{
                    bool accept = true; 
                    for(int j=0; j<21; j++){
                        if(ignore_chars[j] == line[i]){
                            accept = false; 
                            break; 
                        }
                    }
                    if(accept){
                        word += line[i]; 
                    }
                }
            }
            word.erase(0, word.find_first_not_of("-& \'\"\t.><?#@~!$%*()[],"));
            search_query[word_count] = word;

            
            for(int k=0; k<5; k++){
                std::map<std::string, std::string>::iterator itr; 
                itr = inverse_index.find(search_query[k]); 
                if(itr !=inverse_index.end()){
                    write_output_to_file(answers_file_name, itr->second); 
                }
            }
            write_output_to_file(answers_file_name, "\n");                
        }
    }

    ifile.close();
}

int main(){
    
    load_inverse_index_to_memory(index_file_name); 
    clock_t begin = clock();
    read_queries_file(queries_file_name);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC; 
    write_output_to_file(answers_file_name, "total_search_latency in seconds: \t"); 
    write_output_to_file(answers_file_name, boost::lexical_cast<string>(elapsed_secs)); 
    double average_time = elapsed_secs/query_file_length; 
    write_output_to_file(answers_file_name, "average_search_latency in seconds: \t"); 
    write_output_to_file(answers_file_name, boost::lexical_cast<string>(average_time)); 
    
    return 0; 
}





