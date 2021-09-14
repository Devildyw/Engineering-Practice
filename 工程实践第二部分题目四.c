#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status; //Status Ϊ���������ͣ���ֵ�Ǻ������״̬���룬��OK��
typedef struct Book{ //ͼ����Ϣ���� 
	char id[81], ISBN[11], name[51];
	double price;
	int booknum, borrownum, nownum, Nob; 	
} Book;
struct BLNode{//ͼ�鵥��������ڵ㶨�� 
	Book elem;
	struct BLNode * next;
};
typedef struct BLNode *LinkList;
typedef struct reader{//��������Ϣ���� 
	char num[11], name[11];
	double Fine;	 
} reader; 
struct Borrower{//�����ߵ���������ڵ㶨�� 
	reader stu;
	struct Borrower * next;
};
typedef struct Borrower *Borrower;
void print(LinkList L)//����������ָ���ڵ����ϸ��Ϣ
{
    printf("%s\t%s\t%s\t%.2lf\t%d\t%d\t%d\t%d\n", L->elem.id, L->elem.ISBN, L->elem.name, L->elem.price, L->elem.booknum, L->elem.borrownum, L->elem.nownum, L->elem.Nob);
}
void Bsort(LinkList *L)//ͼ����Ĵ��������ɸߵ��ͣ�        
{                                                                           
  	LinkList p = (*L)->next, q;
  	Book temp;
	while(p->next!=NULL)
	{
		q = p->next;
		while(q)
		{
			if(p->elem.Nob < q->elem.Nob)
			{

				temp = p->elem;
				p->elem = q->elem;
				q->elem = temp;
			}
			q = q->next ;
		}
		p = p->next;
	}
}
void Jsort(Borrower *SL)//�����߷����������ɸߵ��ͣ�            
{                                                                           
  	Borrower p = (*SL)->next, q;
  	reader temp;
	while(p->next!=NULL)
	{
		q = p->next;
		while(q)
		{
			if(p->stu.Fine < q->stu.Fine)
			{
				temp = p->stu;
				p->stu = q->stu;
				q->stu = temp;
			}
			q = q->next;
		}
		p = p->next;
	}
}
Status BInitList(LinkList * L)//��ʼ������һ��ͼ������
{
	*L = (LinkList)malloc(sizeof(struct BLNode));
	(*L)->next = NULL;
	return OK;
}
Status SInitList(Borrower * L)//��ʼ������һ������������
{
	*L = (Borrower)malloc(sizeof(struct Borrower));
	(*L)->next = NULL;
	return OK;
}
Status Length(LinkList L)//�������ͼ��������
{
	int length = 0;
	L = L->next;
	while(L)
	{
		length++;
		L = L->next;
	}
	return length;
} 
Status JLength(Borrower SL)//���������������
{
	int length = 0;
	SL = SL->next;
	while(SL)
	{
		length++;
		SL = SL->next;
	}
	return length;
}
Status BF(char *name, char *bname)//ͨ��BF�㷨ȷ�Ϲؼ����Ƿ���������
{
    int i = 0, j = 0;
    while(j<strlen(name)&& i<strlen(bname))
    {
        if(name[j] == bname[i])
        {
            i++;
            j++;
        }
        else
        {
            i = i-j+1;
            j = 0;
        }
    }
    if(j == strlen(name))
    {
        return OK;
    }
    else
    {
        return ERROR;
    }
}
Status BListcreate(LinkList *L,FILE *fp)//¼��ͼ����Ϣ
{	
	LinkList head, node, end=NULL;
	head = *L;																											
	node = (LinkList)malloc(sizeof(struct BLNode));
	if((fp = fopen("E:\\ͼ��.txt", "r"))== NULL)
	{
		printf("δ���ҵ�����ļ����޷���\n\n");
		return ERROR;
	}
	while (fscanf(fp, "%s%s%s%lf%d%d%d%d", node->elem.id, node->elem.ISBN, node->elem.name, &node->elem.price, &node->elem.booknum, &node->elem.borrownum
	, &node->elem.nownum, &node->elem.Nob) == 8)
    {
		node->next = NULL; 
		if(head->next == NULL)
		{
			head->next = node;
		}
		else
			end->next= node;
		end = node;
		node = (LinkList)malloc(sizeof(struct BLNode));
	}
	system("cls");
	return OK; 
}
Status SListcreate(Borrower *L, FILE *fp1)//¼���������Ϣ
{
	Borrower head, node, end=NULL;
	head = *L;
	node = (Borrower)malloc(sizeof(struct Borrower));
	if((fp1 = fopen("E:\\������.txt", "r"))==NULL)
	{
		printf("δ�鵽����ļ����޷���\n\n");
		return ERROR; 
	}
	while(fscanf(fp1, "%s%s%lf", node->stu.num, node->stu.name, &node->stu.Fine)==3)
	{
		node->next = NULL;
		if(head->next ==NULL)
		{
			head->next = node; 
		}
		else
		{
			end->next=node;
		}
		end = node;	
		node = (Borrower)malloc(sizeof(struct Borrower));
	}
	system("cls");
	return OK; 
} 
Status BEdit(LinkList *L, int i)//��ͼ����Ϣ�����޸�
{
    LinkList pre, e, suc;
	int flag = 0;
	pre = *L;
    e = (LinkList)malloc(sizeof(struct BLNode));
    printf("�뽫�޸ĺ����Ϣ������������ IBSN �������� �۸� ͼ������ ������ �ڹ��� ���Ĵ������밴�ո������:\n");
	scanf("%s%s%s%lf%d%d%d%d", e->elem.id, e->elem.ISBN, e->elem.name, &e->elem.price, &e->elem.booknum, &e->elem.borrownum, &e->elem.nownum, &e->elem.Nob);
	if(*L&& (i>=1&&i<=Length(*L)+1) && Length(*L)>=1)
	{	
        while(flag<i-1)
        {
            flag++;
            pre=pre->next;
        }
        suc = pre->next;
        pre->next = e;
        e->next = suc->next;
        free(suc);
	    system("cls");
	    return OK;
	}
	else
	{
		system("cls");
		return ERROR;
	}
}
Status JEdit(Borrower *SL, int i)//�Խ�������Ϣ�����޸�
{
	Borrower pre, e, suc;
	int flag = 0;
	pre = *SL;
    e = (Borrower)malloc(sizeof(struct Borrower));
    printf("�뽫�޸ĺ����Ϣ���� ѧ�� ���� ��������Կո������:\n");
	scanf("%s%s%lf", e->stu.num, e->stu.name, &e->stu.Fine);
	if(*SL&& (i>=1&&i<=JLength(*SL)+1) && JLength(*SL)>=1)
	{	
        while(flag<i-1)
        {
            flag++;
            pre=pre->next;
        }
        suc = pre->next;
        pre->next = e;
        e->next = suc->next;
        free(suc);
	    system("cls");
	    return OK;
	}
	else
	{
		system("cls");
		return ERROR;
	}
}
Status BInsertList(LinkList *L, int i)//����һ���µ�ͼ����Ϣ�ڵ�
{ 
	LinkList pre, e;
	int flag = 0;
	pre = *L;
    e = (LinkList)malloc(sizeof(struct BLNode));
	printf("��������Ҫ�������Ϣ���� IBSN �������� �۸� ͼ������ ������ �ڹ��� ���Ĵ������밴�ո������\n");
	scanf("%s%s%s%lf%d%d%d%d", e->elem.id, e->elem.ISBN, e->elem.name, &e->elem.price, &e->elem.booknum, &e->elem.borrownum, &e->elem.nownum, &e->elem.Nob);
	if(*L && (i>=1&&i<=Length(*L)+1))
	{
		while(flag < i-1)
		{
			flag++;
			pre = pre->next;
		}
		e->next = pre->next;
	    pre->next = e;
	    system("cls");
	    return OK;
	} 
	else
	{
		system("cls");
		return ERROR;
	}
}
Status JInsertList(Borrower *SL, int i)//����һ���µĽ�������Ϣ�ڵ�
{
	Borrower pre, e;
	int flag = 0;
	pre = *SL;
    e = (Borrower)malloc(sizeof(struct Borrower));
	printf("��������Ҫ����Ľ�������Ϣ ѧ�� ���� ������밴�ո������\n");
	scanf("%s%s%lf", e->stu.num, e->stu.name, &e->stu.Fine);
	if(*SL && (i>=1&&i<=JLength(*SL)+1))
	{
		while(flag < i-1)
		{
			flag++;
			pre = pre->next;
		}
		e->next = pre->next;
	    pre->next = e;
	    system("cls");
	    return OK;
	} 
	else
	{
		system("cls");
		return ERROR;
	}
}
Status DeleteList(LinkList *L, int i)//ɾ��һ��ͼ��ڵ�
{
	int flag = 0;
	LinkList pre, e;
	pre =*L;
	if (*L && (i>=1&&i<=Length(*L)+1)&& Length(*L)>=1)
	{	
		while(flag<i-1)
		{
			flag++;
			pre = pre->next;	
		}
		e = pre->next;
		pre->next = e->next;
		free(e);
		system("cls");
	    return OK;
	}
	else
	{
		system("cls");
		return ERROR;
	}
}
Status JDeleteList(Borrower *SL, int i)//ɾ��һ�������߽ڵ�
{
	int flag = 0;
	Borrower pre, e;
	pre =*SL;
	if (*SL && (i>=1&&i<=JLength(*SL)+1)&& JLength(*SL)>=1)
	{	
		while(flag<i-1)
		{
			flag++;
			pre = pre->next;	
		}
		e = pre->next;
		pre->next = e->next;
		free(e);
		system("cls");
	    return OK;
	}
	else
	{
		system("cls");
		return ERROR;
	}
}
Status Statistics(LinkList L, Borrower SL)//ͳ����Ϣ
{
	system("cls");
	char ch[11];
	while(1) 
	{
		printf("��������Ҫͳ����Ϣ�����ͼ�� or �����ߣ�:\n");
		scanf("%s", ch);
		if(strcmp(ch, "ͼ��") == 0)
	    {
	    	if(L)
	    	{
	    		int All_borrownum = 0, All_nownum = 0, All_booknum = 0, i = 0, n;
	    		LinkList pf = L->next;
	    		while(pf!=NULL)
			    {
			    	All_borrownum += pf->elem.borrownum;
			    	All_nownum += pf->elem.nownum;
			    	All_booknum += pf->elem.booknum;
			    	pf = pf->next;
				}
				Bsort(&L);
				printf("ͳ�����!\n"); 
				printf("ͼ��ϵͳ�й���¼��%d��ͼ����Ϣ, ��������Ҫ���ǰ���ٱ������Ϣ:", Length(L));
				scanf("%d", &n);
				printf("���ͳ����Ϣ\n");
				pf = L->next;
				printf("����\t\tISBN\t\t����\t�۸�  ͼ������ ������  �ڹ���  ���Ĵ���\n");
				while(pf!=NULL && i++<n)
				{
					print(pf);
					pf = pf->next;
			   	}
			   	printf("\n������ �ڹ��� ͼ������\n");
				printf("%d\t%d\t%d\n", All_borrownum, All_nownum, All_booknum);
				return OK;
			}
			else
			{
				system("cls");
				return ERROR;
			}
		}
	    else if(strcmp(ch, "������") == 0)
	    {
	    	if(SL)
			{
				int i = 0, n;
			    Borrower sf = SL->next;
			    Jsort(&SL);
			    printf("ͳ�����!\n"); 
			    printf("ͼ��ϵͳ�й���¼��%dλ��������Ϣ, ��������Ҫ���ǰ����λ��������Ϣ:", JLength(SL));
				scanf("%d", &n);
				printf("ͳ�����! ���ͳ����Ϣ\n");
			   	printf("ѧ��\t����\t����\n");
				while(sf!=NULL && i++<n)
				{
					printf("%s\t%s\t%.2lf\t\n", sf->stu.num, sf->stu.name, sf->stu.Fine);
					sf = sf->next;
				}
				return OK;
			}
			else
			{
				system("cls");
				return ERROR;
			}
		}
		else
		{
			printf("������� ����������\n");
		}
	}
}
void BFind_menu(void)//���Ҳ˵�ѡ�� 
{
	sleep(1);
	printf("\t\t********��ӭ���ʹ��ͼ��ݲ�ѯϵͳ********\n\n-����ѡ��-\n\n");
	printf("������ѡ�����\n");
	printf("1.������������\n");
    printf("2.����ISBN����\n");
    printf("3.�������߲���\n");
    printf("4.���ݼ۸��������\n");
    printf("5.�����鼮��������\n");
    printf("6.�����鼮����������\n");
    printf("7.�����鼮�ڹ�������\n");
    printf("8.�����鼮���Ĵ�������\n");
    printf("0.�˳�\n");
}
Status BFind(LinkList L)//ͼ�����
{
	system("cls");
    int choose = -1;
    BFind_menu();
    while(choose != 0)
    {
        printf("��������Ҫ���еĲ���:");
        scanf("%d", &choose);
        switch (choose)
        {
	        case 1:
	            BFind_id(L);
	            BFind_menu();
	            break;
	        case 2:
	            BFind_ISBN(L);
	            BFind_menu();
	            break;
	        case 3:
	            BFind_name(L);
	            BFind_menu();
	            break;
	        case 4:
	            BFind_price(L);
	            BFind_menu();
	            break;
	        case 5:
	            BFind_booknum(L);
	            BFind_menu();
	            break;
	        case 6:
	            BFind_borrownum(L);
	            BFind_menu();
	            break;
	        case 7:
	            BFind_nownum(L);
	            BFind_menu();
	            break;
	        case 8:
	            BFind_Nob(L);
	            BFind_menu();
	            break;
	        default:
	            break;
        }
    }
    system("cls");
    return OK;
}
void JFind_menu(void)//�����߲�ѯ�˵� 
{
	sleep(1);
	printf("\t\t********��ӭ���ʹ�ý����߲�ѯϵͳ********\n\n-����ѡ��-\n\n");
	printf("������ѡ�����\n");
	printf("1.����ѧ�Ų���\n");
    printf("2.������������\n");
    printf("3.���ݷ������������\n");
    printf("0.�˳�\n");
}
Status JFind(Borrower SL)//�����߲���
{
	system("cls");
    int choose = -1;
    JFind_menu();
    while(choose != 0)
    {
        printf("��������Ҫ���еĲ���:");
        scanf("%d", &choose);
        switch (choose)
        {
	        case 1:
	            JFind_num(SL);
	            JFind_menu();
	            break;
	        case 2:
	            JFind_name(SL);
	            JFind_menu();
	            break;
	        case 3:
	            JFind_Fine(SL);
	            JFind_menu();
	            break;
	        default:
	            break;
        }
    }
    system("cls");
    return OK;
}
Status BFind_id(LinkList L)//ͨ�������ؼ��ֽ��в���
{
    char name[81];
    LinkList pre = L->next;
    int flag = 0, i = 0;
    printf("�����������ؼ��ʣ����硰������� �����Ὣ�������С������������ȫ�������\n");
    scanf("%s", name);
    system("cls");
    printf("�������:\n"); 
    while(pre!=NULL)
    {
        if(BF(name, pre->elem.id))
        {
            i++;
            print(pre);
        }
        pre=pre->next;
    }
    if (i == 0)
    {
    	system("cls");
        printf("δ���ҵ������к��йؼ���%s���鼮\n\n", name);
    }
    if(i!=0)
    {
    	printf("�����ҵ�%d���鼮\n",i); 
	}
    return OK;
}
Status BFind_ISBN(LinkList L)//ͨ��ͼ���ISBN���в���
{
    char ISBN[11];
    LinkList pre = L->next;
    int i=0;
    printf("������ͼ���10λISBN����в���:");
    scanf("%s", ISBN);
    system("cls");
    printf("�������:\n"); 
    while(pre!=NULL)
    {
        if(strcmp(ISBN, pre->elem.ISBN) == 0)
        {
        	i++;  
            print(pre);
        }
        pre = pre->next;
    }
    if(i == 0)
    {
    	system("cls");
        printf("δ���ҵ�ISBNΪ%s��ͼ��\n\n",ISBN);
    }
    if(i!=0)
    {
    	printf("�����ҵ�%d���鼮\n", i); 
	}
    return OK;
}
Status BFind_name(LinkList L)//ͨ��ͼ�����ߵ����ֽ��в���
{
    char writername[51];
    LinkList pre = L;
    int i =0;
    printf("������ͼ������������в���:");
    scanf("%s", writername);
    system("cls");
    printf("�������:\n"); 
    while(pre!=NULL)
    {
        if(strcmp(writername, pre->elem.name) == 0)
        {
        	i++;
            print(pre);
        }
        pre = pre->next;
    }
    if(i == 0)
    {
    	system("cls");
        printf("δ���ҵ�%s���ߵ��鼮\n\n",writername);
    }
    if(i!=0)
    {
    	printf("�����ҵ�%d���鼮\n",i); 
	}
    return OK;
}
Status BFind_price(LinkList L)//ͨ��ͼ��ļ۸�������в���
{
    double price, price1;
    LinkList pre = L->next;
    int i=0, temp;
    printf("������ͼ��ļ۸�������в��ң��۸��ÿո������:");
    scanf("%lf%lf", &price, &price1);
    if(price > price1)
    {
    	temp = price;
    	price = price1;
    	price1 = temp;
	}
    system("cls"); 
    printf("�������:\n"); 
    while(pre!=NULL)
    {
        if(pre->elem.price >= price&& pre->elem.price <= price1)
        {
        	i++;
            print(pre);
        }
        pre = pre->next;
    }
    if(i== 0)
    {
    	system("cls");
        printf("δ���ҵ��۸�����Ϊ%.2lf~%.2lf���鼮\n\n",price, price1);
    }
    if(i!=0)
    {
    	printf("�����ҵ�%d���鼮\n", i); 
	}
    return OK;
}
Status BFind_booknum(LinkList L)//ͨ��ͼ����������в���
{
    int booknum;
    LinkList pre = L->next;
    int i =0;
    printf("������ͼ����������в���:");
    scanf("%d", &booknum);
    system("cls");
    printf("�������:\n"); 
    while(pre!=NULL)
    {
        if(booknum == pre->elem.booknum)
        {
        	i++;
            print(pre);
        }
        pre = pre->next;
    }
    if(i == 0)
    {
    	system("cls");
        printf("δ���ҵ�����Ϊ%d���鼮\n\n",booknum);
    }
    if(i!=0)
    {
    	printf("�����ҵ�%d���鼮\n", i); 
	}
    return OK;
}
Status BFind_borrownum(LinkList L)//ͨ��ͼ�����������
{
    int borrownum;
    LinkList pre = L->next;
    int i =0;
    printf("������ͼ��Ľ��������в���:");
    scanf("%d", &borrownum);
    system("cls");
    printf("�������:\n"); 
    while(pre!=NULL)
    {
        if(borrownum == pre->elem.borrownum)
        {
            i++;
            print(pre);
        }
        pre = pre->next;
    }
    if(i == 0)
    {
    	system("cls");
        printf("δ���ҵ�������Ϊ%d���鼮\n\n",borrownum);
    }
    if(i!=0)
    {
    	printf("�����ҵ�%d���鼮\n", i); 
	}
    return OK;
}
Status BFind_nownum(LinkList L)//ͨ��ͼ����ڹ������в���
{
    int nownum;
    LinkList pre = L->next;
    int i =0;
    printf("������ͼ����ڹ������в���:");
    scanf("%d", &nownum);
    system("cls");
    printf("�������:\n"); 
    while(pre!=NULL)
    {
        if(nownum == pre->elem.nownum)
        {
        	i++;
            print(pre);
        }
        pre = pre->next;
    }
    if(i == 0)
    {
    	system("cls");
        printf("δ���ҵ��ڹ���Ϊ%d���鼮\n\n",nownum);
    }
    if(i!=0)
    {
    	printf("�����ҵ�%d���鼮\n", i); 
	}
    return OK;
}
Status BFind_Nob(LinkList L)//ͨ��ͼ��Ľ��Ĵ������в���
{
    int Nob;
    LinkList pre = L->next;
    int i=0;
    printf("������ͼ��Ľ��Ĵ������в���:");
    scanf("%d", &Nob);
    system("cls");
    printf("�������:\n"); 
    while(pre!=NULL)
    {
        if(Nob == pre->elem.Nob)
        {
        	i++;
            print(pre);
        }
        pre = pre->next;
    }
    if(i == 0)
    {
    	system("cls");
        printf("δ���ҵ����Ĵ���Ϊ%d���鼮\n\n",Nob);
    }
    if(i!=0)
    {
    	printf("�����ҵ�%d���鼮\n", i); 
	}
    return OK;
}
Status JFind_num(Borrower SL)//ͨ��ѧ�Ų��� 
{
	char num[11];
    Borrower pre = SL;
    int i =0;
    printf("����������ߵ�ѧ�Ž��в���:");
    scanf("%s", num);
    system("cls");
    printf("�������:\n"); 
    while(pre!=NULL)
    {
        if(strcmp(num, pre->stu.num) == 0)
        {
        	i++;
            printf("%s\t%s\t%.2lf\t\n", pre->stu.num, pre->stu.name, pre->stu.Fine);
        }
        pre = pre->next;
    }
    if(i == 0)
    {
    	system("cls");
        printf("δ���ҵ�ѧ��Ϊ%s�Ľ�����\n\n",num);
    }
    return OK;
}
Status JFind_name(Borrower SL)//ͨ���������� 
{
	char name[11];
    Borrower pre = SL;
    int i =0;
    printf("����������ߵ��������в���:");
    scanf("%s", name);
    system("cls");
    printf("�������:\n"); 
    while(pre!=NULL)
    {
        if(strcmp(name, pre->stu.name) == 0)
        {
        	i++;
            printf("%s\t%s\t%.2lf\t\n", pre->stu.num, pre->stu.name, pre->stu.Fine);
        }
        pre = pre->next;
    }
    if(i == 0)
    {
    	system("cls");
        printf("δ���ҵ�����Ϊ%s�Ľ�����\n\n",name);
    }
    return OK;
}
Status JFind_Fine(Borrower SL)//ͨ��������������� 
{
	double Fine, Fine1;
    Borrower pre = SL->next;
    int i=0, temp;
    printf("����������ߵķ�����������в��ң��۸��ÿո������:");
    scanf("%lf", &Fine);
    scanf("%lf", &Fine1);
    if(Fine > Fine1)
    {
    	temp = Fine;
		Fine = Fine1;
		Fine1 = temp; 
	}
    system("cls"); 
    printf("�������:\n"); 
    while(pre!=NULL)
    {
        if(Fine <= pre->stu.Fine && pre->stu.Fine <=Fine1)
        {
        	i++;
            printf("%s\t%s\t%.2lf\t\n", pre->stu.num, pre->stu.name, pre->stu.Fine);
        }
        pre = pre->next;
    }
    if(i== 0)
    {
    	system("cls");
        printf("δ���ҵ�����������Ϊ%.2lf~%.2lf��ѧ��\n\n",Fine);
    }
    if(i!=0)
    {
    	printf("�����ҵ�%dλ������\n", i); 
	}
    return OK;
}
Status Output(LinkList L, Borrower SL)//�����Ϣ 
{
	int i = 1;
	system("cls");
	char ch[10];
	LinkList p = L->next;
	Borrower p1 = SL->next;
	while(1) 
	{
		printf("��������Ҫ���������(ͼ�� or ������):");
		scanf("%s", ch);
		if(strcmp(ch, "ͼ��") == 0)
		{
			printf("���\t����\t\tISBN\t\t����\t�۸�  ͼ������ ������ �ڹ��� ���Ĵ���\n");
			while(p)
			{
				printf("%d:\t%s\t%s\t%s\t%.2lf\t%d\t%d\t%d\t%d\n",i, p->elem.id, p->elem.ISBN, p->elem.name, p->elem.price, p->elem.booknum, p->elem.borrownum, p->elem.nownum, p->elem.Nob);
				p = p->next;
				i++; 
			}
			break;
		}
		else if(strcmp(ch, "������") == 0)
		{
			int i = 1;
			printf("���\tѧ��\t����\t����\n");
			while(p1)
			{
				printf("%d:\t%s\t%s\t%.2lf\t\n",i, p1->stu.num, p1->stu.name, p1->stu.Fine);
				p1 = p1->next;
				i++; 
			}
			break;
		}
		else
		{
			printf("�������! ����������\n");
			continue;
		}
	}
	return OK;
}
void menu(LinkList L, Borrower SL)//���˵�ѡ�� 
{
	sleep(1);
	printf("\t\t********��ӭ���ʹ��ͼ��ݹ���ϵͳ********\n\n-����ѡ��-\n\n");
	printf("����ͼ��ϵͳ�м�¼��%d����\n", Length(L));
	printf("����ͼ��ϵͳ�м�¼��%dλ������\n", JLength(SL));
	printf("������ѡ�����\n"); 
	printf("\t\t\t1.�޸�\n");
	printf("\t\t\t2.����\n"); 
	printf("\t\t\t3.ɾ��\n");
    printf("\t\t\t4.��ѯ\n");
	printf("\t\t\t5.ͳ�Ƽ���\n");
	printf("\t\t\t6.���ͼ�������ߵ���Ϣ\n"); 
	printf("\t\t\t0.�˳�\n");
}
Status Zsystem(void)//��ϵͳ 
{
	FILE * fp, *fp1;
	int choose=-1, n;
	LinkList L;
	char ch[10];
	Borrower SL;
	BInitList(&L);
	SInitList(&SL);
	BListcreate(&L,fp);
	SListcreate(&SL, fp1);
	menu(L, SL);
	while(choose != 0)
	{
		printf("��������Ҫ���������:");
		scanf("%d", &choose); 
		switch(choose)
		{
			case 1://�޸�ͼ����������Ϣ
				while(1)
				{
					printf("��������Ҫ�޸ĵ����ݣ�ͼ�� or �����ߣ�:");
					scanf("%s", ch);
					if(strcmp(ch, "ͼ��") == 0)
					{
						printf("��������Ҫ�޸ĵ��鱾��λ��:");
						scanf("%d", &n);
						if(BEdit(&L,n))
						{
							printf("�޸ĳɹ�!\n");
						}
						else
						{
							printf("�޸�ʧ��!\n");	
						}
						break; 
					}
					else if(strcmp(ch, "������")==0)
					{
						printf("��������Ҫ�޸ĵĽ����ߵ�λ��:");
						scanf("%d", &n);
						if(JEdit(&SL,n))
						{
							printf("�޸ĳɹ�!\n");
						}
						else
						{
							printf("�޸�ʧ��!\n");	
						}
						break; 	
					}
					else
					{
						printf("�����������������\n");	
					} 
				}
				menu(L, SL);
				break;
			case 2://�����µ�ͼ����������Ϣ
				while(1)
				{
					printf("��������Ҫ���뵽�����ݣ�ͼ�� or �����ߣ�:");
					scanf("%s", ch);
					if(strcmp(ch, "ͼ��") == 0)
					{
						printf("��������Ҫ������鱾��λ��:");
						scanf("%d", &n);
						if(BInsertList(&L,n))
						{
							printf("����ɹ�!\n");
						}
						else
						{
							printf("����ʧ��!\n");	
						}
						break; 
					}
					else if(strcmp(ch, "������")==0)
					{
						printf("��������Ҫ����Ľ����ߵ�λ��:");
						scanf("%d", &n);
						if(JInsertList(&SL,n))
						{
							printf("����ɹ�!\n");
						}
						else
						{
							printf("����ʧ��!\n");	
						}
						break; 	
					}
					else
					{
						printf("�����������������\n");	
					} 
				}
				menu(L, SL);
				break;
			case 3://ɾ��ͼ����������Ϣ
				while(1)
				{
					printf("��������Ҫɾ�������ݣ�ͼ�� or �����ߣ�:");
					scanf("%s", ch);
					if(strcmp(ch, "ͼ��") == 0)
					{
						printf("��������Ҫɾ�����鱾��Ϣ��λ��:");
						scanf("%d", &n);
						if(DeleteList(&L,n))
						{
							printf("ɾ���ɹ�!\n");
						}
						else
						{
							printf("ɾ��ʧ��!\n");	
						}
						break; 
					}
					else if(strcmp(ch, "������")==0)
					{
						printf("��������Ҫɾ���Ľ�������Ϣ��λ��:");
						scanf("%d", &n);
						if(JDeleteList(&SL,n))
						{
							printf("ɾ���ɹ�!\n");
						}
						else
						{
							printf("ɾ��ʧ��!\n");	
						}
						break; 	
					}
					else
					{
						printf("�����������������\n");	
					} 
				}
				menu(L, SL);
				break;
            case 4://��ѯͼ����������Ϣ
                while(1)
				{
					printf("��������Ҫ��ѯ����Ϣ��ͼ�� or �����ߣ�:");
	                scanf("%s", ch);
	                if(strcmp(ch, "ͼ��") == 0)
	                {
	                	if(BFind(L))
	                	{
	                		printf("��ѯ���!\n"); 
	                		break;
						}
					}
					else if(strcmp(ch, "������") == 0)
					{
						if(JFind(SL))
	                	{
	                		printf("��ѯ���!\n"); 
	                		break;
						}
					}
					else
					{
						printf("�����������������\n");
					}
				} 
				menu(L, SL);
				break;
			case 5://ͳ�Ƽ���ͼ����Ϣ 
				if(Statistics(L,SL))
				{
					printf("ͳ�ƽ���!\n");
				}
				else
				{
					printf("ͳ��ʧ��!\n");
				}
				menu(L, SL);
				break; 
			case 6:
				if (Output(L, SL))
				{
					printf("�������\n\n"); 
				}
				menu(L, SL);
				break;
			case 0:
				break; 
			default:
				printf("����������޷�ʶ������������!\n"); 
				; 
		}	
	}
	if((fp = fopen("E:\\ͼ��.txt", "w"))== NULL || (fp1 =fopen("E:\\������.txt", "w")) == NULL)//�˳�ǰ�����в����Ľ�����¶����ļ� 
	{
		printf("�ļ���ʧ�ܣ��˳�ʧ��\n\n");
		return ERROR; 
	}
	L = L->next;
	SL = SL->next; 
	while(L)
	{
		fprintf(fp, "%s %s %s %.2lf %d %d %d %d\n", L->elem.id, L->elem.ISBN, L->elem.name, L->elem.price, L->elem.booknum, L->elem.borrownum, L->elem.nownum, L->elem.Nob);
		L = L->next;
	}
	while(SL)
	{
		fprintf(fp1, "%s %s %.2lf\n", SL->stu.num, SL->stu.name, SL->stu.Fine);
		SL = SL->next;
	}
	printf("�˳��ɹ�!"); 
    fclose(fp1);
	fclose(fp);
	return OK;
}
int main()//������ 
{
	Zsystem();
	return 0;
}

