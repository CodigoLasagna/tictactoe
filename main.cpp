#include <ctime>
#include <iostream>
#include <string>
#include <random>
#include <cmath>

void start_ia();
void start_versus();
void draw(int arr[]);
void act_usr(int arr[]);
void act_comp(int arr[]);
void check_game(int arr[]);
void end_program();

int main(){
    std::string option = "";
    std::cout <<"[1] Juego con IA - [2] Jugador contra jugador\n>";
    std::cin >> option;
    switch (std::stoi(option)) {
        case(1):
            start_ia();
            break;
        case(2):
            start_versus();
            break;
    }
}

void start_ia(){
    srand(time(NULL));
    int tab [9] = {};
    draw(tab);
    int coin {rand()%2};
    if (coin == 0){
        act_usr(tab);
    }else{
        act_comp(tab);
    }
}

void draw(int arr[]){
    std::system("clear");
    std::cout << "  A   B   C\n";
    for (int i = 0; i < 9; ++i){
        if (i == 0 || i == 3 || i == 6){
            std::cout << (i/3)+1;
        }
        if (arr[i] == 0){
            std::cout << "   ";
        }else if (arr[i] == 1){
            std::cout << " X ";
        }else{
            std::cout << " O ";
        }
        if (i < 2 || (i > 2 && i < 5) || (i > 5 && i < 8)){
            std::cout << "|";
        }
        if (i == 2 || i == 5){
            std::cout << "\n ---|---|---\n";
        }
    }
    std::cout << "\n";
}

void act_usr(int arr[]){
    std::string buffer = "";
    std::string letter = "";
    std::string number = "";
    int x{0}, y{0};
    int type{0};
    std::cout << "Turno del jugador: ";
    std::cin >>  buffer;
    if ((int)buffer.size() == 3){
        for (int i = 0; i <(int)buffer.size(); i++){
            if(buffer[i] != '-'){
                if (type == 0){
                    number += buffer[i];
                }else{
                    letter += buffer[i];
                }
            }else{
                type = 1;
            }
        }
    }else{
        number = buffer[0];
        letter = buffer[1];
    }
    type = 0;
    x = std::stoi(number)-1;
    if (letter == "A" || letter == "a"){
        y = 0;
    }else if (letter == "B" || letter == "b"){
        y = 1;
    }else if (letter == "C" || letter == "c"){
        y = 2;
    }
    if (arr[x*3+y] == 0){
        arr[x*3+y] = 1;
    }else{
        std::cout << "Espació ocupado\n";
        act_usr(arr);
    }
    check_game(arr);
    act_comp(arr);
}

void act_comp(int arr[]){
    int pos{(rand()%9)};
    int counter{};
    if (arr[pos] == 0){
        arr[pos] = 2;
    }else{
        for (int i = 0; i < 9; i++){
            if (arr[i] > 0){
                counter += 1;
            }
        }
        if (counter < 9){
            act_comp(arr);
        }else{
            std::cout << "EMPATE!!\n";
            std::cin.get();
        }
    }
    check_game(arr);
    act_usr(arr);
}

void check_game(int arr[]){
    int win{};
    int counter{};
    for (int l = 1; l < 3; l++){
        for (int y = 0; y < 3; y++){
            if (arr[y*3+0] == l && arr[y*3+1] == l && arr[y*3+2] == l){
                win = l;
            }
        }
        for (int x = 0; x < 3; x++){
            if (arr[0*3+x] == l && arr[1*3+x] == l && arr[2*3+x] == l){
                win = l;
            }
        }
        if (arr[0*3+0] == l && arr[1*3+1] == l && arr[2*3+2] == l){
            win = l;
        }
        if (arr[0*3+2] == l && arr[1*3+1] == l && arr[2*3+0] == l){
            win = l;
        }
    }
    for (int i = 0; i < 9; i++){
        if (arr[i] > 0){
            counter += 1;
        }
    }
    draw(arr);
    if (counter >= 9){
        std::cout << "EMPATE!!\n";
            std::cin.get();
            end_program();
    }
    if (win == 1){
        std::cout << "El jugador gana\n";
        std::cin.get();
        end_program();
    }else if (win == 2){
        std::cout << "La IA gana\n";
        std::cin.get();
        end_program();
    }
}

void end_program(){
    std::cin.get();
    exit(3);
}
