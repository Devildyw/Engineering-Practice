#include<stdio.h> 
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
//Status 为函数的类型，其值是函数结果状态代码，如OK等
typedef int Status; 

// ElemType为数据元素类型，根据实际情况而定，这里假设为int 
typedef int ElemType;
struct LNode               /* 结点定义 */     
{
  ElemType data;
  struct LNode *next;
};
typedef struct LNode *LinkList; /* 表的头指针型 */
Status ListInsert(LinkList *L, int i, ElemType e);
LinkList create();
void print(LinkList L);
Status ListLength(LinkList L);
Status GetElem(LinkList L,int i,ElemType *e);
Status LocateElem(LinkList L, ElemType e, int(*equal)(int, int));
Status equal(int a, int b);
void Union(LinkList *La,LinkList Lb);
int main()
{
	LinkList La, Lb;
	La = create();
	Lb = create(); 
	Union(&La, Lb);
	print(La);
	
	return 0;
}
Status ListInsert(LinkList *L, int i, ElemType e)//将元素e插入第i个元素之前 
{
	
	if(*L && (i>=1&&i<=ListLength(*L)+1)){
		LinkList pre = (LinkList)malloc(sizeof(struct LNode)); 
		pre->data = e;
		pre->next = NULL;
		if(*L == NULL)
		{
			*L = (LinkList)malloc(sizeof(struct LNode));
			(*L)->next = NULL;
		}
		if (i-1==0)
		{
			pre->next = (*L)->next;
			(*L)->next = pre;
		}
		else
		{
			int n=0;
			LinkList p = *L;
			while(n<i-1){
				n++;
				p=p->next;	
			}
			printf("%d\n", n);
			pre->next = p->next;
			p->next = pre;
		}
	}
}
LinkList create()//创建链表 
{
	LinkList head = NULL, node, end;
	node =(LinkList)malloc(sizeof(struct LNode));
	scanf("%d", &node->data);
	node->next = NULL;
	while(node->data != -1){
		if(head == NULL)
			head = node; 
		else
			end->next = node;
		end = node;
		node =(struct LNode *)malloc(sizeof(struct LNode));
		scanf("%d", &node->data);
		node->next = NULL;
	}
	return head;
}
Status ListLength(LinkList L)//求链表表长 
{
	L = L->next;
	int length = 0;
	while(L){
		length++;
		L = L->next;	
	}
	return length;
}
Status GetElem(LinkList L,int i,ElemType *e)//取出链表中第i个元素 
{ /* L为单链表的头指针。当第i个元素存在时,
    其值赋给e并返回OK,否则返回ERROR */
   	int j=1; /* j为计数器 */
   	LinkList p=L; /* p指向第一个结点 */
   	while(p&&j<i) /* 顺指针向后查找, 直到p指向第i个元素或p为空 */
	{
    	p=p->next;
    	j++;
   	} 	
   	if(!p||j>i)   /* 第i个元素不存在 */
    	return ERROR;
   	*e=p->data;   /* 取第i个元素 */
	return OK;
}
Status equal(int a, int b)
{
	if(a==b)
		return 1;
	else
		return 0;
}
Status LocateElem(LinkList L, ElemType e, int(*equal)(int, int))//判断元素e是否在链表中存在 
{
	while(L){
		if(equal(L->data, e))
			return 1;
		L=L->next; 
	}
	return 0;
}
Status ListEmpty(LinkList L)
{ /* 初始条件：链式存储的表L已存在。*/
  /*操作结果：若L为空表，则返回TRUE，否则返回FALSE */
    if(L->next)
            return FALSE;
    else
            return TRUE;
}
void Union(LinkList *La,LinkList Lb) 
{ // 将所有在表Lb（代表B集合）中但不在La（代表A集合）中的数据元素插入到La中
   	int i, La_len, Lb_len;
   	ElemType e;
	La_len=ListLength(*La); // 求表La的长度
   	Lb_len=ListLength(Lb);
   	printf("%d\n", La_len);
   	for(i=1;i<=Lb_len;i++)
	{
    	GetElem(Lb,i,&e); // 取表Lb中第i个数据元素赋给变量e
    	if(!LocateElem(*La,e,equal)) // 表La中不存在和e相同的元素,则将e插入La中
      		ListInsert(La,++La_len,e);
   	}
}
void print(LinkList L){
	L= L->next;
	while(L){
		printf("%d ", L->data);
		L = L->next;
	}
}
