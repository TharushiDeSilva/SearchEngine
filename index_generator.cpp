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

const std::string index_file_name  ="index_file.txt"; 
const std::string search_path = "search_space/url"; 
const int dimesion = 60;                                 // number of URL files to read 

std::string ignore_words[11] = {"the", "and", "that", "which", "are", "was", "were", "will", "then", "when", "what"}; 
char ignore_chars[22] = {'&', '.', '>', '<', '?', '#', '@', '~', '!', '$', '%', '*', '(', ')', '[', ']', ',', ' ', '{', '}', ':', ';'}; 


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

}

void clear_local_index(){
    keyword_map.clear(); 
}

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

void generate_inverse_index(){
    
    for(int i=0; i<=dimesion; i++){                                                          // Read each URL in the search space 

        clear_local_index(); 

        std::string file_name = search_path + boost::lexical_cast<string>(i) + ".txt";      //create the file name
        //std::cout<<file_name<<endl; 
        
        ifstream ifile;
        ifile.open (file_name.c_str(), ios::app);                                           //Open the UR
        std::string url ="";                                                                // URL of the webpage can be read from the first line
        
        if(ifile.is_open()) {
            std::string line;                                                             
            bool firstline = true; 
            while (std::getline(ifile, line)) {

                if(firstline){
                    url = line;                                                             // assign the firsline value to url 
                    url.erase(url.find_last_not_of(" \n\r\t")+1);
                    firstline = false;  
                }
                else{
                    // content of the webpage 
                    boost::to_lower(line);                      // convert the whole line into lowercase 
                    line.erase(0, line.find_first_not_of("-& \'\"\t.><?#@~!$%*()[],"));
                    line.erase(line.find_last_not_of("-& \'\"\t.><?#@~!$%*()[],"));
                    
                    // Seperate word by word 
                    std::string word = ""; 
                    for (int i=0; i < line.length( ); i++){
                        for(int j=0; j<sizeof(ignore_chars); j++){
                            if(line[i] == ignore_chars[j]){
                                word.erase(0, word.find_first_not_of("-& \'\"\t.><?#@~!$%*()[],"));
                                if(word.length() >2){                                                   // can remove simple stop words, and empty lines
                                    add_word_to_local_index(word); 
                                }
                                
                                word = ""; 
                                break; 
                            }
                        }
                        word += line[i];  
                    } 
                    word.erase(0, word.find_first_not_of("-& \'\"\t.><?#@~!$%*()[],"));
                    if(word.length() >2){                                                           // can remove simple stop words, and empty lines
                        add_word_to_local_index(word); 
                    }
                }
            }
	    }

        ifile.close(); 

        //Update the reverse_index map
        update_global_index(url); 

    }
}

void write_reverse_index_to_file(std::string filename){                 //write the index_map into a text file for reference 
      std::ofstream ofile;
        ofile.open (filename.c_str(), ios::app);  
        if(ofile.is_open()) {
            std::map<std::string, string>::iterator itr;
            for(itr = index_map.begin(); itr != index_map.end(); itr++){
                ofile<<itr->first<<"\t{"<<itr->second<<"}"<<endl; 
            }
        }
        ofile.close(); 
}

int main(){
    generate_inverse_index(); 
    write_reverse_index_to_file(index_file_name); 


    // search engine part 
    //index_map.find("computer")
    
    return 0; 
}





