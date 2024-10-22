#include "classes.h"
#include <iostream>
#include <fstream>
Processer::Processer(){
    this->in_file="input.txt";
    this->out_file="output.txt";
    this->iter=2147483647;
    this->was_dump = 0;
    this->tick_iter = 2147483647;
    this->was_tick = 0;
}
Processer::~Processer(){
    this->in_file="\0";
    this->out_file="\0";
    this->iter=0;
}


Processer::Processer(vector<string> inp_line){
    if(inp_line.size()==0){
        this->in_file="input.txt";
        this->out_file="output.txt";
        this->iter=2147483647;
        this->was_dump = 0;
        this->tick_iter = 2147483647;
        this->was_tick = 0;
        cout<<"No input file. Base game will start.\n";
    }else if(inp_line.size()==1){
        ifstream inpt(inp_line[0]);
        this->was_dump = 0;
        this->tick_iter = 2147483647;
        this->was_tick = 0;
        this->iter=2147483647;
        this->out_file="output.txt";
        if(inpt.is_open()){
            this->in_file = inp_line[0];
            inpt.close();
        }else{
            this->in_file="input.txt";
            cout<<"Input file can't be opened.Base game will start.\n";
        }
        

    }else if(inp_line.size()==5){
        ifstream inpt(inp_line[0]);
        this->was_dump = 0;
        this->tick_iter = 2147483647;
        this->was_tick = 0;
        if(inpt.is_open()){
            this->in_file = inp_line[0];
            inpt.close();
        }else{
            this->in_file="input.txt";
            cout<<"Input file can't be opened.Base game will start.\n";
        }
        if(inp_line[1]=="-i" && inp_line[3]=="-o"){
            this->iter = atoi(inp_line[2].c_str());
            if(this->iter<0){
                cout<<"Iteration must be > 0. Base iter will be use.\n";
                this->iter = 2147483647;
            }
            this->out_file = inp_line[4];
        }else{
            throw std::invalid_argument("Error: Wrong input!\n");
        }
    }
    else{
        throw std::invalid_argument("Error: Wrong input!\n");
    }
}
string Processer::ret_in_file(){
    return this->in_file;
}
string Processer::ret_out_file(){
    return this->out_file;
}
string Processer::ret_dump_out_file(){
    return this->dump_out_file;
}
int Processer::ret_iter(){
    return this->iter;
}
int Processer::ret_tick_iter(){
    return this->tick_iter;
}
void Processer::dump(string out){

    this->was_dump =1;
    this->dump_out_file = out;
}
void Processer::tick(int n){
    this->was_tick =1;
    this->tick_iter =n;
}
void Processer::no_dump(){

    this->was_dump =0;
}
void Processer::no_tick(){
    this->was_tick =0;
}
int Processer::is_dump(){
    return this->was_dump;
}
int Processer::is_tick(){
    return this->was_tick;
}