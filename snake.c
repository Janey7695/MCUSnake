
#include "snake.h"


snake* head;				//������ͷ�ṹ��ָ��
snake* q;					//�����߽��ṹ��ָ��
food* FOOD;					//����ʳ��ṹ��ָ��
unsigned char Dir;			//����
BOOL Gamestatus=GO;			//��Ϸ״ָ̬ʾ
unsigned int score=0;		//����
unsigned int Sleep_Time=1000;//�ƶ��������Ϸ�Ѷȣ�
unsigned char Food_Score=10;//ÿ��ʳ��ӷ�

//��ʼ����ʱ��
void TIM3_Init(unsigned int arr,unsigned int psc)
{
	TIM_TimeBaseInitTypeDef TIM_Stru;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_Stru.TIM_Prescaler=psc-1;
	TIM_Stru.TIM_Period=arr-1;
	TIM_Stru.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_Stru.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3,&TIM_Stru);
}
void TIM2_Init(unsigned int arr,unsigned int psc)
{
	TIM_TimeBaseInitTypeDef TIM_Stru;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_Stru.TIM_Prescaler=psc-1;
	TIM_Stru.TIM_Period=arr-1;
	TIM_Stru.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_Stru.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2,&TIM_Stru);
}


//�����ߵ������� ����0.96 oled�����ص�Ƚ�С�����ÿ���߻�ʳ���㶼��4�����ص�����ʾ��
void Draw_Snake_Point(unsigned char x,unsigned char y)
{
	Draw_Point(x,y);
	Draw_Point(x-1,y);
	Draw_Point(x-1,y+1);
	Draw_Point(x,y+1);
}

//��ʼ��������ʳ��
void Snake_FOOD_Init()
{
	snake* tail;			//������βָ��
	unsigned char i;
	TIM3_Init(50,65530);	//ʹ�ö�ʱ������0-50��α�����
	TIM2_Init(15,65530);	//ʹ�ö�ʱ������0-15��α�����
	TIM_Cmd(TIM3,ENABLE);
	TIM_Cmd(TIM2,ENABLE);
	tail=(snake*)malloc(sizeof(snake));//Ϊ��β�ṹ������ռ�
	FOOD=(food*)malloc(sizeof(food));//Ϊʳ��ṹ������ռ�
	FOOD->x=50;			//��ʼʳ��x=50 y=44
	FOOD->y=44;
	tail->x=46;			//�ߵĳ�ʼĩ����x=46 y=30
	tail->y=30;
	tail->next=NULL;
	CanvasClear();		//�������
	
	//ͨ��forѭ������3�������ڵ���Ϊ��ʼ����
	for(i=1;i<3;i++)
	{
		head=(snake*)malloc(sizeof(snake));
		head->next=tail;
		head->x=46+i*2;
		head->y=30;
		tail=head;
	}
	
	//����ʼ�õ��������� �������� ��ȥ
	while(tail)
	{
		Draw_Snake_Point(tail->x,tail->y);
		tail=tail->next;
	}
	Draw_Snake_Point(FOOD->x,FOOD->y);
	
	//�ڻ���������д�ַ���
	OLED_ShowStrRAM(0,0,"score:0",16);
	//��ʾ �������� ������
	DisPlay();
	//��ʼ����Ϊ ��
	Dir=RIGHT;
}




//�ж��Ƿ�ҧ���Լ���x,yΪͷ������꣬SΪ�������������
//��ҧ������1 ���򷵻�0
BOOL IF_Hit(unsigned char x,unsigned char y)
{
	q=head->next;
	while(q)
	{	
		if(x==q->x&&y==q->y)
			return HIT;
		q=q->next;

	}
	return NO_HIT;
}

//����һ���µ�ʳ���Ҫ��֤��1. ʳ���������ż������Ϊ4�����ص����һ��ʳ���㣩 2.����������������
void Create_FOOD()
{
	FOOD->x=4+TIM3->CNT*2;
	FOOD->y=18+TIM2->CNT*2;
	while(IF_Hit(FOOD->x,FOOD->y))
	{
		FOOD->x=4+TIM3->CNT*2;
		FOOD->y=18+TIM2->CNT*2;
	}
}


//����Ƿ�Ե�ʳ��
BOOL IF_Get_Food(unsigned char x,unsigned char y) 
{
	if(x==FOOD->x&&y==FOOD->y)
	{
		Create_FOOD();
		score+=Food_Score;
		return Get_Food;
	}
	else
	return NO_Get_Food;

}
//С���ƶ�
void Snake_Move()
{
	//����ǰ������ͷ�����һ���ƶ����Ľ��
	snake* nextpoi;
	nextpoi=(snake*)malloc(sizeof(snake));
	
	if(Dir==UP)
	{
		//���������ƽ���Ȼ��ɾ��ĩ�ڵ㣨û�Ե�ʳ��Ļ���
		nextpoi->x=head->x;
		nextpoi->y=head->y-2;
		if(nextpoi->y==14)
			nextpoi->y=62;
		nextpoi->next=head;
		head=nextpoi;
		//����Ե�ʳ�� ��ɾ��ĩ���
		if(IF_Get_Food(head->x,head->y)==Get_Food)
		{
			q=head;
			while(q)
			{
				Draw_Snake_Point(q->x,q->y);
				q=q->next;
			}
		}
		else{
			q=head;
			while(q->next->next!=NULL)
			{
				Draw_Snake_Point(q->x,q->y);
				q=q->next;
			}
			Draw_Snake_Point(q->x,q->y);
			free(q->next);
			q->next=NULL;
		}
		//��������Լ� ��Ϸ����
		if(IF_Hit(head->x,head->y)==HIT)
		{
			Gamestatus=OVER;
		}
		
	}
	if(Dir==DOWN)
	{
		nextpoi->x=head->x;
		nextpoi->y=head->y+2;
		if(nextpoi->y==64)
			nextpoi->y=16;
		nextpoi->next=head;
		head=nextpoi;
		if(IF_Get_Food(head->x,head->y)==Get_Food)
		{
			q=head;
			while(q)
			{
				Draw_Snake_Point(q->x,q->y);
				q=q->next;
			}
		}
		else{
			q=head;
			while(q->next->next!=NULL)
			{
				Draw_Snake_Point(q->x,q->y);
				q=q->next;
			}
			Draw_Snake_Point(q->x,q->y);
			free(q->next);
			q->next=NULL;
		}
		
		if(IF_Hit(head->x,head->y)==HIT)
		{
			Gamestatus=OVER;
		}
		
	}
	if(Dir==LEFT)
	{
		nextpoi->x=head->x-2;
		nextpoi->y=head->y;
		if(nextpoi->x==0)
			nextpoi->x=126;
		nextpoi->next=head;
		head=nextpoi;
		if(IF_Get_Food(head->x,head->y)==Get_Food)
		{
			q=head;
			while(q)
			{
				Draw_Snake_Point(q->x,q->y);
				q=q->next;
			}
		}
		else{
			q=head;
			while(q->next->next!=NULL)
			{
				Draw_Snake_Point(q->x,q->y);
				q=q->next;
			}
			Draw_Snake_Point(q->x,q->y);
			free(q->next);
			q->next=NULL;
		}
		
		if(IF_Hit(head->x,head->y)==HIT)
		{
			Gamestatus=OVER;
		}
		
	}
	if(Dir==RIGHT)
	{
		nextpoi->x=head->x+2;
		if(nextpoi->x==128)
			nextpoi->x=0;
		nextpoi->y=head->y;
		nextpoi->next=head;
		head=nextpoi;
		if(IF_Get_Food(head->x,head->y)==Get_Food)
		{
			q=head;
			while(q)
			{
				Draw_Snake_Point(q->x,q->y);
				q=q->next;
			}
		}
		else{
			q=head;
			while(q->next->next!=NULL)
			{
				Draw_Snake_Point(q->x,q->y);
				q=q->next;
			}
			Draw_Snake_Point(q->x,q->y);
			free(q->next);
			q->next=NULL;
		}
		
		if(IF_Hit(head->x,head->y)==HIT)
		{
			Gamestatus=OVER;
		}
		
	}
	Draw_Snake_Point(FOOD->x,FOOD->y);
}


//��Ϸѭ������
void GameCir()
{
		//��ջ�������
		CanvasClear();
		//����һ������ ��Ϊ��Ϸ�߿�
		Draw_Rect(0,16,127,63,0);
		//���ƶ�һ��
		Snake_Move();
		//������д�ַ�������ʾ��ǰ����
		OLED_ShowStrRAM(0,0,"score:",16);
		if(score<100)
			OLED_ShowNumRAM(48,0,score,2,16);
		if(score>=100&score<1000)
			OLED_ShowNumRAM(48,0,score,3,16);
		if(score>=1000&score<10000)
			OLED_ShowNumRAM(48,0,score,4,16);
		//������д�ַ�������ʾ��ǰ�Ѷ�
		OLED_ShowNumRAM(96,0,(1200-Sleep_Time)/100,4,16);
		//��ʾ�ոջ��Ƶ������ڵ�һ֡����
		DisPlay();
		//��ʱ
		delay_ms(Sleep_Time);

}




