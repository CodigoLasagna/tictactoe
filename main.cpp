#include <iostream>
#include <thread>
#include <chrono>

void start_menu();
void start_game(int type);
void draw(int arr[]);
void act_usr(int arr[], int player);
void act_comp(int arr[]);
void check_game(int arr[], int player);
void end_game();
void end_program();

int main(){
    start_menu();
}
void start_menu(){
    std::system("clear");
    std::string option = "";
    std::cout <<"[1] JcE - [2] JcJ - [3] salir\n>";
    std::cin >> option;
    if (std::stoi(option) != 3){
        start_game(std::stoi(option)-1);
    }else{
        end_program();
    }
}

void start_game(int type){
    srand(time(NULL));
    int tab [9] = {};
    draw(tab);
    int coin {rand()%2};
    if (type == 0){
        if (coin == 0){
            act_usr(tab, 0);
        }else{
            act_comp(tab);
        }
    }else{
        if (coin == 0){
            act_usr(tab, 1);
        }else{
            act_usr(tab, 2);
        }
    }
}

void start_versus(){

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

void act_usr(int arr[], int player){
    std::string buffer = "";
    std::string letter = "";
    std::string number = "";
    int x{0}, y{0};
    int type{0};
    if (player != 0){
        std::cout << "Turno del jugador " << player << ": ";
    }else{
        std::cout << "Turno del jugador: ";
    }
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
        if (player != 0 ){
            arr[x*3+y] = player;
        }else{
            arr[x*3+y] = 1;
        }
    }else{
        std::cout << "Espació ocupado\n";
        act_usr(arr, player);
    }
    check_game(arr, player);
    if (player == 0){
        act_comp(arr);
    }else if (player == 1){
        act_usr(arr, 2);
    }else{
        act_usr(arr, 1);
    }
    //act_usr(arr);
}

void act_comp(int arr[]){
    int pos{(rand()%9)};
    int counter{};
    if (arr[pos] == 0){
        std::this_thread::sleep_for(std::chrono::seconds(1));
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
            end_game();
        }
    }
    check_game(arr, 0);
    act_usr(arr, 0);
}

void check_game(int arr[], int player){
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
    if (win > 0){
        if (win == 1 && player == 0){
            std::cout << "El jugador gana!\n";
        }else if (win == player){
            std::cout << "El jugador " << player << " gana!\n";
        }else if (win == 2 && player == 0){
            std::cout << "La IA gana\n";
        }
        end_game();
    }
    if (counter >= 9){
        std::cout << "EMPATE!!\n";
        end_game();
    }
}

void end_game(){
    std::cout << "Presione cualquier tecla para continuar...";
    std::cin.get();
    std::cin.get();
    start_menu();
}

void end_program(){
    exit(3);
}
