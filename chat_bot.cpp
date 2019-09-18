#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include "chat_bot.h"
using namespace std;

int intent_identify(string query, struct task_define task_list) {
	int task_id = 99;
	for (int i = 0; i < task_list.task_num; i++) {
		if (query.find(task_list.task_name[i]) != string::npos) {
			task_id = i;
		}
	}
	return task_id;
}

void slot_filling(string query, struct slot_define& slot, struct entity_define entity) {
	for (int i = 0; i < slot.slot_num; i++) {
		slot.slot_value.push_back("null");
		vector<string> tem = entity.entity_value[i];
		for (unsigned int j = 0; j < tem.size(); j++) {
			if (query.find(tem[j]) != string::npos) {
				slot.slot_value[i] = tem[j];
				break;
			}
		}
	}
}

struct block_output diaglogue_block(struct block_input input, struct slot_define& slot, struct block_define block, struct task_define task_list, struct entity_define entity) {
	struct block_output output;
	string content = input.content;
	int task_id = input.task_id;
	int block_id = input.block_id;
	string query;
	cout << content<<endl;
	getline(cin, query);                             ///////�ȴ��û��ش�
	int intent = intent_identify(query, task_list);
	if (intent != 99) {
		task_id = intent;
	}
	slot_filling(query, slot, entity);    ////input.slot��ȷ�ĸ��ʲ���Ҫ���

	///int next_block = judge_next_block(slot, input.condition);

	output.task_id = task_id;
	output.next_block_id = block.block_relation[block_id][0];

	return output;
}

struct block_output message_block(struct block_input input, struct slot_define& slot, struct block_define block) {
	struct block_output output;
	string content = input.content;
	cout << content <<endl;
	output.next_block_id = block.block_relation[input.block_id][0];                     ///����
	output.task_id = input.task_id;
	return output;
}

struct block_output hidden_block(struct block_input input, struct slot_define& slot, struct block_define block, struct entity_define entity) {
	struct block_output output;
	slot_filling(input.query, slot, entity);    ////input.slot��ȷ�ĸ��ʲ���Ҫ���
	output.task_id = input.task_id;
	output.next_block_id = block.block_relation[input.block_id][0];

	return output;
}

/*
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
*/

void auto_init(struct block_define& blocks,struct slot_define& slots,struct task_define& tasks,struct entity_define& entity){
	////�Զ���ʼ����ͼ
	tasks.task_num = 3;
	tasks.task_name.push_back("����");
	tasks.task_name.push_back("��Ʊ");
	tasks.task_name.push_back("���Ƶ�");
	
	///��ʼ���Ի���Ԫ
	blocks.block_num = 5;
	int block_type[5] = { 0,1,1,0,0 };
	for (int i = 0; i < 5; i++) {
		blocks.block_type.push_back(block_type[i]);
	}

	vector<int> vec_tem;
	int num[5] = { 1,1,2,0,0 };
	vec_tem.push_back(1);
	blocks.block_relation.push_back(vec_tem);
	vec_tem.pop_back();
	vec_tem.push_back(2);
	blocks.block_relation.push_back(vec_tem);
	vec_tem.pop_back();
	vec_tem.push_back(3);
	vec_tem.push_back(4);
	blocks.block_relation.push_back(vec_tem);
	
	string message[5] = { "��ã���ӭ������ѧ������","��Ҫȥ�ĸ�����","��Ҫȥ�ĸ�����","������ӭ��","�Ϻ���ӭ��" };
	for (int i = 0; i < blocks.block_num; i++) {
		blocks.message.push_back(message[i]);
	}
	///��ʼ���ʲ�
	slots.slot_num = 2;
	string slot_name[2] = {"����","����"};
	for (int i = 0; i < slots.slot_num; i++) {
		slots.slot_name.push_back(slot_name[i]);
	}

	///��ʼ��ʵ��
	entity.entity_kind = 2;
	vector<string> tem;
	tem.push_back("�й�");
	tem.push_back("����");
	tem.push_back("�ձ�");
	entity.entity_value.push_back(tem);
	tem.clear();
	tem.push_back("����");
	tem.push_back("�Ϻ�");
	tem.push_back("����");
	tem.push_back("����");
	tem.push_back("ŦԼ");
	tem.push_back("��ɼ�");
	entity.entity_value.push_back(tem);
}


int main() {
	/////��Ϣ��Ԫ���ͣ�0������Ϣ��Ԫ��1����Ի���Ԫ��2�������ص�Ԫ
	struct block_define blocks;
	struct slot_define slots;
	struct task_define tasks;
	struct entity_define entity;
	auto_init(blocks,slots,tasks,entity);
	string query;
	int block_id = 0;
	int task_id = 0;   
	///�˴����ܴ��ڱ��������������
	struct block_input input;
	int pass_flag = false;
	while (getline(cin, query)) {
		if (query == "end") {
			break;
		}
		if (block_id == 99) {
			break;
		}
		///������ͼʶ��    
		int intent = intent_identify(query, tasks);
		if (intent != 99) {
			task_id = intent;
		}
		int type = blocks.block_type[block_id];
		input.task_id = task_id;
		input.block_id = block_id;
		input.content = blocks.message[block_id];
		input.query = query;
		struct block_output out;
		if (type == 0) {
			out = message_block(input,slots,blocks);
		}
		else if (type == 1) {
			out = diaglogue_block(input, slots, blocks, tasks, entity);
		}
		else if (type == 2) {                         ///hidden_block ��ô��ת��Ҫ�����о�
			out = hidden_block(input, slots, blocks ,entity);
		}
		block_id = out.next_block_id;
		task_id = out.task_id;
	}
}





