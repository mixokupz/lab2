#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <thread>
#include <atomic>
#include "classes.h"
using namespace std;
std::atomic<bool> running(true);

void command_listener(Processer&proc) {
    std::string command;
    while (running) {
        std::getline(std::cin, command);
        istringstream iss(command);
        string first_str;
        iss>>first_str;
        if (first_str == "exit") {
            std::cout << "Exiting the program..." << std::endl;
            running = false;
        }else if (first_str == "help") {
            std::cout << "dump <filename> - save the universe to a file\ntick <n> - calculate n iterations and print the result. \nexit - end the game\n" << std::endl;
        }else if (first_str == "dump") {
            string second_str;
            iss>>second_str;
            proc.dump(second_str);
            std::cout << "Saving world..\n" << std::endl;

        }else if (first_str == "tick") {
            int n=0;
            iss>>n;
            proc.tick(n);
            std::cout << "After n iterations world'll be printed\n" << std::endl;
        } else {
            std::cout << "Unknown command. Type 'help' for a list of commands." << std::endl;
        }
    }
}


int main(int argc, char** argv){
    vector<string> inp_line;
    //нужна обработка входных данных, типо парсер
    for(int i=1;i<argc;i++){
        inp_line.push_back(argv[i]);
    }
    Processer proc = Processer(inp_line);
    Field field = Field(proc);
    Field old_field = Field(field);
    std::thread cmd_thread(command_listener,std::ref(proc));
    int live_points = 0;
    int iterator = 0;
    int ticks = 0;
        do {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            if(proc.is_dump()){
                ofstream in(proc.ret_dump_out_file());
                field.file_print_field(in);
                in.close();
                proc.no_dump();
            }else if(proc.is_tick()){
                //допсиать
                ticks = proc.ret_tick_iter();
                proc.no_tick();
            }
            field.print_field();
            field.copy_world(field.ret_world(), old_field.ret_world());
            field.new_world(field.ret_world(), old_field.ret_world());

            live_points = field.live_count(field.ret_world());
            cout<<endl;
            
            if (live_points == 0) {
                running = false;
                cout << "All points died. Click on any button." << endl; 
            }
            iterator+=1;
            ticks-=1;
            if(ticks==0){
                cout<<field.ret_name()<<' '<<"#R "<<"B"<<field.ret_for_born()<<"/S"<<field.ret_min_surv()<<field.ret_max_surv()<<endl;
                field.print_field();
            }
            if(iterator>=proc.ret_iter()){
                running = false;
                cout << "Iterations is over. Click on any button." << endl; 
            }
        } while (live_points != 0 && running && iterator<proc.ret_iter());

    cmd_thread.join();

    ofstream in(proc.ret_out_file());
    field.file_print_field(in);
    in.close();

    return 0;
}