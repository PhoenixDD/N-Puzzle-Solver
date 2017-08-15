#include<iostream>
#include<time.h>
#include<fstream>
#include<vector>
#include<unordered_map>
#include<stack>
#define N 4
using namespace std;
/*int grid[N][N]=  {{10,11,6,12},                                    //65 Moves
                 {15,13,0,9},
                 {8,14,2,3},
                 {7,4,1,5}};*/
int grid[N][N]= {{0,12,9,13},                                    //80 Moves
                 {15,11,10,14},
                 {7,8,5,6},
                 {4,3,2,1}};
struct Pattern_check_6
{
    int x1,x2,x3,x4,x5,x6,y1,y2,y3,y4,y5,y6;
};
struct Pattern_check_3
{
    int x1,x2,x3,x4,x5,x6,y1,y2,y3,y4,y5,y6;
};
struct Node                                                         //Basic Node
{
    char from;
    int Grid[N][N],x0,y0,h,p_6_1,p_6_2,p_3;
    Pattern_check_6 temp_6_1,temp_6_2;
    Pattern_check_3 temp_3;
}Start;
int i,j,ctr,threshhold,Pattern_config_3;
long long int Pattern_config_6_1,Pattern_config_6_2;
unordered_map<long long int,int> Pattern_check_6_1,Pattern_check_6_2;
unordered_map<int,int> Pattern_check_3;
bool found=false;
stack<char> path;
clock_t tStart,tEnd;
Pattern_config_6_1_calc(Node* temp_Node)
{
    Pattern_config_6_1=0;
    Pattern_config_6_1+=temp_Node->temp_6_1.x1;Pattern_config_6_1*=10;
    Pattern_config_6_1+=temp_Node->temp_6_1.y1;Pattern_config_6_1*=10;
    Pattern_config_6_1+=temp_Node->temp_6_1.x2;Pattern_config_6_1*=10;
    Pattern_config_6_1+=temp_Node->temp_6_1.y2;Pattern_config_6_1*=10;
    Pattern_config_6_1+=temp_Node->temp_6_1.x3;Pattern_config_6_1*=10;
    Pattern_config_6_1+=temp_Node->temp_6_1.y3;Pattern_config_6_1*=10;
    Pattern_config_6_1+=temp_Node->temp_6_1.x4;Pattern_config_6_1*=10;
    Pattern_config_6_1+=temp_Node->temp_6_1.y4;Pattern_config_6_1*=10;
    Pattern_config_6_1+=temp_Node->temp_6_1.x5;Pattern_config_6_1*=10;
    Pattern_config_6_1+=temp_Node->temp_6_1.y5;Pattern_config_6_1*=10;
    Pattern_config_6_1+=temp_Node->temp_6_1.x6;Pattern_config_6_1*=10;
    Pattern_config_6_1+=temp_Node->temp_6_1.y6;
}
Pattern_config_6_2_calc(Node* temp_Node)
{
    Pattern_config_6_2=0;
    Pattern_config_6_2+=temp_Node->temp_6_2.x1;Pattern_config_6_2*=10;
    Pattern_config_6_2+=temp_Node->temp_6_2.y1;Pattern_config_6_2*=10;
    Pattern_config_6_2+=temp_Node->temp_6_2.x2;Pattern_config_6_2*=10;
    Pattern_config_6_2+=temp_Node->temp_6_2.y2;Pattern_config_6_2*=10;
    Pattern_config_6_2+=temp_Node->temp_6_2.x3;Pattern_config_6_2*=10;
    Pattern_config_6_2+=temp_Node->temp_6_2.y3;Pattern_config_6_2*=10;
    Pattern_config_6_2+=temp_Node->temp_6_2.x4;Pattern_config_6_2*=10;
    Pattern_config_6_2+=temp_Node->temp_6_2.y4;Pattern_config_6_2*=10;
    Pattern_config_6_2+=temp_Node->temp_6_2.x5;Pattern_config_6_2*=10;
    Pattern_config_6_2+=temp_Node->temp_6_2.y5;Pattern_config_6_2*=10;
    Pattern_config_6_2+=temp_Node->temp_6_2.x6;Pattern_config_6_2*=10;
    Pattern_config_6_2+=temp_Node->temp_6_2.y6;
}
Pattern_config_3_calc(Node* temp_Node)
{
    Pattern_config_3=0;
    Pattern_config_3+=temp_Node->temp_3.x1;Pattern_config_3*=10;
    Pattern_config_3+=temp_Node->temp_3.y1;Pattern_config_3*=10;
    Pattern_config_3+=temp_Node->temp_3.x2;Pattern_config_3*=10;
    Pattern_config_3+=temp_Node->temp_3.y2;Pattern_config_3*=10;
    Pattern_config_3+=temp_Node->temp_3.x3;Pattern_config_3*=10;
    Pattern_config_3+=temp_Node->temp_3.y3;
}
showmoves()
{
    cout<<endl<<"Time  Taken:\t"<<(double)tEnd/CLOCKS_PER_SEC<<endl;
    while(!path.empty())
    {
        if(path.top()=='R')
        {
            swap(Start.Grid[Start.y0-1][Start.x0-1],Start.Grid[Start.y0-1][Start.x0-2]);
            Start.x0--;
        }
        if(path.top()=='L')
        {
            swap(Start.Grid[Start.y0-1][Start.x0-1],Start.Grid[Start.y0-1][Start.x0]);
            Start.x0++;
        }
        if(path.top()=='D')
        {
            swap(Start.Grid[Start.y0-1][Start.x0-1],Start.Grid[Start.y0-2][Start.x0-1]);
            Start.y0--;
        }
        if(path.top()=='U')
        {
            swap(Start.Grid[Start.y0-1][Start.x0-1],Start.Grid[Start.y0][Start.x0-1]);
            Start.y0++;
        }
        cout<<path.top()<<endl;
        for(i=0;i<N;i++)
        {
            for(j=0;j<N;j++)
            {
                cout<<Start.Grid[i][j]<<"\t";
            }
            cout<<endl<<endl;
        }
        system("pause");
        cout<<endl;
        path.pop();
    }
}
vector<Node> Neighbors(Node* temp_Node)
{
    vector<Node> neighbors;
    ctr=0;
    if(temp_Node->x0+1<=N&&temp_Node->from!='L')                                     //Space->Right, Move=Left;
    {
        neighbors.push_back(*temp_Node);
        neighbors[ctr].from='R';
        neighbors[ctr].x0++;
        neighbors[ctr].Grid[temp_Node->y0-1][temp_Node->x0-1]=neighbors[ctr].Grid[temp_Node->y0-1][temp_Node->x0];
        neighbors[ctr].Grid[temp_Node->y0-1][temp_Node->x0]=0;
        if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0]==1)
        {
            neighbors[ctr].temp_6_1.x1--;
            Pattern_config_6_1_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_1=(*Pattern_check_6_1.find(Pattern_config_6_1)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0]==2)
        {
            neighbors[ctr].temp_3.x1--;
            Pattern_config_3_calc(&neighbors[ctr]);
            neighbors[ctr].p_3=(*Pattern_check_3.find(Pattern_config_3)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0]==3)
        {
            neighbors[ctr].temp_3.x2--;
            Pattern_config_3_calc(&neighbors[ctr]);
            neighbors[ctr].p_3=(*Pattern_check_3.find(Pattern_config_3)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0]==4)
        {
            neighbors[ctr].temp_3.x3--;
            Pattern_config_3_calc(&neighbors[ctr]);
            neighbors[ctr].p_3=(*Pattern_check_3.find(Pattern_config_3)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0]==5)
        {
            neighbors[ctr].temp_6_1.x2--;
            Pattern_config_6_1_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_1=(*Pattern_check_6_1.find(Pattern_config_6_1)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0]==6)
        {
            neighbors[ctr].temp_6_1.x3--;
            Pattern_config_6_1_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_1=(*Pattern_check_6_1.find(Pattern_config_6_1)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0]==7)
        {
            neighbors[ctr].temp_6_2.x1--;
            Pattern_config_6_2_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_2=(*Pattern_check_6_2.find(Pattern_config_6_2)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0]==8)
        {
            neighbors[ctr].temp_6_2.x2--;
            Pattern_config_6_2_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_2=(*Pattern_check_6_2.find(Pattern_config_6_2)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0]==9)
        {
            neighbors[ctr].temp_6_1.x4--;
            Pattern_config_6_1_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_1=(*Pattern_check_6_1.find(Pattern_config_6_1)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0]==10)
        {
            neighbors[ctr].temp_6_1.x5--;
            Pattern_config_6_1_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_1=(*Pattern_check_6_1.find(Pattern_config_6_1)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0]==11)
        {
            neighbors[ctr].temp_6_2.x3--;
            Pattern_config_6_2_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_2=(*Pattern_check_6_2.find(Pattern_config_6_2)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0]==12)
        {
            neighbors[ctr].temp_6_2.x4--;
            Pattern_config_6_2_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_2=(*Pattern_check_6_2.find(Pattern_config_6_2)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0]==13)
        {
            neighbors[ctr].temp_6_1.x6--;
            Pattern_config_6_1_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_1=(*Pattern_check_6_1.find(Pattern_config_6_1)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0]==14)
        {
            neighbors[ctr].temp_6_2.x5--;
            Pattern_config_6_2_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_2=(*Pattern_check_6_2.find(Pattern_config_6_2)).second;
        }
        else
        {
            neighbors[ctr].temp_6_2.x6--;
            Pattern_config_6_2_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_2=(*Pattern_check_6_2.find(Pattern_config_6_2)).second;
        }
        neighbors[ctr].h=neighbors[ctr].p_6_1+neighbors[ctr].p_6_2+neighbors[ctr].p_3;
        ctr++;
    }
    if(temp_Node->x0-1>0&&temp_Node->from!='R')                                  //Space->Left, Move=Right;
    {
        neighbors.push_back(*temp_Node);
        neighbors[ctr].from='L';
        neighbors[ctr].x0--;
        neighbors[ctr].Grid[temp_Node->y0-1][temp_Node->x0-1]=neighbors[ctr].Grid[temp_Node->y0-1][temp_Node->x0-2];
        neighbors[ctr].Grid[temp_Node->y0-1][temp_Node->x0-2]=0;
        if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0-2]==1)
        {
            neighbors[ctr].temp_6_1.x1++;
            Pattern_config_6_1_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_1=(*Pattern_check_6_1.find(Pattern_config_6_1)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0-2]==2)
        {
           neighbors[ctr].temp_3.x1++;
           Pattern_config_3_calc(&neighbors[ctr]);
           neighbors[ctr].p_3=(*Pattern_check_3.find(Pattern_config_3)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0-2]==3)
        {
            neighbors[ctr].temp_3.x2++;
            Pattern_config_3_calc(&neighbors[ctr]);
            neighbors[ctr].p_3=(*Pattern_check_3.find(Pattern_config_3)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0-2]==4)
        {
            neighbors[ctr].temp_3.x3++;
            Pattern_config_3_calc(&neighbors[ctr]);
            neighbors[ctr].p_3=(*Pattern_check_3.find(Pattern_config_3)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0-2]==5)
        {
            neighbors[ctr].temp_6_1.x2++;
            Pattern_config_6_1_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_1=(*Pattern_check_6_1.find(Pattern_config_6_1)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0-2]==6)
        {
            neighbors[ctr].temp_6_1.x3++;
            Pattern_config_6_1_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_1=(*Pattern_check_6_1.find(Pattern_config_6_1)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0-2]==7)
        {
            neighbors[ctr].temp_6_2.x1++;
            Pattern_config_6_2_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_2=(*Pattern_check_6_2.find(Pattern_config_6_2)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0-2]==8)
        {
            neighbors[ctr].temp_6_2.x2++;
            Pattern_config_6_2_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_2=(*Pattern_check_6_2.find(Pattern_config_6_2)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0-2]==9)
        {
            neighbors[ctr].temp_6_1.x4++;
            Pattern_config_6_1_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_1=(*Pattern_check_6_1.find(Pattern_config_6_1)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0-2]==10)
        {
            neighbors[ctr].temp_6_1.x5++;
            Pattern_config_6_1_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_1=(*Pattern_check_6_1.find(Pattern_config_6_1)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0-2]==11)
        {
            neighbors[ctr].temp_6_2.x3++;
            Pattern_config_6_2_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_2=(*Pattern_check_6_2.find(Pattern_config_6_2)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0-2]==12)
        {
            neighbors[ctr].temp_6_2.x4++;
            Pattern_config_6_2_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_2=(*Pattern_check_6_2.find(Pattern_config_6_2)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0-2]==13)
        {
            neighbors[ctr].temp_6_1.x6++;
            Pattern_config_6_1_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_1=(*Pattern_check_6_1.find(Pattern_config_6_1)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0-2]==14)
        {
            neighbors[ctr].temp_6_2.x5++;
            Pattern_config_6_2_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_2=(*Pattern_check_6_2.find(Pattern_config_6_2)).second;
        }
        else
        {
            neighbors[ctr].temp_6_2.x6++;
            Pattern_config_6_2_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_2=(*Pattern_check_6_2.find(Pattern_config_6_2)).second;
        }
        neighbors[ctr].h=neighbors[ctr].p_6_1+neighbors[ctr].p_6_2+neighbors[ctr].p_3;
        ctr++;
    }
    if(temp_Node->y0+1<=N&&temp_Node->from!='U')                                  //Space->Down Move=Up
    {
        neighbors.push_back(*temp_Node);
        neighbors[ctr].from='D';
        neighbors[ctr].y0++;
        neighbors[ctr].Grid[temp_Node->y0-1][temp_Node->x0-1]=neighbors[ctr].Grid[temp_Node->y0][temp_Node->x0-1];
        neighbors[ctr].Grid[temp_Node->y0][temp_Node->x0-1]=0;
        if(temp_Node->Grid[temp_Node->y0][temp_Node->x0-1]==1)
        {
            neighbors[ctr].temp_6_1.y1--;
            Pattern_config_6_1_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_1=(*Pattern_check_6_1.find(Pattern_config_6_1)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0][temp_Node->x0-1]==2)
        {
            neighbors[ctr].temp_3.y1--;
            Pattern_config_3_calc(&neighbors[ctr]);
            neighbors[ctr].p_3=(*Pattern_check_3.find(Pattern_config_3)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0][temp_Node->x0-1]==3)
        {
            neighbors[ctr].temp_3.y2--;
            Pattern_config_3_calc(&neighbors[ctr]);
            neighbors[ctr].p_3=(*Pattern_check_3.find(Pattern_config_3)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0][temp_Node->x0-1]==4)
        {
            neighbors[ctr].temp_3.y3--;
            Pattern_config_3_calc(&neighbors[ctr]);
            neighbors[ctr].p_3=(*Pattern_check_3.find(Pattern_config_3)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0][temp_Node->x0-1]==5)
        {
            neighbors[ctr].temp_6_1.y2--;
            Pattern_config_6_1_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_1=(*Pattern_check_6_1.find(Pattern_config_6_1)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0][temp_Node->x0-1]==6)
        {
            neighbors[ctr].temp_6_1.y3--;
            Pattern_config_6_1_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_1=(*Pattern_check_6_1.find(Pattern_config_6_1)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0][temp_Node->x0-1]==7)
        {
            neighbors[ctr].temp_6_2.y1--;
            Pattern_config_6_2_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_2=(*Pattern_check_6_2.find(Pattern_config_6_2)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0][temp_Node->x0-1]==8)
        {
            neighbors[ctr].temp_6_2.y2--;
            Pattern_config_6_2_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_2=(*Pattern_check_6_2.find(Pattern_config_6_2)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0][temp_Node->x0-1]==9)
        {
            neighbors[ctr].temp_6_1.y4--;
            Pattern_config_6_1_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_1=(*Pattern_check_6_1.find(Pattern_config_6_1)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0][temp_Node->x0-1]==10)
        {
            neighbors[ctr].temp_6_1.y5--;
            Pattern_config_6_1_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_1=(*Pattern_check_6_1.find(Pattern_config_6_1)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0][temp_Node->x0-1]==11)
        {
            neighbors[ctr].temp_6_2.y3--;
            Pattern_config_6_2_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_2=(*Pattern_check_6_2.find(Pattern_config_6_2)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0][temp_Node->x0-1]==12)
        {
            neighbors[ctr].temp_6_2.y4--;
            Pattern_config_6_2_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_2=(*Pattern_check_6_2.find(Pattern_config_6_2)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0][temp_Node->x0-1]==13)
        {
            neighbors[ctr].temp_6_1.y6--;
            Pattern_config_6_1_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_1=(*Pattern_check_6_1.find(Pattern_config_6_1)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0][temp_Node->x0-1]==14)
        {
            neighbors[ctr].temp_6_2.y5--;
            Pattern_config_6_2_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_2=(*Pattern_check_6_2.find(Pattern_config_6_2)).second;
        }
        else
        {
            neighbors[ctr].temp_6_2.y6--;
            Pattern_config_6_2_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_2=(*Pattern_check_6_2.find(Pattern_config_6_2)).second;
        }
        neighbors[ctr].h=neighbors[ctr].p_6_1+neighbors[ctr].p_6_2+neighbors[ctr].p_3;
        ctr++;
    }
    if(temp_Node->y0-1>0&&temp_Node->from!='D')                                   //Space->Up  Move=Down
    {
        neighbors.push_back(*temp_Node);
        neighbors[ctr].from='U';
        neighbors[ctr].y0--;
        neighbors[ctr].Grid[temp_Node->y0-1][temp_Node->x0-1]=neighbors[ctr].Grid[temp_Node->y0-2][temp_Node->x0-1];
        neighbors[ctr].Grid[temp_Node->y0-2][temp_Node->x0-1]=0;
        if(temp_Node->Grid[temp_Node->y0-2][temp_Node->x0-1]==1)
        {
            neighbors[ctr].temp_6_1.y1++;
            Pattern_config_6_1_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_1=(*Pattern_check_6_1.find(Pattern_config_6_1)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-2][temp_Node->x0-1]==2)
        {
            neighbors[ctr].temp_3.y1++;
            Pattern_config_3_calc(&neighbors[ctr]);
            neighbors[ctr].p_3=(*Pattern_check_3.find(Pattern_config_3)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-2][temp_Node->x0-1]==3)
        {
            neighbors[ctr].temp_3.y2++;
            Pattern_config_3_calc(&neighbors[ctr]);
            neighbors[ctr].p_3=(*Pattern_check_3.find(Pattern_config_3)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-2][temp_Node->x0-1]==4)
        {
            neighbors[ctr].temp_3.y3++;
            Pattern_config_3_calc(&neighbors[ctr]);
            neighbors[ctr].p_3=(*Pattern_check_3.find(Pattern_config_3)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-2][temp_Node->x0-1]==5)
        {
            neighbors[ctr].temp_6_1.y2++;
            Pattern_config_6_1_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_1=(*Pattern_check_6_1.find(Pattern_config_6_1)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-2][temp_Node->x0-1]==6)
        {
            neighbors[ctr].temp_6_1.y3++;
            Pattern_config_6_1_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_1=(*Pattern_check_6_1.find(Pattern_config_6_1)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-2][temp_Node->x0-1]==7)
        {
            neighbors[ctr].temp_6_2.y1++;
            Pattern_config_6_2_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_2=(*Pattern_check_6_2.find(Pattern_config_6_2)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-2][temp_Node->x0-1]==8)
        {
            neighbors[ctr].temp_6_2.y2++;
            Pattern_config_6_2_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_2=(*Pattern_check_6_2.find(Pattern_config_6_2)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-2][temp_Node->x0-1]==9)
        {
            neighbors[ctr].temp_6_1.y4++;
            Pattern_config_6_1_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_1=(*Pattern_check_6_1.find(Pattern_config_6_1)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-2][temp_Node->x0-1]==10)
        {
            neighbors[ctr].temp_6_1.y5++;
            Pattern_config_6_1_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_1=(*Pattern_check_6_1.find(Pattern_config_6_1)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-2][temp_Node->x0-1]==11)
        {
            neighbors[ctr].temp_6_2.y3++;
            Pattern_config_6_2_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_2=(*Pattern_check_6_2.find(Pattern_config_6_2)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-2][temp_Node->x0-1]==12)
        {
            neighbors[ctr].temp_6_2.y4++;
            Pattern_config_6_2_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_2=(*Pattern_check_6_2.find(Pattern_config_6_2)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-2][temp_Node->x0-1]==13)
        {
            neighbors[ctr].temp_6_1.y6++;
            Pattern_config_6_1_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_1=(*Pattern_check_6_1.find(Pattern_config_6_1)).second;
        }
        else if(temp_Node->Grid[temp_Node->y0-2][temp_Node->x0-1]==14)
        {
            neighbors[ctr].temp_6_2.y5++;
            Pattern_config_6_2_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_2=(*Pattern_check_6_2.find(Pattern_config_6_2)).second;
        }
        else
        {
            neighbors[ctr].temp_6_2.y6++;
            Pattern_config_6_2_calc(&neighbors[ctr]);
            neighbors[ctr].p_6_2=(*Pattern_check_6_2.find(Pattern_config_6_2)).second;
        }
        neighbors[ctr].h=neighbors[ctr].p_6_1+neighbors[ctr].p_6_2+neighbors[ctr].p_3;
    }
    return neighbors;
}
int searching(Node* node,int g)
{
    int f,t;
    f=g+node->h;
    if(f>threshhold||found==true)
        return f;
    if(node->h==0)
    {
        tEnd=clock()-tStart;
        if(node->from=='L')
            path.push('R');
        if(node->from=='R')
            path.push('L');
        if(node->from=='U')
            path.push('D');
        if(node->from=='D')
            path.push('U');
        found=true;
        cout<<"Moves required:\t"<<g<<endl;
        return 0;
    }
    int minimum=INT_MAX;
    for(auto &neighbor:Neighbors(node))
    {
        t=searching(&neighbor,g+1);
        if(t<minimum)
            minimum=t;
    }
    if(found==true)
    {
        if(node->from=='L')
            path.push('R');
        if(node->from=='R')
            path.push('L');
        if(node->from=='U')
            path.push('D');
        if(node->from=='D')
            path.push('U');
    }
    return minimum;
}
Idastar()
{
    tStart=clock();
    while(1)
    {
        if(found==true)
            break;
        int t;
        t=searching(&Start,0);
        threshhold=t;
        /*if(clock()-(double)tStart/CLOCKS_PER_SEC>10000)
        {
            cout<<"Time limit exceeded";
            exit(0);
        }*/
    }
}
int main()
{
    int cost;
    ifstream in_6_1("Pattern_6_1.db",ios::binary);
    ifstream in_6_2("Pattern_6_2.db",ios::binary);
    ifstream in_3("Pattern_3.db",ios::binary);
    while(in_6_1.peek()!=EOF)
    {
        in_6_1.read((char*)&Pattern_config_6_1,sizeof(Pattern_config_6_1));
        in_6_1.read((char*)&cost,sizeof(cost));
        Pattern_check_6_1.insert(make_pair(Pattern_config_6_1,cost));
    }
    in_6_1.close();
    while(in_6_2.peek()!=EOF)
    {
        in_6_2.read((char*)&Pattern_config_6_2,sizeof(Pattern_config_6_2));
        in_6_2.read((char*)&cost,sizeof(cost));
        Pattern_check_6_2.insert(make_pair(Pattern_config_6_2,cost));
    }
    in_6_2.close();
    while(in_3.peek()!=EOF)
    {
        in_3.read((char*)&Pattern_config_3,sizeof(Pattern_config_3));
        in_3.read((char*)&cost,sizeof(cost));
        Pattern_check_3.insert(make_pair(Pattern_config_3,cost));
    }
    in_3.close();
    tStart=clock();
    for(int i=0;i<N;i++)                                                        //Start Recognition and filling 'Start' members.
    {
        for(int j=0;j<N;j++)
        {
            if(grid[i][j]==0)
            {
                Start.x0=j+1;
                Start.y0=i+1;
            }
            else if(grid[i][j]==1)
            {
                Start.temp_6_1.x1=j+1;
                Start.temp_6_1.y1=i+1;
            }
            else if(grid[i][j]==2)
            {
                Start.temp_3.x1=j+1;
                Start.temp_3.y1=i+1;
            }
            else if(grid[i][j]==3)
            {
                Start.temp_3.x2=j+1;
                Start.temp_3.y2=i+1;
            }
            else if(grid[i][j]==4)
            {
                Start.temp_3.x3=j+1;
                Start.temp_3.y3=i+1;
            }
            else if(grid[i][j]==5)
            {
                Start.temp_6_1.x2=j+1;
                Start.temp_6_1.y2=i+1;
            }
            else if(grid[i][j]==6)
            {
                Start.temp_6_1.x3=j+1;
                Start.temp_6_1.y3=i+1;
            }
            else if(grid[i][j]==7)
            {
                Start.temp_6_2.x1=j+1;
                Start.temp_6_2.y1=i+1;
            }
            else if(grid[i][j]==8)
            {
                Start.temp_6_2.x2=j+1;
                Start.temp_6_2.y2=i+1;
            }
            if(grid[i][j]==9)
            {
                Start.temp_6_1.x4=j+1;
                Start.temp_6_1.y4=i+1;
            }
            else if(grid[i][j]==10)
            {
                Start.temp_6_1.x5=j+1;
                Start.temp_6_1.y5=i+1;
            }
            else if(grid[i][j]==11)
            {
                Start.temp_6_2.x3=j+1;
                Start.temp_6_2.y3=i+1;
            }
            else if(grid[i][j]==12)
            {
                Start.temp_6_2.x4=j+1;
                Start.temp_6_2.y4=i+1;
            }
            else if(grid[i][j]==13)
            {
                Start.temp_6_1.x6=j+1;
                Start.temp_6_1.y6=i+1;
            }
            else if(grid[i][j]==14)
            {
                Start.temp_6_2.x5=j+1;
                Start.temp_6_2.y5=i+1;
            }
            else if(grid[i][j]==15)
            {
                Start.temp_6_2.x6=j+1;
                Start.temp_6_2.y6=i+1;
            }
            Start.Grid[i][j]=grid[i][j];
        }
    }
    cout<<"Pattern database loaded"<<endl;
    Pattern_config_6_1_calc(&Start);
    Pattern_config_6_2_calc(&Start);
    Pattern_config_3_calc(&Start);
    Start.p_6_1=(*Pattern_check_6_1.find(Pattern_config_6_1)).second;
    Start.p_6_2=(*Pattern_check_6_2.find(Pattern_config_6_2)).second;
    Start.p_3=(*Pattern_check_3.find(Pattern_config_3)).second;
    Start.h=Start.p_6_1+Start.p_6_2+Start.p_3;
    threshhold=Start.h;
    Idastar();
    showmoves();
    cout<<"Time  Taken:\t"<<(double)tEnd/CLOCKS_PER_SEC<<endl;
}
