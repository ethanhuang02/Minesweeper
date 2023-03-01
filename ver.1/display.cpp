for(int i=0;i<8;i++){
	for(int j=0;j<8;j++){
		if(field[i][j]==0||field[i][j]==87){
			cout<<" . ";
		}	
		if(field[i][j]==99){
			cout<<" # ";
		}
		if(mark[i][j]==2){
			cout<<" M ";
		}	
	}
	cout<<endl;
}

