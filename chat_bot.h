#pragma once

#include<string>
#include<vector>
using namespace std;

struct block_define {
	int block_num;
	vector<vector<int>> block_relation;    
	///外层vector下标表示block_id，内层小vector表示该block后面连接的block_id
	vector<int> block_type;
	vector<string> message;
};

struct slot_define {
	int slot_num;
	vector<string> slot_name;
	vector<string> slot_value;
};

struct task_define {
	int task_num;
	vector<string> task_name;
};

struct entity_define {
	int entity_kind;
	vector<vector<string>> entity_value;
};

struct judge_condition {
	bool is_judge;
	int judge_num;
	int slot_id;
	vector<string> judge_value;
	vector<char> judge_symbol;
	vector<int> skip_block;
};

struct block_input {
	int task_id;
	int block_id;
	string content;
	string query;
	struct judge_condition condition;
};


struct block_output {
	int task_id;
	int next_block_id;
};
