#include <string>
#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
using namespace std;

template <class ElementType>

class ReversiBot {
private:
    int findPos(std::array<char, 64>& grid, int position, int positionN, char markB, bool empty) {
        int row = position / 8;
        int column = position % 8;
        if (positionN == 1) {
            for (int j = column+1; j < 8; j++) {
                if (grid[row * 8 + j] == '-' && empty == false) {
                    return (row * 8 + j);
                }
                else if(grid[row * 8 + j] == '-' && empty == true){
                    return -1;
                }
                else if (grid[row * 8 + j] == markB && empty == true) {
                    return position;
                }
                else if (grid[row * 8 + j] == markB && empty == false){
                    return -1;
                }
            }
            return -1;
        }
        if (positionN == 2) {
            for (int i = row+1; i < 8; i++) {
                if (grid[i * 8 + column] == '-' && empty == false) {
                    return (i * 8 + column);
                }
                else if (grid[i * 8 + column] == '-' && empty == true) {
                    return -1;
                }
                else if (grid[i * 8 + column] == markB && empty == true) {
                    return position;
                }
                else if (grid[i * 8 + column] == markB && empty == false) {
                    return -1;
                }
            }
            return -1;
        }
        if (positionN == 3) {
            if (position%8!=7) {
                for (int i = position+9; i < 64; i += 9) {
                    if (grid[i] == '-' && empty == false) {
                        return i;
                    }
                    else if (grid[i] == '-' && empty == true) {
                        return -1;
                    }
                    else if (grid[i] == markB && empty == true) {
                        return position;
                    }
                    else if (grid[i] == markB && empty == false) {
                        return -1;
                    }
                    if (i / 8 == 7 || i % 8 == 7) {
                        return -1;
                    }
                }
            }
            return -1;
        }
        if (positionN == 4) {
            if (position%8!=0) {
                for (int i = position+7; i < 64; i += 7) {
                    if (grid[i] == '-' && empty == false) {
                        return i;
                    }
                    else if (grid[i] == '-' && empty == true) {
                        return -1;
                    }
                    else if (grid[i] == markB && empty == true) {
                        return position;
                    }
                    else if (grid[i] == markB && empty == false) {
                        return -1;
                    }
                    if (i / 8 == 7 || i % 8 == 0) {
                        return -1;
                    }
                }
                return -1;
            }
        }
        return -1;
    }
public:
    int X;
    int O;
    int turn;

    ReversiBot() {
        X = 0;
        O = 0;
        turn = 0;
    }

    void Reset() {
        X = 0;
        O = 0;
        turn = 0;
    }

    void display(std::array<char, 64>& grid) {
        std::cout << "  0 1 2 3 4 5 6 7 " << std::endl;
        std::cout << " -----------------" << std::endl;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (j == 0) {
                    if (grid[i * 8 + j] != '-') {
                        std::cout << char(65+i)<< "|" << grid[i * 8 + j];
                    }
                    else {
                        std::cout << char(65+i)<< "| ";
                    }
                }
                else if (j != 7) {
                    if (grid[i * 8 + j] != '-') {
                        std::cout << "|" << grid[i * 8 + j];
                    }
                    else {
                        std::cout << "| ";
                    }
                }
                else {
                    if (grid[i * 8 + j] != '-') {
                        std::cout << "|" << grid[i * 8 + j] << "|" << std::endl;
                    }
                    else {
                        std::cout << "| |" << std::endl;
                    }
                }
            }
            std::cout << " -----------------" << std::endl;
        }
    }

    std::vector<int> findMove(std::array<char, 64>& grid, char markB, char markU) {
        std::vector<int> v;
        for (int row = 0; row < 8; row++) {
            for (int column = 0; column < 8; column++) {
                if (grid[row * 8 + column] == markU) {
                    int position1 = row * 8 + (column - 1); //left from position
                    int position2 = (row - 1) * 8 + column; //up from position
                    int position3 = (row - 1) * 8 + column - 1; //left-up from position
                    int position4 = (row - 1) * 8 + column + 1; //right-up from position
                    int check1 = -1;
                    int check2 = -1;
                    int check3 = -1;
                    int check4 = -1;
                    if (position1 <= 63 && position1 >= 0 && grid[position1] == markB && column!=0) {
                        check1 = findPos(grid, position1, 1, markB, false);
                    }
                    else if (position1 <= 63 && position1 >= 0 && grid[position1] == '-' && column!=0) {
                        check1 = findPos(grid, position1, 1, markB, true);
                    }

                    if (check1 != -1) {
                        if (find(v.begin(), v.end(), check1)== v.end()) {
                            v.push_back(check1);
                        }
                    }

                    if (position2 <= 63 && position2 >= 0 && grid[position2] == markB) {
                        check2 = findPos(grid, position2, 2, markB, false);
                    }
                    else if (position2 <= 63 && position2 >= 0 && grid[position2] == '-') {
                        check2 = findPos(grid, position2, 2, markB, true);
                    }

                    if (check2 != -1) {
                        if (find(v.begin(), v.end(), check2) == v.end()) {
                            v.push_back(check2);
                        }
                    }

                    if (position3 <= 63 && position3 >= 0 && grid[position3] == markB && column!=0) {
                        check3 = findPos(grid, position3, 3, markB, false);
                    }
                    else if (position3 <= 63 && position3 >= 0 && grid[position3] == '-' && column!=0) {
                        check3 = findPos(grid, position3, 3, markB, true);
                    }

                    if (check3 != -1) {
                        if (find(v.begin(), v.end(), check3) == v.end()) {
                            v.push_back(check3);
                        }
                    }

                    if (position4 <= 63 && position4 >= 0 && grid[position4] == markB && column!=7) {
                        check4 = findPos(grid, position4, 4, markB, false);
                    }
                    else if (position4 <= 63 && position4 >= 0 && grid[position4] == '-' && column!=7) {
                        check4 = findPos(grid, position4, 4, markB, true);
                    }

                    if (check4 != -1) {
                        if (find(v.begin(), v.end(), check4) == v.end()) {
                            v.push_back(check4);
                        }
                    }

                }
            }
        }
        return v;
    }


    void process(std::array<char, 64>& grid, int position, char mark){
        char markO;
        if(mark=='X'){
            markO='O';
        }
        else{
            markO='X';
        }

        int row = position / 8;
        int column = position % 8;

        if(position-1<=63 && position-1>=0){
            if(grid[position-1]==markO){
                for (int j = column-1; j >= 0; j--) {
                    if (grid[row * 8 + j] == mark) {
                        for(int k=row * 8 + j; k<position;k++){
                            grid[k]=mark;
                        }
                        break;
                    }
                    else if(grid[row * 8 + j] == '-'){
                        break;
                    }
                }
            }
        }
        if(position+1<=63 && position+1>=0){
            if(grid[position+1]==markO){
                for (int j = column+1; j < 8; j++) {
                    if (grid[row * 8 + j] == mark) {
                        for(int k=row * 8 + j; k>position;k--){
                            grid[k]=mark;
                        }
                        break;
                    }
                    else if(grid[row * 8 + j] == '-'){
                        break;
                    }
                }
            }
        }
        if (position-8<=63 && position-8>=0) {
            if (grid[position-8]==markO) {
                for (int i = row-1; i >= 0; i--) {
                    if (grid[i * 8 + column] == mark) {
                        for (int k=i * 8 + column; k<position;k+=8) {
                            grid[k]=mark;
                        }
                        break;
                    }
                    else if(grid[i * 8 + column] == '-'){
                        break;
                    }
                }
            }
        }
        if(position+8<=63 && position+8>=0){
            if(grid[position+8]==markO){
                for (int i = row+1; i <= 7; i++) {
                    if (grid[i * 8 + column] == mark) {
                        for (int k=i * 8 + column; k>position;k-=8) {
                            grid[k]=mark;
                        }
                        break;
                    }
                    else if(grid[i * 8 + column] == '-'){
                        break;
                    }
                }
            }
        }
        if(position-7<=63 && position-7>=0){
            if (grid[position-7]==markO && column!=7) {
                for (int i = position-7; i >= 0; i -= 7) {
                    if (grid[i] == mark) {
                        for (int k=i;k<position;k+=7) {
                            grid[k]=mark;
                        }
                        break;
                    }
                    else if(grid[i] == '-'){
                        break;
                    }
                    if (i / 8 == 0 || i % 8 == 7) {
                        break;
                    }
                }
            }
        }
        if(position+7<=63 && position+7>=0){
            if(grid[position+7]==markO && column!=0){
                for (int i = position+7; i <= 63; i += 7) {
                    if (grid[i] == mark) {
                        for (int k=i;k>position;k-=7) {
                            grid[k]=mark;
                        }
                        break;
                    }
                    else if(grid[i] == '-'){
                        break;
                    }
                    if (i / 8 == 7 || i % 8 == 0) {
                        break;
                    }
                }
            }
        }
        if(position+9<=63 && position+9>=0){
            if (grid[position+9]==markO && column!=7) {
                for (int i = position+9; i <= 63; i += 9) {
                    if (grid[i] == mark) {
                        for (int k=i;k>position;k-=9) {
                            grid[k]=mark;
                        }
                        break;
                    }
                    else if(grid[i] == '-'){
                        break;
                    }
                    if (i / 8 == 7 || i % 8 == 7) {
                        break;
                    }
                }
            }
        }
        if(position-9<=63 && position-9>=0){
            if(grid[position-9]==markO && column!=0){
                for (int i = position-9; i >= 0; i -= 9) {
                    if (grid[i] == mark) {
                        for (int k=i;k<position;k+=9) {
                            grid[k]=mark;
                        }
                        break;
                    }
                    else if(grid[i] == '-'){
                        break;
                    }
                    if (i / 8 == 0 || i % 8 == 0) {
                        break;
                    }
                }
            }
        }
        
    }
};

class MCTnode{
public:
    int play;
    int win;
    int move;
    std::array<char, 64> grid;

    MCTnode(std::array<char, 64>& board){
        std::copy(board.begin(),board.end(),grid.begin());
        win=0;
        play=0;
    }
};


class MCT {
public:
    //MCTnode* root;
    std::vector<MCTnode> choices;
    std::array<std::vector<MCTnode>, 60> database;
    std::array<double, 64> ScoreBoard;


    MCT(){
        //root=NULL;
    }

    void treeReset(){
        //delete root;
        choices.clear();
    }

    void treeSet(std::array<char, 64>& grid, vector<int> movement, char mark){
        std::array<char, 64> temp;
        ReversiBot<void> *bot = new ReversiBot<void>();
        //root = new MCTnode(grid);
        //choices.resize(movement.size());
        for(int i=0;i<movement.size();i++){
            copy(grid.begin(),grid.end(),temp.begin());
            temp[movement[i]]=mark;
            //copy(temp.begin(), temp.end(), choices[i].grid.begin());
            bot->process(temp, movement[i], mark);
            choices.push_back(MCTnode(temp));
            choices[i].move=movement[i];
        }
        int col;
        int row;
        for(int i=0;i<64;i++){
            col=i%8;
            row=i/8;
            if(i==0 || i==7 || i==56 || i==63){
                ScoreBoard[i]=1;
            }
            else if(i==9 || i==14 || i==49 || i==54){
                ScoreBoard[i]=0;
            }
            else if(row==0 && (col!=1 || col!=6)){
                ScoreBoard[i]=0.5;
            }
            else if(row==7 && (col!=1 || col!=6)){
                ScoreBoard[i]=0.5;
            }
            else if(row==0 && (col==1 || col==6)){
                ScoreBoard[i]=0;
            }
            else if(row==7 && (col==1 || col==6)){
                ScoreBoard[i]=0;
            }
            else if(col==0 && (row!=1 || row!=6)){
                ScoreBoard[i]=0.5;
            }
            else if(col==7 && (row!=1 || row!=6)){
                ScoreBoard[i]=0.5;
            }
            else if(col==0 && (row==1 || row==6)){
                ScoreBoard[i]=0;
            }
            else if(col==0 && (row==1 || row==6)){
                ScoreBoard[i]=0;
            }
            else{
                ScoreBoard[i]=0.3;
            }
        }
    }
};