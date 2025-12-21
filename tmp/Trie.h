#pragma once
#include <string>
#include <utility>
#include "Dynamic_array.h"
using namespace std;

const int max_char = 128;

struct Trie_node{
    int cnt_string , cnt_transaction;
    pair<Trie_node* , int> par;
    Trie_node* child[max_char];
    bool end_of_string;
    int id;

    Trie_node(){
        cnt_string = cnt_transaction = 0;
        par = make_pair(nullptr , 0);
        for (int c = 0 ; c < max_char ; c++) child[c] = nullptr;
        end_of_string = false;
        id = -1;
    }
};

struct Trie{
    Trie_node* head;
    int ID;

    Trie(){ head = new Trie_node(); ID = 0; }

    ~Trie(){ clear_all(); delete head; }

    void clear_recursive(Trie_node* cur){
        if(!cur) return;
        for (int c = 0 ; c < max_char ; c++){
            if (cur->child[c] != nullptr){
                clear_recursive(cur->child[c]);
            }
        }
        delete cur;
    }

    void clear_all(){
        for(int c=0; c<max_char; c++)
            if(head->child[c]) clear_recursive(head->child[c]);

        for(int c=0; c<max_char; c++) head->child[c] = nullptr;
        ID = 0;
    }

    bool exist(string &s){
        Trie_node* cur = head;
        for (int i = 0 ; i < int(s.size()) ; i++){
            int c = int(s[i]);
            if (cur->child[c] == nullptr) return false;
            cur = cur->child[c];
        }
        return cur->end_of_string;
    }

    Trie_node* get_id(string &s){
        Trie_node* cur = head;
        for (int i = 0 ; i < int(s.size()) ; i++){
            int c = int(s[i]);
            if (cur->child[c] == nullptr) return nullptr;
            cur = cur->child[c];
        }
        return (cur->end_of_string) ? cur : nullptr;
    }

    void ins(string &s){
        Trie_node* cur = head;
        for (int i = 0 ; i < int(s.size()) ; i++){
            int c = int(s[i]);
            if (cur->child[c] == nullptr){
                cur->child[c] = new Trie_node();
                cur->child[c]->par = make_pair(cur , c);
            }
            cur = cur->child[c];
            cur->cnt_string++;
        }
        cur->end_of_string = true;
    }

    void del(string &s){
        Trie_node* cur = head;
        for (int i = 0 ; i < int(s.size()) ; i++){
            int c = int(s[i]);
            cur = cur->child[c];
            cur->cnt_string--;
             if (cur->cnt_string == 0){
                Trie_node* par_node = cur->par.first;
                par_node->child[c] = nullptr;
                clear_recursive(cur);
                return;
            }
        }
        cur->end_of_string = false;
    }

    string get_string(Trie_node* cur){
        string s;
        while (cur != head && cur != nullptr){
            s.push_back(char(cur->par.second));
            cur = cur->par.first;
        }
        reverse(s.begin() , s.end());
        return s;
    }

    void dfs_string(Trie_node *cur , string &s , Dynamic_array<string> &arr){
        if (cur->end_of_string){
            arr.push_back(s);
            cur->id = ID++;
        } else cur->id = -1;

        for (int c = 0 ; c < max_char ; c++){
            if (cur->child[c]){
                s.push_back(char(c));
                dfs_string(cur->child[c] , s , arr);
                s.pop_back();
            }
        }
    }

    Dynamic_array<string> get_arr_string(){
        ID = 0;
        Dynamic_array<string> arr;
        string s;
        dfs_string(head , s , arr);
        return arr;
    }

    void dfs_id(Trie_node *cur , Dynamic_array<Trie_node*> &arr){
        if (cur->end_of_string) arr.push_back(cur);
        for (int c = 0 ; c < max_char ; c++){
            if (cur->child[c]) dfs_id(cur->child[c] , arr);
        }
    }

    Dynamic_array<Trie_node*> get_arr_id(){
        Dynamic_array<Trie_node*> arr;
        dfs_id(head , arr);
        return arr;
    }
};
