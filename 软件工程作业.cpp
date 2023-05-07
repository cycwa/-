#include<stdio.h>
#include<stdlib.h>
using namespace std;
#include<iostream>
#define MAX 32767//�������ֵ��

//����������ڽӾ��󣬵�������֮�����·��������·��Ȩֵ����������֮�䲻����·��������MAX�������Ǹõ㱾������0�� 

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



Edge* InitEdge(Graph *G,int index)//��ʼ��U���� 
{
	Edge* edge=(Edge*)malloc(sizeof(Edge)*G->vexNum);//����ռ� 
	for (int i=0;i< G->vexNum;i++)
	{
        edge[i].vex = G->vexs[index]; 
        edge[i].weight = G->arcs[index][i];
    }
    return edge;
} 

int getMinEdge(Edge* edge,Graph *G)//�õ�Edge��Ȩֵ��С�ı� 
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
	for(int i=0;i<G->vexNum-1;i++)//�Ѿ�����һ�����㣬ֻ��Ҫ����n-1�μ��� 
	{
		min=getMinEdge(edge,G);
		printf("V%c --> V%c,weight=%d\n",edge[min].vex,G->vexs[min],edge[min].weight);
		edge[min].weight=0;	//���Ѿ�ѡ�õĵ���뼯��U�� 
		for(int j=0;j<G->vexNum;j++)//������һ���� 
		{
			if(G->arcs[min][j]<edge[j].weight)
			{
				edge[j].weight=G->arcs[min][j];
				edge[j].vex=G->vexs[min];
			}
		}
	}
}
Graph *InitGraph(int vexNum)//�Դ��붥�������Ӧ�ĳ�ʼ��һ��ͼ �� 
{
	Graph* G=(Graph*)malloc(sizeof(Graph)); 
	G->vexs=(char*)malloc(sizeof(char)*vexNum);
	G->arcs=(int**)malloc(sizeof(int*)*vexNum); 
	for(int i=0;i< vexNum;i++){
		G->arcs[i]=(int*)malloc(sizeof(int)*vexNum); 
	} //Ϊ��ά���鿪�ٿռ䣬���ö���ָ�롣
	G->vexNum=vexNum;
	G->arcNum=0;
	return G; 
}

void creat(Graph *G,char *vexs,int *arcs)//����ͼ�ĺ��� 
{
	for(int i=0;i<G->vexNum;i++)
	{
		G->vexs[i]=vexs[i];
		for(int j=0;j<G->vexNum;j++)
		{
			G->arcs[i][j]=*(arcs+i*G->vexNum+j);//�˴��������һά����ת��Ϊ��ά���顣
			if(G->arcs[i][j]!=0 && G->arcs[i][j] != MAX)
			{
				G->arcNum++;
			}
		}
	}
	 G -> arcNum /= 2;//����ͼ�ı�����Ҫ����������2 
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
	cout<<"��ӭʹ�ñ�����У�����跽�����밴Ҫ���������¸����裬���������Ϊ��ʡ�ɱ�����У�����跽��"<<endl;
	cout<<endl; 
	int vexNum;
	
	cout<<"������У����������"<<endl;
	
	scanf("%d",&vexNum);
	
	Graph *G=InitGraph(vexNum);
	


	int *visited=(int *)malloc(sizeof(int)*vexNum);//����һ���������Ѿ����ʹ��Ľڵ� 
	for(int i=0;i<G->vexNum;i++)
	{
		visited[i]=0;
	}
	
	cout<<endl<<"������У�������н���������"<<endl;//����У�������� 
	char *vexs=(char*)malloc(sizeof(char)*G->vexNum); //��ʼ�� 
	scanf("%s",vexs);
	
	cout<<endl<<"������У���ڽ�����Ӧ���ڽӾ�������������֮����ͨ���������Ӧ�ĵ�·����ɱ��������뽨����������0"<<endl;//�������Ӧ���ڽӾ��� 
	int arcs[vexNum][vexNum];//����һ����ά���� 
	for(int i=0;i<G->vexNum;i++)
	{
		for(int j=0;j<G->vexNum;j++)
		{
			scanf("%d",&arcs[i][j]);
		}
	}
	
	creat(G,(char*)vexs,(int*)arcs);
		
	int index1;//����������ȱ������ 
	int index2;//������С��������� 
	
	cout<<endl<<"������������ȱ�������ʼ��"<<endl; 
	cin>>index1;
	cout<<"������ȱ����Ľ��Ϊ��"<<endl;  
	DFS(G,visited,index1);//������ȱ��� 
	cout<<endl;
	
	cout<<endl<<"��������С����������ʼ��"<<endl; 
	cin>>index2;
	cout<<endl<<"���վ���prim�㷨�õ�����ѽ��跽��Ϊ��"<<endl; 
	prim(G,index2);//prim�㷨�����С������ 
	
	
	return 0;
}


