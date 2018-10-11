#include<bits/stdc++.h>
using namespace std;

struct node{

	char *valuePtr;
	struct node *next = NULL; 
};

class StringBuilder{

	

	void preCompute(char pattern[], int lps[]){

	    int index = 0, i;
	    lps[0] = 0;
	    i = 1;

	    int length = 0;

		while(pattern[length]!='\0')
			length++;
	    
	    while(i<length){

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

	    int length = 0;

		while(pattern[length]!='\0')
			length++;

		int lps[length] = {0};

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

	struct node *listHead = (struct node *)malloc(sizeof(struct node));
	struct node *listTail = listHead;


	void stringInitialize(char *data){

		free(listHead);
		this->listHead = (struct node *)malloc(sizeof(struct node));
		this->listHead->valuePtr = data;
		this->listHead->next = NULL;
		this->listTail = this->listHead; 

	}

	void stringAppend(StringBuilder obj){

		this->listTail->next = obj.listHead;
		this->listTail = obj.listTail;
		this->listTail->next = NULL;
	}

	int findSubstring(char* pattern){


		int length = 0;

		int i = 0;

		struct node *temp = this->listHead;

		while(temp!=NULL){
			
			while(temp->valuePtr[i]!='\0'){
				i++;
			}	

			
			length += i;	
			i = 0;
		
			temp = temp->next;
		}


		char mainString[length] = {'\0'};
		length = 0;
		temp = this->listHead;
		i = 0;

		while(temp!=NULL){

			while(temp->valuePtr[i]!='\0'){
				mainString[i+length] = temp->valuePtr[i];
				i++;
			}	
			
			temp = temp->next;
			length += i;	
			i = 0;
		}

		mainString[length] = '\0';

		return subStringSearch(mainString,pattern);
	}


	void printString(){

		int length = 0;

		int i = 0;

		struct node *temp = this->listHead;
		
		while(temp!=NULL){

			while(temp->valuePtr[i]!='\0'){
				i++;
			}	

			temp = temp->next;
			length += i;	
			i = 0;
		}

		char mainString[length-1] = {'\0'};
		
		length = 0;
		temp = this->listHead;
		i = 0;

		while(temp!=NULL){

			while(temp->valuePtr[i]!='\0'){
				mainString[i+length] = temp->valuePtr[i];
				i++;
			}	
			temp = temp->next;
			length += i;	
			i = 0;
		}
		mainString[length] = '\0';
		printf("%s\n",mainString );
	}

};

int main(){

	StringBuilder s1,s2,s3,s4;

 	s1.stringInitialize("Hello");
 	s2.stringInitialize("Prakash");
 	s3.stringInitialize("Jha");
 	s4.stringInitialize("ok");
 	
 	s1.stringAppend(s2);
 	s3.stringAppend(s4);
    // s1.stringAppend(s3);
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
	s4.printString();
	return 0;
}