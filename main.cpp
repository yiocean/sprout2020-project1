#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include "help.h"
#include "ebook.h"

using namespace std;

int *find_position(const char text[], const char pattern[])
{
    static int index[MAX_LEN];
    int index_num = 0;
    int pat_num = 0;
    int lenth_text = strlen(text);
    int lenth_pat = strlen(pattern);
    
    int t_or_f = 0;
	//用來避免比如 text[i] == pattern[0]，但text[i+1] != pattern[1]之類的情況 
    //(若有上述情況的話則 t_or_f必!=lenth_pat => 就不會是我們所要找的) 
    
    for(int i=0 ; i<lenth_text ; i++){
    	if(text[i] == pattern[0]){
    		for(int k=i ; k<lenth_pat+i ;k++){
    			if(text[k] != pattern[pat_num]){
    				break;
				}
				else{
					t_or_f++;
					pat_num++;
				}
				
			}
			if(pat_num == lenth_pat){
				index[index_num] = i;
				index_num++;
			}
		}
		pat_num = 0;
	}
	index[index_num] = -1;

    return index;
}

static int save;
static int num = 0;
bool RunCmd(EBook &book, int &pid, const char cmd[])
{
	//goto
	char cmd_new[5];
    strncpy(cmd_new, cmd, 4);
    if(strcmp(cmd_new, "goto") == 0){
    	if(isdigit(cmd[6]) != 0 && cmd[6] != '-1'){
    		int num_10 = cmd[5] - '0';
   	 		int num_01 = cmd[6] - '0';
    		num = (num_10 * 10)+(num_01);
		}
		else{
			num = cmd[5] - '0';
		}
		
    	PrintPage(book, num);
    	pid = num;
		return true;
	}
	
	//search
	else if (strcmp(cmd, "Search") == 0){
        FindString(book, pid);
        return true;
    }
	
	//exit
	else if(strcmp(cmd, "exit") == 0){
		exit(0);
		return true;
	}
	
	//Qsave
	else if(strcmp(cmd, "Qsave") == 0){
		save=pid;
		return true;
	}
	
	//Qload
	else if(strcmp(cmd, "Qload") == 0){
		PrintPage(book, save);
		pid = save ;
		return true;
	}
	
    return false;
}

int main()
{
    EBook book;
    const char *bookname = "meme.txt";
    if (!LoadBook(bookname, book))
    {
        return -1;
    }
    //PrintPage(book, 2);
    std::cout << "load book " << bookname << "!" << std::endl;
    std::cout << "Press any key to read the book" << std::endl;
    Getch();

    int current = 0;
    PrintPage(book, current);
    while (true)
    {
        if (!GetCmd(book, current))
        {
            std::cerr << "Something went wrong..." << std::endl;
            break;
        }
    }

    return 0;
}
