#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>
using namespace std;



//ADT Graph is used to dynamically create a graph which is a 2-D matrix
struct Graph{
int **p;

};
///////////////////////////////////////////////////////////////////

//ADT List is used to create a list of all the games to be played
struct List{

int l[40000];
}checklist,temp_list;
////////////////////////////////////////////////////////////////


//ADT Index is used to map the index of a matrix to a game; for ex: 1 is index to (1,2)
struct index{

int team1,team2;

}ind[40000];
////////////////////////////////////////////////////////////////////////////////


void make_index(int n)                // Function used for making index
{

    int add=(n*(n-1))/2;
    int i=0;

      for(int j=1;j<n;j++)
      {
        for(int k=j+1;k<=n;k++)
        {
           ind[i].team1=j;
           ind[i].team2=k;
           ind[i+add].team1=k;
           ind[i+add].team2=j;
           i++;
        }

      }

}


bool check(int a,int b)   // This function is used to check whether two games are disjoint or not
{
    if(ind[a].team1==ind[b].team1 || ind[a].team1==ind[b].team2 || ind[a].team2==ind[b].team1 || ind[a].team2==ind[b].team2)
        return true;
    else
        return false;


}


void make_graph(Graph G,int m_size)    // This function is used to create graph
{

    int i,j;
    bool link;
    for(i=0;i<m_size;i++)
    {
        for( j=0;j<m_size;j++)
        {
           link=check(i,j);
           if(link==true)
            G.p[i][j]=1;
           else
            G.p[i][j]=0;
        }
    }

}

void initialize_list(int n)        // this function is used to initialize the list
{

  for(int i=0;i<n;i++)
    checklist.l[i]=1;
}


int find_pair(int n)   // This function is used to find the games which can be played on the same day
{
    for(int i=0;i<n;i++)
    {
        if(checklist.l[i]==1)
         {
             checklist.l[i]=0;
                return i;
         }

    }
     return -1;


}

make_null(List temp)              // To remove the games played from the list
{
    for(int i=0; i<40000;i++ )
        temp.l[i]=-1;


}


bool check_in_temp_list(List temp_list,int list_inc,int col)    // To check the dependency of a game with other games which are scheduled on the same day
{
    int i;
    bool res;
    for(i=0;i<list_inc;i++)
    {
        res=check(temp_list.l[i],col);
        if(res==true)
            return false;

    }
    return true;


}

int n,total_match;
int i,j,matrix_size,row,num_match_day,list_inc=0;


void greedy(Graph *G)            //Greedy algorithm to implement graph coloring problem
{

    while(total_match != 0)       //Loop until all matches get played
    {

        make_null(temp_list);
        list_inc=0;
        row=find_pair(matrix_size);                               //Take out one game from the list
        cout<<"("<<ind[row].team1<<","<<ind[row].team2<<")" ;     // Print the first game
        total_match--;
        temp_list.l[list_inc++]=row;                              // Put the game in the temp list to check dependency
        for(i=0;i<matrix_size;i++)                               //To set the column of that particular game to 1 so that it can't get choosen next time
            G->p[i][row]=1;


        for(i=0;i<matrix_size;i++)
        {
            if(G->p[row][i]==0 && check_in_temp_list(temp_list,list_inc,i)) //Find other game in the same row which does not conflict with temp list games
            {
                cout<<"; ("<<ind[i].team1<<","<<ind[i].team2<<")" ;    //Print other games
                checklist.l[i]=0;                                //Remove that game from the list
                temp_list.l[list_inc++]=i;                       //Put this game in the temp list
                total_match--;
                for(j=0;j<matrix_size;j++)                 //To set the column of that particular game to 1 so that it can't get choosen next time
                   G->p[j][i]=1;

            }

        }

        cout<<endl<<endl;



    }





}







int main()
{

    cout<<"Enter the number of teams in range (1,140):";
    cin>>n;

    if(n<1 ||n>140)
    {
        cout<<"Invalid input or out of bounds";
         exit(0);
    }


    total_match=n*(n-1);
    Graph *G=new Graph();


    //Dynamically creating a 2D matrix
    G->p=new int*[total_match];
    for(i = 0; i < total_match; i++)
    {
       G->p[i] = new int[total_match];
    }

////////////////////////////////


    matrix_size=total_match;
    make_index(n);
    make_graph(*G,matrix_size);
    initialize_list(matrix_size);
    greedy(G);


}

