#include<bits/stdc++.h>
#define ll long long int

using namespace std;


ll MAX_SIZE  = 100000000;
ll kIndex  = 100000;

//ll numArray[MAX_SIZE];



ll partition(ll numArray[], ll l, ll r){

    ll x = numArray[r], i=l; 
    for (ll j=l;j<=r-1;j++){

        if (numArray[j] <= x){

        	ll temp = numArray[i];
			numArray[i] = numArray[j];        	
            numArray[j] = temp; 
            i++; 
        } 
    } 
    
    ll temp = numArray[i];
	numArray[i] = numArray[r];        	
    numArray[r] = temp; 
    
    return i; 
} 


ll randomPartition(ll numArray[], ll l, ll r){

    ll n = r-l+1; 
    ll pivot = rand() % n;

    ll temp = numArray[l + pivot];
	numArray[l + pivot] = numArray[r];        	
    numArray[r] = temp;

    return partition(numArray, l, r); 
} 

ll kthSmallest(ll numArray[], ll l, ll r,ll k){


    if (k > 0 && k <= r - l + 1){

        ll pos = randomPartition(numArray,l, r); 
  
        if (pos-l == k-1) 
            return numArray[pos]; 
        if (pos-l > k-1)   
            return kthSmallest(numArray, l, pos-1, k); 
  
        return kthSmallest(numArray,pos+1, r, k-pos+l-1); 
    } 

    return INT_MAX; 
} 




int main(){

	// srand((unsigned)time(0)); 
	 
	// for(ll i=0; i<MAX_SIZE; i++){ 
	//     numArray[i] = (rand()%MAX_SIZE)+1; 
	// } 

	cout<<"enter size of array: ";
	cin>>MAX_SIZE;

	ll numArray[MAX_SIZE];
	for(ll i=0;i<MAX_SIZE;i++)
		cin>>numArray[i];

	cout<<"Enter K: ";
	cin>>kIndex;


	clock_t currTime; 
    double timeInterval;

////////////my fuction for nth smallest/////////////////////////////

    currTime = clock(); 

    cout<<kthSmallest(numArray,0,MAX_SIZE,kIndex)<<"\n";

    timeInterval = (double)(clock() - currTime)/CLOCKS_PER_SEC; 
    
    cout<<"My fuction: "<<timeInterval<<"\n"; 

///////////////////////////// stl ////////////////////////////////////////

    currTime = clock(); 

    nth_element(numArray, numArray+kIndex-1, numArray+MAX_SIZE);
    
    cout<<numArray[kIndex-1]<<"\n";

    timeInterval = (double)(clock() - currTime)/CLOCKS_PER_SEC; 
    
    cout<<"stl: "<<timeInterval<<"\n"; 
    
    return 0;
}