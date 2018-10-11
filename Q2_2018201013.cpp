#include <bits/stdc++.h>
#define maxDegree 4
#define minDegree 2

using namespace std;


struct btreeNode{

    int value[maxDegree+1];
    int currSize;
    struct btreeNode *childPtr[maxDegree + 1];
};

struct btreeNode *root;

struct btreeNode * createNode(int value, struct btreeNode *child){
    struct btreeNode *newNode;
    newNode = (struct btreeNode *)malloc(sizeof(struct btreeNode));
    newNode->value[1] = value;
    newNode->currSize = 1;
    newNode->childPtr[0] = root;
    newNode->childPtr[1] = child;
    return newNode;
}

void insertIntoNode(int value, int pos, struct btreeNode *node,struct btreeNode *child){
    int j = node->currSize;
    while (j > pos) {
        node->value[j + 1] = node->value[j];
        node->childPtr[j + 1] = node->childPtr[j];
        j--;
    }
    node->value[j + 1] = value;
    node->childPtr[j + 1] = child;
    node->currSize++;
}

void splitNode(int value, int *pvalue, int pos, struct btreeNode *node,struct btreeNode *child, struct btreeNode **newNode){
    int mid, j;

    if(pos > minDegree)
        mid = minDegree + 1;
    else
        mid = minDegree;

    *newNode = (struct btreeNode *)malloc(sizeof(struct btreeNode));
    j = mid + 1;
    while (j <= maxDegree) {
        (*newNode)->value[j - mid] = node->value[j];
        (*newNode)->childPtr[j - mid] = node->childPtr[j];
        j++;
    }
    node->currSize = mid;
    (*newNode)->currSize = maxDegree - mid;

    if (pos <= minDegree) {
        insertIntoNode(value, pos, node, child);
    } else {
        insertIntoNode(value, pos - mid, *newNode, child);
    }
    *pvalue = node->value[node->currSize];
    (*newNode)->childPtr[0] = node->childPtr[node->currSize];
    node->currSize--;
}


int setValueInNode(int value, int *pvalue,struct btreeNode *node, struct btreeNode **child){

    int pos;
    if(!node){
        *pvalue = value;
        *child = NULL;
        return 1;
    }

    if(value < node->value[1]){
       pos = 0;
    }else{
        for(pos = node->currSize;value < node->value[pos] && pos > 1; pos--);
        if(value == node->value[pos]) {
            printf("Duplicates not allowed\n");
            return 0;
        }
    }
    if (setValueInNode(value, pvalue, node->childPtr[pos], child)) {
        if (node->currSize < maxDegree) {
            insertIntoNode(*pvalue, pos, node, *child);
        } else {
            splitNode(*pvalue, pvalue, pos, node, *child, child);
            return 1;
        }
    }
    return 0;
}

void insertion(int value){
    int flag, data;
    struct btreeNode *child;

    flag = setValueInNode(value, &data, root, &child);
    if (flag)
        root = createNode(data, child);
}


void searching(int value, int *pos, struct btreeNode *root) {
    
    if(!root){
        return;
    }

    if(value < root->value[1]){
        *pos = 0;
    }else{
        
        for (*pos = root->currSize;(value < root->value[*pos] && *pos > 1); (*pos)--);
        
        if (value == root->value[*pos]) {
            printf("Given data %d is present in B-Tree", value);
            return;
        }
    }
    searching(value, pos, root->childPtr[*pos]);
    return;
}


void traversal(struct btreeNode *root) {
    int i;
    if (root) {
        for (i = 0; i < root->currSize; i++) {
            traversal(root->childPtr[i]);
            printf("%d ", root->value[i + 1]);
        }
        traversal(root->childPtr[i]);
    }
}

int main(){

    int value, choice;
    while (1) {
            
        cout<<"1. Insertion\n2. Searching\n3. Traversal\n4. Exit\nEnter your choice: ";
        
        cin>>choice;
        
        if(choice == 1){

            cout<<"Enter your input: ";
            cin>>value;
            insertion(value);

        }else if(choice == 2){

            cout<<"Enter the element to search: ";
            cin>>value;
            searching(value, &choice, root);

        }else if(choice == 3){

            traversal(root);

        }else if(choice == 4){
            return 0;
        }else {
            cout<<"Wrong Input\n";
        }
        cout<<"\n";
    }

    return 0;
}

