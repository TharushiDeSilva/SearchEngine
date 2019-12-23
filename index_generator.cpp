//This is a simple prgtram to 
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <map> 
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

using namespace std; 

static std::map<string, string> index_map; 
static std::map<string, int> keyword_map;  

const std::string index_file_name  ="ind_file.txt"; 
const std::string search_path = "search_space/url"; 
const int dimesion = 1;                                 // number of URL files to read 

std::string ignore_words[11] = {"the", "and", "that", "which", "are", "was", "were", "will", "then", "when", "what"}; 
char ignore_chars[18] = {'&', '.', '>', '<', '?', '#', '@', '~', '!', '$', '%', '*', '(', ')', '[', ']', ',', ' '}; 


void generate_inverse_index(){
    
    for(int i=0; i<=dimesion; i++){                                                          // Read each URL in the search space 
        std::string file_name = search_path + boost::lexical_cast<string>(i) + ".txt";      //create the file name
        //std::cout<<file_name<<endl; 
        
        ifstream ifile;
        ifile.open (file_name.c_str(), ios::app);                                           //Open the UR
        
        if(ifile.is_open()) {
            std::string line; 
            std::string url ="";                                                            // URL of the webpage can be read from the first line 
            bool firstline = true; 
            while (std::getline(ifile, line)) {

                if(firstline){
                    url = line;                                                             // assign the firsline value to url 
                    firstline = false;  
                }
                else{
                    // content of the webpage 
                    boost::to_lower(line);                      // convert the whole line into lowercase 
                    line.erase(0, line.find_first_not_of("& \'\"\t.><?#@~!$%*()[],"));
                    line.erase(line.find_last_not_of("& \'\"\t.><?#@~!$%*()[],"));
                    
                    // Seperate word by word 
                    std::string word = ""; 
                    for (int i=0; i < line.length( ); i++){
                        for(int j=0; j<sizeof(ignore_chars); j++){
                            if(line[i] == ignore_chars[j]){
                                word.erase(0, word.find_first_not_of("& \'\"\t.><?#@~!$%*()[],"));
                                if(word.length() >2){                                                   // can remove simple stop words, and empty lines
                                    std::cout<<word<<endl;
                                }
                                
                                word = ""; 
                                break; 
                            }
                        }
                        word += line[i];  
                    } 
                    word.erase(0, word.find_first_not_of("& \'\"\t.><?#@~!$%*()[],"));
                    if(word.length() >2){                                                           // can remove simple stop words, and empty lines
                        std::cout<<word<<endl;
                    }
                }
            }
	    }

        ifile.close(); 
    }
}

int main(){
    generate_inverse_index(); 
    return 0; 
}
