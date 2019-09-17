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
		if (slot.slot_value[slot_id] ==condition.judge_value[i]) {  //////��������������Ϊһ������
			return condition.skip_block[i];
		}                                   
	}
	return condition.skip_block[condition.judge_num - 1];    ///����else���ֵ�ֵ
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
	vector<float> task_score = intent_identify(query, task_list);   /////��ͼʶ��
	///�õ�����task_score
	int max = 0;
	int maxmum = 0;
	for (int i = 0; i < task_list.task_num; i++) {
		if (task_score[i] > max) {
			max = i;
			maxmum = task_score[i];
		}
	}
	if (limit_score <= maxmum) {
		///��ͼ��ת
		task_id = input.task_id;
	}
	slot = slot_filling(query, input.slot);    ////input.slot��ȷ�ĸ��ʲ���Ҫ���
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
	output.next_block_id = input.block_id;                     ///����
	output.content = input.content;
	output.task_id = input.task_id;
	return output;
}

struct hidden_block_output hidden_block(struct hidden_block_input input,struct slot_define& slot) {
	struct hidden_block_output output;
	slot = slot_filling(input.query, input.slot);    ////input.slot��ȷ�ĸ��ʲ���Ҫ���
	output.task_id = input.task_id;
	output.slot = slot;
	output.next_block_id = 0;            //////��Ҫ�޸�

	return output;
}

void init(struct block_define& blocks,struct slot_define& slots,struct task_define& tasks) {
	////��ʼ����ͼ
	cout << "�½�����ͼ�����ǣ�";
	cin>>tasks.task_num;
	cout << "ÿ����ͼ�ֱ��ǣ�";
	for (int i = 0; i < tasks.task_num; i++) {
		string tem;
		cin>>tem;
		tasks.task_name->push_back(tem);
	}
	///��ʼ���Ի���Ԫ
	cout << "�½��ĶԻ���Ԫ�����ǣ�";
	cin >> blocks.block_num;
	cout << "ÿ���Ի���Ԫ�������ǣ�";
	for (int i = 0; i < blocks.block_num; i++) {
		int tem;
		cin >> tem;
		blocks.block_type.push_back(tem);
	}
	cout << "ÿ���Ի���Ԫ�ĺ�����Ԫ�ǣ�";
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
	///��ʼ���ʲ�
	cout << "�½��Ĵʲ۸����ǣ�";
	cin >> slots.slot_num;
	cout << "ÿ���ʲ۵������ǣ�";
	for (int i = 0; i < slots.slot_num; i++) {
		string tem;
		cin >> tem;
		slots.slot_name->push_back(tem);
	}
}

int main() {
	/////��Ϣ��Ԫ���ͣ�0������Ϣ��Ԫ��1����Ի���Ԫ��2�������ص�Ԫ
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





