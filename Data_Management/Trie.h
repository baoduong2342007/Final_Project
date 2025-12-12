#pragma once

#include <bits/stdc++.h>

using namespace std;

//ASCII have 128 character : 0 -> 127
const int max_char = 128;

struct Trie_node{
    int cnt_string , cnt_transaction;
    pair<Trie_node* , int> par;
    Trie_node* child[max_char];
    bool end_of_string;

    Trie_node(){
        cnt_string = cnt_transaction = 0;
        par = make_pair(nullptr , 0);
        for (int c = 0 ; c < max_char ; c++){
            child[c] = nullptr;
        }
        end_of_string = false;
    }
};

//Trie also calls prefix subtree
//link : https://wiki.vnoi.info/algo/string/trie

struct Trie{
    Trie_node* head;

    Trie(){
        head = new Trie_node();
    }

    void clear_all(Trie_node* cur){
        for (int c = 0 ; c < max_char ; c++){
            if (cur->child[c] != nullptr){
                clear_all(cur->child[c]);
            }
        }
        delete cur;
    }

    void clear_all(){
        clear_all(head);
        head = nullptr;
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
        if (cur->end_of_string == true) return cur; else return nullptr;
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
                clear_all(cur);
                return;
            }
        }
        cur->end_of_string = false;
    }

    void print(Trie_node* cur){
        if (cur == head) return;
        print(cur->par.first);
        cout << char(cur->par.second);
    }
    //print does not (endl or "\n")
};
