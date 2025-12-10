#pragma once

#include<bits/stdc++.h>

using namespace std;

template <typename data_type>

class Dynamic_array{
private:

    data_type* arr;
    int cur_n , max_n;

    void expand(){
        data_type* tmp = new data_type[max_n * 2];
        for (int i = 0 ; i < cur_n ; i++){
            tmp[i] = arr[i];
        }
        delete[] arr;
        arr = tmp;
        max_n *= 2;
    }

public:

    Dynamic_array(){
        cur_n = 0;
        max_n = 1;
        arr = new data_type[max_n];
    }

    void clear_all(){
        delete[] arr;
    }

    int find_id(data_type X){
        for (int i = 0 ; i < cur_n ; i++){
            if (arr[i] == X) return i;
        }
        return -1;
    }

    void add(data_type X){
        int p = find_id(X);
        if (p != -1) return;
        if (cur_n + 1 > max_n) expand();
        arr[cur_n] = X;
        cur_n++;
    }

    void del(data_type X){
        int p = find_id(X);
        if (p == -1) return;
        for (int i = p + 1 ; i < cur_n ; i++){
            arr[i - 1] = arr[i];
        }
        cur_n--;
    }

    data_type get(int id){
        return arr[id];
    }
};
