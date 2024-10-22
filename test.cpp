#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "classes.h"
#include "gtest/gtest.h"

TEST(processer_test, processer_ret_in_file) {
    Processer proc = Processer();
    string infile = proc.ret_in_file();
    ASSERT_EQ(infile, "input.txt");
}
TEST(processer_test, processer_ret_out_file) {
    Processer proc = Processer();
    string outfile = proc.ret_out_file();
    ASSERT_EQ(outfile, "output.txt");
}
TEST(processer_test, processer_ret_iter) {
    Processer proc = Processer();
    int iter = proc.ret_iter();
    ASSERT_EQ(iter, 2147483647);
}
TEST(processer_test, processer_create_inp_line) {
    vector<string> inp_line = {"input.txt", "-i" ,"30" ,"-o", "file.txt"};
    Processer proc = Processer(inp_line);
    
    ASSERT_EQ(proc.ret_in_file(), "input.txt");
    ASSERT_EQ(proc.ret_iter(), 30);
    ASSERT_EQ(proc.ret_out_file(), "file.txt");

    vector<string> s_inp_line = {"input.txt"};
    Processer s_proc = Processer(s_inp_line);
    
    ASSERT_EQ(s_proc.ret_in_file(), "input.txt");
    ASSERT_EQ(s_proc.ret_iter(), 2147483647);
    ASSERT_EQ(s_proc.ret_out_file(), "output.txt");

    vector<string> d_inp_line = {};
    Processer d_proc = Processer(d_inp_line);
    
    ASSERT_EQ(d_proc.ret_in_file(), "input.txt");
    ASSERT_EQ(d_proc.ret_iter(), 2147483647);
    ASSERT_EQ(d_proc.ret_out_file(), "output.txt");


}
TEST(processer_test, processer_is_dump) {
    Processer proc = Processer();
    ASSERT_EQ(proc.is_dump(), 0);

    Processer s_proc = Processer();
    s_proc.dump("dump.txt");
    ASSERT_EQ(s_proc.is_dump(), 1);
    ASSERT_EQ(s_proc.ret_dump_out_file(), "dump.txt");
}
TEST(processer_test, processer_is_tick) {
    Processer proc = Processer();
    ASSERT_EQ(proc.is_tick(), 0);

    Processer s_proc = Processer();
    s_proc.tick(3);
    ASSERT_EQ(s_proc.is_tick(), 1);
    ASSERT_EQ(s_proc.ret_tick_iter(), 3);

}
TEST(processer_test, processer_no_tick) {
    Processer proc = Processer();
    proc.tick(3);
    ASSERT_EQ(proc.is_tick(), 1);
    proc.no_tick();
    ASSERT_EQ(proc.is_tick(), 0);
}
TEST(processer_test, processer_no_dump) {
    Processer proc = Processer();
    proc.dump("dump.txt");
    ASSERT_EQ(proc.is_dump(), 1);
    proc.no_dump();
    ASSERT_EQ(proc.is_dump(), 0);
}
TEST(field_test, field_create) {
    Field field = Field();
    ASSERT_EQ(field.ret_name(), "\0");
    ASSERT_EQ(field.ret_for_born(), 0);
    ASSERT_EQ(field.ret_min_surv(), 0);
    ASSERT_EQ(field.ret_max_surv(), 0);    
}
TEST(field_test, field_by_proc_create) {
    vector<string> inp_line = {"input.txt", "-i" ,"30" ,"-o", "file.txt"};
    Processer proc = Processer(inp_line);
    
    Field field = Field(proc);
    
    ASSERT_EQ(field.ret_name(), "My game");
    ASSERT_EQ(field.ret_for_born(), 3);
    ASSERT_EQ(field.ret_min_surv(), 4);
    ASSERT_EQ(field.ret_max_surv(), 5);    
}
TEST(field_test, field_by_field_create) {
    vector<string> inp_line = {"input.txt", "-i" ,"30" ,"-o", "file.txt"};
    Processer proc = Processer(inp_line);
    
    Field field = Field(proc);

    Field s_field = Field(field);
    
    ASSERT_EQ(field.ret_name(), s_field.ret_name());
    ASSERT_EQ(field.ret_for_born(), s_field.ret_for_born());
    ASSERT_EQ(field.ret_min_surv(), s_field.ret_min_surv());
    ASSERT_EQ(field.ret_max_surv(), s_field.ret_max_surv());    
}
TEST(field_test, field_print_file) {
    vector<string> inp_line = {"input.txt", "-i" ,"30" ,"-o", "file.txt"};
    Processer proc = Processer(inp_line);
    
    Field field = Field(proc);
    ofstream out("field_out_file.txt");
    field.file_print_field(out);
    out.close();
    ifstream in("field_out_file.txt");
    char c;
    int** world = field.ret_world();
    int s_world[111];
    int x =0;
    while(!in.eof()){
        in>>c;
        if(c=='-' || c=='*'){
            if(c=='*'){
                s_world[x] = 1;
            }else if(c=='-'){
                s_world[x] = 0;
            }
            x+=1;
        }
    }
    for(int i=0;i<11;i++){
        for(int j=0;j<10;j++){
            ASSERT_EQ(s_world[10*i+j],world[i][j]);
        }
    }


}
TEST(field_test, field_count_live) {
    vector<string> inp_line = {"input.txt", "-i" ,"30" ,"-o", "file.txt"};
    Processer proc = Processer(inp_line);
    
    Field field = Field(proc);
    
    int live = field.live_count(field.ret_world());
    ASSERT_EQ(live,30);

}
TEST(field_test, field_copy_world) {
    vector<string> inp_line = {"input.txt", "-i" ,"30" ,"-o", "file.txt"};
    Processer proc = Processer(inp_line);
    
    Field field = Field(proc);
    int **mas;
    mas = new int*[11];
    for(int i=0;i<11;i++){
        mas[i] = new int[10];
    }
    field.copy_world(field.ret_world(),mas);
    int **mas_s = field.ret_world();
    for(int i=0;i<11;i++){
        for(int j=0;j<10;j++){
            ASSERT_EQ(mas[i][j],mas_s[i][j]);
        }
    }
    for(int i=0;i<11;i++){
        delete[] mas[i];
    }
    delete [] mas;
    
}
TEST(field_test, field_count_live_neighbours) {
    vector<string> inp_line = {"input.txt", "-i" ,"30" ,"-o", "file.txt"};
    Processer proc = Processer(inp_line);
    
    Field field = Field(proc);
    int live = field.live_count_neighbors(field.ret_world(),6,3);
    ASSERT_EQ(live,2);
}
