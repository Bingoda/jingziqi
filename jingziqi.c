#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define LINE_LENGTH 3
#define LINE_COUNT 8
#define C_MARK 'O'
#define P_MARK 'X'



/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/*
��ʽ
===================== 
1 2 3
4 5 6
7 8 9
===================== 
*/ 
typedef struct{
	
	int id;
	int x;
	int y;	
	char mark;
	bool hasObj;
	int line_cnt;
	void *pline[4];
} Point;

typedef struct{
	void *pPts[LINE_LENGTH];
	int p_mark;
	int c_mark;
	int none;
} Line;

void init();
void draw();
bool isExist(Point*, char);
bool isWin();
int AI();
int toi(char);
Point* getPoint();
void updateLines();

Point p_arr[LINE_LENGTH*LINE_LENGTH];
Line l_arr[LINE_COUNT];

int main(int argc, char *argv[]) {

				
	bool end = true;
	
	int input = 0;
	init();
	draw();
	while(end){
		printf("������(1-9),��0�˳���");
		scanf("%1d",&input);
		if(input==0){
			break;
		}
		Point *p = getPoint(input);
		if(isExist(p,P_MARK)){
			printf("�Ѿ�����,����������\n");
			continue;
		}else{
			draw();
			printf("������%dλ�ñ����O\n",AI());
		}
		draw();
		end = !isWin(p);

	}
	 system("pause");
	return 0;
}

//�ж��Ƿ�ռ����λ��ûռλ���޸����� 
bool isExist(Point* p, char c){
	bool result = false;
	if(p->hasObj){
		result = true;
	}else{
		p->mark = c;
		p->hasObj = true;
		updateLines(p);
	}
	return result;
}
void updateLines(Point *p){
	for(int i = 0; i< p->line_cnt;i++){
		Line* pl = p->pline[i];
		if(p->mark == P_MARK){
			pl->p_mark++;
		}else if(p->mark == C_MARK){
			pl->c_mark++;
		}
		pl->none--;
	}
}
//�ж���Ӯ 
bool isWin(Point *p){
	int cnt;
	bool result = false;
	for(int i = 0;i<p->line_cnt;i++){
		Line* pl = (p->pline[i]);
		cnt = 0;
		for(int j = 0;j<LINE_LENGTH;j++){
			Point *pp = pl->pPts[j];
			if(pp->mark == P_MARK){
				cnt++;
			}
		}
		if(cnt>=LINE_LENGTH){
			result = true;
			printf("�ɹ�����\n"); 
			break;
		}
	}
	return result;
}

//AI �����жϣ�1.�ж�AI�Ƿ�������  2.�ж�����Ƿ������� 3.��û��� 
int AI(){
//	int next;
//	for(int i = 0;i<LINE_COUNT;i++){
//		if(l_arr[i].c_mark==2){
//			
//		} 
//			
//	}
	int i;
	for(i = 0;i<LINE_LENGTH*LINE_LENGTH&&isExist(&p_arr[i],C_MARK);i++){
		
	}
	return i + 1;
}

int toi(char c){
	return (c - 48);
}

//�������� 
void draw(){
	printf("=====================================\n");
	for(int i = 0;i<LINE_LENGTH*LINE_LENGTH;i++){
		if(p_arr[i].hasObj){
			printf("%c ",p_arr[i].mark);
		}else{
			printf("%d ",p_arr[i].id);
		}
		if(p_arr[i].id % LINE_LENGTH == 0){
			printf("\n");
		}
	}
	printf("=====================================\n");
}

Point* getPoint(int input){
	input--;
	return &p_arr[input];
}

void init(){
	//8������ 
	const int lines[][LINE_LENGTH]={1,2,3,4,5,6,7,8,9,1,4,7,2,5,8,3,6,9,1,5,9,3,5,7};
	for(int i = 0;i<LINE_LENGTH*LINE_LENGTH;i++){
		p_arr[i]=(Point){i+1, i%LINE_LENGTH,i/LINE_LENGTH};
	}
	for(int i = 0; i<LINE_COUNT;i++){
		l_arr[i].none = LINE_LENGTH;
		for(int j = 0;j<LINE_LENGTH;j++){
			l_arr[i].pPts[j] = &p_arr[lines[i][j]-1];
			p_arr[lines[i][j]-1].pline[p_arr[lines[i][j]-1].line_cnt++] = &l_arr[i];
		}
	}
}


