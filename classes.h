#include <iostream>
#include <vector>
using namespace std;

class Processer{

    private:
        string in_file;
        string out_file;
        string dump_out_file;
        int iter;
        int was_dump;
        int tick_iter;
        int was_tick;

    public:
        Processer();
        ~Processer();
        Processer(vector<string> inp_line);
        bool proc_opened();
        string ret_in_file();
        string ret_out_file();
        string ret_dump_out_file();
        int ret_iter();
        int ret_tick_iter();
        void dump(string out);
        void tick(int n);
        void no_dump();
        void no_tick();
        int is_dump();
        int is_tick();
};

class Field{
    private:
        string field_name;
        int for_born;
        int min_for_survive=0;
        int max_for_survive=0;
        int x_size;
        int y_size;
        int **world;    
    public:
        Field();
        ~Field();
        Field(Processer &proc);
        Field(Field &field);
        void print_field();
        void file_print_field(ofstream &in);
        int live_count(int**world);
        void watch_neighbors(int neigh[][2], int x, int y);
        int live_count_neighbors(int **world, int x, int y);
        void new_world(int** world, int **prev_world);
        void copy_world(int** src, int** dest);
        int** ret_world();
        string ret_name();
        int ret_for_born();
        int ret_min_surv();
        int ret_max_surv();
};