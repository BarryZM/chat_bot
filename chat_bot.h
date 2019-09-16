#include<cstdio>
#include<string>
#include<vector>
using namespace std;


struct slot_define {
	int slot_num;
	vector<string> slot_name[5];
	vector<string> slot_value[5];
};

struct judge_condition {
	bool is_judge;
	int judge_num;
	int slot_id;
	vector<string> judge_value[5];
	vector<int> skip_block;
};

struct task {
	int task_num;
	vector<string> task_name[5];
};

struct diaglogue_block_input {
	int task_id;
	int block_id;
	string content;
	bool is_content;
	struct slot_define slot;
	struct judge_condition condition;
	struct task task_list;
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