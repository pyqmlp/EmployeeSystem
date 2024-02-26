#include<stdio.h>
#include<stdbool.h>
#include<Windows.h>
#define fileName "EmployeeInfo.txt"//保存数据的文件的文件名
#define MAX 20//id或name的最大长度
int num = 0;//统计职工人数
struct Employee//职工数据结构体
{
	char id[MAX];//ID号
	char name[MAX];//姓名
	double base;//基本工资
	double post;//职务工资
	double allowance;//津贴
	double medicare;//医疗保险
	double fund;//公积金
	double salary;//总工资
};
struct Node//链表节点结构体
{
	struct Employee data;//职工数据
	struct Node* next;//指向下一节点的结构体指针
};

struct Node* headNode = NULL;//指向第一个职工
//相关函数
void Menu();//菜单
void UserChoose();//用户选择
void Insert();//添加数据，按照id升序的顺序向链表添加数据
void Print();//显示记录，按格式化表输出职工信息，以及平均值
void PrintPart();//不输出品均值的显示记录
void readEmployeeInfoFromFile();//从文件中读取职工信息
void writeEmployeeInfoToFile();//把职工信息写入文件中
void Readdata(struct Employee readdata);//将从文件中读取到的职工信息添加到链表中
void SelectSearchMode();//选择查找记录的方式
void SearchByID();//通过id查找
void SearchByName();//通过名字查找
struct Node* FindByID(char id[]);
struct Node* FindByName(char Name[]);
void SelectDeleteMode();//选择删除方式
void DistroyList();//清空链表
void DeleteByID(char id[]);//通过id删除节点
void DeleteByName(char name[]);//通过名字删除节点
void SelectChangeMode();//选择修改方式
void ChangeAll(struct Node* temp);//修改职工的全部信息
void ChangeID(struct Node* temp);
void ChangeName(struct Node* temp);
void ChangeBase(struct Node* temp);
void ChangePost(struct Node* temp);
void ChangeAllowance(struct Node* temp);
void ChangeMedicare(struct Node* temp);
void ChangeFund(struct Node* temp);
void Statistics();//统计

int main()
{
	readEmployeeInfoFromFile();//从文件中读取数据
	while (true)
	{
		Menu();//菜单
		UserChoose();//用户选择
		writeEmployeeInfoToFile();//写入文件
		system("pause");//按任意键继续
		system("cls");//清屏
	}
	while (true);//防止程序意外退出
	return 0;
}

void Menu()
{
	printf("-----------------------职工工资管理系统---------------------\n");
	printf("\t\t\t系统当前职工数:%d\n", num);
	printf("\t\t\t1.添加记录\n");
	printf("\t\t\t2.显示记录\n");
	printf("\t\t\t3.修改记录\n");
	printf("\t\t\t4.查找记录\n");
	printf("\t\t\t5.删除记录\n");
	printf("\t\t\t6.统计\n");
	printf("\t\t\t0.退出系统\n");
	printf("------------------------------------------------------------\n");
	printf("请根据序号(0-6)选择对应功能:");
}
void UserChoose()
{
	char  choose;
	scanf(" %c", &choose);
	while (getchar() != '\n')
		;
	switch (choose)
	{
	case '1':Insert();//添加记录
		break;
	case '2':system("cls");
		Print();//显示记录
		break;
	case '3':SelectChangeMode();//修改记录
		break;
	case '4':SelectSearchMode();//查找记录
		break;
	case '5':SelectDeleteMode();//删除记录
		break;
	case '6':Statistics();//统计
		break;
	case '0':printf("正常退出\n");//退出系统
		exit(0);
		break;
	default:printf("输入错误\n");
	}
}
void Insert()
{
	system("cls");
	struct Node* cur, * prev, * new_node;
	new_node = (struct Node*)malloc(sizeof(struct Node));
	if (new_node == NULL)
	{
		printf("添加失败\n");
		return;
	}
	printf("----------------请输入职工的信息------------------\n");
	printf("ID号:");
	scanf("%s", new_node->data.id);

	for (cur = headNode, prev = NULL;
		cur != NULL && strcmp(cur->data.id, new_node->data.id) < 0;
		prev = cur, cur = cur->next)
		;

	while (cur != NULL && strcmp(cur->data.id, new_node->data.id) == 0)
	{
		printf("id已经存在,重新输入\n");
		printf("ID号:");
		scanf("%s", new_node->data.id);

		for (cur = headNode, prev = NULL;
			cur != NULL && strcmp(cur->data.id, new_node->data.id) < 0;
			prev = cur, cur = cur->next)
			;
	}
	printf("姓名:");
	scanf("%s", new_node->data.name);
	printf("基本工资:");
	scanf("%lf", &new_node->data.base);
	printf("职务工资:");
	scanf("%lf", &new_node->data.post);
	printf("津贴:");
	scanf("%lf", &new_node->data.allowance);
	printf("医疗保险:");
	scanf("%lf", &new_node->data.medicare);
	printf("公积金:");
	scanf("%lf", &new_node->data.fund);
	new_node->data.salary = new_node->data.base + new_node->data.post + new_node->data.allowance + new_node->data.medicare + new_node->data.fund;//修改工资之后修改找总工资
	new_node->next = cur;
	if (prev == NULL) headNode = new_node;
	else prev->next = new_node;
	num++;
}
void Readdata(struct Employee readdata)
{
	struct Node* cur, * prev, * new_node;
	new_node = (struct Node*)malloc(sizeof(struct Node));
	for (cur = headNode, prev = NULL;
		cur != NULL && strcmp(cur->data.id, new_node->data.id) < 0;
		prev = cur, cur = cur->next)
		;
	strcpy(new_node->data.id, readdata.id);
	strcpy(new_node->data.name, readdata.name);
	new_node->data.base = readdata.base;
	new_node->data.post = readdata.post;
	new_node->data.allowance = readdata.allowance;
	new_node->data.medicare = readdata.medicare;
	new_node->data.fund = readdata.fund;
	new_node->data.salary = new_node->data.base + new_node->data.post + new_node->data.allowance + new_node->data.medicare + new_node->data.fund;
	new_node->next = cur;
	if (prev == NULL) headNode = new_node;
	else prev->next = new_node;
	num++;
}
void Print()
{
	
	if (headNode == NULL)
	{
		printf("当前系统为空,请添加后重试\n");
		return;
	}

	struct Node* pMove;
	double sum1 = 0;
	double avr1 = 0;
	double sum2 = 0;
	double avr2 = 0;
	double sum3 = 0;
	double avr3 = 0;
	double sum4 = 0;
	double avr4 = 0;
	double sum5 = 0;
	double avr5 = 0;
	double sum6 = 0;
	double avr6 = 0;
	printf("职工工资信息表\n");
	printf("ID号\t姓名\t基本工资\t职务工资\t津贴\t医疗保险\t公积金\t总工资\n");
	for (pMove = headNode; pMove != NULL; pMove = pMove->next)
	{
		printf("%s\t%s\t%.0f\t\t%.0f\t\t%.0f\t%.0f\t\t%.0f\t%.0f\t\n",
			pMove->data.id,
			pMove->data.name,
			pMove->data.base,
			pMove->data.post,
			pMove->data.allowance,
			pMove->data.medicare,
			pMove->data.fund,
			pMove->data.salary);
		sum1 += pMove->data.base;
		sum2 += pMove->data.post;
		sum3 += pMove->data.allowance;
		sum4 += pMove->data.medicare;
		sum5 += pMove->data.fund;
		sum6 += pMove->data.salary;
	}
	avr1 = sum1 / num;
	avr2 = sum2 / num;
	avr3 = sum3 / num;
	avr4 = sum4 / num;
	avr5 = sum5 / num;
	avr6 = sum6 / num;
	printf("--------------------------------------------------------------------------------------\n");
	printf("各项平均工资\t%.1f\t\t%.1f\t\t%.1f\t%.1f\t\t%.1f\t%.1f\n", avr1, avr2, avr3, avr4, avr5, avr6);
}
void PrintPart()
{
	struct Node* pMove;
	printf("ID号\t姓名\t基本工资\t职务工资\t津贴\t医疗保险\t公积金\t总工资\n");
	for (pMove = headNode; pMove != NULL; pMove = pMove->next)
	{
		printf("%s\t%s\t%.0f\t\t%.0f\t\t%.0f\t%.0f\t\t%.0f\t%.0f\t\n",
			pMove->data.id,
			pMove->data.name,
			pMove->data.base,
			pMove->data.post,
			pMove->data.allowance,
			pMove->data.medicare,
			pMove->data.fund,
			pMove->data.salary);
	}
	printf("--------------------------------------------------------------------------------------\n");
}
void readEmployeeInfoFromFile()
{
	FILE* read = fopen(fileName, "r");
	if (read == NULL)//判断打开文件是否成功
	{
		read = fopen(fileName, "w+");//不能打开文件或者文件不存在则新建一个文件
		return;
	}
	else {
		struct Employee readdata;
		while (fscanf(read, "%s\t%s\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", readdata.id, readdata.name, &readdata.base, &readdata.post, &readdata.allowance, &readdata.medicare, &readdata.fund, &readdata.salary) != EOF)
		{
			Readdata(readdata);//将文件中的数据保存到链表
		}

	}
	fclose(read);//关闭文件
}
void writeEmployeeInfoToFile()
{
	FILE* write = fopen(fileName, "w");//打开文件
	struct Node* pMove = headNode;
	while (pMove)
	{
		fprintf(write, "%s\t%s\t%.0f\t%.0f\t%.0f\t%.0f\t%.0f\t%.0f\n",
			pMove->data.id, pMove->data.name, pMove->data.base, pMove->data.post,
			pMove->data.allowance, pMove->data.medicare, pMove->data.fund, pMove->data.salary);
		pMove = pMove->next;//指针后移
	}
	//关闭文件
	fclose(write);//关闭文件
}
void SelectSearchMode()
{
	system("cls");
	//判断链表是否为空
	if (headNode == NULL)
	{
		printf("当前系统为空,请添加后重试\n");
		return;
	}
	char choose;
	do
	{
		printf("1.通过id查找\t2.通过姓名查找\t0.返回\n");
		printf("请选择:");
		scanf(" %c", &choose);
		while (getchar() != '\n')
			;
		switch (choose)
		{
		case '1':SearchByID();//通过id查找
			break;
		case '2':SearchByName();//通过姓名查找
			break;
		case '0'://返回菜单
			return;
		default:printf("输入错误，请重新输入\n");
			break;
		}
	} while (choose > '2' || choose < '0');

}
void SearchByID()
{
	char id[MAX];
	struct Node* temp;
	printf("输入查找的职工的id:");
	scanf("%s", id);
	temp = FindByID(id);
	if (temp != NULL)
	{
		printf("ID号\t姓名\t基本工资\t职务工资\t津贴\t医疗保险\t公积金\t总工资\n");
		printf("%s\t%s\t%.0f\t\t%.0f\t\t%.0f\t%.0f\t\t%.0f\t%.0f\t\n",
			temp->data.id,
			temp->data.name,
			temp->data.base,
			temp->data.post,
			temp->data.allowance,
			temp->data.medicare,
			temp->data.fund,
			temp->data.salary);
	}
	else printf("系统中无id为%s的职工", id);
}
void SearchByName()
{
	char name[MAX];
	struct Node* temp;
	printf("输入查找的职工的姓名:");
	scanf("%s", name);
	temp = FindByName(name);
	if (temp != NULL)
	{
		printf("ID号\t姓名\t基本工资\t职务工资\t津贴\t医疗保险\t公积金\t总工资\n");
		printf("%s\t%s\t%.0f\t\t%.0f\t\t%.0f\t%.0f\t\t%.0f\t%.0f\t\n",
			temp->data.id,
			temp->data.name,
			temp->data.base,
			temp->data.post,
			temp->data.allowance,
			temp->data.medicare,
			temp->data.fund,
			temp->data.salary);
	}
	else printf("系统中无姓名为%s的职工", name);
}
struct Node* FindByID(char id[])
{
	struct Node* p;
	for (p = headNode;
		p != NULL && strcmp(p->data.id, id) < 0;
		p = p->next)
		;
	if (p != NULL && strcmp(p->data.id, id) == 0)
		return p;
	return NULL;
}
struct Node* FindByName(char name[])
{
	struct Node* p;
	for (p = headNode;
		p != NULL && strcmp(p->data.name, name) != 0;
		p = p->next)
		;
	if (p != NULL && strcmp(p->data.name, name) == 0)
		return p;
	return NULL;
}
void SelectDeleteMode()
{
	system("cls");
	if (headNode == NULL)
	{
		printf("当前系统为空,请添加后重试\n");
		return;
	}
	char choose;
	struct Node* temp;
	do
	{
		printf("1.通过id删除\t2.通过姓名删除\t3.清空系统\t0.返回\n");
		printf("请选择:");
		scanf(" %c", &choose);
		while (getchar() != '\n')
			;
		switch (choose)
		{
		case '1':printf("请输入要删除的职工的id:");
			char id[MAX];
			scanf("%s", id);
			temp = FindByID(id);
			while (getchar() != '\n')
				;
			if (temp != NULL)
			{
				printf("ID号\t姓名\t基本工资\t职务工资\t津贴\t医疗保险\t公积金\t总工资\n");
				printf("%s\t%s\t%.0f\t\t%.0f\t\t%.0f\t%.0f\t\t%.0f\t%.0f\t\n",
					temp->data.id,
					temp->data.name,
					temp->data.base,
					temp->data.post,
					temp->data.allowance,
					temp->data.medicare,
					temp->data.fund,
					temp->data.salary);
				printf("确认删除Y/y\t取消N/n\n");
				printf("是否确认删除:");
				scanf("%c", &choose);
				if (choose == 'Y' || choose == 'y')
				{
					DeleteByID(id);
					printf("删除成功!\n");
					num--;
				}
				else if (choose == 'N' || choose == 'n')
				{
					printf("取消删除\n");
				}
				else printf("输入错误!\n");
			}
			else printf("系统中无id为%s的职工\n", id);
			break;
		case '2':
			printf("请输入要删除的职工的姓名:");
			char name[MAX];
			scanf("%s", name);
			temp = FindByName(name);
			while (getchar() != '\n')
				;
			if (temp != NULL)
			{
				printf("ID号\t姓名\t基本工资\t职务工资\t津贴\t医疗保险\t公积金\t总工资\n");
				printf("%s\t%s\t%.0f\t\t%.0f\t\t%.0f\t%.0f\t\t%.0f\t%.0f\t\n",
					temp->data.id,
					temp->data.name,
					temp->data.base,
					temp->data.post,
					temp->data.allowance,
					temp->data.medicare,
					temp->data.fund,
					temp->data.salary);
				printf("确认删除Y/y\t取消N/n\n");
				printf("是否确认删除:");
				scanf("%c", &choose);
				if (choose == 'Y' || choose == 'y')
				{
					DeleteByName(name);
					printf("删除成功!\n");
					num--;
				}
				else if (choose == 'N' || choose == 'n')
				{
					printf("取消删除\n");
				}
				else printf("输入错误!\n");
			}
			else printf("系统中无姓名为%s的职工\n", name);

			break;
		case '3':DistroyList();
			printf("清空成功!\n");
			num = 0;
			break;
		case '0':
			return;
		default:printf("输入错误，请重新输入\n");
			break;
		}
	} while (choose > '3' || choose < '0');

}
void DistroyList()
{

	struct Node* cur, * next;
	cur = headNode;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	headNode = NULL;
}
void DeleteByID(char id[])
{
	struct Node* cur, * prev;
	for (cur = headNode, prev = NULL;
		strcmp(cur->data.id, id) != 0 && cur != NULL;
		prev = cur, cur = cur->next)
		;
	if (cur == NULL)
		printf("系统中无id为%s的职工", id);
	if (prev == NULL)
		headNode = headNode->next;
	else
		prev->next = cur->next;
}
void DeleteByName(char name[])
{
	struct Node* cur, * prev;
	for (cur = headNode, prev = NULL;
		strcmp(cur->data.name, name) != 0 && cur != NULL;
		prev = cur, cur = cur->next)
		;
	if (cur == NULL)
		printf("系统中无姓名为%s的职工", name);
	if (prev == NULL)
		headNode = headNode->next;
	else
		prev->next = cur->next;
}
void Statistics()
{
	system("cls");
	if (headNode == NULL)
	{
		printf("当前当前系统为空,请添加后重试\n");
		return;
	}
	double people = 0;
	double minSalary;
	double maxSalary;
	printf("输入工资范围\n");
	printf("最低工资:");
	scanf("%lf", &minSalary);
	printf("最高工资:");
	scanf("%lf", &maxSalary);
	struct Node* pMove = headNode; 
	for (; pMove != NULL; pMove = pMove->next)
	{
		double sum = 0;
		sum = sum + pMove->data.base + pMove->data.post + pMove->data.allowance;
		if (sum >= minSalary && sum <= maxSalary) people++;
	}
	double percent = people / num * 100;
	system("cls");
	Print();
	printf("职工工资前三项之和在%.0f~%.0f之间的人数有%.0f人,占总人数的%.0f%%\n", minSalary, maxSalary, people, percent);
	
}
void SelectChangeMode()
{
	system("cls");
	if (headNode == NULL)
	{
		printf("当前系统为空,请添加后重试\n");
		return;
	}
	PrintPart();
	char id[MAX];
	struct Node* temp;
	printf("输入要修改的职工的id:");
	scanf("%s", id);
	temp = FindByID(id);
	if (temp != NULL)
	{
		system("cls");
		printf("ID号\t姓名\t基本工资\t职务工资\t津贴\t医疗保险\t公积金\t总工资\n");
		printf("%s\t%s\t%.0f\t\t%.0f\t\t%.0f\t%.0f\t\t%.0f\t%.0f\t\n",
			temp->data.id,
			temp->data.name,
			temp->data.base,
			temp->data.post,
			temp->data.allowance,
			temp->data.medicare,
			temp->data.fund,
			temp->data.salary);
		printf("--------------------------------------------------------------------------------------\n");
		printf("1.修改全部信息\t2.修改ID\t3.修改姓名\t4.修改基本工资\t5.修改职务工资\n6.修改津贴\t7.修改医疗保险\t8.修改公积金\t9.返回\n");
		printf("请选择修改方式:");
		char choose;
		do
		{
			scanf(" %c", &choose);
			while (getchar() != '\n')
				;
			switch (choose)
			{
			case '1':ChangeAll(temp);
				break;
			case '2':ChangeID(temp);
				break;
			case '3':ChangeName(temp);
				break;
			case '4':ChangeBase(temp);
				break;
			case '5':ChangePost(temp);
				break;
			case '6':ChangeAllowance(temp);
				break;
			case '7':ChangeMedicare(temp);
				break;
			case '8':ChangeFund(temp);
				break;
			case '9':return;
			default:printf("输入错误，请重新输入\n");
				break;
			}
			if (choose != '2' && choose != '3')	temp->data.salary = temp->data.base + temp->data.post + temp->data.allowance + temp->data.medicare + temp->data.fund;
		} while (choose > '9' || choose < '1');
		printf("修改成功!\n");
	}
	else
	{
		printf("系统中无id为%s的职工\n", id);
	}
}
void ChangeAll(struct Node* temp)
{
	ChangeName(temp);
	ChangeBase(temp);
	ChangePost(temp);
	ChangeAllowance(temp);
	ChangeMedicare(temp);
	ChangeFund(temp);
}
void ChangeID(struct Node* temp)
{
	struct Node* p;
	char id[20];
	do
	{
		printf("请输入修改后的id:");
		scanf("%s", id);
		p = FindByID(id);
		if (p != NULL) printf("id已经存在,请重新输入\n");
	} while (p != NULL);
	strcpy(temp->data.id, id);
}
void ChangeName(struct Node* temp)
{
	printf("请输入修改后的姓名:");
	scanf("%s", temp->data.name);
}
void ChangeBase(struct Node* temp)
{
	printf("请输入修改后的基本工资:");
	scanf("%lf", &temp->data.base);
}
void ChangePost(struct Node* temp)
{
	printf("请输入修改后的职务工资:");
	scanf("%lf", &temp->data.post);
}
void ChangeAllowance(struct Node* temp)
{
	printf("请输入修改后的津贴:");
	scanf("%lf", &temp->data.allowance);
}
void ChangeMedicare(struct Node* temp)
{
	printf("请输入修改后的医疗保险:");
	scanf("%lf", &temp->data.medicare);
}
void ChangeFund(struct Node* temp)
{
	printf("请输入修改后的公积金:");
	scanf("%lf", &temp->data.fund);
}
