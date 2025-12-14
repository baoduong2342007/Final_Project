#include <bits/stdc++.h>
#include "Data_Persistence.h"

using namespace std;

void read_string(ifstream &fin , string &s){
    int n;
    fin.read((char*)&n , sizeof(int));
    s.clear();
    if (n > 0){
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

void load_data(Trie &X , string filename){
    ifstream fin;
    fin.open(filename , ios::binary);
    if (fin.is_open() == false) return;
    int n; string s;
    fin.read((char*)&n , sizeof(int));
    for (int i = 0 ; i < n ; i++){
        read_string(fin , s);
        X.ins(s);
    }
    fin.close();
}

void save_data(Trie &X , string filename){
    ofstream fout;
    fout.open(filename , ios::binary);
    if (fout.is_open() == false) return;
    Dynamic_array<string> arr = X.get_arr_string();
    fout.write((char*)&arr.cur_n , sizeof(int));
    for (int i = 0 ; i < arr.cur_n ; i++){
        string s = arr.get_val(i);
        write_string(fout , s);
    }
    arr.clear_all();
    fout.close();
}

void load_transaction(){
    ifstream fin;
    fin.open("transaction.bin" , ios::binary);
    if (fin.is_open() == false) return;
    Dynamic_array<Trie_node*> wallet_table_id = wallet.get_arr_id();
    Dynamic_array<Trie_node*> income_table_id = income.get_arr_id();
    Dynamic_array<Trie_node*> expense_table_id = expense.get_arr_id();
    int num;
    fin.read((char*)&num , sizeof(num));
    for (int i = 0 ; i < num ; i++){
        Transaction X;
        fin.read((char*)&X.date , sizeof(Date));
        fin.read((char*)&X.source , sizeof(int));
        //
        int id_source;
        fin.read((char*)&id_source , sizeof(int));
        X.source_id = (X.source == 1) ? income_table_id.get_val(id_source) : expense_table_id.get_val(id_source);
        X.source_id->cnt_transaction++;
        //
        int id_wallet;
        fin.read((char*)&id_wallet , sizeof(int));
        X.wallet_id = wallet_table_id.get_val(id_wallet);
        X.wallet_id->cnt_transaction++;
        //
        fin.read((char*)&X.amount , sizeof(long long));
        read_string(fin , X.description);
        event.push_back(X);
    }
    wallet_table_id.clear_all();
    income_table_id.clear_all();
    expense_table_id.clear_all();
    fin.close();
}

void save_transaction(){
    ofstream fout;
    fout.open("transaction.bin" , ios::binary);
    if (fout.is_open() == false) return;
    fout.write((char*)&event.cur_n , sizeof(int));
    for (int i = 0 ; i < event.cur_n ; i++){
        Transaction X = event.get_val(i);
        fout.write((char*)&X.date , sizeof(X.date));
        fout.write((char*)&X.source , sizeof(X.source));
        fout.write((char*)&X.source_id->id , sizeof(X.source_id->id));
        fout.write((char*)&X.wallet_id->id , sizeof(X.wallet_id->id));
        fout.write((char*)&X.amount , sizeof(X.amount));
        write_string(fout , X.description);
    }
    fout.close();
}

void load(){
    load_data(wallet , "wallet.bin");
    load_data(income , "income.bin");
    load_data(expense , "expense.bin");
    load_transaction();
}

void save(){
    save_data(wallet , "wallet.bin");
    save_data(income , "income.bin");
    save_data(expense , "expense.bin");
    save_transaction();
}
