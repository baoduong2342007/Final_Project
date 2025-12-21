#pragma once

using namespace std;

template <typename data_type>

class Dynamic_array{
private:

    data_type* arr;

public:

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

    Dynamic_array(){
        cur_n = 0;
        max_n = 1;
        arr = new data_type[max_n];
    }

    void clear_all(){
        delete[] arr;
    }

    data_type get_val(int id){
        return arr[id];
    }

    bool exist(data_type &X){
        for (int i = 0 ; i < cur_n ; i++){
            if (arr[i] == X) return true;
        }
        return false;
    }

    int find_pos(data_type &X){
        for (int i = 0 ; i < cur_n ; i++){
            if (arr[i] == X) return i;
        }
        return cur_n;
    }

    void ins(int pos , data_type &X){
        if (cur_n == max_n) expand();
        for (int i = cur_n ; i > pos ; i--){
            arr[i] = arr[i - 1];
        }
        arr[pos] = X;
        cur_n++;
    }

    void del(int pos){
        for (int i = pos + 1 ; i < cur_n ; i++){
            arr[i - 1] = arr[i];
        }
        cur_n--;
    }

    void push_back(data_type &X){
        ins(cur_n , X);
    }

    void pop_back(data_type){
        if (cur_n == 0) return;
        del(cur_n - 1);
    }
};
