#include<stdio.h>
#include<string.h>
#include<Windows.h>
#include<time.h>
#include<conio.h>
#include <stdlib.h>



void cover();
void game();
void help();
void relevant();

void graph();                 //Χǽ��ӡ   ͬʱ���� ����
void gotoxy(int x, int y);    //�����ת����ΪX 0,1,2..
void gotoprint(int x, int y); //�����ת��ӡ
void gotodelete(int x, int y);//�����תɾ��
void creatfood();             //�������ʳ��   Ҫ��
int ClickControl();           //��ȡ�����ź�  ��֪ʶ����ʱ��ȡ�����źź�����
int Judge();                  //��Ϸ�����ж�
void MovingBody();            //�ߵ��ƶ�
void eating();                //�߳Ե�������Ĳ������쳤��
void ChangeBody(int a,int b); //�ߵ�����任,��һ������ǰһ��STRUCT,a,bΪhead֮ǰ����
void Finish();                //��������   ��ʾ����
void createnermy();           //�����������     ����ͼ���Χǽ��ͬ  ���ŷ�����ÿһ�α仯����������


  void savedata(int scores);    //�������  �Ա������ʷ��߷ֵıȽ�  ������cԴ��������·����ļ��� scores.bin
int * loaddata();			  //��ȡ����  ����һάָ��   �Ǵ�1��ʼ��  ���飡����
void sort(int * scores);      //�����Ҵ�ӡ �Ӵ�С     �Ǵ�1��ʼ�ŵ�
void printfline(int x, int y);
void printfrow(int x,int y);
void printfcover();
void graph2();
int scanfnum();               //���������



/*ȫ�ֱ��� + Ԥ����*/
 struct Snakes
{
	int x;
	int y;
	struct Snakes *next;
};
 typedef struct Snakes snake;
snake *head,*tail;
int freephead(snake*phead);  //�ͷ�ָ������

struct Food
{
	int x;
	int y;
}food;
char name[20];
  unsigned int score = 0;
char click = 1;
int speed;
 int number = 9;   				//���ݶ���ĸ���   ȫ�ֱ�����


struct enermy
{
	int x;
	int y;

};
 struct enermy enermy[6];              //3������  ���ɴ���




int main()
{

	pal:
	cover();
	system("cls");
	graph();
	creatfood();
	createnermy();
	ClickControl();
	click = 0;
	//reephead(head);

	goto pal;


	return 0;
}




void graph()
{
	score = 0;
	int i;
	for (i = 0; i<58; i += 2)
	{
		gotoprint(i, 0);
		gotoprint(i, 26);
	}
	for (i = 1; i < 26; i++)
	{
		gotoprint(0, i);
		gotoprint(56, i);
	}
	gotoxy(77,14);
	printf("Score:");
	gotoxy(77,15);
	printf("%u",score);
	head = (snake*)malloc(sizeof(snake));
	head->x = 16;
	head->y = 15;

	tail = (snake*)malloc(sizeof(snake));
	snake *p = (snake*)malloc(sizeof(snake));
	snake *q = (snake*)malloc(sizeof(snake));
	p->x = 16;
	p->y = 16;
	q->x = 16;
	q->y = 17;
	head->next = p;
	p->next = q;
	q->next = tail;
	tail->next = NULL;
	tail->x = 4;
	tail->y = 2;

}

void gotoxy(int x, int y)
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}

void gotoprint(int x, int y)
{
	gotoxy(x, y);
	printf("��");
}

void gotodelete(int x, int y)
{
	gotoxy(x, y);
	printf("  ");
}

void creatfood()
{
	srand((int)time(NULL));
	lab:
	food.y = rand() % (25 - 1 + 1) + 1;
	food.x = rand() % (54 - 2 + 1) + 2;
	if (food.x % 2 != 0)
	{
		food.x = food.x+1;
	}
	snake *judge = head;
	for(;;)
	{
		if (judge->next == NULL) break;
		if (food.x == judge->x&&food.y == judge->y)
		{
			goto lab;
		}
		judge = judge->next;
	}
	gotoxy(food.x, food.y);
	printf("��");
}

int ClickControl()
{
	char c; int n = 0;
	for(;;)
	{   n++;
	    /*if(n==1)
	    {
	    	if (_kbhit())
		 {
			click = _getch();
			if(click == 's') click = 'w';
			fflush(stdin);

		 }
		}*/
		if (Judge()==0) return 0;
		if (_kbhit())
		{
			c = _getch();
			if((c=='a'&&click!='d')||(c=='w'&&click!='s')||(c=='d'&&click!='a')||(c=='s'&&click!='w'))
			{
				click = c;
			}

		}
		MovingBody();
		eating();
	}
	return 1;
}

void MovingBody()
{
	int count = 0;
	int a = head->x, b = head->y;
	snake *p = head;
	//ͨ������պ��ӡʵ�ֶ���Ч��
	for(;;)
	{
		if (p->next == NULL) break;
		gotodelete(p->x, p->y);
		count++;
		p = p->next;
	}
	switch (click)
	{
		case 'w':
			head->y -= 1;
			ChangeBody(a,b);
			break;
		case 's':
			head->y += 1;
			ChangeBody(a,b);
			break;
		case 'a':
			head->x -= 2;
			ChangeBody(a,b);
			break;
		case 'd':
			head->x += 2;
			ChangeBody(a,b);
			break;
		case 'p':
			   click = 1;
			break;
	}
	p = head;
	for(;;)
	{
		if (p->next == NULL) break;
		gotoprint(p->x, p->y);
		p = p->next;
	}
	p = head;
	gotoxy(0, 28);
	if (count <= 10) speed = 150;                   //�޸�
	else if (count > 10 && count <= 20) speed = 120;
	else if (count > 20 && count <= 40) speed = 80;
	else speed = 40;
	Sleep(speed);
}

void eating()
{
	if (head->x == food.x&&head->y == food.y)
	{
		creatfood();
		snake *_new = (snake*)malloc(sizeof(snake));
		snake *p;
		p = head;
		for(;;)
		{
			if (p->next->next == NULL) break;
			p = p->next;
		}
		p->next = _new;
		_new->next = tail;
		score += 5;
		gotoxy(77, 15);
		printf("%u", score);
		int i = 0;
		for(i=0;i<6;i++)
		{
			gotodelete(enermy[i].x,enermy[i].y);
		}

		createnermy();
		graph2();
	}
}

void ChangeBody(int a,int b)
{
	snake *p = head->next;
	int mid1, mid2,_mid1,_mid2;
	mid1 = p->x;
	mid2 = p->y;
	for(;;)
	{
		if (p->next->next == NULL) break;
		_mid1 = p->next->x;
		_mid2 = p->next->y;
		p->next->x = mid1;
		p->next->y = mid2;
		mid1 = _mid1;
		mid2 = _mid2;
		p = p->next;
	}
	p = head->next;

	{
		p->x = a;
		p->y = b;
	}
}

int Judge()
{
	if (head->x == 0|| head->x == 56 || head->y == 0 || head->y == 26)
	{
		Finish();
		return 0;
	}
	int i=0;
	for(i=0;i<6;i++)
    {
    	if(head->x ==enermy[i].x&&head->y ==enermy[i].y)
	{
		Finish();
		return 0;
	}
	}

	snake *p = head->next;
	for(;;)
	{
		if (p->next == NULL) break;
		if (head->x == p->x&&head->y == p->y)
		{
			Finish();
			return 0;
		}
		p = p->next;
	}
	return 1;
}

void Finish()
{
	savedata(score);


	system("cls");

	gotoxy(18, 14);
	printf("��Ϸ����");
	gotoxy(16, 16);
	printf(" Final Score is %u", score);

	gotoxy(0, 27);//freephead (head);
	system("pause");fflush(stdin);
}
void createnermy()
{
    int i = 0;
	for(i=0;i<6;i++)
	{

		lable:
	srand((int)time(NULL)*(i+2));
    enermy[i].y = rand() % (25 - 1 + 1) + 1;
	enermy[i].x = rand() % (54 - 2 + 1) + 2;
	if (enermy[i].x % 2 != 0)
	{
		enermy[i].x = enermy[i].x+1;
	}
	snake *judge = head;
	for(;;)
	{
		if (judge->next == NULL) break;
		if (enermy[i].x == judge->x&&enermy[i].y == judge->y)
		{
			goto lable;
		}
		judge = judge->next;
	}
	if(enermy[i].x ==food.x&&enermy[i].y==food.y)
	{
		goto lable;
	}
	gotoxy(enermy[i].x, enermy[i].y);
	printf("��");
	}

}

void savedata(int scores)
{
	FILE*ph;
	ph = fopen("scores.bin","ab+");
    if(ph ==NULL)
    {
        ph = fopen("scores.bin","wb+");
    }

	fputc(scores,ph);
	fclose(ph);
}
 int * loaddata()
 {
 	int * p;
 	FILE * ph;
	p = (int *)malloc(sizeof(int)*100);
 	ph=fopen("scores.bin","rb");
 	int i=1;
	  do
 	 {

 	 	p[i] = fgetc(ph);
 	 	i++;

	  }while(p[i-1]!=EOF);
 	   number = i-2;
 	   fclose(ph);
	return p;                     //��������ݸ���Ϊ i-2��
 }
 void cover()
{
	int choice = 0, i;
	system("cls");
	printfcover();
	gotoxy(53, 10);
	printf("̰����\n");
	gotoxy(52, 11);
	printf("1.��ʼ��Ϸ.\n");
	gotoxy(52, 12);
	printf("2.����.\n");
	gotoxy(52, 13);
	printf("3.�����Ϣ.\n");
	gotoxy(52, 14);
	printf("4.�˳�.\n");
	gotoxy(25, 17);
	printf("��ѡ���ܼ�:");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:game();
			break;
		case 2:help();
			break;
		case 3:relevant();
			break;
		case 4:exit(0);
			break;
		default:
			printf("û�����ѡ��.\n");
	}




}
void game()
{   printfcover();
	gotoxy(52, 11);
	printf("          ");
	gotoxy(52, 12);
	printf("       ");
	gotoxy(52, 13);
	printf("           \n");
	gotoxy(52, 14);
	printf("         \n");
	gotoxy(25, 17);
	printf("               ");
	gotoxy(52, 11);
	printf("1����ʼ�µ���Ϸ\n");
	gotoxy(52, 12);
	printf("2����ʷ��������\n");
	gotoxy(52, 13);
	printf("3������\n");
	gotoxy(25, 17);
	printf("��ѡ���ܼ�:");
	int choice1 ;
	choice1 = scanfnum();
	if(choice1 ==1)
	{
	}
	if(choice1 ==2)
	{   int *p;
        system("cls");
		p = loaddata();
		sort(p);
		system("pause");
		system("cls");
		game();

	}
	if(choice1 == 3) cover();
}
void help()//�����������˽���Ϸ
{

	int choice = 1;
	system("cls");
	printfcover();
	gotoxy(27, 9);
	printf("��Ϸ��������:w,��:s,��:a,��:d.\n");
	gotoxy(27, 10);
	printf("ע���������ײ��ǽ�ڣ�������������.\n");
	gotoxy(27, 11);
	printf("�����밴0.\n");
	gotoxy(25, 17);
	scanf("%d",&choice);
	switch(choice)
	{
		case 0:cover();
			break;
		default:
			printf("û�����ѡ��.\n");
	}


}
void relevant()
{
	int choice = 1, i;
	system("cls");
	printfcover();
	gotoxy(27, 9);
	printf("��������:̰����.\n");
	gotoxy(27, 10);
	printf("�汾��Ϣ:̰����1��.\n");
	gotoxy(27, 11);
	printf("����ʱ��:2019/1/1.\n");
	gotoxy(27, 12);
	printf("������:YYQvigeto  ѧ��:xxxxxxxxx  רҵ:xxxx  �༶:xxx\n");
	gotoxy(27, 13);

	gotoxy(27, 14);

	gotoxy(27, 15);
	printf("�����밴0.\n");
	gotoxy(25, 17);
	scanf("%d",&choice);
	switch(choice)
	{
		case 0:cover();
			break;
		default:
			printf("û�����ѡ��.\n");
	}


}
void sort(int * scores)
{   int i,j,k;
	unsigned int *num;                   //ת��
	num = (unsigned int *)malloc(sizeof(unsigned int )*(number+1));
	for(i=1;i<=number;i++)
	{
		num[i] = scores[i];

	}
	for(j = 1;j<=number-1;j++)
	{
		for(k=1;k<=number-1;k++)
		{
			int num1;
			if(num[k]<num[k+1])
			{
				num1 = num[k];
				num[k]= num[k+1];
				num[k+1] = num1;

			}
		}
	}
	gotoxy(54,17);
	printf("	��ʷ������������  ");
	putchar('\n');
	int z;
	for(z = 1;z<=number;z++)
	{
		gotoxy(54,17+z);
		printf("%d��%u\n",z,num[z]);
	}


}

 int scanfnum()
 {
     int num;

    while(scanf("%d",&num) != 1|| num !=1 &&num != 2 && num!=3)
    {
        fflush(stdin);//fputc('\n',stdout);
        printf("���������룺");

    }
    return num;

 }
int freephead(snake*phead)    //ͷָ�� �������ͷ�  �����ͷŵ�����
{

     int n;
    snake*p = phead;
    int number=1; //����ڵ���  ����ͷָ�� ��βָ��


       while(p->next!=NULL)
       {
           number++;
           p=p->next;
       }
       n=number;
       p = phead;
       int number3;
       for(number3 = number;number3>0;number3--)
       {
           int number2=number3-1;
           for(;number2>0;number2--)
           {
               p=p->next;

           }

           free(p);
       }


       return n;


}

void printfline(int x, int y)
{
	gotoxy(x, y);
	printf("=");
}
void printfrow(int x,int y)
{
	gotoxy(x, y);
	printf("�U");
}
void printfcover()
{
	int i;
	for(i=27;i<89;i++)
	{
		printfline(i,8);
		printfline(i,16);
	}
	for(i=9;i<16;i++)
	{
		printfrow(25,i);
		printfrow(89,i);
	}
}
void graph2()
{
	int i;
	for (i = 0; i<58; i += 2)
	{
		gotoprint(i, 0);
		gotoprint(i, 26);
	}
	for (i = 1; i < 26; i++)
	{
		gotoprint(0, i);
		gotoprint(56, i);
	}
}

