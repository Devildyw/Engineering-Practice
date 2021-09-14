#include<stdio.h> 
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
//Status Ϊ���������ͣ���ֵ�Ǻ������״̬���룬��OK��
typedef int Status; 

// ElemTypeΪ����Ԫ�����ͣ�����ʵ������������������Ϊint 
typedef int ElemType;
struct LNode               /* ��㶨�� */     
{
  ElemType data;
  struct LNode *next;
};
typedef struct LNode *LinkList; /* ���ͷָ���� */
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
Status ListInsert(LinkList *L, int i, ElemType e)//��Ԫ��e�����i��Ԫ��֮ǰ 
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
LinkList create()//�������� 
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
Status ListLength(LinkList L)//������� 
{
	L = L->next;
	int length = 0;
	while(L){
		length++;
		L = L->next;	
	}
	return length;
}
Status GetElem(LinkList L,int i,ElemType *e)//ȡ�������е�i��Ԫ�� 
{ /* LΪ�������ͷָ�롣����i��Ԫ�ش���ʱ,
    ��ֵ����e������OK,���򷵻�ERROR */
   	int j=1; /* jΪ������ */
   	LinkList p=L; /* pָ���һ����� */
   	while(p&&j<i) /* ˳ָ��������, ֱ��pָ���i��Ԫ�ػ�pΪ�� */
	{
    	p=p->next;
    	j++;
   	} 	
   	if(!p||j>i)   /* ��i��Ԫ�ز����� */
    	return ERROR;
   	*e=p->data;   /* ȡ��i��Ԫ�� */
	return OK;
}
Status equal(int a, int b)
{
	if(a==b)
		return 1;
	else
		return 0;
}
Status LocateElem(LinkList L, ElemType e, int(*equal)(int, int))//�ж�Ԫ��e�Ƿ��������д��� 
{
	while(L){
		if(equal(L->data, e))
			return 1;
		L=L->next; 
	}
	return 0;
}
Status ListEmpty(LinkList L)
{ /* ��ʼ��������ʽ�洢�ı�L�Ѵ��ڡ�*/
  /*�����������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
    if(L->next)
            return FALSE;
    else
            return TRUE;
}
void Union(LinkList *La,LinkList Lb) 
{ // �������ڱ�Lb������B���ϣ��е�����La������A���ϣ��е�����Ԫ�ز��뵽La��
   	int i, La_len, Lb_len;
   	ElemType e;
	La_len=ListLength(*La); // ���La�ĳ���
   	Lb_len=ListLength(Lb);
   	printf("%d\n", La_len);
   	for(i=1;i<=Lb_len;i++)
	{
    	GetElem(Lb,i,&e); // ȡ��Lb�е�i������Ԫ�ظ�������e
    	if(!LocateElem(*La,e,equal)) // ��La�в����ں�e��ͬ��Ԫ��,��e����La��
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
