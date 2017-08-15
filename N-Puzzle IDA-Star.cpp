#include<iostream>
#include<math.h>
#include<vector>
#include<time.h>
#include<stack>
#define N 4
using namespace std;
int grid[N][N]=  {{10,11,6,12},                                    //65 Moves
                 {15,13,0,9},
                 {8,14,2,3},
                 {7,4,1,5}};
/*int grid[N][N]={{2,8,7,11},                                            //42 Moves
                 {5,0,4,15},
                 {13,9,14,3},
                 {1,10,6,12}};*/
struct Node                                                         //Basic Node
{
    char from;
    int Grid[N][N],x0,y0,manhattan_h,h;
    Node(int x=0,int y=0,char direction='X')
    {
        x0=x;
        y0=y;
        from=direction;
    }
}Start;
int i,j,threshhold,linear_horizontal_conflicts=0,linear_vertical_conflicts=0,maxi,maxj,original_h,exchanged_h,global_g;
clock_t tStart,tEnd;
bool found=false;
stack<char> path;
showmoves()
{
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
vector<Node> Neighbors(Node* temp_Node)                                                        //Uses Manhattan Heuristics and linear conflict
{
    int ctr=0;
    vector<Node> neighbors;
    linear_horizontal_conflicts=0;linear_vertical_conflicts=0;
    if(temp_Node->x0+1<=N&&temp_Node->from!='L')                                  //Space->Right, Move=Left;
    {
        neighbors.push_back(Node(temp_Node->x0+1,temp_Node->y0,'R'));
        for(i=0;i<N;i++)
        {
            maxi=-1;
            maxj=-1;
            for(j=0;j<N;j++)
            {
                if(i==temp_Node->y0-1&&j==temp_Node->x0-1)
                    neighbors[ctr].Grid[i][j]=temp_Node->Grid[i][j+1];
                else if(i==temp_Node->y0-1&&j==temp_Node->x0)
                    neighbors[ctr].Grid[i][j]=temp_Node->Grid[i][j-1];
                else
                    neighbors[ctr].Grid[i][j]=temp_Node->Grid[i][j];
                if((i==temp_Node->y0-1&&j==temp_Node->x0-1))
                {
                    if(temp_Node->Grid[i][j+1]!=0&&(temp_Node->Grid[i][j+1]-1)/N==i)
                        if(temp_Node->Grid[i][j+1]>maxi)
                            maxi=temp_Node->Grid[i][j+1];
                        else
                            linear_horizontal_conflicts++;
                }
                else if(i==temp_Node->y0-1&&j==temp_Node->x0)
                {
                    if(temp_Node->Grid[i][j-1]!=0&&(temp_Node->Grid[i][j-1]-1)/N==i)
                        if(temp_Node->Grid[i][j-1]>maxi)
                            maxi=temp_Node->Grid[i][j-1];
                         else
                            linear_horizontal_conflicts++;
                }
                else
                {
                    if(temp_Node->Grid[i][j]!=0&&(temp_Node->Grid[i][j]-1)/N==i)
                        if(temp_Node->Grid[i][j]>maxi)
                            maxi=temp_Node->Grid[i][j];
                        else
                            linear_horizontal_conflicts++;
                }
                if((j==temp_Node->y0-1&&i==temp_Node->x0-1))
                {
                    if(temp_Node->Grid[j][i+1]!=0&&(temp_Node->Grid[j][i+1]-1)%N==i)
                        if(temp_Node->Grid[j][i+1]>maxj)
                            maxj=temp_Node->Grid[j][i+1];
                        else
                            linear_vertical_conflicts++;
                }
                else if(j==temp_Node->y0-1&&i==temp_Node->x0)
                {
                    if(temp_Node->Grid[j][i-1]!=0&&(temp_Node->Grid[j][i-1]-1)%N==i)
                        if(temp_Node->Grid[j][i-1]>maxj)
                            maxj=temp_Node->Grid[j][i-1];
                        else
                            linear_vertical_conflicts++;
                }
                else
                    if(temp_Node->Grid[j][i]!=0&&(temp_Node->Grid[j][i]-1)%N==i)
                        if(temp_Node->Grid[j][i]>maxj)
                            maxj=temp_Node->Grid[j][i];
                        else
                            linear_vertical_conflicts++;
            }
        }
        original_h=abs(temp_Node->y0-1-(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0]-1)/N)+abs(temp_Node->x0-(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0]-1)%N);
        exchanged_h=+abs(temp_Node->y0-1-(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0]-1)/N)+abs(temp_Node->x0-1-(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0]-1)%N);
        neighbors[ctr].manhattan_h=temp_Node->manhattan_h+exchanged_h-original_h;
        neighbors[ctr].h=neighbors[ctr].manhattan_h+2*linear_vertical_conflicts+2*linear_horizontal_conflicts;
        ctr++;
    }
    if(temp_Node->x0-1>0&&temp_Node->from!='R')                                  //Space->Left, Move=Right;
    {
        linear_horizontal_conflicts=0;linear_vertical_conflicts=0;
        neighbors.push_back(Node(temp_Node->x0-1,temp_Node->y0,'L'));
        for(i=0;i<N;i++)
        {
            maxi=-1;
            maxj=-1;
            for(j=0;j<N;j++)
            {
                if(i==temp_Node->y0-1&&j==temp_Node->x0-1)
                    neighbors[ctr].Grid[i][j]=temp_Node->Grid[i][j-1];
                else if(i==temp_Node->y0-1&&j==temp_Node->x0-2)
                    neighbors[ctr].Grid[i][j]=temp_Node->Grid[i][j+1];
                else
                    neighbors[ctr].Grid[i][j]=temp_Node->Grid[i][j];
                if((i==temp_Node->y0-1&&j==temp_Node->x0-1))
                {
                    if(temp_Node->Grid[i][j-1]!=0&&(temp_Node->Grid[i][j-1]-1)/N==i)
                        if(temp_Node->Grid[i][j-1]>maxi)
                            maxi=temp_Node->Grid[i][j-1];
                        else
                            linear_horizontal_conflicts++;
                }
                else if(i==temp_Node->y0-1&&j==temp_Node->x0-2)
                {
                    if(temp_Node->Grid[i][j+1]!=0&&(temp_Node->Grid[i][j+1]-1)/N==i)
                        if(temp_Node->Grid[i][j+1]>maxi)
                            maxi=temp_Node->Grid[i][j+1];
                         else
                            linear_horizontal_conflicts++;
                }
                else
                {
                    if(temp_Node->Grid[i][j]!=0&&(temp_Node->Grid[i][j]-1)/N==i)
                        if(temp_Node->Grid[i][j]>maxi)
                            maxi=temp_Node->Grid[i][j];
                        else
                            linear_horizontal_conflicts++;
                }
                if((j==temp_Node->y0-1&&i==temp_Node->x0-1))
                {
                    if(temp_Node->Grid[j][i-1]!=0&&(temp_Node->Grid[j][i-1]-1)%N==i)
                        if(temp_Node->Grid[j][i-1]>maxj)
                            maxj=temp_Node->Grid[j][i-1];
                        else
                            linear_vertical_conflicts++;
                }
                else if(j==temp_Node->y0-1&&i==temp_Node->x0-2)
                {
                    if(temp_Node->Grid[j][i+1]!=0&&(temp_Node->Grid[j][i+1]-1)%N==i)
                        if(temp_Node->Grid[j][i+1]>maxj)
                            maxj=temp_Node->Grid[j][i+1];
                        else
                            linear_vertical_conflicts++;
                }
                else
                    if(temp_Node->Grid[j][i]!=0&&(temp_Node->Grid[j][i]-1)%N==i)
                        if(temp_Node->Grid[j][i]>maxj)
                            maxj=temp_Node->Grid[j][i];
                        else
                            linear_vertical_conflicts++;
            }
        }
        original_h=abs(temp_Node->y0-1-(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0-2]-1)/N)+abs(temp_Node->x0-2-(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0-2]-1)%N);
        exchanged_h=abs(temp_Node->y0-1-(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0-2]-1)/N)+abs(temp_Node->x0-1-(temp_Node->Grid[temp_Node->y0-1][temp_Node->x0-2]-1)%N);
        neighbors[ctr].manhattan_h=temp_Node->manhattan_h+exchanged_h-original_h;
        neighbors[ctr].h=neighbors[ctr].manhattan_h+2*linear_vertical_conflicts+2*linear_horizontal_conflicts;
        ctr++;
    }
    if(temp_Node->y0+1<=N&&temp_Node->from!='U')                                  //Space->Down Move=Up
    {
        linear_horizontal_conflicts=0;linear_vertical_conflicts=0;
        neighbors.push_back(Node(temp_Node->x0,temp_Node->y0+1,'D'));
        for(i=0;i<N;i++)
        {
            maxi=-1;
            maxj=-1;
            for(j=0;j<N;j++)
            {
                if(i==temp_Node->y0-1&&j==temp_Node->x0-1)
                    neighbors[ctr].Grid[i][j]=temp_Node->Grid[i+1][j];
                else if(i==temp_Node->y0&&j==temp_Node->x0-1)
                    neighbors[ctr].Grid[i][j]=temp_Node->Grid[i-1][j];
                else
                    neighbors[ctr].Grid[i][j]=temp_Node->Grid[i][j];
                if((i==temp_Node->y0-1&&j==temp_Node->x0-1))
                {
                    if(temp_Node->Grid[i+1][j]!=0&&(temp_Node->Grid[i+1][j]-1)/N==i)
                        if(temp_Node->Grid[i+1][j]>maxi)
                            maxi=temp_Node->Grid[i+1][j];
                        else
                            linear_horizontal_conflicts++;
                }
                else if(i==temp_Node->y0&&j==temp_Node->x0-1)
                {
                    if(temp_Node->Grid[i-1][j]!=0&&(temp_Node->Grid[i-1][j]-1)/N==i)
                        if(temp_Node->Grid[i-1][j]>maxi)
                            maxi=temp_Node->Grid[i-1][j];
                         else
                            linear_horizontal_conflicts++;
                }
                else
                {
                    if(temp_Node->Grid[i][j]!=0&&(temp_Node->Grid[i][j]-1)/N==i)
                        if(temp_Node->Grid[i][j]>maxi)
                            maxi=temp_Node->Grid[i][j];
                        else
                            linear_horizontal_conflicts++;
                }
                if((j==temp_Node->y0-1&&i==temp_Node->x0-1))
                {
                    if(temp_Node->Grid[j+1][i]!=0&&(temp_Node->Grid[j+1][i]-1)%N==i)
                        if(temp_Node->Grid[j+1][i]>maxj)
                            maxj=temp_Node->Grid[j+1][i];
                        else
                            linear_vertical_conflicts++;
                }
                else if(j==temp_Node->y0&&i==temp_Node->x0-1)
                {
                    if(temp_Node->Grid[j-1][i]!=0&&(temp_Node->Grid[j-1][i]-1)%N==i)
                        if(temp_Node->Grid[j-1][i]>maxj)
                            maxj=temp_Node->Grid[j-1][i];
                        else
                            linear_vertical_conflicts++;
                }
                else
                    if(temp_Node->Grid[j][i]!=0&&(temp_Node->Grid[j][i]-1)%N==i)
                        if(temp_Node->Grid[j][i]>maxj)
                            maxj=temp_Node->Grid[j][i];
                        else
                            linear_vertical_conflicts++;
            }
        }
        original_h=abs(temp_Node->y0-(temp_Node->Grid[temp_Node->y0][temp_Node->x0-1]-1)/N)+abs(temp_Node->x0-1-(temp_Node->Grid[temp_Node->y0][temp_Node->x0-1]-1)%N);
        exchanged_h=abs(temp_Node->y0-1-(temp_Node->Grid[temp_Node->y0][temp_Node->x0-1]-1)/N)+abs(temp_Node->x0-1-(temp_Node->Grid[temp_Node->y0][temp_Node->x0-1]-1)%N);
        neighbors[ctr].manhattan_h=temp_Node->manhattan_h+exchanged_h-original_h;
        neighbors[ctr].h=neighbors[ctr].manhattan_h+2*linear_vertical_conflicts+2*linear_horizontal_conflicts;
        ctr++;
    }
    if(temp_Node->y0-1>0&&temp_Node->from!='D')                                   //Space->Up  Move=Down
    {
        linear_horizontal_conflicts=0;linear_vertical_conflicts=0;
        neighbors.push_back(Node(temp_Node->x0,temp_Node->y0-1,'U'));
        for(i=0;i<N;i++)
        {
            maxi=-1;
            maxj=-1;
            for(j=0;j<N;j++)
            {
                if(i==temp_Node->y0-1&&j==temp_Node->x0-1)
                    neighbors[ctr].Grid[i][j]=temp_Node->Grid[i-1][j];
                else if(i==temp_Node->y0-2&&j==temp_Node->x0-1)
                    neighbors[ctr].Grid[i][j]=temp_Node->Grid[i+1][j];
                else
                   neighbors[ctr].Grid[i][j]=temp_Node->Grid[i][j];
                if((i==temp_Node->y0-1&&j==temp_Node->x0-1))
                {
                    if(temp_Node->Grid[i-1][j]!=0&&(temp_Node->Grid[i-1][j]-1)/N==i)
                        if(temp_Node->Grid[i-1][j]>maxi)
                            maxi=temp_Node->Grid[i-1][j];
                        else
                            linear_horizontal_conflicts++;
                }
                else if(i==temp_Node->y0-2&&j==temp_Node->x0-1)
                {
                    if(temp_Node->Grid[i+1][j]!=0&&(temp_Node->Grid[i+1][j]-1)/N==i)
                        if(temp_Node->Grid[i+1][j]>maxi)
                            maxi=temp_Node->Grid[i+1][j];
                         else
                            linear_horizontal_conflicts++;
                }
                else
                {
                    if(temp_Node->Grid[i][j]!=0&&(temp_Node->Grid[i][j]-1)/N==i)
                        if(temp_Node->Grid[i][j]>maxi)
                            maxi=temp_Node->Grid[i][j];
                        else
                            linear_horizontal_conflicts++;
                }
                if((j==temp_Node->y0-1&&i==temp_Node->x0-1))
                {
                    if(temp_Node->Grid[j-1][i]!=0&&(temp_Node->Grid[j-1][i]-1)%N==i)
                        if(temp_Node->Grid[j-1][i]>maxj)
                            maxj=temp_Node->Grid[j-1][i];
                        else
                            linear_vertical_conflicts++;
                }
                else if(j==temp_Node->y0-2&&i==temp_Node->x0-1)
                {
                    if(temp_Node->Grid[j+1][i]!=0&&(temp_Node->Grid[j+1][i]-1)%N==i)
                        if(temp_Node->Grid[j+1][i]>maxj)
                            maxj=temp_Node->Grid[j+1][i];
                        else
                            linear_vertical_conflicts++;
                }
                else
                    if(temp_Node->Grid[j][i]!=0&&(temp_Node->Grid[j][i]-1)%N==i)
                        if(temp_Node->Grid[j][i]>maxj)
                            maxj=temp_Node->Grid[j][i];
                        else
                            linear_vertical_conflicts++;

            }
        }
        original_h=abs(temp_Node->y0-2-(temp_Node->Grid[temp_Node->y0-2][temp_Node->x0-1]-1)/N)+abs(temp_Node->x0-1-(temp_Node->Grid[temp_Node->y0-2][temp_Node->x0-1]-1)%N);
        exchanged_h=abs(temp_Node->y0-1-(temp_Node->Grid[temp_Node->y0-2][temp_Node->x0-1]-1)/N)+abs(temp_Node->x0-1-(temp_Node->Grid[temp_Node->y0-2][temp_Node->x0-1]-1)%N);
        neighbors[ctr].manhattan_h=temp_Node->manhattan_h+exchanged_h-original_h;
        neighbors[ctr].h=neighbors[ctr].manhattan_h+2*linear_vertical_conflicts+2*linear_horizontal_conflicts;
    }
    return neighbors;
}
int searching(Node* node,int g)
{
    int f,t;
    f=g+node->h;
    if(f>threshhold||found==true)
        return f;
    if(g>global_g)
    {
        system("cls");
        cout<<"Moves:\t"<<g;
        global_g=g;
    }
    if(node->h==0)
    {
        tEnd=clock()-tStart;
        system("cls");
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
    for(i=0;i<N;i++)                                                        //Start Recognition and filling 'Start' members.
    {
        maxi=-1;
        maxj=-1;
        for(j=0;j<N;j++)
        {
            if(grid[i][j]!=0&&(grid[i][j]-1)/N==i)
                if(grid[i][j]>maxi)
                    maxi=grid[i][j];
                else
                    linear_horizontal_conflicts++;
            if(grid[j][i]!=0&&(grid[j][i]-1)%N==i)
                if(grid[j][i]>maxj)
                    maxj=grid[j][i];
                else
                    linear_vertical_conflicts++;
            if(grid[i][j]==0)
            {
                Start.x0=j+1;
                Start.y0=i+1;
            }
            else
                Start.manhattan_h+=abs(i-(grid[i][j]-1)/N)+abs(j-(grid[i][j]-1)%N);
            Start.Grid[i][j]=grid[i][j];
        }
    }
    Start.h+=Start.manhattan_h+2*linear_horizontal_conflicts+2*linear_vertical_conflicts;
    threshhold=Start.h;
    Idastar();
    showmoves();
    cout<<"Time  Taken:\t"<<(double)tEnd/CLOCKS_PER_SEC<<endl;
}
