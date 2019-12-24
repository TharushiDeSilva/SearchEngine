//This is a simple prgtram to 
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <map> 
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

using namespace std; 

static std::map<string, string> inverse_index; 

const std::string index_file_name  ="inv_index.txt"; 
const std::string answers_file_name  ="answer.txt";
const std::string queries_file_name  ="queries.txt"; 

std::string ignore_words[11] = {"the", "and", "that", "which", "are", "was", "were", "will", "then", "when", "what"}; 
char ignore_chars[21] = {'&', '.', '>', '<', '?', '#', '@', '~', '!', '$', '%', '*', '(', ')', '[', ']', ',', '{', '}', ':', ';'}; 


/*
void add_word_to_local_index(std::string word){
    std::map<std::string, int>::iterator itr; 
    itr = keyword_map.find(word); 
    if(itr != keyword_map.end()){
                                                            // if the word is found previously in the map 
        int count = itr->second; 
        count +=1;                         // increse the number of occurances 
        itr->second = count; 
    }else{
        keyword_map.insert(std::pair<string, int>(word, 1));    // first time the word is found in the file 
    }

}*/
/*
void clear_local_index(){
    keyword_map.clear(); 
}
*/
/*
void update_global_index(std::string url){                      // adding the global keyword indices into index map 
    std::map<std::string, int>::iterator itr_local;
    for(itr_local = keyword_map.begin(); itr_local != keyword_map.end(); itr_local++){
        std::string pre_keyword = itr_local->first; 
        bool valid = true; 
        for(int k=0; k < 11; k++){
            if(pre_keyword == ignore_words[k]){
                //std::cout<<"break word detected: "<<pre_keyword<<std::endl;
                valid = false;  
                break;                                       //stop word detected
            }
        }
        
        std::map<std::string, string>::iterator itr; 

        if(valid){
            itr = index_map.find(pre_keyword); 
        
            if(itr != index_map.end()){                     //if the keyword exists
                std::string url_list = itr->second; 
                url_list += ", " + url; 
                itr->second = url_list; 
            }else{
                index_map.insert(std::pair<string, string>(pre_keyword, url));
            }
        }
        
                      
    }
}
*/


void load_inverse_index_to_memory(std::string file){
    std::ifstream ifile; 
    ifile.open(file.c_str(), ios::app); 

    string keyword, url_set; 
    while(ifile >>keyword>>url_set){
        inverse_index.insert(std::pair<string, string>(keyword, url_set));
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
                if(search_query[k]==""){
                    break; 
                }else{
                    std::map<std::string, string>::iterator itr;
                    itr = inverse_index.find(search_query[k]);  
                     
                    if(itr != inverse_index.end()){
                        // if the search keyword is found 
                    }
                } 
            }
            write_output_to_file(answers_file_name, "\n"); 
        }
    }

    ifile.close();
}

int main(){
    
    load_inverse_index_to_memory(index_file_name); 
    read_queries_file(queries_file_name); 
    return 0; 
}





