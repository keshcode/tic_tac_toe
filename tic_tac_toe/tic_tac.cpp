#include<iostream>
#include<cmath>
#include<map>
#include<vector>
#include<stdlib.h>
#define SIZE 3
using namespace std;


void intilize_matrix(char **matrix,int size){
	/*
	   Intilize the matrix char array to the required size
	   @param char **matrix reference to the 2d array
	   @param int size is size of the matrix defined in macros  
	*/
	for(int i=0;i<size;i++){
		matrix[i] = new char[size];
		for(int j=0;j<size;j++){
			matrix[i][j]=' ';
		} 
	}
}

bool is_valid_move(int pos_x,int pos_y,char **matrix){
	/*
		Validate the coordinates of move ,if it's inside boundry and if is or isn't the previous move
		@param int pos_x x coordinate
		@param int pos_y y coordinate
		@param char **matrix reference to 2d array
	*/
	if(pos_x>=0 && pos_x<SIZE && pos_y>=0 && pos_y<SIZE && matrix[pos_x][pos_y]==' '){
		return 1;
	}
	return 0;
}

void insert_into_matrix(char **matrix,int pos_x,int pos_y,char shape){
	/*
		inserts element at given coordinates
		@param char **matrix reference to 2d array
		@param int pos_x x coordinate
		@param int pos_y y coordinate
		@param char shape Shape to be inserted 
	*/
	matrix[pos_x][pos_y]=shape;
}

void generate_computer_move(int *pos_x,int *pos_y,char **martix){
		/*
			Generate random coordinates for the computer to insert into and also validate the move
			@param int pos_x x coordonate
			@param int pos_y y coordinate
			@char **matric reference to 2d array
		*/
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
	/*
		Prints the complete matrix
		@param char ** matrix reference to 2d array
		@param int size is the size of the matrix 
	*/
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			cout<<matrix[i][j]<<" ";
		}
		cout<<"\n";
	}
}

bool row_check(vector<pair<int,int> > moves){
	/*
		Checks for existance of complete row combination to wining
		@param vector<pair<int,int> > moves is the collection each move with it's coordinates
	*/
	map<int,vector<int> > hash;
	for(int i=0;i<moves.size();i++){
		hash[moves[i].first].push_back(moves[i].second);
		if(hash[moves[i].first].size()==SIZE){
			return 1;
		}
	}
	return 0;

}

bool col_check(vector<pair<int,int> > moves){
	/*
		Checks for existance of complete col combination to wining
		@param vector<pair<int,int> > moves is the collection each move with it's coordinates
	*/
	map<int,vector<int> > hash;
	for(int i=0;i<moves.size();i++){
		hash[moves[i].second].push_back(moves[i].first);
		if(hash[moves[i].second].size()==SIZE){
			return 1;
		}
	}
	return 0;

}

bool diagonale(vector<pair<int,int> > moves){
	/*
		Checks for existance of complete diagonal combination to wining
		@param vector<pair<int,int> > moves is the collection each move with it's coordinates
	*/
	int count =0;
	for(int i=0;i<moves.size();i++){
		if(moves[i].first == moves[i].second)
		count++;
	}
	if(count == SIZE){
		return 1;
	}
	return 0;
}

bool opp_diagonale(vector<pair<int,int> > moves){
	/*
		Checks for existance of complete opp diagonal combination to wining
		@param vector<pair<int,int> > moves is the collection each move with it's coordinates
	*/
	int count =0;
	for(int i=0;i<moves.size();i++){
		if(moves[i].first+moves[i].second == SIZE-1)
		count++;
	}
	if(count == SIZE){
		return 1;
	}
	return 0;
}

int check_victory(vector<pair<int,int> > moves){
	/*
		Checks for existance of any combination to wining
		@param vector<pair<int,int> > moves is the collection each move with it's coordinates
	*/
	if(row_check(moves)||col_check(moves)||diagonale(moves)||opp_diagonale(moves))
		return 1;
	return 0;
}

void input_shape_option(char *user_shape,char *comp_shape){
	/*
		Inputs shape options and checks for it's validity
		@param char *user_shape reference to user shape to update 
		@parma char *comp_shape reference to computer shape to update
	*/
	string shape_option;
	cout<<"choose x or o\n";
	getline(cin,shape_option,'\n');
	if(shape_option.size()>1 || ((shape_option[0] == 'x' || shape_option[0] == 'X') && (shape_option[0] == 'o' || shape_option[0] == 'O'))){
		system("clear");
		cout<<"#ERROR : Invalid Choose\n";
		input_shape_option(user_shape,comp_shape);
	}
	if(shape_option[0] == 'x'){
		*user_shape = 'x';
		*comp_shape = 'o';
	}else if(shape_option[0] == 'X'){
		*user_shape = 'X';
		*comp_shape = 'O';
	}else if(shape_option[0] == 'o'){	
		*user_shape = 'o';
		*comp_shape = 'x';
	}else if(shape_option[0] == 'O'){
		*user_shape = 'O';
		*comp_shape = 'X';
	}
}

void display_matrix_details(char **matrix,char user_shape){
	/*
		Displays matrix and its details 
		@param char **matrix refference to 2d array 
		@param char user_shape is choosed user shape
	*/
	cout<<"choose x or o\n";
        cout << user_shape << "\n";
	cout<< "Enter the corridnates to insert in "<<SIZE<<" by "<<SIZE<<": x y (input format) Exp: 1 2\n";
        print_matrix(matrix,SIZE);	
}

bool start_game(){
	/*
		start_game is the main controller function that controls the follow of game
		it inputs shape ,and coordinate to insert
		it also calls the generate_computer_move to gernerate new valid coordinate 
	*/
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
	
	system("clear");
	for(int i=0;i<user_terns;i++){
		display_matrix_details(matrix,user_shape);
		cin>>pos_x>>pos_y;
		while(cin.fail()){
			cout<<"#ERROR : Invalid Coordinates\n";
			cin.clear();
			cin.ignore(256,'\n');
			display_matrix_details(matrix,user_shape);
			cin>>pos_x>>pos_y;
		}
		if(is_valid_move(pos_x,pos_y,matrix)){
			system("clear");	
			insert_into_matrix(matrix,pos_x,pos_y,user_shape);
			pair<int,int> user_move = make_pair(pos_x,pos_y);
			user_moves.push_back(user_move);
			if(i>=SIZE-1 && check_victory(user_moves)){
				display_matrix_details(matrix,user_shape);
				cout<< "\n====YOU WIN====\n";
				return 0;			
			}
			if(i<(SIZE*SIZE/2)){
				generate_computer_move(&pos_x,&pos_y,matrix);
				insert_into_matrix(matrix,pos_x,pos_y,computer_shape);
				pair<int,int> comp_move = make_pair(pos_x,pos_y);
				comp_moves.push_back(comp_move);
				if(i>=SIZE-1 && check_victory(comp_moves)){
					display_matrix_details(matrix,user_shape);
					cout<< "\n====BETTER LUCK NEXT TIME====\n";
					return 0;			
				}
			}
		}else{
			system("clear");
			cout<<"#ERROR : Invalid Coordinates\n";
			i--;
		}
	}
	display_matrix_details(matrix,user_shape);
	cout<< "\n====IT'S A DRAW====\n";
	return 0;
}

int main(){
	start_game();
	string user_wanna_play;
	while(1){
		cout<<"\n#Press 1 to Play again\n"<<"#Press any other key for exit";//other key include only all alpha numeric and symbols excluding 1
		cin>>user_wanna_play;
		cin.ignore(256,'\n');
		if(user_wanna_play == "1"){
			system("clear");
			start_game();
		}else{
			return 0;
		}
	}
	return 0;
}
