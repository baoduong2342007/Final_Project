#pragma once

#include "Global.h"

void read_string(ifstream &fin , string &s);

void write_string(ofstream &fout , string &s);

void save_data(Trie &X , string &filename);

void load_data(Trie &X , string &filename);

void load_transaction();

void save_transaction();

void load();

void save();
