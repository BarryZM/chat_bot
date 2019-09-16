#include<cstdio>
#include<string>
#include<iostream>
#include<vector>
#include<algorithm>
#include "chat_bot.h"
using namespace std;
const int limit_score;

vector<float> intent_identify(string query, struct task task_list) {

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
	struct task task_list = input.task_list;
	string query;
	if (input.is_content == true) {
		cout << content;
	}
	getline(cin, query);
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
	output.block_id = input.block_id;
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



int main() {

}
