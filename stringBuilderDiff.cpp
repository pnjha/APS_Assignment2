#include<bits/stdc++.h>
using namespace std;


class stringBuilder{

private:
		int length = 0;
		int capacity = 1;
		int defaultCapacity = 3;
		double resizeRatio = 2;
		char *stringPtr;

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
			
			int  len = 0,i = 0;
			
			while(data[i]!='\0'){
				i++;
			}

			len = i;

			if(this->defaultCapacity<len)
				this->capacity = this->defaultCapacity*2;

			this->stringPtr = (char*)malloc(capacity*sizeof(char));
			this->length = len;

			i = 0;
			
			while(data[i]!='\0'){
				this->stringPtr[i] = data[i];
				i++;
			}

		}

		void stringAppend(stringBuilder stringToAppend){
			
			int len = stringToAppend.getLength();
			
			if(this->capacity<len+this->length){
				
				this->capacity = (this->capacity+len)*this->resizeRatio;
				char *temp = (char*)malloc(capacity*sizeof(char));

				int i = 0;

				while(this->stringPtr[i]!='\0'){
					temp[i] = this->stringPtr[i];
					i++;
				}				

				i = 0;

				while(stringToAppend.stringPtr[i]!='\0'){
					temp[i+this->length] = stringToAppend.stringPtr[i];
					i++;
				}				

				this->length += len;
				this->stringPtr = temp;

			}else{

				int i = 0;

				while(stringToAppend.stringPtr[i]!='\0'){
					cout<<stringToAppend.stringPtr[i]<<"\n";
					this->stringPtr[i+this->length] = stringToAppend.stringPtr[i];
					i++;
				}						

				i = 0;
				this->length += len;
			}


		}

		int getLength(){
			return this->length;
		}

		int findSubstring(char* pattern){

			return subStringSearch(this->stringPtr,pattern);
		}

		void printString(){

			printf("%s\n",this->stringPtr);

		}

		char operator[](int index){
 			return this->stringPtr[index];
 		}

};



int main(){



	stringBuilder s1,s2,s3;

 	s1.stringInitialize("Hello");
 	s2.stringInitialize("Prakash");
 	s3.stringInitialize("Jha");
 	
 	s1.stringAppend(s2);
    s2.stringAppend(s3);
    s3.stringAppend(s1);

 	
 	int index = s2.findSubstring("a");
 	cout<<index+1<<"\n";

 	s1.printString();
 	s2.printString();
 	s3.printString();

 	cout<<s1[2]<<"\n";
 	cout<<s2[2]<<"\n";
 	cout<<s3[2]<<"\n";

	return 0;
}
