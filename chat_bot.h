#include<cstdio>
#include<string>
#include<vector>
using namespace std;
const int block_max_num = 50;    ///���Ԫ����
const int slot_max_num = 20;     ///���ʲ۸���
const int judge_max_num = 10;      ///�����ת��������
const int task_max_num = 20;     ///�����ͼ����

struct block_define {
	int block_num;
	vector<vector<int>> block_relation[block_max_num];    
	///���vector�±��ʾblock_id���ڲ�Сvector��ʾ��block�������ӵ�block_id
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