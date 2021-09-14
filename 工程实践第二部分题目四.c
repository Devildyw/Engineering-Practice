#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status; //Status 为函数的类型，其值是函数结果状态代码，如OK等
typedef struct Book{ //图书信息定义 
	char id[81], ISBN[11], name[51];
	double price;
	int booknum, borrownum, nownum, Nob; 	
} Book;
struct BLNode{//图书单链表链表节点定义 
	Book elem;
	struct BLNode * next;
};
typedef struct BLNode *LinkList;
typedef struct reader{//借阅者信息定义 
	char num[11], name[11];
	double Fine;	 
} reader; 
struct Borrower{//借阅者单链表链表节点定义 
	reader stu;
	struct Borrower * next;
};
typedef struct Borrower *Borrower;
void print(LinkList L)//输出函数输出指定节点的详细信息
{
    printf("%s\t%s\t%s\t%.2lf\t%d\t%d\t%d\t%d\n", L->elem.id, L->elem.ISBN, L->elem.name, L->elem.price, L->elem.booknum, L->elem.borrownum, L->elem.nownum, L->elem.Nob);
}
void Bsort(LinkList *L)//图书借阅次数排序（由高到低）        
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
void Jsort(Borrower *SL)//借阅者罚款金额排序（由高到低）            
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
Status BInitList(LinkList * L)//初始化创建一个图书链表
{
	*L = (LinkList)malloc(sizeof(struct BLNode));
	(*L)->next = NULL;
	return OK;
}
Status SInitList(Borrower * L)//初始化创建一个借阅者链表
{
	*L = (Borrower)malloc(sizeof(struct Borrower));
	(*L)->next = NULL;
	return OK;
}
Status Length(LinkList L)//计算计算图书链表长度
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
Status JLength(Borrower SL)//计算借阅者链表长度
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
Status BF(char *name, char *bname)//通过BF算法确认关键词是否在书名中
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
Status BListcreate(LinkList *L,FILE *fp)//录入图书信息
{	
	LinkList head, node, end=NULL;
	head = *L;																											
	node = (LinkList)malloc(sizeof(struct BLNode));
	if((fp = fopen("E:\\图书.txt", "r"))== NULL)
	{
		printf("未查找到相关文件，无法打开\n\n");
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
Status SListcreate(Borrower *L, FILE *fp1)//录入借阅者信息
{
	Borrower head, node, end=NULL;
	head = *L;
	node = (Borrower)malloc(sizeof(struct Borrower));
	if((fp1 = fopen("E:\\借阅者.txt", "r"))==NULL)
	{
		printf("未查到相关文件，无法打开\n\n");
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
Status BEdit(LinkList *L, int i)//对图书信息进行修改
{
    LinkList pre, e, suc;
	int flag = 0;
	pre = *L;
    e = (LinkList)malloc(sizeof(struct BLNode));
    printf("请将修改后的信息重新输入书名 IBSN 作者姓名 价格 图书总量 借阅量 在馆量 借阅次数（请按空格隔开）:\n");
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
Status JEdit(Borrower *SL, int i)//对借阅者信息进行修改
{
	Borrower pre, e, suc;
	int flag = 0;
	pre = *SL;
    e = (Borrower)malloc(sizeof(struct Borrower));
    printf("请将修改后的信息输入 学号 姓名 罚款金额（请以空格隔开）:\n");
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
Status BInsertList(LinkList *L, int i)//插入一个新的图书信息节点
{ 
	LinkList pre, e;
	int flag = 0;
	pre = *L;
    e = (LinkList)malloc(sizeof(struct BLNode));
	printf("请输入你要插入的信息书名 IBSN 作者姓名 价格 图书总量 借阅量 在馆量 借阅次数（请按空格隔开）\n");
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
Status JInsertList(Borrower *SL, int i)//插入一个新的借阅者信息节点
{
	Borrower pre, e;
	int flag = 0;
	pre = *SL;
    e = (Borrower)malloc(sizeof(struct Borrower));
	printf("请输入你要插入的借阅者信息 学号 姓名 罚款金额（请按空格隔开）\n");
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
Status DeleteList(LinkList *L, int i)//删除一个图书节点
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
Status JDeleteList(Borrower *SL, int i)//删除一个借阅者节点
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
Status Statistics(LinkList L, Borrower SL)//统计信息
{
	system("cls");
	char ch[11];
	while(1) 
	{
		printf("请输入你要统计信息的类别（图书 or 借阅者）:\n");
		scanf("%s", ch);
		if(strcmp(ch, "图书") == 0)
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
				printf("统计完毕!\n"); 
				printf("图书系统中共记录了%d本图书信息, 请输入你要输出前多少本书的信息:", Length(L));
				scanf("%d", &n);
				printf("输出统计信息\n");
				pf = L->next;
				printf("书名\t\tISBN\t\t作者\t价格  图书总量 借阅量  在馆量  借阅次数\n");
				while(pf!=NULL && i++<n)
				{
					print(pf);
					pf = pf->next;
			   	}
			   	printf("\n借阅量 在馆量 图书总数\n");
				printf("%d\t%d\t%d\n", All_borrownum, All_nownum, All_booknum);
				return OK;
			}
			else
			{
				system("cls");
				return ERROR;
			}
		}
	    else if(strcmp(ch, "借阅者") == 0)
	    {
	    	if(SL)
			{
				int i = 0, n;
			    Borrower sf = SL->next;
			    Jsort(&SL);
			    printf("统计完毕!\n"); 
			    printf("图书系统中共记录了%d位借阅者信息, 请输入你要输出前多少位借阅者信息:", JLength(SL));
				scanf("%d", &n);
				printf("统计完毕! 输出统计信息\n");
			   	printf("学号\t姓名\t罚款\n");
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
			printf("输入错误！ 请重新输入\n");
		}
	}
}
void BFind_menu(void)//查找菜单选项 
{
	sleep(1);
	printf("\t\t********欢迎大家使用图书馆查询系统********\n\n-操作选单-\n\n");
	printf("用数字选择操作\n");
	printf("1.根据书名查找\n");
    printf("2.根据ISBN查找\n");
    printf("3.根据作者查找\n");
    printf("4.根据价格区间查找\n");
    printf("5.根据书籍总数查找\n");
    printf("6.根据书籍借阅量查找\n");
    printf("7.根据书籍在馆量查找\n");
    printf("8.根据书籍借阅次数查找\n");
    printf("0.退出\n");
}
Status BFind(LinkList L)//图书查找
{
	system("cls");
    int choose = -1;
    BFind_menu();
    while(choose != 0)
    {
        printf("请输入你要进行的操作:");
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
void JFind_menu(void)//借阅者查询菜单 
{
	sleep(1);
	printf("\t\t********欢迎大家使用借阅者查询系统********\n\n-操作选单-\n\n");
	printf("用数字选择操作\n");
	printf("1.根据学号查找\n");
    printf("2.根据姓名查找\n");
    printf("3.根据罚款金额区间查找\n");
    printf("0.退出\n");
}
Status JFind(Borrower SL)//借阅者查找
{
	system("cls");
    int choose = -1;
    JFind_menu();
    while(choose != 0)
    {
        printf("请输入你要进行的操作:");
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
Status BFind_id(LinkList L)//通过书名关键字进行查找
{
    char name[81];
    LinkList pre = L->next;
    int flag = 0, i = 0;
    printf("请输入书名关键词（例如“计算机” 输入后会将书名中有“计算机”的书全部输出）\n");
    scanf("%s", name);
    system("cls");
    printf("结果如下:\n"); 
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
        printf("未查找到书名中含有关键词%s的书籍\n\n", name);
    }
    if(i!=0)
    {
    	printf("共查找到%d本书籍\n",i); 
	}
    return OK;
}
Status BFind_ISBN(LinkList L)//通过图书的ISBN进行查找
{
    char ISBN[11];
    LinkList pre = L->next;
    int i=0;
    printf("请输入图书的10位ISBN码进行查找:");
    scanf("%s", ISBN);
    system("cls");
    printf("结果如下:\n"); 
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
        printf("未查找到ISBN为%s的图书\n\n",ISBN);
    }
    if(i!=0)
    {
    	printf("共查找到%d本书籍\n", i); 
	}
    return OK;
}
Status BFind_name(LinkList L)//通过图书作者的名字进行查找
{
    char writername[51];
    LinkList pre = L;
    int i =0;
    printf("请输入图书的作者名进行查找:");
    scanf("%s", writername);
    system("cls");
    printf("结果如下:\n"); 
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
        printf("未查找到%s作者的书籍\n\n",writername);
    }
    if(i!=0)
    {
    	printf("共查找到%d本书籍\n",i); 
	}
    return OK;
}
Status BFind_price(LinkList L)//通过图书的价格区间进行查找
{
    double price, price1;
    LinkList pre = L->next;
    int i=0, temp;
    printf("请输入图书的价格区间进行查找（价格用空格隔开）:");
    scanf("%lf%lf", &price, &price1);
    if(price > price1)
    {
    	temp = price;
    	price = price1;
    	price1 = temp;
	}
    system("cls"); 
    printf("结果如下:\n"); 
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
        printf("未查找到价格区间为%.2lf~%.2lf的书籍\n\n",price, price1);
    }
    if(i!=0)
    {
    	printf("共查找到%d本书籍\n", i); 
	}
    return OK;
}
Status BFind_booknum(LinkList L)//通过图书的总量进行查找
{
    int booknum;
    LinkList pre = L->next;
    int i =0;
    printf("请输入图书的总数进行查找:");
    scanf("%d", &booknum);
    system("cls");
    printf("结果如下:\n"); 
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
        printf("未查找到总数为%d的书籍\n\n",booknum);
    }
    if(i!=0)
    {
    	printf("共查找到%d本书籍\n", i); 
	}
    return OK;
}
Status BFind_borrownum(LinkList L)//通过图书借阅量查找
{
    int borrownum;
    LinkList pre = L->next;
    int i =0;
    printf("请输入图书的借阅量进行查找:");
    scanf("%d", &borrownum);
    system("cls");
    printf("结果如下:\n"); 
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
        printf("未查找到借阅量为%d的书籍\n\n",borrownum);
    }
    if(i!=0)
    {
    	printf("共查找到%d本书籍\n", i); 
	}
    return OK;
}
Status BFind_nownum(LinkList L)//通过图书的在馆量进行查找
{
    int nownum;
    LinkList pre = L->next;
    int i =0;
    printf("请输入图书的在馆量进行查找:");
    scanf("%d", &nownum);
    system("cls");
    printf("结果如下:\n"); 
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
        printf("未查找到在馆量为%d的书籍\n\n",nownum);
    }
    if(i!=0)
    {
    	printf("共查找到%d本书籍\n", i); 
	}
    return OK;
}
Status BFind_Nob(LinkList L)//通过图书的借阅次数进行查找
{
    int Nob;
    LinkList pre = L->next;
    int i=0;
    printf("请输入图书的借阅次数进行查找:");
    scanf("%d", &Nob);
    system("cls");
    printf("结果如下:\n"); 
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
        printf("未查找到借阅次数为%d的书籍\n\n",Nob);
    }
    if(i!=0)
    {
    	printf("共查找到%d本书籍\n", i); 
	}
    return OK;
}
Status JFind_num(Borrower SL)//通过学号查找 
{
	char num[11];
    Borrower pre = SL;
    int i =0;
    printf("请输入借阅者的学号进行查找:");
    scanf("%s", num);
    system("cls");
    printf("结果如下:\n"); 
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
        printf("未查找到学号为%s的借阅者\n\n",num);
    }
    return OK;
}
Status JFind_name(Borrower SL)//通过姓名查找 
{
	char name[11];
    Borrower pre = SL;
    int i =0;
    printf("请输入借阅者的姓名进行查找:");
    scanf("%s", name);
    system("cls");
    printf("结果如下:\n"); 
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
        printf("未查找到姓名为%s的借阅者\n\n",name);
    }
    return OK;
}
Status JFind_Fine(Borrower SL)//通过罚款金额区间查找 
{
	double Fine, Fine1;
    Borrower pre = SL->next;
    int i=0, temp;
    printf("请输入借阅者的罚款金额区间进行查找（价格用空格隔开）:");
    scanf("%lf", &Fine);
    scanf("%lf", &Fine1);
    if(Fine > Fine1)
    {
    	temp = Fine;
		Fine = Fine1;
		Fine1 = temp; 
	}
    system("cls"); 
    printf("结果如下:\n"); 
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
        printf("未查找到罚款金额区间为%.2lf~%.2lf的学生\n\n",Fine);
    }
    if(i!=0)
    {
    	printf("共查找到%d位借阅者\n", i); 
	}
    return OK;
}
Status Output(LinkList L, Borrower SL)//输出信息 
{
	int i = 1;
	system("cls");
	char ch[10];
	LinkList p = L->next;
	Borrower p1 = SL->next;
	while(1) 
	{
		printf("请输入你要输出的内容(图书 or 借阅者):");
		scanf("%s", ch);
		if(strcmp(ch, "图书") == 0)
		{
			printf("序号\t书名\t\tISBN\t\t作者\t价格  图书总量 借阅量 在馆量 借阅次数\n");
			while(p)
			{
				printf("%d:\t%s\t%s\t%s\t%.2lf\t%d\t%d\t%d\t%d\n",i, p->elem.id, p->elem.ISBN, p->elem.name, p->elem.price, p->elem.booknum, p->elem.borrownum, p->elem.nownum, p->elem.Nob);
				p = p->next;
				i++; 
			}
			break;
		}
		else if(strcmp(ch, "借阅者") == 0)
		{
			int i = 1;
			printf("序号\t学号\t姓名\t罚款\n");
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
			printf("输入错误! 请重新输入\n");
			continue;
		}
	}
	return OK;
}
void menu(LinkList L, Borrower SL)//主菜单选项 
{
	sleep(1);
	printf("\t\t********欢迎大家使用图书馆管理系统********\n\n-操作选单-\n\n");
	printf("现在图书系统中记录了%d本书\n", Length(L));
	printf("现在图书系统中记录了%d位借阅者\n", JLength(SL));
	printf("用数字选择操作\n"); 
	printf("\t\t\t1.修改\n");
	printf("\t\t\t2.插入\n"); 
	printf("\t\t\t3.删除\n");
    printf("\t\t\t4.查询\n");
	printf("\t\t\t5.统计计算\n");
	printf("\t\t\t6.输出图书或借阅者的信息\n"); 
	printf("\t\t\t0.退出\n");
}
Status Zsystem(void)//总系统 
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
		printf("请输入你要操作的序号:");
		scanf("%d", &choose); 
		switch(choose)
		{
			case 1://修改图书或借阅者信息
				while(1)
				{
					printf("请输入你要修改的内容（图书 or 借阅者）:");
					scanf("%s", ch);
					if(strcmp(ch, "图书") == 0)
					{
						printf("请输入你要修改的书本的位置:");
						scanf("%d", &n);
						if(BEdit(&L,n))
						{
							printf("修改成功!\n");
						}
						else
						{
							printf("修改失败!\n");	
						}
						break; 
					}
					else if(strcmp(ch, "借阅者")==0)
					{
						printf("请输入你要修改的借阅者的位置:");
						scanf("%d", &n);
						if(JEdit(&SL,n))
						{
							printf("修改成功!\n");
						}
						else
						{
							printf("修改失败!\n");	
						}
						break; 	
					}
					else
					{
						printf("输入错误！请重新输入\n");	
					} 
				}
				menu(L, SL);
				break;
			case 2://插入新的图书或借阅者信息
				while(1)
				{
					printf("请输入你要插入到的内容（图书 or 借阅者）:");
					scanf("%s", ch);
					if(strcmp(ch, "图书") == 0)
					{
						printf("请输入你要插入的书本的位置:");
						scanf("%d", &n);
						if(BInsertList(&L,n))
						{
							printf("插入成功!\n");
						}
						else
						{
							printf("插入失败!\n");	
						}
						break; 
					}
					else if(strcmp(ch, "借阅者")==0)
					{
						printf("请输入你要插入的借阅者的位置:");
						scanf("%d", &n);
						if(JInsertList(&SL,n))
						{
							printf("插入成功!\n");
						}
						else
						{
							printf("插入失败!\n");	
						}
						break; 	
					}
					else
					{
						printf("输入错误！请重新输入\n");	
					} 
				}
				menu(L, SL);
				break;
			case 3://删除图书或借阅者信息
				while(1)
				{
					printf("请输入你要删除的内容（图书 or 借阅者）:");
					scanf("%s", ch);
					if(strcmp(ch, "图书") == 0)
					{
						printf("请输入你要删除的书本信息的位置:");
						scanf("%d", &n);
						if(DeleteList(&L,n))
						{
							printf("删除成功!\n");
						}
						else
						{
							printf("删除失败!\n");	
						}
						break; 
					}
					else if(strcmp(ch, "借阅者")==0)
					{
						printf("请输入你要删除的借阅者信息的位置:");
						scanf("%d", &n);
						if(JDeleteList(&SL,n))
						{
							printf("删除成功!\n");
						}
						else
						{
							printf("删除失败!\n");	
						}
						break; 	
					}
					else
					{
						printf("输入错误！请重新输入\n");	
					} 
				}
				menu(L, SL);
				break;
            case 4://查询图书或借阅者信息
                while(1)
				{
					printf("请输入你要查询的信息（图书 or 借阅者）:");
	                scanf("%s", ch);
	                if(strcmp(ch, "图书") == 0)
	                {
	                	if(BFind(L))
	                	{
	                		printf("查询完毕!\n"); 
	                		break;
						}
					}
					else if(strcmp(ch, "借阅者") == 0)
					{
						if(JFind(SL))
	                	{
	                		printf("查询完毕!\n"); 
	                		break;
						}
					}
					else
					{
						printf("输入错误！请重新输入\n");
					}
				} 
				menu(L, SL);
				break;
			case 5://统计计算图书信息 
				if(Statistics(L,SL))
				{
					printf("统计结束!\n");
				}
				else
				{
					printf("统计失败!\n");
				}
				menu(L, SL);
				break; 
			case 6:
				if (Output(L, SL))
				{
					printf("输出结束\n\n"); 
				}
				menu(L, SL);
				break;
			case 0:
				break; 
			default:
				printf("输入的内容无法识别，请重新输入!\n"); 
				; 
		}	
	}
	if((fp = fopen("E:\\图书.txt", "w"))== NULL || (fp1 =fopen("E:\\借阅者.txt", "w")) == NULL)//退出前将所有操作的结果重新读入文件 
	{
		printf("文件打开失败！退出失败\n\n");
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
	printf("退出成功!"); 
    fclose(fp1);
	fclose(fp);
	return OK;
}
int main()//主函数 
{
	Zsystem();
	return 0;
}

