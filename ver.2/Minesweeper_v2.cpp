#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

void initialize(int **field,int **count,int rows, int cols){	
	if(cols==8){
		int randombomb;
		srand((unsigned)time(NULL));
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++){
				randombomb=rand()%50;
				if(randombomb==1){
					field[i][j]=87;
				}
			}		
		}	
	}
	else if(cols==16){
		int randombomb2;
		srand((unsigned)time(NULL));
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++){
				randombomb2=rand()%10;
				if(randombomb2<3){
					field[i][j]=87;
				}
			}		
		}	
	}
	system("CLS");
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			cout<<" - ";
		}
		cout<<endl;
	}
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			if(field[i][j]==87){
				if(i-1>=0&&j-1>=0)		count[i-1][j-1]++;					
				if(j-1>=0)				count[i][j-1]++;						
				if(i+1<rows&&j-1>=0)	count[i+1][j-1]++;						
				if(i+1<rows)			count[i+1][j]++;						
				if(i+1<rows&&j+1<cols)	count[i+1][j+1]++;						
				if(j+1<cols)			count[i][j+1]++;						
				if(i-1>=0&&j+1<cols)	count[i-1][j+1]++;						
				if(i-1>=0)				count[i-1][j]++;					
			}
		}
	} 
}
void step(int **field,int **mark,int **count,int x,int y,int rows,int cols){
	if(field[x][y]==0&&mark[x][y]==0||field[x][y]==0&&mark[x][y]==2){
		mark[x][y]=1;
		if(count[x][y]==0){					
			if(x-1>=0&&y-1>=0)		step(field,mark,count,x-1,y-1,rows,cols);			
			if(y-1>=0)				step(field,mark,count,x,y-1,rows,cols);			
			if(x+1<rows&&y-1>=0)	step(field,mark,count,x+1,y-1,rows,cols);			
			if(x+1<rows)			step(field,mark,count,x+1,y,rows,cols);				
			if(x+1<rows&&y+1<cols)	step(field,mark,count,x+1,y+1,rows,cols);			
			if(y+1<cols)			step(field,mark,count,x,y+1,rows,cols);				
			if(x-1>=0&&y+1<cols)	step(field,mark,count,x-1,y+1,rows,cols);				
			if(x-1>=0)				step(field,mark,count,x-1,y,rows,cols);
		}		
	}
}
void printfield(int **field,int **mark,int **count,int won,int rows,int cols){
	system("CLS");//¨ê·sµe­± 
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			if(won==1&&field[i][j]==87)		cout<<" * ";
			else if(won!=1&&mark[i][j]==0)	cout<<" - ";														
			else if(won!=1&&mark[i][j]==2)	cout<<" M ";									
			else if(mark[i][j]==1)			cout<<" "<<count[i][j]<<" ";														
		}
		cout<<endl;
	}
} 
int winornot(int **field,int **mark,int rows,int cols){
	int numofbombs=0;
	int numofmarkbombs=0;
	int numofopen=0;
	int numofcanopen=0;
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			if(field[i][j]==87) 				numofbombs++;
			if(field[i][j]==87&&mark[i][j]==2) 	numofmarkbombs++;
			if(mark[i][j]==1) 					numofopen++;
			if(field[i][j]==0) 					numofcanopen++;			
		}		
	}
	if(numofbombs==numofmarkbombs&&numofopen==numofcanopen)	return 1;
	else return 0;
} 
void deletearray(int **field,int **mark,int **count,int rows){
	for (int i = 0; i < rows; i++) {
		delete [] field[i];
		delete [] mark[i];
		delete [] count[i];
	}
	delete [] field;
	delete [] mark;
	delete [] count;
}

int main(){
	int won=0;
	string start;
	string newgame("new");
	string continuegame("continue");	
	cout<<"\n\n\n\n\n\n\n\n\n";	
	cout<<"New game or continue?";
	while(won!=1){
		cout<<"\nPlease enter new or continue:";	
		cin>>start;
		if(start!=newgame&&start!=continuegame){
			cout<<"\nWrong command.\n";
		}		
		if(start==newgame){
			while(won!=1){
				string level;
				string easy("easy");
				string hard("hard");
				int rows=8;
				int cols;
				cout<<"\nPlease chose a level.\nPlease enter easy or hard:";
				cin>>level;
				if(level!=easy&&level!=hard){
					cout<<"\nWrong command.\n";
				}				
				else if(level==easy){
					cols=8;				
				}
				else if(level==hard){
					cols=16;
				}
				if(level==easy||level==hard){				
					int **field=new int*[rows];
					int **mark=new int*[rows];
					int **count=new int*[rows];
					for(int i=0;i<rows;i++){
						field[i]=new int[cols];
						mark[i]=new int[cols];
						count[i]=new int[cols];
					}
					for(int i=0;i<rows;i++){
						for(int j=0;j<cols;j++){
							field[i][j]=0;
							mark[i][j]=0;
							count[i][j]=0;
						}
					}
					initialize(field,count,rows,cols);
					int x,y;			
					string input;
					string open("open");
					string note("mark");
					string save("save");
					while(won!=1){
						cout<<"\nPlease enter open or mark or save:"; 
						cin>>input;
						if(input!=open&&input!=note&&input!=save){
							cout<<"\nWrong command.\n";
						}
						if(input==save){
							ofstream savefile;
							savefile.open("data.dat",ios::binary);
							savefile.write((char*)&rows,sizeof(int));
							savefile.write((char*)&cols,sizeof(int));
							for(int i=0;i<rows;i++){
								savefile.write((char*)field[i],cols*sizeof(int));
							}
							for(int i=0;i<rows;i++){
								savefile.write((char*)mark[i],cols*sizeof(int));
							}
							for(int i=0;i<rows;i++){
								savefile.write((char*)count[i],cols*sizeof(int));
							}
							savefile.close();
							cout<<"\nGame saved.\n";
						}
						while(input==open||input==note){
							cout<<"\nPlease enter x y(x and y are 1~8):";
							cin>>x>>y;
							x-=1;
							y-=1;
							if(x<0||x>rows||y<0||y>cols){
								cout<<"\nOut of range.\n\n";
							}		
							else if(input==open){								
								if(field[x][y]==87){//§PÂ_¬O§_¬°¬µ¼u
									system("CLS");
									step(field,mark,count,x,y,rows,cols);				
									for(int i=0;i<rows;i++){//¿é¥X½ò¨ì¦a¹pªº½L­± 
										for(int j=0;j<cols;j++){
											if(field[i][j]==87)	    cout<<" * ";							
											else if(mark[i][j]==0)	cout<<" - ";							
											else if(mark[i][j]==1)	cout<<" "<<count[i][j]<<" ";								
											else if(mark[i][j]==2)	cout<<" M ";															
										}
										cout<<endl;
									}
									cout<<"\nYou Lose!!\n";
									won=1;
									if(won==1){
										deletearray(field,mark,count,rows);
									}
									break;
								}
								else if(field[x][y]==0){
									step(field,mark,count,x,y,rows,cols);	
									won=winornot(field,mark,rows,cols);
									printfield(field,mark,count,won,rows,cols);																	
									if(won==1){//§PÂ_³Ó­t	
										cout<<"\nYou Win!!\n"<<endl;
										deletearray(field,mark,count,rows);
										break;
									}
									break;	
								}
							}
							else if(input==note){
								if(mark[x][y]==2){
									mark[x][y]=0;
									printfield(field,mark,count,won,rows,cols);
									break;
								}
								else if(mark[x][y]==0){
									mark[x][y]=2;
									printfield(field,mark,count,won,rows,cols);
									break;
								}
								else{
									printfield(field,mark,count,won,rows,cols);
									break;
								} 												
								won=winornot(field,mark,rows,cols);//§PÂ_³Ó­t
								if(won==1){
									cout<<"\nYou Win!!\n"<<endl;									
									deletearray(field,mark,count,rows);									
									break;
								}	
							}                       	
						}										
					}
				}							
			}
		}
		if(start==continuegame){//ÅªÀÉ 
			int rows,cols;
			ifstream load;
			load.open("data.dat",ios::binary);			
			load.read((char*)&rows,sizeof(int));
			load.read((char*)&cols,sizeof(int));
			int **field=new int*[rows];
			int **mark=new int*[rows];
			int **count=new int*[rows];
			for(int i=0;i<rows;i++){
				field[i]=new int[cols];
				mark[i]=new int[cols];
				count[i]=new int[cols];
			}
			for(int i=0;i<rows;i++){
				load.read((char*)field[i],cols*sizeof(int));
			}
			for(int i=0;i<rows;i++){
				load.read((char*)mark[i],cols*sizeof(int));
			}
			for(int i=0;i<rows;i++){
				load.read((char*)count[i],cols*sizeof(int));
			}
			if(!load){
				cout<<"\nNo record.\n";
			}
			else{			
				int won=0;
				printfield(field,mark,count,won,rows,cols);
				int x,y;	
				string input;
				string open("open");
				string note("mark");
				string save("save");
				while(won!=1){
					cout<<"\nPlease enter open or mark or save:"; 
					cin>>input;
					if(input!=open&&input!=note&&input!=save){
						cout<<"\nWrong command.\n";
					}
					if(input==save){
						ofstream savefile;
						savefile.open("data.dat",ios::binary);
						savefile.write((char*)&rows,sizeof(int));
						savefile.write((char*)&cols,sizeof(int));
						for(int i=0;i<rows;i++){
							savefile.write((char*)field[i],cols*sizeof(int));
						}
						for(int i=0;i<rows;i++){
							savefile.write((char*)mark[i],cols*sizeof(int));
						}
						for(int i=0;i<rows;i++){
							savefile.write((char*)count[i],cols*sizeof(int));
						}
						savefile.close();
						cout<<"\nGame saved.\n";
					}
					while(input==open||input==note){
						cout<<"\nPlease enter x y(x and y are 1~8):";
						cin>>x>>y;
						cout<<endl;
						x-=1;
						y-=1;
						if(x<0||x>rows||y<0||y>cols){
							cout<<"\nOut of range.\n";
						}		
						else if(input==open){							
							if(field[x][y]==87){//§PÂ_¬O§_¬°¬µ¼u
								system("CLS");
								step(field,mark,count,x,y,rows,cols);//¿é¥X½ò¨ì¦a¹pªº½L­±				
								for(int i=0;i<rows;i++){
									for(int j=0;j<cols;j++){
										if(field[i][j]==87)	    cout<<" * ";							
										else if(mark[i][j]==0)	cout<<" - ";							
										else if(mark[i][j]==1)	cout<<" "<<count[i][j]<<" ";								
										else if(mark[i][j]==2)	cout<<" M ";															
									}
									cout<<endl;
								}
								cout<<"\nYou Lose!!\n";
								won=1;
								if(won==1){
									deletearray(field,mark,count,rows);
								}
								break;
							}
							else if(field[x][y]==0){
								step(field,mark,count,x,y,rows,cols);	
								won=winornot(field,mark,rows,cols);//§PÂ_³Ó­t
								printfield(field,mark,count,won,rows,cols);																		
								if(won==1){
									cout<<"\nYou Win!!\n"<<endl;
									deletearray(field,mark,count,rows);
									break;
								}
								break;	
							}
						}
						else if(input==note){
							if(mark[x][y]==2){
								mark[x][y]=0;
								printfield(field,mark,count,won,rows,cols);
								break;
							}
							else if(mark[x][y]==0){
								mark[x][y]=2;
								printfield(field,mark,count,won,rows,cols);
								break;
							}
							else{
								printfield(field,mark,count,won,rows,cols);
								break;
							} 											
							won=winornot(field,mark,rows,cols);//§PÂ_³Ó­t
							if(won==1){
								cout<<"\nYou Win!!\n"<<endl;
								deletearray(field,mark,count,rows);
								break;
							}	
						}	
					}										
				}
			}
		}		
	}	
	system("pause");
	return 0;
}
