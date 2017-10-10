#include<iostream>
#include<cmath>
#include<map>
#include<vector>
#include<stdlib.h>
#define SIZE 3
using namespace std;


void intilize_matrix(char **matrix,int size){
	for(int i=0;i<size;i++){
		matrix[i] = new char[size];
		for(int j=0;j<size;j++){
			matrix[i][j]=' ';
		} 
	}
}

bool is_valid_move(int pos_x,int pos_y,char **matrix){
	if(pos_x>=0 && pos_x<SIZE && pos_y>=0 && pos_y<SIZE && matrix[pos_x][pos_y]==' '){
		return 1;
	}
	return 0;
}

void insert_into_matrix(char **matrix,int pos_x,int pos_y,char shape){
	matrix[pos_x][pos_y]=shape;
}

void generate_computer_move(int *pos_x,int *pos_y,char **martix){
		int x = rand() %3 +0;
		int y = rand() %3 +0;
		if(is_valid_move(x,y,martix)){
			*pos_x = x;
			*pos_y = y;
		}else{
			generate_computer_move(pos_x,pos_y,martix);
		}
}

void print_matrix(char **matrix,int size){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			cout<<matrix[i][j]<<" ";
		}
		cout<<"\n";
	}
}

bool row_check(vector<pair<int,int> > moves){
	int count =0;
	map<int,vector<int> > hash;
	for(int i=0;i<moves.size();i++){
		hash[moves[i].first].push_back(moves[i].second);
		if(hash[moves[i].first].size()==SIZE){
			//cout<<"\nRow victory\n";	
			return 1;
		}
	}
	return 0;

}

bool col_check(vector<pair<int,int> > moves){
	int count =0;
	map<int,vector<int> > hash;
	for(int i=0;i<moves.size();i++){
		hash[moves[i].second].push_back(moves[i].first);
		if(hash[moves[i].second].size()==SIZE){
			//cout<<"\nCol victory\n";
			return 1;
		}
	}
	return 0;

}

bool diagonale(vector<pair<int,int> > moves){
	int count =0;
	for(int i=0;i<moves.size();i++){
		if(moves[i].first == moves[i].second)
		count++;
	}
	if(count == SIZE){
		//cout<<"\nits dialgonal vicotry\n";
		return 1;
	}
	return 0;
}

bool diagonale1(vector<pair<int,int> > moves){
	int count =0;
	for(int i=0;i<moves.size();i++){
		if(moves[i].first+moves[i].second == SIZE-1)
		count++;
	}
	if(count == SIZE){
		//cout<<"\n its opt diagonal victory\n";
		return 1;
	}
	return 0;
}

int check_victory(vector<pair<int,int> > moves){
	if(row_check(moves)||col_check(moves)||diagonale(moves)||diagonale1(moves))
		return 1;
	return 0;
}

void input_shape_option(char *user_shape,char *comp_shape){
	string shape_option;
	cout<<"\nchoose x or o\n";
	getline(cin,shape_option);
	if(shape_option.size()>1 || (shape_option[0]!='x' && shape_option[0]!='o')){
		system("clear");
		cout<<"\n#ERROR : Invalid Choose\n";
		input_shape_option(user_shape,comp_shape);
	}
	if(shape_option[0] == 'x' || shape_option[0] == 'X'){
		*user_shape = 'x';
		*comp_shape = '0';
	}else if (shape_option[0] == 'o' || shape_option[0] == 'O'){	
		*user_shape = 'o';
		*comp_shape = 'x';
	}
}

bool start_game(){
	char **matrix = new char*[SIZE];
	char user_shape,computer_shape,shape_option;
	vector<pair<int,int> > user_moves;
	vector<pair<int,int> > comp_moves;
	int pos_x,pos_y;
	
	intilize_matrix(matrix,SIZE);
	input_shape_option(&user_shape,&computer_shape);
	system("clear");
	
	int user_terns = (SIZE*SIZE/2);
	if((SIZE*SIZE)%2!=0){
		user_terns++;
	} 
	
	for(int i=0;i<user_terns;i++){
		cout<< "Enter the corridnates to insert in "<<SIZE<<" by "<<SIZE<<": x y (input format) Exp: 1 2\n";
		cin>>pos_x>>pos_y;
		while(cin.fail()){
			cout<<"#ERROR : Invalid Coordinates\n";
			cin.clear();
			cin.ignore(256,'\n');
			system("clear");
			cout<< "Enter the corridnates to insert in "<<SIZE<<" by "<<SIZE<<": x y (input format) Exp: 1 2\n";
			cin>>pos_x>>pos_y;
		}
		if(is_valid_move(pos_x,pos_y,matrix)){
			system("clear");	
			insert_into_matrix(matrix,pos_x,pos_y,user_shape);
			pair<int,int> user_move = make_pair(pos_x,pos_y);
			user_moves.push_back(user_move);
			if(i>=SIZE-1 && check_victory(user_moves)){
				print_matrix(matrix,SIZE);
				cout<< "\n====YOU WIN====\n";
				return 0;			
			}
			if(i<(SIZE*SIZE/2)){
				generate_computer_move(&pos_x,&pos_y,matrix);
				insert_into_matrix(matrix,pos_x,pos_y,computer_shape);
				pair<int,int> comp_move = make_pair(pos_x,pos_y);
				comp_moves.push_back(comp_move);
				if(i>=SIZE-1 && check_victory(comp_moves)){
					print_matrix(matrix,SIZE);
					cout<< "\n====BETTER LUCK NEXT TIME====\n";
					return 0;			
				}
			}
			print_matrix(matrix,SIZE);
		}else{
			system("clear");
			cout<<"\n#ERROR : Invalid Coordinates\n";
			print_matrix(matrix,SIZE);
			i--;
		}
	}
	return 0;
}

int main(){
	start_game();
	string user_wanna_play;
	while(1){
		cout<<"\n play again, #press 1\n"<<"exit, #press any key";
		cin>>user_wanna_play;
		if(user_wanna_play == "1"){
			system("clear");
			start_game();
		}else{
			return 0;
		}
	}
	return 0;
}
