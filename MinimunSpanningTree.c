#include <stdio.h>
#include <stdlib.h>


//인접 정점
typedef struct AdjVertex
{
	char aName;
	int weight;		//가중치
	struct AdjVertex* next;	//연결리스트
}AdjVertex;


//정점
typedef struct Vertex
{
	char vName;
	AdjVertex* aHead; 	//자신의 인접 정점을 가리킴 
	struct Vertex* next; 	//연결리스트
}Vertex;


//그래프
typedef struct 
{
	Vertex* vHead;		//그래프의 헤드가 정점의 연결리스트 관리
	int vCount;
}Graph;




//그래프 초기화 함수
void init(Graph *G)
{
	G->vHead = NULL;
	G->vCount = 0;
}

void makeVertex(Graph *G, char vName)
{
	vertex* v = (Vertex*)malloc(sizeof(Vertex));
	v->vName = vName;
	v->aHead = NULL;
	v->next = NULL;

	G->vCount++;

	Vertex *p = G->vHead;
	if(p==NULL)
		G->vHead = v;
	else
	{
		while(p->next != NULL)
			p = p-> next;	//가장 마지막에 추가하기
		p->next = v;
	}
}

void makeAdjVertex(Vertex* v, char aName, int w)
{
	AdjVertex* a = (AdjVertex*)malloc(sizeof(AdjVertex));
	a->aName= aName;
	a->weight = w;
	a->next = NULL;

	AdjVertex* p = v->aHead;
	if(p==NULL)
		G->aHead = a;
	else
	{
		while(p->next != NULL)
			p = p-> next;	
		p->next = a;
	}
}


Vertex* findVertex(Graph *G, char vName)
{
	Vertex* v = G->vHead;
	while(v->NAme != vName)
		v = v->next;
	
	return v;
}

void insertEdge(Graph *G, char v1, char v2, int w)
{
	//v1
	Vertex *v = findVertex(G, v1);
	makeAdjVertex(v, v2, w);

	//v2
	v = findVertex(G, v2);
	makeAdjVertex(v, v1, w);

}


void print(Graph* G)
{
	Vertex* p;
	AdjVertex* q;
	
	for(p = G->vHead; p!=NULL; p=p->next)
	{
		printf("[%c]: ", p->vName);
		for(q = p->aHead; q!=NULL; q=q->next)
			printf("[%c: %2d]: ", q->aName, q->weight);		
		printf("\n")
	}
	printf("\n")
}


int main()
{
	Graph G;
	init(&G);

	makeVertex(&G, 'a'); makeVertex(&G, 'b'); makeVertex(&G, 'c');
	makeVertex(&G, 'd'); makeVertex(&G, 'e'); makeVertex(&G, 'f');
	makeVertex(&G, 'g'); makeVertex(&G, 'h'); makeVertex(&G, 'i');

	insertEdge(%G, 'a', 'b',4); insertEdge(%G, 'a', 'h',8);
	insertEdge(%G, 'b', 'c',8); insertEdge(%G, 'b', 'h',11);
	insertEdge(%G, 'c', 'd',7); insertEdge(%G, 'c', 'f',4);
	insertEdge(%G, 'c', 'i',2); insertEdge(%G, 'd', 'e',9);
	insertEdge(%G, 'd', 'f',14); insertEdge(%G, 'e', 'f',10);
	insertEdge(%G, 'f', 'g',2); insertEdge(%G, 'g', 'h',1);
	insertEdge(%G, 'g', 'i',6); insertEdge(%G, 'h', 'i',7);

	print(&G);
	
	return 0;
}

