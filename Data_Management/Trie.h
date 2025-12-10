#pragma once

#include <bits/stdc++.h>

using namespace std;

//ASCII have 128 character : 0 -> 127
const int max_char = 128;

struct Trie_node{
    int cnt[max_char];
    pair<Trie_node* , int> par;
    Trie_node* child[max_char];
    bool end_of_string;

    Trie_node(){
        par = make_pair(nullptr , -1);
        for (int c = 0 ; c < max_char ; c++){
            cnt[c] = 0;
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
            cur->cnt[c]++;
            if (cur->child[c] == nullptr){
                cur->child[c] = new Trie_node();
                cur->child[c]->par = make_pair(cur , c);
            }
            cur = cur->child[c];
        }
        cur->end_of_string = true;
    }

    void del(string &s){
        Trie_node* cur = head;
        for (int i = 0 ; i < int(s.size()) ; i++){
            int c = int(s[i]);
            cur->cnt[c]--;
            if (cur->cnt[c] == 0){
                clear_all(cur->child[c]);
                cur->child[c] = nullptr;
                break;
            }
            cur = cur->child[c];
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
