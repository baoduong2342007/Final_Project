#pragma once
#include<bits/stdc++.h>
using namespace std;

template <typename data_type>
class Dynamic_array{
private:
    data_type* arr;
public:
    int cur_n , max_n;

    Dynamic_array(){
        cur_n = 0; max_n = 1;
        arr = new data_type[max_n];
    }

    ~Dynamic_array(){
        if(arr) { delete[] arr; arr = nullptr; }
    }

    Dynamic_array(const Dynamic_array& other) {
        cur_n = other.cur_n; max_n = other.max_n;
        arr = new data_type[max_n];
        for (int i = 0; i < cur_n; i++) arr[i] = other.arr[i];
    }

    Dynamic_array& operator=(const Dynamic_array& other) {
        if (this != &other) {
            delete[] arr;
            cur_n = other.cur_n; max_n = other.max_n;
            arr = new data_type[max_n];
            for (int i = 0; i < cur_n; i++) arr[i] = other.arr[i];
        }
        return *this;
    }

    void expand(){
        data_type* tmp = new data_type[max_n * 2];
        for (int i = 0 ; i < cur_n ; i++) tmp[i] = arr[i];
        delete[] arr;
        arr = tmp;
        max_n *= 2;
    }

    void clear_all(){
        delete[] arr;
        cur_n = 0; max_n = 1;
        arr = new data_type[max_n];
    }

    data_type& get_val(int id){ return arr[id]; }

    bool exist(const data_type &X){
        for (int i = 0 ; i < cur_n ; i++) if (arr[i] == X) return true;
        return false;
    }

    int find_pos(const data_type &X){
        for (int i = 0 ; i < cur_n ; i++) if (arr[i] == X) return i;
        return cur_n;
    }

    void ins(int pos , const data_type &X){
        if (cur_n == max_n) expand();
        for (int i = cur_n ; i > pos ; i--) arr[i] = arr[i - 1];
        arr[pos] = X;
        cur_n++;
    }

    void del(int pos){
        for (int i = pos + 1 ; i < cur_n ; i++) arr[i - 1] = arr[i];
        cur_n--;
    }

    void push_back(const data_type &X){ ins(cur_n , X); }

    void pop_back(){ if (cur_n > 0) del(cur_n - 1); }
};
