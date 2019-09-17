#include<cstdio>
#include<string>
#include<iostream>
#include<vector>
#include<algorithm>
#include "chat_bot.h"
using namespace std;
const int limit_score;

vector<float> intent_identify(string query, struct task_define task_list) {

}

struct slot_define slot_filling(string query, struct slot_define slot) {

}

int judge_next_block(struct slot_define slot,struct judge_condition condition) {
	if (condition.is_judge == false) {
		return -1;
	}
	int slot_id = condition.slot_id;
	for (int i = 0; i < condition.judge_num - 1; i++) {
		if (slot.slot_value[slot_id] ==condition.judge_value[i]) {  //////待改正：条件作为一个整体
			return condition.skip_block[i];
		}                                   
	}
	return condition.skip_block[condition.judge_num - 1];    ///返回else部分的值
}

struct diaglogue_block_output diaglogue_block(struct diaglogue_block_input input,struct slot_define& slot) {
	struct diaglogue_block_output output;
	string content = input.content;
	int task_id = input.task_id;
	struct task_define task_list = input.task_list;
	string query;
	if (input.is_content == true) {
		cout << content;
	}
	query = input.query;
	vector<float> task_score = intent_identify(query, task_list);   /////意图识别
	///得到最大的task_score
	int max = 0;
	int maxmum = 0;
	for (int i = 0; i < task_list.task_num; i++) {
		if (task_score[i] > max) {
			max = i;
			maxmum = task_score[i];
		}
	}
	if (limit_score <= maxmum) {
		///意图跳转
		task_id = input.task_id;
	}
	slot = slot_filling(query, input.slot);    ////input.slot明确哪个词槽需要填充
	int next_block = judge_next_block(slot,input.condition);

	output.slot = slot;
	output.task_id = task_id;
	output.next_block_id = next_block;

	return output;
}

struct message_block_output message_block(struct message_block_input input) {
	struct message_block_output output;
	string content = input.content;
	cout << content;
	output.next_block_id = input.block_id;                     ///待定
	output.content = input.content;
	output.task_id = input.task_id;
	return output;
}

struct hidden_block_output hidden_block(struct hidden_block_input input,struct slot_define& slot) {
	struct hidden_block_output output;
	slot = slot_filling(input.query, input.slot);    ////input.slot明确哪个词槽需要填充
	output.task_id = input.task_id;
	output.slot = slot;
	output.next_block_id = 0;            //////需要修改

	return output;
}

void init(struct block_define& blocks,struct slot_define& slots,struct task_define& tasks) {
	////初始化意图
	cout << "新建的意图个数是：";
	cin>>tasks.task_num;
	cout << "每个意图分别是：";
	for (int i = 0; i < tasks.task_num; i++) {
		string tem;
		cin>>tem;
		tasks.task_name->push_back(tem);
	}
	///初始化对话单元
	cout << "新建的对话单元个数是：";
	cin >> blocks.block_num;
	cout << "每个对话单元的类型是：";
	for (int i = 0; i < blocks.block_num; i++) {
		int tem;
		cin >> tem;
		blocks.block_type.push_back(tem);
	}
	cout << "每个对话单元的后续单元是：";
	for (int i = 0; i < blocks.block_num; i++) {
		int num;
		cin >> num;
		int tem;
		vector<int> vec_tem;
		for (int j = 0; j < num; j++) {
			cin >> tem;
			vec_tem.push_back(tem);
		}
		blocks.block_relation->push_back(vec_tem);
	}
	for (int i = 0; i < blocks.block_num; i++) {
		string tem;
		cin >> tem;
		blocks.message.push_back(tem);
	}
	///初始化词槽
	cout << "新建的词槽个数是：";
	cin >> slots.slot_num;
	cout << "每个词槽的名字是：";
	for (int i = 0; i < slots.slot_num; i++) {
		string tem;
		cin >> tem;
		slots.slot_name->push_back(tem);
	}
}

int main() {
	/////消息单元类型：0代表消息单元，1代表对话单元，2代表隐藏单元
	struct block_define blocks;
	struct slot_define slots;
	struct task_define tasks;
	init(blocks,slots,tasks);
	string query;
	int block_id = 0;
	while (getline(cin, query)) {
		if (query == "end") {
			break;
		}
		vector<float> intent = intent_identify(query, tasks);
		int type = blocks.block_type[block_id];
		if (type == 0) {
			struct message_block_input msg_input;
			msg_input.content = blocks.message[block_id];
			msg_input.task_id = 0;
			msg_input.block_id = block_id;
			struct message_block_output msg_output = message_block(msg_input);
		}
		if (type == 1) {
			struct diaglogue_block_input dia_input;
			dia_input.block_id = block_id;
			dia_input.task_id = 0;
			dia_input.content = blocks.message[block_id];
			dia_input.slot = slots;
			dia_input.query = query;
			struct diaglogue_block_output dia_output = diaglogue_block(dia_input, slots);
		}
		if (type == 2) {
			struct hidden_block_input hd_input;
			hd_input.block_id = block_id;
			hd_input.task_id = 0;
			hd_input.slot = slots;
			hd_input.query = query;
			struct hidden_block_output hd_output = hidden_block(hd_input, slots);
		}
		block_id++;
	}



}





