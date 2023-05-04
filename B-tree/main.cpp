#include <iostream>
#include <vector>
#include<algorithm>
#include<string>
#include "B+tree.h"
#include <cstdlib>
#include <array>
#include <map>

using namespace std;



class Pair{
  public:
  int id;
  vector<int>data;

  Pair(vector<int> data, int id )
  { 
    this->data = data;
    this->id = id;
  }

  Pair()
  {
    this->id =0;
  }


};


// *************************************Global object containing all boxes co-ordinates **********************************
vector<Pair> container;
map<vector<int>,int> dict;

 int internalNodeLen = 2, leafNodeLen = 3;  // some random intial value
    
/// ******************* Intialize Trees **************************************** 
BPTree* co_ordinate_BPTree = new BPTree(leafNodeLen, internalNodeLen);
BPTree* start_x_Co_ordinate_BPTree = new BPTree(leafNodeLen, internalNodeLen);
BPTree* end_x_Co_ordinate_BPTree = new BPTree(leafNodeLen, internalNodeLen);
BPTree* start_y_Co_ordinate_BPTree = new BPTree(leafNodeLen, internalNodeLen);
BPTree* end_y_Co_ordinate_BPTree = new BPTree(leafNodeLen, internalNodeLen);



 vector<int> end_X;
 vector<int> end_Y ;
 vector<int> start_X ;
 vector<int> start_Y;

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


 
// INDEX representation
    
    // 0 -> xStart
    // 1 -> yEnd
    // 2 -> xEnd
    // 3 -> yEnd
    // 4 -> xStart
    // 5 -> yStart
    // 6 -> xEnd
    // 7 -> yStart


// checkY function will be used for leftNeighbors & rightNeighbors vector.
// checkX function will be used for topNeighbors & bottomNeighbors vector.

// vector arr represents the vector over which we will be iterating.

// zIndex represents the index of the box for which we are finding the neighbors.

// boxCoordinate is a table i.e vector of vectors that stores the coordinates of the boxes.

// resultArray is the vector that stores the indexes of all the boxes that are the neighbors of zIndex.

void checkY(std::vector <int> arr, int zIndex, vector<Pair> boxCoordinates, std::vector <int>& resultArray){

    
    
    for(int i = 0; i < arr.size(); i++){

        int checkIndex = arr[i];

        if(
            (boxCoordinates[zIndex].data[7] <= boxCoordinates[checkIndex].data[1]  &&  boxCoordinates[checkIndex].data[1] <= boxCoordinates[zIndex].data[1] )||
            (boxCoordinates[zIndex].data[7] <= boxCoordinates[checkIndex].data[7] &&  boxCoordinates[checkIndex].data[7] <= boxCoordinates[zIndex].data[1])||
            (boxCoordinates[zIndex].data[7] <= boxCoordinates[checkIndex].data[7]  && boxCoordinates[checkIndex].data[1]<=boxCoordinates[zIndex].data[1] ) ||
            (boxCoordinates[zIndex].data[7] >= boxCoordinates[checkIndex].data[7]  && boxCoordinates[checkIndex].data[1]>=boxCoordinates[zIndex].data[1])
            ){
                resultArray.push_back(checkIndex);
            }

    }
}




void checkX(std::vector <int>& arr, int zIndex, vector<Pair> boxCoordinates, std::vector <int>& resultArray){

    for(int i = 0; i < (arr.size()); i++){

        int checkIndex = arr[i];
        

        if(
        //    ( boxCoordinates[zIndex][0] <= boxCoordinates[checkIndex][0] &&  boxCoordinates[checkIndex][0]<= boxCoordinates[zIndex][2]) ||
        //     (boxCoordinates[zIndex][0] <= boxCoordinates[checkIndex][2]  &&  boxCoordinates[checkIndex][2]<= boxCoordinates[zIndex][2])
        ( boxCoordinates[zIndex].data[0] <= boxCoordinates[checkIndex].data[0] &&  boxCoordinates[checkIndex].data[0]<= boxCoordinates[zIndex].data[2]) ||
            (boxCoordinates[zIndex].data[0] <= boxCoordinates[checkIndex].data[2]  &&  boxCoordinates[checkIndex].data[2]<= boxCoordinates[zIndex].data[2])||
            (boxCoordinates[zIndex].data[0]<=boxCoordinates[checkIndex].data[0] && boxCoordinates[checkIndex].data[2]<=boxCoordinates[zIndex].data[2])||
            (boxCoordinates[zIndex].data[0]>=boxCoordinates[checkIndex].data[0] && boxCoordinates[checkIndex].data[2]>=boxCoordinates[zIndex].data[2])
            ){
                resultArray.push_back(checkIndex);
            }
            
    }
}



void insertIntoContainer()
{
   
   vector<int> co_ordinates;
   int temp;
   int id =0;
   cout<<"Enter the co-ordinates of input box : "<<endl;

   cout<<"Enter the co-ordinates of Top left corener of the box "<<endl;
   cin>>temp;
   co_ordinates.push_back(temp);
   cin>>temp;
   co_ordinates.push_back(temp);

   cout<<"Enter the co-ordintes of Top Right corener of the box "<<endl;
   cin>>temp;
   co_ordinates.push_back(temp);
   cin>>temp;
   co_ordinates.push_back(temp);

   cout<<"Enter the co-ordinates of Bottom left corner of the box"<<endl;
   cin>>temp;
   co_ordinates.push_back(temp);
   cin>>temp;
   co_ordinates.push_back(temp);

   cout<<"Enter the co-ordinates of the Bottom Right corner of the box "<<endl;
    cin>>temp;
   co_ordinates.push_back(temp);
   cin>>temp;
   co_ordinates.push_back(temp);


  //  cout<<"Enter a unique id for the box : "<<endl;
  //  cin>>id;
   // Here we can insert id into a global hashset using which we can check the uniqeness of the id 
   id =9;
   dict[co_ordinates]=id;
   Pair box(co_ordinates,id);

  // pushing box into container
  int size = container.size();
  container.push_back(box);

  //pushing coordinates values into respective trees( X_Start, Y_start, X_end, Y_end)
  
  start_x_Co_ordinate_BPTree->insert(box.data[0],size);
  start_y_Co_ordinate_BPTree->insert(box.data[5],size);
  end_x_Co_ordinate_BPTree->insert(box.data[2],size);
  end_y_Co_ordinate_BPTree->insert(box.data[1],size);
  

}



void removeBoxContainer(vector<int>box)
{
  Pair cur;
  int value = dict[box];
  int n = container.size();
  for( int i =0;i<n;i++)
  {
    cur=container[i];
    if (cur.id ==value)
    {
        container.erase(container.begin()+i);
        return;
    }
  }

  // remove from all the trees too remaining 
}

void printTree()
{

cout<<"Start X tree "<<endl;
printMethod(start_x_Co_ordinate_BPTree);


cout<<"end X tree "<<endl;
printMethod(end_x_Co_ordinate_BPTree);

cout<<"Start Y tree "<<endl;
printMethod(start_y_Co_ordinate_BPTree);


cout<<"end Y tree "<<endl;
printMethod(end_y_Co_ordinate_BPTree);
}


vector<vector<int>> FindNeighbourPhase2(int idx)
{
  vector<vector<int>> ans;
vector<int> Xstart_selected;
checkY(start_X,idx,container,Xstart_selected);

vector<int>Xend_selected;
checkY(end_X,idx,container,Xend_selected);

vector<int>Ystart_Selected;
checkX(start_Y,idx,container,Ystart_Selected);

vector<int>Yend_Selected;
checkX(end_Y,idx,container,Yend_Selected);


ans.push_back(Xstart_selected);
ans.push_back(Xend_selected);
ans.push_back(Ystart_Selected);
ans.push_back(Yend_Selected);


cout<<"Xstart_selected Filtered boxes : "<<Xstart_selected.size()<<endl;
for ( int i : Xstart_selected)
{
    cout<<i<<" , ";
}
cout<<endl;



cout<<"Xend_selected Filtered boxes : "<<Xend_selected.size()<<endl;
for ( int i : Xend_selected)
{
    cout<<i<<" , ";
}
cout<<endl;



cout<<"Ystart_Selected Filtered boxes "<<Ystart_Selected.size()<<endl;
for ( int i : Ystart_Selected)
{
    cout<<i<<" , ";
}
cout<<endl;



cout<<"Yend_Selected Filtered boxes "<<Yend_Selected.size()<<endl;
for ( int i : Yend_Selected)
{
    cout<<i<<" , ";
}
cout<<endl;

return ans;
}

void FindNeighbourPhase1()
{
  int idx;
  cout<<"Enter the box index for which Neighbour has to be find : "<<endl;
  cin>>idx;
  
 Pair curPair = container[idx];
 vector<int> curBox = curPair.data;
 end_X = end_x_Co_ordinate_BPTree->newSearch(curBox[0],curBox[2]);
 end_Y = end_y_Co_ordinate_BPTree->newSearch(curBox[7],curBox[1]);
 start_X = start_x_Co_ordinate_BPTree->newSearch(curBox[0],curBox[2]);
 start_Y = start_y_Co_ordinate_BPTree->newSearch(curBox[7],curBox[1]);


cout<<"Start Y : elements "<< start_Y.size()<<endl;
  for ( int i  : start_Y)
  {
     cout<<i<<" ";
  }

  cout<<endl;

  cout<<"end Y : elemets "<<end_Y.size()<<endl;
  for (int i: end_Y)
  {
    cout<<i<<" ";
  }
  cout<<endl;

  cout<<"start_X : elements "<<start_X.size()<<endl;
  
  for (int i: start_X)
  {
    cout<<i<<" ";
  }
  cout<<endl;

  cout<<" end_x : elements "<<end_X.size()<<endl;

  for ( int i : end_X)
  {
    cout<<i<< " ";
  }
  cout<<endl;
  
  FindNeighbourPhase2(idx);

}



int main ()
{
    
    bool flag = true;
    int option;

    // **************** Inserting Spatial Data *****************************************
    
    
    // INput-1
    // vector<int> p1 = {-4,2,0,2,-4,0,0,0};
    // vector<int> p2 = {-2,0,2,0,-2,-2,2,-2};
    // vector<int> p3 ={2,2,4,2,2,0,4,0};
    
    // input2
    
  
  do{
        cout << "\nPlease provide the queries with respective keys : " << endl;
        cout << "\tPress 1: Insert a box \n\tPress 2:Find Neighbours \n\tPress 3: Print Trees \n\tPress 4: End the program"<<endl;
        cin >> option;

        switch(option)
        {
          case 1:
             insertIntoContainer();
             break;
          case 2:
             FindNeighbourPhase1();
             break;
          case 3:
             printTree();
             break;
          case 4:
             flag=false;
             break;
          default :
            cout<<"Please Enter a valid command "<<endl;
            break;
        }
  }while(flag);

    // vector<int>p1 = {-6,6,2,6,-6,0,2,0};
    // vector<int>p2 = {2,6,8,6,2,0,8,0};
    // vector<int>p3 = {6,4,10,4,6,0,10,0};
    // vector<int>p4 = {-10,2,-8,2,-10,0,-8,0};
    // vector<int>p5 = {-4,0,0,0,-4,-6,0,-6};
    // vector<int>p6 = {-12,-6,-4,-6,-12,-12,-4,-12};

    // Pair one = Pair(p1,1);
    // Pair two = Pair(p2,2);
    // Pair three = Pair(p3,3);
    // Pair four = Pair(p4,4);
    // Pair five = Pair(p5,5);
    // Pair six = Pair(p6,6);
    
    // dict[p1]=1;
    // dict[p2]=2;
    // dict[p3]=3;
    // dict[p4]=4;
    // dict[p5]=5;
    // dict[p6]=6;
    
    // container.push_back(one);
    // container.push_back(two);
    // container.push_back(three);
    // container.push_back(four);
    // container.push_back(five);
    // container.push_back(six);
    
   

    // input3
    // vector<int>p1 = {0,2,2,4,2,0,4,3};
    // vector<int>p2 = {0,0,3,0,0,-2,3,-2};


 
    

  //  int idx=0;
  
  //  for ( Pair p :container )
  //  {
  //   vector<int> i = p.data;
  //    co_ordinate_BPTree->insert(idx,idx);
  //    start_x_Co_ordinate_BPTree->insert(i[0],idx);
  //    end_x_Co_ordinate_BPTree->insert(i[2],idx);
  //    start_y_Co_ordinate_BPTree->insert(i[5],idx);
  //    end_y_Co_ordinate_BPTree->insert(i[1],idx);
     
  //    idx++;
  //  }
   

  //************************Function (printTree()) to Print all the B+trees ***********************************

  // printTree();


//***************************************** Looking at B+Tree Formed for each start and end cordinates of all boxes *******************
//****************AND*************************Printing Match boxes in range of target box in each direction*************************** 




end_X;
end_Y ;
start_X ;
start_Y;




// /**
//  * left -X_end
//  * right - X_start
//  * Top - y-Start
//  * Bottom - y-end
//  * 
//  * **/


// **************** Generating Matching Boxes and printing box index*****************************************

// vector<vector<int>> solutionBoxes = FindNeighbour();

return 0;

}





