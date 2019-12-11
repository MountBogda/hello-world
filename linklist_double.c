#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define NodeLen sizeof(struct tagNode)

typedef struct tagNode
{
    int val;
    struct tagNode *lLink,*rLink;
} Node;

int listLen;

Node *create()
{
    Node *pHead;
    Node *pTail;
    Node *pNew;
    int nodeVal;

    pHead = (Node *)malloc(NodeLen);
    if (pHead == NULL)
    {
        printf("head Node create failed!\n");
        exit(-1); //exit whole progarm, return to OS.
    }
    pTail = pHead;
    pTail->rLink = NULL;

    printf("input list length:");
    scanf("%d", &listLen);

    for (int i = 0; i < listLen; i++)
    {
        pNew = (Node *)malloc(NodeLen);
        if (pNew == NULL)
        {
            printf("new Node create failed!\n");
            exit(-1);
        }
        printf("node %d data:", i);
        scanf("%d", &nodeVal);

        pNew->val = nodeVal;
        pTail->rLink = pNew;
		pNew->lLink = pTail;
        pNew->rLink = NULL;
        pTail = pNew; //pTail updated for next new Node.
    }

    printf("create linklist length %d.\n", listLen);
    return pHead;
}
void print(const Node *pHead)
{
    Node *pTmp;
    Node *pNew;
    pTmp = pHead;
    int len = 0; //linklist length

    printf("pHead: %x ", pHead);
    printf("pHead next: %x\n", pHead->rLink);
    //case1: len=0,no print; case2: len=1,print once.
    while (pTmp->rLink != NULL)//pTmp = pHead
    {
        pTmp = pTmp->rLink;
        printf("node %d value: %d ", len, pTmp->val);
        printf("pTmp: %x ", pTmp);
        printf("pTmp next: %x\n", pTmp->rLink);
        len++;
    }
    printf("print linklist length: %d.\n", len);
}

Node *insert(Node *pHead, int ist_num)
{
    Node *pNew;
    Node *pTmp, *pFormer,*pLatter;
    pTmp = pHead;
    int nodeVal;

    pNew = (Node *)malloc(NodeLen);
    if (pNew == NULL)
    {
        printf("new Node create failed!\n");
        exit(-1);
    }
    printf("insert node %d data:", ist_num);
    scanf("%d", &nodeVal);
    pNew->val = nodeVal;

    //pTmp is the target node.
    for (int i = 0; i <= ist_num; i++)
    {
        pFormer = pTmp;
        pTmp = pTmp->rLink;
    }
    pFormer->rLink = pNew;
	pNew->lLink = pFormer;
    pNew->rLink = pTmp;

    return pHead;

}
void delete (Node *pHead, int dlt_num)
{
    Node *pTmp, *pFormer, *pLatter;
    pTmp = pHead;

    //pTmp is the target node.
    for (int i = 0; i <= dlt_num; i++)
    {
        pFormer = pTmp;
        pTmp = pTmp->rLink;
    }
    pLatter = pTmp->rLink;
    pFormer->rLink = pLatter;
	pLatter->lLink = pFormer;
    free(pTmp);//if free(pTmp->next),pTmp->next changed while pFormer->next changed.
}

int main()
{
    int ist_num = 2;
    int dlt_num = 2;

    Node *pList;
    pList = create();
    print(pList);

    insert(pList, ist_num);
    print(pList);

    delete(pList, dlt_num);
    print(pList);
    return 0;
}
