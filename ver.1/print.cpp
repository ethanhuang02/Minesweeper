//¿é¥X½L­±ªºfunction
void printfield(int field[][8],int mark[][8],int count[][8],int x,int y){	
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(field[x][y]==87){
				if(field[i][j]==87)	    cout<<" ¡°";							
				else if(mark[i][j]==0)	cout<<" ¡¼";							
				else if(mark[i][j]==1)	cout<<" "<<count[i][j]<<" ";								
				else if(mark[i][j]==2)	cout<<" M ";								
			}
			if(field[x][y]==0){
				if(mark[i][j]==0)	cout<<" ¡¼";														
				if(mark[i][j]==1)	cout<<" "<<count[i][j]<<" ";									
				if(mark[i][j]==2)	cout<<" M ";
			}
		}
		cout<<endl;
	}	
}
