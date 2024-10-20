#include "classes.h"
#include <fstream>
#include <iostream>
#include <sstream>
Field::Field(){
    this->field_name="\0";
    //используем fieldcreate
    this->for_born=0;
    this->min_for_survive=0;
    this->max_for_survive=0;
    this->x_size=10;
    this->y_size=10;
    this->world = new int*[this->x_size];
    for(int i=0;i<this->x_size;i++){
        this->world[i] = new int[this->y_size];
    }
}
Field::~Field(){
    this->field_name="\0";
    this->for_born=0;
    this->min_for_survive=0;
    this->max_for_survive=0;
    this->x_size=0;
    this->y_size=0;
    for(int i=0;i<this->x_size;i++){
        delete[] this->world[i];
    }
    delete [] this->world;
}
Field::Field(Field &field){
    this->field_name=field.field_name;
    this->x_size=field.x_size;
    this->y_size=field.y_size;
    this->world = new int*[this->x_size];
    for(int i=0;i<this->x_size;i++){
        this->world[i] = new int[this->y_size];
    }
}
Field::Field(Processer &proc){
    //создаем поле
    ifstream inpt(proc.ret_in_file());
    
    string readen;
    while(getline(inpt,readen)){
        if (readen[0] == '#') {
            if (readen[1] == 'N') {
                this->field_name = readen.substr(3); 
            } else if (readen[1] == 'R') {
                string rules = readen.substr(3);
                size_t b_pos = rules.find('B');
                size_t s_pos = rules.find('S');
                this->for_born = stoi(rules.substr(b_pos + 1, s_pos - b_pos - 1));
                this->min_for_survive = stoi(rules.substr(s_pos + 1, 1)); 
                this->max_for_survive = stoi(rules.substr(s_pos + 2));
            } else if (readen[1] == 'S') {
                stringstream str(readen.substr(3)); 
                char slash;
                str >> this->x_size;
                str >> slash;
                str >> this->y_size;

                this->world = new int*[this->x_size];
                for(int i=0;i<this->x_size;i++){
                    this->world[i] = new int[this->y_size];
                }
                for(int i=0;i<this->x_size;i++){
                    for(int j=0;j<this->y_size;j++){
                        this->world[i][j] = 0;
                    }
                }
            }
        } else {
            stringstream str(readen);
            int x = 0;
            int y = 0;
            while (str >> x >> y) {
                this->world[x][y] =1;
            }
        }
    }
}
void Field::file_print_field(ofstream &in){
    for (int i = 0; i < this->x_size; i++) {
        for (int j = 0; j < this->y_size; j++) {
            if (world[i][j] == 1) {
                in << '*';
            } else {
                in << '-';
            }
            in << ' ';
        }
        in << endl;
    }
}
void Field::print_field(){
    for (int i = 0; i < this->x_size; i++) {
        for (int j = 0; j < this->y_size; j++) {
            if (world[i][j] == 1) {
                cout << '*';
            } else {
                cout << '-';
            }
            cout << ' ';
        }
        cout << endl;
    }
    cout<<endl;
    cout<<endl;
}
int Field::live_count(int** world){
    int count = 0;
    for (int i = 0; i < this->x_size; i++) {
        for (int j = 0; j < this->y_size; j++) {
            if (world[i][j] == 1) {
                count++;
            }
        }
    }
    return count;
}
void Field::watch_neighbors(int neigh[][2], int x, int y){
    int i, j;
    int k = 0;

    for (i = x - 1; i <= x + 1; i++) {
        for (j = y - 1; j <= y + 1; j++) {
            if (i == x && j == y) {
                continue;
            }
            neigh[k][0] = i;
            neigh[k][1] = j;
            k++;
        }
    }
}
int Field::live_count_neighbors(int **world, int x, int y){
    int count = 0;
    int i;
    int nb[8][2];
    int _x = 0;
    int _y =0 ;

    watch_neighbors(nb, x, y);

    for (i = 0; i < 8; i++) {
        _x = nb[i][0];
        _y = nb[i][1];

        if (_x < 0 || _y < 0) {
            continue;
        }
        if (_x >= this->x_size || _y >= this->y_size) {
            continue;
        }

        if (world[_x][_y] == 1) {
            count++;
        }
    }

    return count;
}
void Field::new_world(int** world, int **old_world){
    int i;
    int j;
    int live_nb;
    int p;

    for (i = 0; i < this->x_size; i++) {
        for (j = 0; j < this->y_size; j++) {
            p = old_world[i][j];
            live_nb = live_count_neighbors(old_world, i, j);

            if (p == 0) {
                if (live_nb == this->for_born) {
                    world[i][j] = 1;
                }
            } else {
                if (live_nb < this->min_for_survive || live_nb > this->max_for_survive) {
                    world[i][j] = 0;
                }
            }
        }
    }
}
void Field::copy_world(int** src, int** dest){
    for (int i = 0; i < this->x_size; i++) {
        for (int j = 0; j < this->y_size; j++) {
            dest[i][j] = src[i][j];
        }
    }
}
int**Field::ret_world(){
    return this->world;
}
string Field::ret_name(){
    return this->field_name;
}

int Field::ret_for_born(){
    return this->for_born;
}
int Field::ret_min_surv(){
    return this->min_for_survive;
}
int Field::ret_max_surv(){
    return this->max_for_survive;
}