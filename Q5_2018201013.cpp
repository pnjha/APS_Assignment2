#include<bits/stdc++.h>
using namespace std;

class StringBuilder{

	char *valuePtr;
	vector<StringBuilder> list;

	void preCompute(char pattern[], int lps[]){

	    int index = 0, i;
	    lps[0] = 0;
	    i = 1;
	    
	    while(i<strlen(pattern)){

		   if(pattern[i] == pattern[index]){
			   index++;
			   lps[i] = index;
			   i++;
		   }
		   else{

			   if(index != 0)
			     index = lps[index-1];
			   else{

			     lps[i] = 0;
			     i++;
			   }
		   }
	    }
	}

	int subStringSearch(char mainString[], char pattern[]){

		int j=0,i=0;
		int lps[strlen(pattern)] = {0};

		preCompute(pattern,lps);

		int lengthMainString = 0, lengthPattern = 0;
		while(mainString[i]!='\0'){
			i++;
		}			

		lengthMainString = i;
		i = 0;

		while(pattern[i]!='\0'){
			i++;
		}			

		lengthPattern = i;
		i = 0;

		while(i < lengthMainString){

		    if(pattern[j] == mainString[i]){
			    j++;
			    i++;
		    }
			    if(j == lengthPattern){
			    return i-j;
		    }
		    else if(pattern[j] != mainString[i]){

			    if(j != 0)
			   		j = lps[j-1];
			    else
			   		i = i+1;
		    }
		}

		return -1;
	}

public: 

	void stringInitialize(char *data){

		valuePtr = data;
	}

	void stringAppend(StringBuilder obj){

		list.push_back(obj);

	}

	int findSubstring(char* pattern){

		int length = 0;

		int i = 0;
		while(valuePtr[i]!='\0'){
			i++;
		}

		length += i;

		for(i=0;i<list.size();i++){
			int j = 0;
			while(list[i].valuePtr[j]!='\0'){
				j++;
			}

			length += j;
		}


		char mainString[length-1] = {'\0'};

		i = 0;
		while(valuePtr[i]!='\0'){
			mainString[i] = this->valuePtr[i];
			i++;
		}		

		length = i;


		for(i=0;i<list.size();i++){
			int j = 0;
			while(list[i].valuePtr[j]!='\0'){
				
				mainString[length+j] = list[i].valuePtr[j];
				j++;
				
			}

			length += j;
		}		
		mainString[length] = '\0';

		printf("%s\n", mainString);

		return subStringSearch(mainString,pattern);
	}


	void printString(){

		int i = 0,length = 0;


		printf("%s",this->valuePtr);
		

		for(i=0;i<list.size();i++){
		
			printf("%s",list[i].valuePtr);
		}		
		cout<<"\n";
	}

};

int main(){

	StringBuilder s1,s2,s3;

 	s1.stringInitialize("Hello");
 	s2.stringInitialize("Prakash");
 	s3.stringInitialize("Jha");
 	
 	s1.stringAppend(s2);
    // s2.stringAppend(s3);
    // s3.stringAppend(s1);

 	
 	int index = s1.findSubstring("ash");
 	
 	if(index == -1)
 		cout<<"String not found\n";
 	else
 		cout<<"String found at index: "<<index<<"\n";

 	s1.printString();
 	s2.printString();
 	s3.printString();
	
	return 0;
}