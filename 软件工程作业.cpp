#include<stdio.h>
#include<stdlib.h>
using namespace std;
#include<iostream>
#define MAX 32767//定义最大值。

//对于输入的邻接矩阵，当两个点之间存在路径，输入路径权值，当两个点之间不存在路径，输入MAX，当点是该点本身，输入0。 

typedef struct Graph{
	char *vexs;
	int **arcs;
	int vexNum;
	int arcNum;
}Graph;

typedef struct Edge{
	char vex;
	int weight;
}Edge;



Edge* InitEdge(Graph *G,int index)//初始化U集合 
{
	Edge* edge=(Edge*)malloc(sizeof(Edge)*G->vexNum);//分配空间 
	for (int i=0;i< G->vexNum;i++)
	{
        edge[i].vex = G->vexs[index]; 
        edge[i].weight = G->arcs[index][i];
    }
    return edge;
} 

int getMinEdge(Edge* edge,Graph *G)//得到Edge中权值最小的边 
{
    int index;
    int min=MAX;
    for (int i=0;i<G->vexNum;i++) 
	{
        if (edge[i].weight!=0&&min>edge[i].weight) 
		{
            min=edge[i].weight;
            index=i;
        }
    }
    return index;
}

void prim(Graph *G,int index)
{
	int min;
	Edge *edge=InitEdge(G,index);
	for(int i=0;i<G->vexNum-1;i++)//已经加入一个顶点，只需要检索n-1次即可 
	{
		min=getMinEdge(edge,G);
		printf("V%c --> V%c,weight=%d\n",edge[min].vex,G->vexs[min],edge[min].weight);
		edge[min].weight=0;	//将已经选用的点放入集合U中 
		for(int j=0;j<G->vexNum;j++)//更新下一个点 
		{
			if(G->arcs[min][j]<edge[j].weight)
			{
				edge[j].weight=G->arcs[min][j];
				edge[j].vex=G->vexs[min];
			}
		}
	}
}
Graph *InitGraph(int vexNum)//对传入顶点个数相应的初始化一个图 。 
{
	Graph* G=(Graph*)malloc(sizeof(Graph)); 
	G->vexs=(char*)malloc(sizeof(char)*vexNum);
	G->arcs=(int**)malloc(sizeof(int*)*vexNum); 
	for(int i=0;i< vexNum;i++){
		G->arcs[i]=(int*)malloc(sizeof(int)*vexNum); 
	} //为二维数组开辟空间，采用二级指针。
	G->vexNum=vexNum;
	G->arcNum=0;
	return G; 
}

void creat(Graph *G,char *vexs,int *arcs)//创建图的函数 
{
	for(int i=0;i<G->vexNum;i++)
	{
		G->vexs[i]=vexs[i];
		for(int j=0;j<G->vexNum;j++)
		{
			G->arcs[i][j]=*(arcs+i*G->vexNum+j);//此处将输入的一维数组转化为二维数组。
			if(G->arcs[i][j]!=0 && G->arcs[i][j] != MAX)
			{
				G->arcNum++;
			}
		}
	}
	 G -> arcNum /= 2;//无向图的边数需要将顶点数除2 
} 

void DFS(Graph *G,int *visited,int index)
{
	printf("%c ",G->vexs[index]);
	visited[index]=1;
	for(int i=0;i<G->vexNum;i++)
	{
		if( G->arcs[index][i] >0 && G->arcs[index][i] != MAX && !visited[i] ){
			DFS(G,visited,i);
		}
	}
	
	
}

int main()
{
	cout<<"欢迎使用本程序校区建设方案，请按要求输入以下各步骤，最后输出结果为最省成本的新校区建设方案"<<endl;
	cout<<endl; 
	int vexNum;
	
	cout<<"请输入校区建筑总数"<<endl;
	
	scanf("%d",&vexNum);
	
	Graph *G=InitGraph(vexNum);
	


	int *visited=(int *)malloc(sizeof(int)*vexNum);//定义一个数组标记已经访问过的节点 
	for(int i=0;i<G->vexNum;i++)
	{
		visited[i]=0;
	}
	
	cout<<endl<<"请输入校区内所有建筑的名称"<<endl;//输入校区的名称 
	char *vexs=(char*)malloc(sizeof(char)*G->vexNum); //初始化 
	scanf("%s",vexs);
	
	cout<<endl<<"请输入校区内建筑对应的邻接矩阵，若两个建筑之间连通，则输入对应的道路建设成本，建筑与建筑本身输入0"<<endl;//输入相对应的邻接矩阵 
	int arcs[vexNum][vexNum];//定义一个二维数组 
	for(int i=0;i<G->vexNum;i++)
	{
		for(int j=0;j<G->vexNum;j++)
		{
			scanf("%d",&arcs[i][j]);
		}
	}
	
	creat(G,(char*)vexs,(int*)arcs);
		
	int index1;//定义深度优先遍历起点 
	int index2;//定义最小生成树起点 
	
	cout<<endl<<"请输入深度优先遍历的起始点"<<endl; 
	cin>>index1;
	cout<<"深度优先遍历的结果为："<<endl;  
	DFS(G,visited,index1);//深度优先遍历 
	cout<<endl;
	
	cout<<endl<<"请输入最小生成树的起始点"<<endl; 
	cin>>index2;
	cout<<endl<<"最终经过prim算法得到的最佳建设方案为："<<endl; 
	prim(G,index2);//prim算法求除最小生成树 
	
	
	return 0;
}


