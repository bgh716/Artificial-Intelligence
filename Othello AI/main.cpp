#include <string>
#include <cctype>
#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
#include "reversi.h"
#include <stdlib.h>
using namespace std;

int conclusion(MCT &tree, char markB, char markU, int turn){
    double score=0;
    double bestScore=0;
    int bestIndex=0;
    double score2=0;
    double bestScore2=0;
    double value=0;
    ReversiBot<void> *bot = new ReversiBot<void>();
    std::vector<int> next;
    std::array<char, 64> temp;
    for(int i=0;i<tree.database[turn].size();i++){
        for (int j=0;j<tree.choices.size();j++) {
            if (equal(tree.database[turn][i].grid.begin(),
                tree.database[turn][i].grid.end(), tree.choices[j].grid.begin()
            )) {
                next.clear();
                score=double(tree.database[turn][i].win)/double(tree.database[turn][i].play);
                next=bot->findMove(tree.choices[j].grid, markU, markB);
                for(int k=0;k<next.size();k++){
                    copy(tree.choices[j].grid.begin(),
                    tree.choices[j].grid.end(),temp.begin());
                    temp[next[k]]=markU;
                    bot->process(temp, next[k], markU);
                    for (int q=0;q<tree.database[turn+1].size();q++) {
                        if (equal(tree.database[turn+1][q].grid.begin(),
                            tree.database[turn+1][q].grid.end(), temp.begin()
                        )) {
                            score2=double(tree.database[turn+1][q].win)/double(tree.database[turn+1][q].play);
                            if(score2>=bestScore2){
                                bestScore2=score2;
                            }
                        }
                    }
                }
                bestScore2=1-bestScore2;
                score=score*0.333333; //
                bestScore2=bestScore2*0.333333; //
                value=tree.ScoreBoard[tree.choices[j].move];
                value=value*0.333333; //
                score=score+bestScore2+value;
                if (score>=bestScore) {
                    bestScore=score;
                    bestIndex=j;
                }
            }
        }
    }
    std::cout <<"score is: " <<bestScore << std::endl;
    return tree.choices[bestIndex].move;
}

int conclusionT(MCT &tree, char markB, char markU, int turn){
    double score=0;
    double bestScore=0;
    int bestIndex=0;
    ReversiBot<void> *bot = new ReversiBot<void>();
    for(int i=0;i<tree.database[turn].size();i++){
        for (int j=0;j<tree.choices.size();j++) {
            if (equal(tree.database[turn][i].grid.begin(),
                tree.database[turn][i].grid.end(), tree.choices[j].grid.begin()
            )) {
                score=double(tree.database[turn][i].win)/double(tree.database[turn][i].play);
                if (score>=bestScore) {
                    bestScore=score;
                    bestIndex=j;
                }
            }
        }
    }
    std::cout <<"score is: " <<bestScore << std::endl;
    return tree.choices[bestIndex].move;
}

int findBest(MCT &tree, char markU, char markB, int turn, int test, int test2){
    int N;
    if(test==1){
		N = 10;
    }
    else{
		N = 40;
    }
    std::vector<std::array<char, 64>> tempB;
    int tempBidx=0;
    std::vector<std::array<char, 64>> tempO;
    int tempOidx=0;
    std::array<char, 64> grid;
    std::vector<int> movement;
    ReversiBot<void> *bot = new ReversiBot<void>();
    int len;
    int random;
    int finish=0;
    int bot1;
    int bot2;
    int robot1_turn;
    int robot2_turn;
    int dupCheck=0;
    std::vector<int> TurnsB;
    std::vector<int> TurnsO;
    srand((unsigned int)time(0));
    for (int k=0;k<tree.choices.size();k++) {
        for (int i=0;i<N;i++) {
            finish=0;
            bot->turn=turn+1;
            tempB.clear();
            tempO.clear();
            TurnsB.clear();
            TurnsO.clear();
            //tempBidx=0;
            //tempOidx=0;
            TurnsB.push_back(bot->turn);
            grid=tree.choices[k].grid;
            //tempB.resize(70);
            //copy(grid.begin(),grid.end(),tempB[tempBidx].begin());
            //tempBidx++;
            //tempO.resize(70);
            tempB.push_back(grid);
            robot1_turn;
            robot2_turn;
            bot1=0;
            bot2=0;

            movement = bot->findMove(grid, markU, markB);
            bot->X=0;
            bot->O=0;
            for (int i=0;i<64;i++) {
                if (grid[i]=='X') {
                    bot->X+=1;
                }
                else if (grid[i]=='O') {
                    bot->O+=1;
                }
            }
            if (bot->X==0 || bot->O==0) {
                robot2_turn=0;
                robot1_turn=0;
                finish=1;
                if (bot->X==0 && markB=='X') {
                    bot2=1;
                }
                else if (bot->X==0 && markU=='X') {
                    bot1=1;
                }
                else if (bot->O==0 && markB=='O') {
                    bot2=1;
                }
                else if (bot->O==0 && markU=='O') {
                    bot1=1;
                }
            }
            else if (bot->turn==60) {
                robot2_turn=0;
                robot1_turn=0;
                finish=1;
                if (bot->X>=bot->O && markB=='X') {
                    bot1=1;
                }
                else if (bot->X>=bot->O && markU=='X') {
                    bot2=1;
                }
                if (bot->O>=bot->X && markB=='O') {
                    bot1=1;
                }
                else if (bot->O>=bot->X && markU=='O') {
                    bot2=1;
                }
            }
            else if (movement.size()==0) {
                movement = bot->findMove(grid, markB, markU);
                if (movement.size()==0) {
                    robot2_turn=0;
                    robot1_turn=0;
                    finish=1;
                    if (bot->X>=bot->O && markB=='X') {
                        bot1=1;
                    }
                    else if (bot->X>=bot->O && markU=='X') {
                        bot2=1;
                    }
                    if (bot->O>=bot->X && markB=='O') {
                        bot1=1;
                    }
                    else if (bot->O>=bot->X && markU=='O') {
                        bot2=1;
                    }
                }
                else {
                    robot2_turn=0;
                    robot1_turn=1;
                }
            }
            else {
                robot2_turn=1;
                robot1_turn=0;
            }
            while (finish==0) {
                while (robot1_turn == 1) {
                    movement = bot->findMove(grid, markB, markU);
                    len=movement.size();
                    random=movement[rand() % len];
                    grid[random]=markB;
                    bot->process(grid, random, markB);
                    //copy(grid.begin(),grid.end(),tempB[tempBidx].begin());
                    //tempBidx++;
                    tempB.push_back(grid);
                    movement = bot->findMove(grid, markU, markB);
                    bot->X=0;
                    bot->O=0;
                    for (int i=0;i<64;i++) {
                        if (grid[i]=='X') {
                            bot->X+=1;
                        }
                        else if (grid[i]=='O') {
                            bot->O+=1;
                        }
                    }
                    bot->turn+=1;
                    TurnsB.push_back(bot->turn);
                    if (bot->X==0 || bot->O==0) {
                        robot2_turn=0;
                        robot1_turn=0;
                        finish=1;
                        if(bot->X==0 && markB=='X'){
                            bot2=1;
                        }
                        else if(bot->X==0 && markU=='X'){
                            bot1=1;
                        }
                        else if(bot->O==0 && markB=='O'){
                            bot2=1;
                        }
                        else if(bot->O==0 && markU=='O'){
                            bot1=1;
                        }
                    }
                    else if (bot->turn==60) {
                        robot2_turn=0;
                        robot1_turn=0;
                        finish=1;
                        if(bot->X>=bot->O && markB=='X'){
                            bot1=1;
                        }
                        else if(bot->X>=bot->O && markU=='X'){
                            bot2=1;
                        }
                        if(bot->O>=bot->X && markB=='O'){
                            bot1=1;
                        }
                        else if(bot->O>=bot->X && markU=='O'){
                            bot2=1;
                        }
                    }
                    else if (movement.size()==0) {
                        movement = bot->findMove(grid, markB, markU);
                        if (movement.size()==0) {
                            robot2_turn=0;
                            robot1_turn=0;
                            finish=1;
                            if (bot->X>=bot->O && markB=='X') {
                                bot1=1;
                            }
                            else if (bot->X>=bot->O && markU=='X') {
                                bot2=1;
                            }
                            if (bot->O>=bot->X && markB=='O') {
                                bot1=1;
                            }
                            else if (bot->O>=bot->X && markU=='O') {
                                bot2=1;
                            }
                        }
                        else {
                            robot2_turn=0;
                            robot1_turn=1;
                        }
                    }
                    else {
                        robot2_turn=1;
                        robot1_turn=0;
                    }
                }

                while (robot2_turn == 1) {
                    movement = bot->findMove(grid, markU, markB);
                    len=movement.size();
                    random=movement[rand() % len];
                    grid[random]=markU;
                    bot->process(grid, random, markU);
                    //copy(grid.begin(),grid.end(),tempO[tempOidx].begin());
                    //tempOidx++;
                    tempO.push_back(grid);
                    movement = bot->findMove(grid, markB, markU);
                    bot->X=0;
                    bot->O=0;
                    for (int i=0;i<64;i++) {
                        if (grid[i]=='X') {
                            bot->X+=1;
                        }
                        else if (grid[i]=='O') {
                            bot->O+=1;
                        }
                    }
                    bot->turn+=1;
                    TurnsO.push_back(bot->turn);
                    if (bot->X==0 || bot->O==0) {
                        robot2_turn=0;
                        robot1_turn=0;
                        finish=1;
                        if (bot->X==0 && markB=='X') {
                            bot2=1;
                        }
                        else if (bot->X==0 && markU=='X') {
                            bot1=1;
                        }
                        else if (bot->O==0 && markB=='O') {
                            bot2=1;
                        }
                        else if (bot->O==0 && markU=='O') {
                            bot1=1;
                        }
                    }
                    else if (bot->turn==60) {
                        robot2_turn=0;
                        robot1_turn=0;
                        finish=1;
                        if (bot->X>=bot->O && markB=='X') {
                            bot1=1;
                        }
                        else if (bot->X>=bot->O && markU=='X') {
                            bot2=1;
                        }
                        if (bot->O>=bot->X && markB=='O') {
                            bot1=1;
                        }
                        else if (bot->O>=bot->X && markU=='O') {
                            bot2=1;
                        }
                    }
                    else if (movement.size()==0) {
                        movement = bot->findMove(grid, markU, markB);
                        if (movement.size()==0) {
                            robot2_turn=0;
                            robot1_turn=0;
                            finish=1;
                            if (bot->X>=bot->O && markB=='X') {
                                bot1=1;
                            }
                            else if (bot->X>=bot->O && markU=='X') {
                                bot2=1;
                            }
                            if (bot->O>=bot->X && markB=='O') {
                                bot1=1;
                            }
                            else if (bot->O>=bot->X && markU=='O') {
                                bot2=1;
                            }
                        }
                        else {
                            robot2_turn=1;
                            robot1_turn=0;
                        }
                    }
                    else {
                        robot2_turn=0;
                        robot1_turn=1;
                    }
                }
            }
            if(bot1==1){
                for(int j=0;j<tempB.size();j++){
                    dupCheck=0;
                    if(tree.database[TurnsB[j]-1].size()==0){
                        dupCheck=1;
                    }
                    for (int t=0;t<tree.database[TurnsB[j]-1].size();t++) {
                        if (equal(tree.database[TurnsB[j]-1][t].grid.begin(),
                            tree.database[TurnsB[j]-1][t].grid.end(), tempB[j].begin()
                        )) {
                            tree.database[TurnsB[j]-1][t].play+=1;
                            tree.database[TurnsB[j]-1][t].win+=1;
                            dupCheck=0;
                            break;
                        }
                        else {
                            dupCheck=1;
                        }
                    }
                    if(dupCheck==1){
                        tree.database[TurnsB[j]-1].push_back(MCTnode(tempB[j]));
                        tree.database[TurnsB[j]-1].back().play+=1;
                        tree.database[TurnsB[j]-1].back().win+=1;
                    }
                }
                for(int j=0;j<tempO.size();j++){
                    dupCheck=0;
                    if(tree.database[TurnsO[j]-1].size()==0){
                        dupCheck=1;
                    }
                    for (int t=0;t<tree.database[TurnsO[j]-1].size();t++) {
                        if (equal(tree.database[TurnsO[j]-1][t].grid.begin(),
                            tree.database[TurnsO[j]-1][t].grid.end(), tempO[j].begin()
                        )) {
                            tree.database[TurnsO[j]-1][t].play+=1;
                            dupCheck=0;
                            break;
                        }
                        else {
                            dupCheck=1;
                        }
                    }
                    if(dupCheck==1){
                        tree.database[TurnsO[j]-1].push_back(MCTnode(tempO[j]));
                        tree.database[TurnsO[j]-1].back().play+=1;
                    }
                }
            }
            else{
                for(int j=0;j<tempB.size();j++){
                    dupCheck=0;
                    if(tree.database[TurnsB[j]-1].size()==0){
                        dupCheck=1;
                    }
                    for (int t=0;t<tree.database[TurnsB[j]-1].size();t++) {
                        if (equal(tree.database[TurnsB[j]-1][t].grid.begin(),
                            tree.database[TurnsB[j]-1][t].grid.end(), tempB[j].begin()
                        )) {
                            tree.database[TurnsB[j]-1][t].play+=1;
                            dupCheck=0;
                            break;
                        }
                        else {
                            dupCheck=1;
                        }
                    }
                    if(dupCheck==1){
                        tree.database[TurnsB[j]-1].push_back(MCTnode(tempB[j]));
                        tree.database[TurnsB[j]-1].back().play+=1;
                    }
                }
                for(int j=0;j<tempO.size();j++){
                    dupCheck=0;
                    if(tree.database[TurnsO[j]-1].size()==0){
                        dupCheck=1;
                    }
                    for (int t=0;t<tree.database[TurnsO[j]-1].size();t++) {
                        if (equal(tree.database[TurnsO[j]-1][t].grid.begin(),
                            tree.database[TurnsO[j]-1][t].grid.end(), tempO[j].begin()
                        )) {
                            tree.database[TurnsO[j]-1][t].play+=1;
                            tree.database[TurnsO[j]-1][t].win+=1;
                            dupCheck=0;
                            break;
                        }
                        else {
                            dupCheck=1;
                        }
                    }
                    if(dupCheck==1){
                        tree.database[TurnsO[j]-1].push_back(MCTnode(tempO[j]));
                        tree.database[TurnsO[j]-1].back().play+=1;
                        tree.database[TurnsO[j]-1].back().win+=1;
                    }
                }
            }
        }
    }
    if(test2==0){
        return conclusion(tree, markB, markU , turn);
    }
    else{
        return conclusionT(tree, markB, markU , turn);
    }
}


int main(int argc, char *args[]) {
    int Sturn;
    std::vector<int> movement;
    std::array<char, 64> grid;
    ReversiBot<void> *bot = new ReversiBot<void>();
    MCT tree;
    char end;
    int inputCheck = 0;
    char markU;
    char markB;
    int user_turn=0;
    int robot_turn=0;
    int len;
    int random;
    char row;
    int column;
    int rowN;
    int finish;
    int test=0;

    std::cout << "Type 'y' to play a game (y/n): ";
    while (inputCheck == 0) {
        std::cin >> end;
        if (std::cin.fail() || (end != 'y' && end != 'n')) {
            cin.clear();
            cin.ignore(1000, '\n');
            std::cout << "Please type valid option (y/n)" << std::endl;
            std::cout << "Type 'y' to play a game (y/n): ";
        }
        else {
            inputCheck = 1;
        }
    }
    inputCheck = 0;


    while (end == 'y') {
        std::cout << "Type your turn (1/2/(3 for test)): ";
        while (inputCheck == 0) {
            std::cin >> Sturn;
            if (std::cin.fail() || (Sturn != 1 && Sturn != 2 && Sturn != 3)) {
                cin.clear();
                cin.ignore(1000, '\n');
                std::cout << "Please type valid option (1/2)" << std::endl;
                std::cout << "Type your turn (1/2/(3 for test)): ";
            }
            else {
                inputCheck = 1;
            }
        }
        inputCheck = 0;


        if (Sturn == 1) {
            markU = 'X';
            markB = 'O';
            user_turn = 1;
            robot_turn=0;
            test=0;
        }
        else if(Sturn==2){
            markU = 'O';
            markB = 'X';
            user_turn = 0;
            robot_turn=1;
            test=0;
        }
        else{
            test=1;
            markU = 'X';
            markB = 'O';
            user_turn = 1;
            robot_turn=0;
        }
        bot->Reset();
        grid.fill('-');
        grid[27] = 'O';
        grid[28] = 'X';
        grid[35] = 'X';
        grid[36] = 'O';
        finish=0;

        while (finish == 0){
            while (user_turn == 1){
                if (test == 0){
                    movement = bot->findMove(grid, markU, markB);
                    for (int i = 0; i < movement.size(); i++){
                        grid[movement[i]] = '*';
                    }
                    bot->display(grid);
					for (int i = 0; i < movement.size(); i++) {
						grid[movement[i]] = '-';
					}
                    std::cout << "Select Row(A~H): ";
                    while (inputCheck == 0){
                        std::cin >> row;
                        if (std::cin.fail() || (row != 'A' && row != 'B' && row != 'C' && row != 'D' && row != 'E' && row != 'F' && row != 'G' && row != 'H')){
                            cin.clear();
                            cin.ignore(1000, '\n');
                            std::cout << "Please type valid option (A~H)" << std::endl;
                            std::cout << "Select Row(A~H): ";
                        }
                        else{
                            inputCheck = 1;
                        }
                    }
                    inputCheck = 0;
                    rowN = int(row) - 65;

                    std::cout << "Select Column(0~7): ";
                    while (inputCheck == 0){
                        std::cin >> column;
                        if (std::cin.fail() || (column != 0 && column != 1 && column != 2 && column != 3 && column != 4 && column != 5 && column != 6 && column != 7)){
                            cin.clear();
                            cin.ignore(1000, '\n');
                            std::cout << "Please type valid option (0~7)" << std::endl;
                            std::cout << "Select Column(0~7): ";
                        }
                        else{
                            inputCheck = 1;
                        }
                    }
                    inputCheck = 0;

                    if (find(movement.begin(), movement.end(), (rowN * 8 + column)) == movement.end()){
                        std::cout << "Please type valid position" << std::endl;
                    }
                    else{
                        grid[rowN * 8 + column] = markU;
                        bot->process(grid, (rowN * 8 + column), markU);
                        movement = bot->findMove(grid, markB, markU);
                        bot->X = 0;
                        bot->O = 0;
                        for (int i = 0; i < 64; i++){
                            if (grid[i] == 'X'){
                                bot->X += 1;
                            }
                            else if (grid[i] == 'O'){
                                bot->O += 1;
                            }
                        }
                        bot->turn += 1;
                        if (bot->X == 0 || bot->O == 0){
                            user_turn = 0;
                            robot_turn = 0;
                            bot->display(grid);
                            finish = 1;
                            if (bot->X == 0){
                                std::cout << "X won!" << std::endl;
                            }
                            else{
                                std::cout << "O won!" << std::endl;
                            }
                        }
                        else if (bot->turn == 60){
                            user_turn = 0;
                            robot_turn = 0;
                            bot->display(grid);
                            finish = 1;
                            if (bot->X > bot->O){
                                std::cout << "X won!" << std::endl;
                            }
                            else if (bot->O > bot->X){
                                std::cout << "O won!" << std::endl;
                            }
                            else{
                                std::cout << "Draw!" << std::endl;
                            }
                        }
                        else if (movement.size() == 0){
                            movement = bot->findMove(grid, markU, markB);
                            if (movement.size() == 0){
                                user_turn = 0;
                                robot_turn = 0;
                                bot->display(grid);
                                finish = 1;
                                if (bot->X > bot->O){
                                    std::cout << "X won!" << std::endl;
                                }
                                else if (bot->O > bot->X){
                                    std::cout << "O won!" << std::endl;
                                }
                                else{
                                    std::cout << "Draw!" << std::endl;
                                }
                            }
                            else{
                                user_turn = 1;
                                robot_turn = 0;
                            }
                        }
                        else{
                            user_turn = 0;
                            robot_turn = 1;
                        }
                    }
                }
                else{
                    movement = bot->findMove(grid, markU, markB);
                    for (int i = 0; i < movement.size(); i++){
                        grid[movement[i]] = '*';
                    }
                    //bot->display(grid);
                    for (int i = 0; i < movement.size(); i++){
                        grid[movement[i]] = '-';
                    }
                    tree.treeSet(grid, movement, markU);
                    random = findBest(tree, markB, markU, bot->turn, test ,1);
                    tree.treeReset();
                    grid[random] = markU;
                    bot->process(grid, random, markU);
                    movement = bot->findMove(grid, markB, markU);
                    bot->X = 0;
                    bot->O = 0;
                    for (int i = 0; i < 64; i++){
                        if (grid[i] == 'X'){
                            bot->X += 1;
                        }
                        else if (grid[i] == 'O'){
                            bot->O += 1;
                        }
                    }
                    bot->turn += 1;
                    if (bot->X == 0 || bot->O == 0){
                        user_turn = 0;
                        robot_turn = 0;
                        bot->display(grid);
                        finish = 1;
                        if (bot->X == 0){
                            std::cout << "X won!" << std::endl;
                        }
                        else{
                            std::cout << "O won!" << std::endl;
                        }
                    }
                    else if (bot->turn == 60){
                        user_turn = 0;
                        robot_turn = 0;
                        bot->display(grid);
                        finish = 1;
                        if (bot->X > bot->O){
                            std::cout << "X won!" << std::endl;
                        }
                        else if (bot->O > bot->X){
                            std::cout << "O won!" << std::endl;
                        }
                        else{
                            std::cout << "Draw!" << std::endl;
                        }
                    }
                    else if (movement.size() == 0){
                        movement = bot->findMove(grid, markU, markB);
                        if (movement.size() == 0){
                            user_turn = 0;
                            robot_turn = 0;
                            bot->display(grid);
                            finish = 1;
                            if (bot->X > bot->O){
                                std::cout << "X won!" << std::endl;
                            }
                            else if (bot->O > bot->X){
                                std::cout << "O won!" << std::endl;
                            }
                            else{
                                std::cout << "Draw!" << std::endl;
                            }
                        }
                        else{
                            user_turn = 1;
                            robot_turn = 0;
                        }
                    }
                    else{
                        user_turn = 0;
                        robot_turn = 1;
                    }
                }
            }

            while (robot_turn == 1) {
                movement = bot->findMove(grid, markB, markU);
                for(int i=0;i<movement.size();i++){
                    grid[movement[i]]='*';
                }
                if(test==0){
                    bot->display(grid);
                }
                for(int i=0;i<movement.size();i++){
                    grid[movement[i]]='-';
                }
                tree.treeSet(grid, movement, markB);
                random=findBest(tree, markU, markB, bot->turn, test ,0);
                tree.treeReset();
                grid[random]=markB;
                bot->process(grid,random,markB);
                movement = bot->findMove(grid, markU, markB);
                bot->X=0;
                bot->O=0;
                for (int i=0;i<64;i++) {
                    if (grid[i]=='X') {
                        bot->X+=1;
                    }
                    else if (grid[i]=='O') {
                        bot->O+=1;
                    }
                }
                bot->turn+=1;
                if (bot->X==0 || bot->O==0) {
                    user_turn=0;
                    robot_turn=0;
                    bot->display(grid);
                    finish=1;
                    if(bot->X==0){
                        std::cout<<"X won!"<<std::endl;
                    }
                    else{
                        std::cout<<"O won!"<<std::endl;
                    }
                }
                else if (bot->turn==60) {
                    user_turn=0;
                    robot_turn=0;
                    bot->display(grid);
                    finish=1;
                    if(bot->X>bot->O){
                        std::cout<<"X won!"<<std::endl;
                    }
                    else if(bot->O>bot->X){
                        std::cout<<"O won!"<<std::endl;
                    }
                    else{
                        std::cout<<"Draw!"<<std::endl;
                    }
                }
                else if (movement.size()==0) {
                    movement = bot->findMove(grid, markB, markU);
                    if(movement.size()==0){
                        user_turn=0;
                        robot_turn=0;
                        bot->display(grid);
                        finish=1;
                        if(bot->X>bot->O){
                            std::cout<<"X won!"<<std::endl;
                        }
                        else if(bot->O>bot->X){
                            std::cout<<"O won!"<<std::endl;
                        }
                        else{
                            std::cout<<"Draw!"<<std::endl;
                        }
                    }
                    else{
                        user_turn=0;
                        robot_turn=1;
                    }
                }
                else {
                    user_turn=1;
                    robot_turn=0;
                }
            }
        }
        for(int o=0;o<tree.database.size();o++){
            tree.database[o].clear();
        }
        std::cout << "Type 'y' to play a game (y/n): ";
        while (inputCheck == 0) {
            std::cin >> end;
            if (std::cin.fail() || (end != 'y' && end != 'n')) {
                cin.clear();
                cin.ignore(1000, '\n');
                std::cout << "Please type valid option (y/n)" << std::endl;
                std::cout << "Type 'y' to play a game (y/n): ";
            }
            else {
                inputCheck = 1;
            }
        }
        inputCheck = 0;
    }

}