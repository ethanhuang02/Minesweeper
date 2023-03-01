#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;
//初始值=0;炸彈=87;踩過=1;標示=2;
//開格子的function 
void step(int field[][9],int mark[][9],int count[][9],int x,int y){ 
	if(field[x][y]==0&&mark[x][y]==0||field[x][y]==0&&mark[x][y]==2){
		mark[x][y]=1;
		if(count[x][y]==0){					
			if(x-1>=1&&y-1>=1)	step(field,mark,count,x-1,y-1);			
			if(y-1>=1)			step(field,mark,count,x,y-1);			
			if(x+1<9&&y-1>=1)	step(field,mark,count,x+1,y-1);			
			if(x+1<9)			step(field,mark,count,x+1,y);				
			if(x+1<9&&y+1<9)	step(field,mark,count,x+1,y+1);			
			if(y+1<9)			step(field,mark,count,x,y+1);				
			if(x-1>=1&&y+1<9)	step(field,mark,count,x-1,y+1);				
			if(x-1>=1)			step(field,mark,count,x-1,y);
		}		
	}								
}  
//判斷勝負的function
int winornot(int field[][9],int mark[][9]){
	int numofbombs=0;
	int numofmarkbombs=0;
	int numofopen=0;
	int numofcanopen=0;
	for(int i=1;i<9;i++){
		for(int j=1;j<9;j++){
			if(field[i][j]==87) 				numofbombs++;
			if(field[i][j]==87&&mark[i][j]==2) 	numofmarkbombs++;
			if(mark[i][j]==1) 					numofopen++;
			if(field[i][j]==0) 					numofcanopen++;			
		}		
	}
	if(numofbombs==numofmarkbombs&&numofopen==numofcanopen)		return 1;
	else return 0;
} 
//主函式 
int main(){		
	//盤面 8*8
	int field[9][9]; 
	int mark[9][9];  
	int count[9][9];
	for(int i=1;i<9;i++){
		for(int j=1;j<9;j++){
			field[i][j]=0;
			mark[i][j]=0;
			count[i][j]=0;
		}		
	}
	//隨機炸彈 機率20%
	int randombomb;
	srand((unsigned)time(NULL));
	for(int i=1;i<9;i++){
		for(int j=1;j<9;j++){
			randombomb=rand()%20;
			if(randombomb==1){
				field[i][j]=87;
			}
		}		
	}
	//輸出盤面 
	cout<<"\n☆歡迎來到踩地雷☆\n\n";
	for(int i=0;i<9;i++){
		if(i>0)cout<<i<<" ";
		if(i==0)cout<<" ";
		for(int j=0;j<9;j++){
			if(i==0)cout<<" ";
			if(i==0&&j>0)cout<<j;
			if(i>0&&j>0)cout<<"■";
		}
		cout<<endl;
	}
	//解答 
	/*for(int i=1;i<9;i++){
		cout<<"  ";
		for(int j=1;j<9;j++){			
			cout<<setw(2)<<field[i][j];
		}
		cout<<endl;
	}*/
	//計算每格旁邊有多少bomb  
	for(int i=1;i<9;i++){
		for(int j=1;j<9;j++){
			if(field[i][j]==87){
				if(i-1>=1&&j-1>=1)	count[i-1][j-1]++;					
				if(j-1>=1)			count[i][j-1]++;						
				if(i+1<9&&j-1>=1)	count[i+1][j-1]++;						
				if(i+1<9)			count[i+1][j]++;						
				if(i+1<9&&j+1<9)	count[i+1][j+1]++;						
				if(j+1<9)			count[i][j+1]++;						
				if(i-1>=1&&j+1<9)	count[i-1][j+1]++;						
				if(i-1>=1)			count[i-1][j]++;					
			}
		}
	} 	
	int x,y,move,won;
	string input;
	string open("open");
	string note("mark");
	do{
		//選擇行動
		cout<<"\n請輸入所要執行的動作(open x y或mark x y)："; 
		cin>>input>>x>>y;
		if(input!=open&&input!=note||x<1||x>8||y<1||y>8){
			cout<<"\n ※無法執行的指令※\n";
		}		
		else if(input==open){
			//判斷是否為炸彈
			if(field[x][y]==87){
				step(field,mark,count,x,y);				
				for(int i=0;i<9;i++){
					if(i>0)	cout<<i<<" ";
					if(i==0)cout<<" ";
					for(int j=0;j<9;j++){
						if(i==0)		cout<<" ";
						if(i==0&&j>0)	cout<<j;
						if(i>0&&j>0){
							if(field[i][j]==87)	    cout<<"※";							
							else if(mark[i][j]==0)	cout<<"■";							
							else if(mark[i][j]==1)	cout<<" "<<count[i][j];								
							else if(mark[i][j]==2)	cout<<" M";
						}															
					}
					cout<<endl;
				}
				cout<<"\n               你輸了!!\n";
				cout<<"\n◢▆▅▄▃崩╰(〒皿〒)╯潰▃▄▅▇◣\n"; 
				break;
			}
			else if(field[x][y]==0){
				step(field,mark,count,x,y);	
				won=winornot(field,mark);			
				for(int i=0;i<9;i++){
					if(i>0)	cout<<i<<" ";
					if(i==0)cout<<" ";
					for(int j=0;j<9;j++){
						if(i==0)		cout<<" ";
						if(i==0&&j>0)	cout<<j;
						if(i>0&&j>0){
							if(won==1&&field[i][j]==87)	cout<<"※";
							if(won!=1&&mark[i][j]==0)	cout<<"■";	
							if(won!=1&&mark[i][j]==2)	cout<<" M";	
							if(mark[i][j]==1)			cout<<" "<<count[i][j];
						}									
					}
					cout<<endl;
				}
				//判斷勝負1								
				if(won==1){
					cout<<"\n你贏了!!灑花~~~~~(*￣▽￣)/‧☆*'*-.,_,.-*'*-.,_☆"<<endl;
					break;
				}	
			}
		}
		else if(input==note){
			if(mark[x][y]==2){
				mark[x][y]=0;
				for(int i=0;i<9;i++){
					if(i>0)	cout<<i<<" ";
					if(i==0)cout<<" ";
					for(int j=0;j<9;j++){
						if(i==0)		cout<<" ";
						if(i==0&&j>0)	cout<<j;
						if(i>0&&j>0){
							if(won==1&&field[i][j]==87)	cout<<"※";
							if(won!=1&&mark[i][j]==0)	cout<<"■";														
							if(won!=1&&mark[i][j]==2)	cout<<" M";									
							if(mark[i][j]==1)			cout<<" "<<count[i][j];
						}														
					}
					cout<<endl;
				}
			}
			else {
				mark[x][y]=2;
				for(int i=0;i<9;i++){
					if(i>0)	cout<<i<<" ";
					if(i==0)cout<<" ";
					for(int j=0;j<9;j++){
						if(i==0)		cout<<" ";
						if(i==0&&j>0)	cout<<j;
						if(i>0&&j>0){
							if(won==1&&field[i][j]==87)	cout<<"※";
							if(won!=1&&mark[i][j]==0)	cout<<"■";														
							if(won!=1&&mark[i][j]==2)	cout<<" M";									
							if(mark[i][j]==1)			cout<<" "<<count[i][j];
						}														
					}
					cout<<endl;
				}
			} 				
			//判斷勝負
			won=winornot(field,mark);
			if(won==1){
				cout<<"\n你贏了!!灑花~~~~~(*￣▽￣)/‧☆*'*-.,_,.-*'*-.,_☆"<<endl;
				break;
			}
		}		
	}while(won!=1);
	return 0;
}
