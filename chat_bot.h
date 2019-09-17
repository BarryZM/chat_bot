#include<cstdio>
#include<string>
#include<vector>
using namespace std;
const int block_max_num = 50;    ///最大单元个数
const int slot_max_num = 20;     ///最大词槽个数
const int judge_max_num = 10;      ///最大跳转条件个数
const int task_max_num = 20;     ///最大意图个数

struct block_define {
	int block_num;
	vector<vector<int>> block_relation[block_max_num];    
	///外层vector下标表示block_id，内层小vector表示该block后面连接的block_id
	vector<int> block_type;
	vector<string> message;
};


struct slot_define {
	int slot_num;
	vector<string> slot_name[slot_max_num];
	vector<string> slot_value[slot_max_num];
};

struct judge_condition {
	bool is_judge;
	int judge_num;
	int slot_id;
	vector<string> judge_value[judge_max_num];
	vector<int> skip_block;
};

struct task_define {
	int task_num;
	vector<string> task_name[task_max_num];
};

struct diaglogue_block_input {
	int task_id;
	int block_id;
	string content;
	bool is_content;
	struct slot_define slot;
	struct judge_condition condition;
	struct task_define task_list;
	string query;
};

struct diaglogue_block_output {
	int task_id;
	int next_block_id;
	struct slot_define slot;
};

struct message_block_input {
	int task_id;
	int block_id;
	string content;
};

struct message_block_output {
	int task_id;
	int next_block_id;
	string content;
};

struct hidden_block_input {
	int task_id;
	int block_id;
	string query;
	struct slot_define slot;
};

struct hidden_block_output {
	int task_id;
	int next_block_id;
	struct slot_define slot;
};