#include<stdio.h>
#include<stdbool.h>
#include<Windows.h>
#define fileName "EmployeeInfo.txt"//�������ݵ��ļ����ļ���
#define MAX 20//id��name����󳤶�
int num = 0;//ͳ��ְ������
struct Employee//ְ�����ݽṹ��
{
	char id[MAX];//ID��
	char name[MAX];//����
	double base;//��������
	double post;//ְ����
	double allowance;//����
	double medicare;//ҽ�Ʊ���
	double fund;//������
	double salary;//�ܹ���
};
struct Node//����ڵ�ṹ��
{
	struct Employee data;//ְ������
	struct Node* next;//ָ����һ�ڵ�Ľṹ��ָ��
};

struct Node* headNode = NULL;//ָ���һ��ְ��
//��غ���
void Menu();//�˵�
void UserChoose();//�û�ѡ��
void Insert();//������ݣ�����id�����˳���������������
void Print();//��ʾ��¼������ʽ�������ְ����Ϣ���Լ�ƽ��ֵ
void PrintPart();//�����Ʒ��ֵ����ʾ��¼
void readEmployeeInfoFromFile();//���ļ��ж�ȡְ����Ϣ
void writeEmployeeInfoToFile();//��ְ����Ϣд���ļ���
void Readdata(struct Employee readdata);//�����ļ��ж�ȡ����ְ����Ϣ��ӵ�������
void SelectSearchMode();//ѡ����Ҽ�¼�ķ�ʽ
void SearchByID();//ͨ��id����
void SearchByName();//ͨ�����ֲ���
struct Node* FindByID(char id[]);
struct Node* FindByName(char Name[]);
void SelectDeleteMode();//ѡ��ɾ����ʽ
void DistroyList();//�������
void DeleteByID(char id[]);//ͨ��idɾ���ڵ�
void DeleteByName(char name[]);//ͨ������ɾ���ڵ�
void SelectChangeMode();//ѡ���޸ķ�ʽ
void ChangeAll(struct Node* temp);//�޸�ְ����ȫ����Ϣ
void ChangeID(struct Node* temp);
void ChangeName(struct Node* temp);
void ChangeBase(struct Node* temp);
void ChangePost(struct Node* temp);
void ChangeAllowance(struct Node* temp);
void ChangeMedicare(struct Node* temp);
void ChangeFund(struct Node* temp);
void Statistics();//ͳ��

int main()
{
	readEmployeeInfoFromFile();//���ļ��ж�ȡ����
	while (true)
	{
		Menu();//�˵�
		UserChoose();//�û�ѡ��
		writeEmployeeInfoToFile();//д���ļ�
		system("pause");//�����������
		system("cls");//����
	}
	while (true);//��ֹ���������˳�
	return 0;
}

void Menu()
{
	printf("-----------------------ְ�����ʹ���ϵͳ---------------------\n");
	printf("\t\t\tϵͳ��ǰְ����:%d\n", num);
	printf("\t\t\t1.��Ӽ�¼\n");
	printf("\t\t\t2.��ʾ��¼\n");
	printf("\t\t\t3.�޸ļ�¼\n");
	printf("\t\t\t4.���Ҽ�¼\n");
	printf("\t\t\t5.ɾ����¼\n");
	printf("\t\t\t6.ͳ��\n");
	printf("\t\t\t0.�˳�ϵͳ\n");
	printf("------------------------------------------------------------\n");
	printf("��������(0-6)ѡ���Ӧ����:");
}
void UserChoose()
{
	char  choose;
	scanf(" %c", &choose);
	while (getchar() != '\n')
		;
	switch (choose)
	{
	case '1':Insert();//��Ӽ�¼
		break;
	case '2':system("cls");
		Print();//��ʾ��¼
		break;
	case '3':SelectChangeMode();//�޸ļ�¼
		break;
	case '4':SelectSearchMode();//���Ҽ�¼
		break;
	case '5':SelectDeleteMode();//ɾ����¼
		break;
	case '6':Statistics();//ͳ��
		break;
	case '0':printf("�����˳�\n");//�˳�ϵͳ
		exit(0);
		break;
	default:printf("�������\n");
	}
}
void Insert()
{
	system("cls");
	struct Node* cur, * prev, * new_node;
	new_node = (struct Node*)malloc(sizeof(struct Node));
	if (new_node == NULL)
	{
		printf("���ʧ��\n");
		return;
	}
	printf("----------------������ְ������Ϣ------------------\n");
	printf("ID��:");
	scanf("%s", new_node->data.id);

	for (cur = headNode, prev = NULL;
		cur != NULL && strcmp(cur->data.id, new_node->data.id) < 0;
		prev = cur, cur = cur->next)
		;

	while (cur != NULL && strcmp(cur->data.id, new_node->data.id) == 0)
	{
		printf("id�Ѿ�����,��������\n");
		printf("ID��:");
		scanf("%s", new_node->data.id);

		for (cur = headNode, prev = NULL;
			cur != NULL && strcmp(cur->data.id, new_node->data.id) < 0;
			prev = cur, cur = cur->next)
			;
	}
	printf("����:");
	scanf("%s", new_node->data.name);
	printf("��������:");
	scanf("%lf", &new_node->data.base);
	printf("ְ����:");
	scanf("%lf", &new_node->data.post);
	printf("����:");
	scanf("%lf", &new_node->data.allowance);
	printf("ҽ�Ʊ���:");
	scanf("%lf", &new_node->data.medicare);
	printf("������:");
	scanf("%lf", &new_node->data.fund);
	new_node->data.salary = new_node->data.base + new_node->data.post + new_node->data.allowance + new_node->data.medicare + new_node->data.fund;//�޸Ĺ���֮���޸����ܹ���
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
		printf("��ǰϵͳΪ��,����Ӻ�����\n");
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
	printf("ְ��������Ϣ��\n");
	printf("ID��\t����\t��������\tְ����\t����\tҽ�Ʊ���\t������\t�ܹ���\n");
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
	printf("����ƽ������\t%.1f\t\t%.1f\t\t%.1f\t%.1f\t\t%.1f\t%.1f\n", avr1, avr2, avr3, avr4, avr5, avr6);
}
void PrintPart()
{
	struct Node* pMove;
	printf("ID��\t����\t��������\tְ����\t����\tҽ�Ʊ���\t������\t�ܹ���\n");
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
	if (read == NULL)//�жϴ��ļ��Ƿ�ɹ�
	{
		read = fopen(fileName, "w+");//���ܴ��ļ������ļ����������½�һ���ļ�
		return;
	}
	else {
		struct Employee readdata;
		while (fscanf(read, "%s\t%s\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", readdata.id, readdata.name, &readdata.base, &readdata.post, &readdata.allowance, &readdata.medicare, &readdata.fund, &readdata.salary) != EOF)
		{
			Readdata(readdata);//���ļ��е����ݱ��浽����
		}

	}
	fclose(read);//�ر��ļ�
}
void writeEmployeeInfoToFile()
{
	FILE* write = fopen(fileName, "w");//���ļ�
	struct Node* pMove = headNode;
	while (pMove)
	{
		fprintf(write, "%s\t%s\t%.0f\t%.0f\t%.0f\t%.0f\t%.0f\t%.0f\n",
			pMove->data.id, pMove->data.name, pMove->data.base, pMove->data.post,
			pMove->data.allowance, pMove->data.medicare, pMove->data.fund, pMove->data.salary);
		pMove = pMove->next;//ָ�����
	}
	//�ر��ļ�
	fclose(write);//�ر��ļ�
}
void SelectSearchMode()
{
	system("cls");
	//�ж������Ƿ�Ϊ��
	if (headNode == NULL)
	{
		printf("��ǰϵͳΪ��,����Ӻ�����\n");
		return;
	}
	char choose;
	do
	{
		printf("1.ͨ��id����\t2.ͨ����������\t0.����\n");
		printf("��ѡ��:");
		scanf(" %c", &choose);
		while (getchar() != '\n')
			;
		switch (choose)
		{
		case '1':SearchByID();//ͨ��id����
			break;
		case '2':SearchByName();//ͨ����������
			break;
		case '0'://���ز˵�
			return;
		default:printf("�����������������\n");
			break;
		}
	} while (choose > '2' || choose < '0');

}
void SearchByID()
{
	char id[MAX];
	struct Node* temp;
	printf("������ҵ�ְ����id:");
	scanf("%s", id);
	temp = FindByID(id);
	if (temp != NULL)
	{
		printf("ID��\t����\t��������\tְ����\t����\tҽ�Ʊ���\t������\t�ܹ���\n");
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
	else printf("ϵͳ����idΪ%s��ְ��", id);
}
void SearchByName()
{
	char name[MAX];
	struct Node* temp;
	printf("������ҵ�ְ��������:");
	scanf("%s", name);
	temp = FindByName(name);
	if (temp != NULL)
	{
		printf("ID��\t����\t��������\tְ����\t����\tҽ�Ʊ���\t������\t�ܹ���\n");
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
	else printf("ϵͳ��������Ϊ%s��ְ��", name);
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
		printf("��ǰϵͳΪ��,����Ӻ�����\n");
		return;
	}
	char choose;
	struct Node* temp;
	do
	{
		printf("1.ͨ��idɾ��\t2.ͨ������ɾ��\t3.���ϵͳ\t0.����\n");
		printf("��ѡ��:");
		scanf(" %c", &choose);
		while (getchar() != '\n')
			;
		switch (choose)
		{
		case '1':printf("������Ҫɾ����ְ����id:");
			char id[MAX];
			scanf("%s", id);
			temp = FindByID(id);
			while (getchar() != '\n')
				;
			if (temp != NULL)
			{
				printf("ID��\t����\t��������\tְ����\t����\tҽ�Ʊ���\t������\t�ܹ���\n");
				printf("%s\t%s\t%.0f\t\t%.0f\t\t%.0f\t%.0f\t\t%.0f\t%.0f\t\n",
					temp->data.id,
					temp->data.name,
					temp->data.base,
					temp->data.post,
					temp->data.allowance,
					temp->data.medicare,
					temp->data.fund,
					temp->data.salary);
				printf("ȷ��ɾ��Y/y\tȡ��N/n\n");
				printf("�Ƿ�ȷ��ɾ��:");
				scanf("%c", &choose);
				if (choose == 'Y' || choose == 'y')
				{
					DeleteByID(id);
					printf("ɾ���ɹ�!\n");
					num--;
				}
				else if (choose == 'N' || choose == 'n')
				{
					printf("ȡ��ɾ��\n");
				}
				else printf("�������!\n");
			}
			else printf("ϵͳ����idΪ%s��ְ��\n", id);
			break;
		case '2':
			printf("������Ҫɾ����ְ��������:");
			char name[MAX];
			scanf("%s", name);
			temp = FindByName(name);
			while (getchar() != '\n')
				;
			if (temp != NULL)
			{
				printf("ID��\t����\t��������\tְ����\t����\tҽ�Ʊ���\t������\t�ܹ���\n");
				printf("%s\t%s\t%.0f\t\t%.0f\t\t%.0f\t%.0f\t\t%.0f\t%.0f\t\n",
					temp->data.id,
					temp->data.name,
					temp->data.base,
					temp->data.post,
					temp->data.allowance,
					temp->data.medicare,
					temp->data.fund,
					temp->data.salary);
				printf("ȷ��ɾ��Y/y\tȡ��N/n\n");
				printf("�Ƿ�ȷ��ɾ��:");
				scanf("%c", &choose);
				if (choose == 'Y' || choose == 'y')
				{
					DeleteByName(name);
					printf("ɾ���ɹ�!\n");
					num--;
				}
				else if (choose == 'N' || choose == 'n')
				{
					printf("ȡ��ɾ��\n");
				}
				else printf("�������!\n");
			}
			else printf("ϵͳ��������Ϊ%s��ְ��\n", name);

			break;
		case '3':DistroyList();
			printf("��ճɹ�!\n");
			num = 0;
			break;
		case '0':
			return;
		default:printf("�����������������\n");
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
		printf("ϵͳ����idΪ%s��ְ��", id);
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
		printf("ϵͳ��������Ϊ%s��ְ��", name);
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
		printf("��ǰ��ǰϵͳΪ��,����Ӻ�����\n");
		return;
	}
	double people = 0;
	double minSalary;
	double maxSalary;
	printf("���빤�ʷ�Χ\n");
	printf("��͹���:");
	scanf("%lf", &minSalary);
	printf("��߹���:");
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
	printf("ְ������ǰ����֮����%.0f~%.0f֮���������%.0f��,ռ��������%.0f%%\n", minSalary, maxSalary, people, percent);
	
}
void SelectChangeMode()
{
	system("cls");
	if (headNode == NULL)
	{
		printf("��ǰϵͳΪ��,����Ӻ�����\n");
		return;
	}
	PrintPart();
	char id[MAX];
	struct Node* temp;
	printf("����Ҫ�޸ĵ�ְ����id:");
	scanf("%s", id);
	temp = FindByID(id);
	if (temp != NULL)
	{
		system("cls");
		printf("ID��\t����\t��������\tְ����\t����\tҽ�Ʊ���\t������\t�ܹ���\n");
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
		printf("1.�޸�ȫ����Ϣ\t2.�޸�ID\t3.�޸�����\t4.�޸Ļ�������\t5.�޸�ְ����\n6.�޸Ľ���\t7.�޸�ҽ�Ʊ���\t8.�޸Ĺ�����\t9.����\n");
		printf("��ѡ���޸ķ�ʽ:");
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
			default:printf("�����������������\n");
				break;
			}
			if (choose != '2' && choose != '3')	temp->data.salary = temp->data.base + temp->data.post + temp->data.allowance + temp->data.medicare + temp->data.fund;
		} while (choose > '9' || choose < '1');
		printf("�޸ĳɹ�!\n");
	}
	else
	{
		printf("ϵͳ����idΪ%s��ְ��\n", id);
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
		printf("�������޸ĺ��id:");
		scanf("%s", id);
		p = FindByID(id);
		if (p != NULL) printf("id�Ѿ�����,����������\n");
	} while (p != NULL);
	strcpy(temp->data.id, id);
}
void ChangeName(struct Node* temp)
{
	printf("�������޸ĺ������:");
	scanf("%s", temp->data.name);
}
void ChangeBase(struct Node* temp)
{
	printf("�������޸ĺ�Ļ�������:");
	scanf("%lf", &temp->data.base);
}
void ChangePost(struct Node* temp)
{
	printf("�������޸ĺ��ְ����:");
	scanf("%lf", &temp->data.post);
}
void ChangeAllowance(struct Node* temp)
{
	printf("�������޸ĺ�Ľ���:");
	scanf("%lf", &temp->data.allowance);
}
void ChangeMedicare(struct Node* temp)
{
	printf("�������޸ĺ��ҽ�Ʊ���:");
	scanf("%lf", &temp->data.medicare);
}
void ChangeFund(struct Node* temp)
{
	printf("�������޸ĺ�Ĺ�����:");
	scanf("%lf", &temp->data.fund);
}
