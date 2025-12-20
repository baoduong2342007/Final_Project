#include <bits/stdc++.h>
#include "Data_Persistence.h"

using namespace std;

void read_string(ifstream &fin , string &s){
    int n;
    fin.read((char*)&n , sizeof(int));
    s.clear();
    if (fin && n > 0){
        s.resize(n);
        fin.read((char*)&s[0] , n * sizeof(char));
    }
}

void write_string(ofstream &fout , string &s){
    int n = int(s.size());
    fout.write((char*)&n , sizeof(int));
    if (n > 0){
        fout.write((char*)&s[0] , n * sizeof(char));
    }
}

Trie_node* find_node_safe(Dynamic_array<Trie_node*> &arr, int id) {
    if (id >= 0 && id < arr.cur_n) return arr.get_val(id);
    return nullptr;
}

void load_data(Trie &X , string filename){
    ifstream fin(filename , ios::binary);
    if (fin.is_open()){
        if (fin.peek() == ifstream::traits_type::eof()) {
            fin.close(); return;
        }

        int n;
        fin.read((char*)&n , sizeof(int));
        if(!fin) { fin.close(); return; }

        string s;
        for (int i = 0 ; i < n ; i++){
            read_string(fin , s);
            X.ins(s);
        }
        fin.close();
    }
}

void save_data(Trie &X , string filename){
    ofstream fout(filename , ios::binary);
    if (fout.is_open()){
        Dynamic_array<string> arr = X.get_arr_string();
        fout.write((char*)&arr.cur_n , sizeof(int));
        for (int i = 0 ; i < arr.cur_n ; i++){
            string s = arr.get_val(i);
            write_string(fout , s);
        }
        fout.close();
    }
}

void load_transaction(){
    ifstream fin("transaction.bin" , ios::binary);
    if (fin.is_open()){
        if (fin.peek() == ifstream::traits_type::eof()) {
            fin.close(); return;
        }

        Dynamic_array<Trie_node*> w_ids = wallet.get_arr_id();
        Dynamic_array<Trie_node*> inc_ids = income.get_arr_id();
        Dynamic_array<Trie_node*> exp_ids = expense.get_arr_id();

        int num;
        fin.read((char*)&num , sizeof(num));
        if(!fin) { fin.close(); return; }

        for (int i = 0 ; i < num ; i++){
            Transaction X;
            fin.read((char*)&X.date , sizeof(Date));
            fin.read((char*)&X.source , sizeof(int));

            int sid; fin.read((char*)&sid , sizeof(int));
            X.source_id = (X.source == 1) ? find_node_safe(inc_ids, sid) : find_node_safe(exp_ids, sid);
            if(X.source_id) X.source_id->cnt_transaction++;

            int wid; fin.read((char*)&wid , sizeof(int));
            X.wallet_id = find_node_safe(w_ids, wid);
            if(X.wallet_id) X.wallet_id->cnt_transaction++;

            fin.read((char*)&X.amount , sizeof(long long));
            read_string(fin , X.description);

            event.push_back(X);
        }
        fin.close();
    }
}

void save_transaction(){
    ofstream fout("transaction.bin" , ios::binary);
    if (fout.is_open()){
        fout.write((char*)&event.cur_n , sizeof(int));
        for (int i = 0 ; i < event.cur_n ; i++){
            Transaction &X = event.get_val(i);
            fout.write((char*)&X.date , sizeof(Date));
            fout.write((char*)&X.source , sizeof(int));

            int sid = (X.source_id) ? X.source_id->id : -1;
            fout.write((char*)&sid , sizeof(int));

            int wid = (X.wallet_id) ? X.wallet_id->id : -1;
            fout.write((char*)&wid , sizeof(int));

            fout.write((char*)&X.amount , sizeof(long long));
            write_string(fout , X.description);
        }
        fout.close();
    }
}

void load_recurring(){
    ifstream fin("recurring.bin" , ios::binary);
    if (fin.is_open()){
        if (fin.peek() == ifstream::traits_type::eof()) {
            fin.close(); return;
        }

        Dynamic_array<Trie_node*> w_ids = wallet.get_arr_id();
        Dynamic_array<Trie_node*> inc_ids = income.get_arr_id();
        Dynamic_array<Trie_node*> exp_ids = expense.get_arr_id();

        int num;
        fin.read((char*)&num , sizeof(num));
        if(!fin) { fin.close(); return; }

        for (int i = 0 ; i < num ; i++){
            RecurringTransaction X;
            fin.read((char*)&X.start_date , sizeof(Date));
            fin.read((char*)&X.end_date , sizeof(Date));
            fin.read((char*)&X.source , sizeof(int));

            int sid; fin.read((char*)&sid , sizeof(int));
            X.source_id = (X.source == 1) ? find_node_safe(inc_ids, sid) : find_node_safe(exp_ids, sid);
            if(X.source_id) X.source_id->cnt_transaction++;

            int wid; fin.read((char*)&wid , sizeof(int));
            X.wallet_id = find_node_safe(w_ids, wid);
            if(X.wallet_id) X.wallet_id->cnt_transaction++;

            fin.read((char*)&X.amount , sizeof(long long));
            read_string(fin , X.description);

            auto_event.push_back(X);
        }
        fin.close();
    }
}

void save_recurring(){
    ofstream fout("recurring.bin" , ios::binary);
    if (fout.is_open()){
        fout.write((char*)&auto_event.cur_n , sizeof(int));
        for (int i = 0 ; i < auto_event.cur_n ; i++){
            RecurringTransaction &X = auto_event.get_val(i);
            fout.write((char*)&X.start_date , sizeof(Date));
            fout.write((char*)&X.end_date , sizeof(Date));
            fout.write((char*)&X.source , sizeof(int));

            int sid = (X.source_id) ? X.source_id->id : -1;
            fout.write((char*)&sid , sizeof(int));

            int wid = (X.wallet_id) ? X.wallet_id->id : -1;
            fout.write((char*)&wid , sizeof(int));

            fout.write((char*)&X.amount , sizeof(long long));
            write_string(fout , X.description);
        }
        fout.close();
    }
}

void load(){
    load_data(wallet , "wallet.bin");
    load_data(income , "income.bin");
    load_data(expense , "expense.bin");
    load_transaction();
    load_recurring();
}

void save(){
    save_data(wallet , "wallet.bin");
    save_data(income , "income.bin");
    save_data(expense , "expense.bin");
    save_transaction();
    save_recurring();
}
