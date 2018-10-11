#include<bits/stdc++.h>
#define ull  long long int

using namespace std;

template<class TKEY, class TVAL>
struct hashPair{
	TKEY key;
	TVAL value;
	struct hashPair *chainNext = NULL;
};



template<class TKEY, class TVAL>
class unorderedMap{

public: 
	
	struct hashPair<TKEY,TVAL> *hashTable = (struct hashPair<TKEY,TVAL>*)malloc(sizeof(struct hashPair<TKEY,TVAL>));
	ull randomPrime, randomNum1 , randomNum2;
	ull hashTableSize = 0;

	unorderedMap(int size){

		hashTable = (struct hashPair<TKEY,TVAL>*)malloc(size*sizeof(struct hashPair<TKEY,TVAL>));
		this->hashTableSize = size;
		this->initialiseRandomVariable();
	}



	bool isPrime(ull value){

	    for (int i = 2; i <= value/2; i++){

	        if (value%i == 0)  
	            return false;
	    }

	    return true;
	}


	ull findNextPrime(ull value){

	    ull nextPrime = value;
	    bool found = false;
	    while (!found){

	        nextPrime++;
	        if (isPrime(nextPrime)){
	            found = true;
	            break;
	        }
	    }
	    return nextPrime;
	}



	void initialiseRandomVariable(){

		ull randomValue = (rand()%(1000000000 - 100000001)) + 100000000; 

		this->randomPrime = findNextPrime(randomValue);
		this->randomNum1 = rand()%randomPrime;
		this->randomNum2 = rand()%randomPrime;

	}


	ull preHash(string str){
		
	    unsigned long hash = 1000000007;
	    int c,i=0;

	    while (i<str.length()){
	    	c = str[i];
	    	i++;
	        hash = ((hash<<5) + hash) + c;
	    }

	    return hash%786;
	}

	ull preHash(ull key){

		return (key*randomNum2)%randomPrime;

	}


	ull hashFunction(ull preHashedKey){

		ull hashIndex = 0;

		hashIndex = (((randomNum1*preHashedKey) + randomNum2)%randomPrime)%hashTableSize; 

		return hashIndex;
	}

	struct hashPair<TKEY,TVAL>* searchHashTable(TKEY key){

		TKEY inputKey = key;
		ull k = preHash(key);
		ull hashIndex = hashFunction(k);

		struct hashPair<TKEY,TVAL> *node = NULL;
		node = hashTable[hashIndex].chainNext;

		while(node){
			if(node->key == inputKey){
				
				return node;
			}
			node = node->chainNext;
		}

		
		return NULL;
	}


	void insertIntoHashTable(TKEY key, TVAL value){

		struct hashPair<TKEY,TVAL> *searchNode = searchHashTable(key);
		if(searchNode!=NULL){
			searchNode->value = value;
		}else{

			TKEY inputKey = key;
			ull preHashedKey = preHash(key);

			ull hashIndex = hashFunction(preHashedKey);

			//cout<<key<<" hashIndex: "<<hashIndex<<"\n";

			struct hashPair<TKEY,TVAL> *chainNode = (struct hashPair<TKEY,TVAL> *)malloc(sizeof(struct hashPair<TKEY,TVAL>));
			chainNode->key = inputKey;
			chainNode->value = value;

			struct hashPair<TKEY,TVAL> *temp = hashTable[hashIndex].chainNext; 

			hashTable[hashIndex].chainNext = chainNode;
			chainNode->chainNext = temp;

		}
	}

	void printHashTable(){

		struct hashPair<TKEY,TVAL> *node = NULL;

		for(ull i=0;i<hashTableSize;i++){
			node = hashTable[i].chainNext;
			while(node){
				cout<<node->key<<" -> "<<node->value<<" ";
				node = node->chainNext;
			}
			cout<<"\n";
		}

	}


	void deleteFromHashTable(TKEY key){

		TKEY inputKey = key;
		ull preHashedKey = preHash(key);
		ull hashIndex = hashFunction(preHashedKey);

		struct hashPair<TKEY,TVAL> *node = NULL , *prevNode = NULL;
		node = hashTable[hashIndex].chainNext;
		prevNode = hashTable+hashIndex;

		while(node){
			if(node->key == inputKey){
				
				prevNode->chainNext = node->chainNext;
				free(node);
				break;
			}
			prevNode = node; 
			node = node->chainNext;
		}		

	}

};

int main(){
	
	//initialiseRandomVariable();

	int choice = 0;

	// string key;
	// string value;

	// int key;
	// int value;

	// string key;
	// int value;

	// unorderedMap<int,string> obj(5); 

	// obj.insertIntoHashTable(1,"sdf");
	// obj.printHashTable();

	// unorderedMap<string,string> obj2(4); 

	// obj2.insertIntoHashTable("sdgsdfsdfgdfg","sdf");
	// obj2.printHashTable();

	// unorderedMap<string ,int> obj3(3); 

	// obj3.insertIntoHashTable("dsgsdf",5);
	// obj3.printHashTable();

	// unorderedMap<int,int> obj4(9); 

	// obj4.insertIntoHashTable(1,8);
	// obj4.printHashTable();

	int key;
	int value;

	unorderedMap<int,int> obj(10); 

	while(true){

		cout<<"1. Insert Element\n2. Delete Element\n3. Search Element\n4. Print Hash Table\n5. Exit\nEnter your choice: ";
		cin>>choice;

		if(choice==1){
			
			cout<<"Enter key: ";
			cin>>key;
			cout<<"\n";
			cout<<"Enter value: ";
			cin>>value;
			cout<<"\n";
			obj.insertIntoHashTable(key,value);
			
		}else if(choice==2){

			cout<<"Enter key: ";
			cin>>key;
			cout<<"\n";
			obj.deleteFromHashTable(key);
	
		}else if(choice==3){
	
			cout<<"Enter key: ";
			cin>>key;
			cout<<"\n";
			struct hashPair<int,int> *searchNode = obj.searchHashTable(key);
			if(searchNode!=NULL)
				cout<<"Search successful\nKey: "<<searchNode->key<<"\nValue: "<<searchNode->value<<"\n";
			else
				cout<<"Search Unsuccessful Key Not Found\n";
			
			
		}else if(choice==4){
	
			obj.printHashTable();

		}else  if(choice==5){
			return 0;
		}else{
			cout<<"Wrong input entered";
		}
	}

	return 0;
}