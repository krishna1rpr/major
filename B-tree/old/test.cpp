#include <iostream>
#include <vector>
#include<algorithm>
#include<string>
#include "B+tree.h"
#include <cstdlib>
#include <array>
using namespace std;
void insertionMethod(BPTree** bPTree) {
    int key;   // id
    int value;  // age
    cout << "Please provide the key: ";
    cin >> key;
    cout << "\nEnter your value";
    cin >> value;
    (*bPTree)->insert(key, value);
    cout << "Insertion of roll No: " << key << " Successful"<<endl;
}

void searchMethod(BPTree* tree) {
    int id;
    cout << "What's the id to Search? ";
    cin >> id;
    tree->search(id);
}

void printMethod(BPTree* bPTree) {
    int type;
    cout<<"1.Level Order Traversal"<<endl;
    cout<<"2.Seqential Traversal "<<endl;
    cin>>type;
    if (type==1)
    {
    cout << "\nHere is your Tree Structure" << endl;
    bPTree->printTreeLevelOrder(bPTree->root);
    }
    else{
      cout << "\nHere is your Tree Structure" << endl;
      bPTree->printTree(bPTree->root);
    }   
        
}


void deleteMethod(BPTree* bPTree) {
    cout << "Showing you the Tree, Choose a key from here: " << endl;
    bPTree->printTree(bPTree->root);
 
    int keyTodelete;
    cout << "Enter a key to delete: " << endl;
    cin >> keyTodelete;
    bPTree->remove(keyTodelete);

    //Displaying
    bPTree->printTree(bPTree->root);
}


int main ()
{
    
    bool flag = true;
    int option;

    int internalNodeLen = 4, leafNodeLen = 3;  // some random intial value

    BPTree* co_ordinate_BPTree = new BPTree(leafNodeLen, internalNodeLen);
    BPTree* start_x_Co_ordinate_BPTree = new BPTree(leafNodeLen, internalNodeLen);
    BPTree* end_x_Co_ordinate_BPTree = new BPTree(leafNodeLen, internalNodeLen);
    BPTree* start_y_Co_ordinate_BPTree = new BPTree(leafNodeLen, internalNodeLen);
    BPTree* end_y_Co_ordinate_BPTree = new BPTree(leafNodeLen, internalNodeLen);

    vector<array<int,8>> co_ordinates;

    array<int,8> p1 = {{-4,2,0,2,-4,0,0,0}};
    array<int,8> p2 = {{-2,0,2,0,-2,-2,2,-2}};
    array<int,8> p3 ={{2,2,4,2,2,0,4,0}};

    co_ordinates.push_back(p1);
    co_ordinates.push_back(p2);
    co_ordinates.push_back(p3);


   int idx=0;
   for ( array<int,8> i :co_ordinates )
   {
     co_ordinate_BPTree->insert(idx,idx);
     start_x_Co_ordinate_BPTree->insert(i[0],idx);
     end_x_Co_ordinate_BPTree->insert(i[2],idx);
     start_y_Co_ordinate_BPTree->insert(i[5],idx);
     end_y_Co_ordinate_BPTree->insert(i[1],idx);
     idx++;
   }

  vector<int> ans = start_x_Co_ordinate_BPTree->newSearch(-3,0);
  cout<<"VECTOR Size : "<<ans.size()<<endl;

  for ( int i : ans)
  {
    cout<<i<<""<<endl;
  }

    return 0;

}
