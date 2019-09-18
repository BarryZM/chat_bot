#include<cstdio>
#include<string>
#include<iostream>
#include<vector>
#include<algorithm>
#include "chat_bot.h"
#include "utils.cpp"
using namespace std;
/*
struct block_output diaglogue_block(struct block_input input, struct slot_define& slot, struct block_define block,struct task_define task_list,struct entity_define entity) {
	struct block_output output;
	string content = input.content;
	int task_id = input.task_id;
	int block_id = input.block_id;
	string query;
	cout << content;
	getline(cin,query);                             ///////等待用户回答
	int intent = intent_identify(query,task_list);
	if (intent != 99) {
		task_id = intent;
	}
	slot_filling(query, slot, entity);    ////input.slot明确哪个词槽需要填充

	///int next_block = judge_next_block(slot, input.condition);

	output.task_id = task_id;
	output.next_block_id = block.block_relation[block_id][0];

	return output;
}

struct block_output message_block(struct block_input input,struct slot_define& slot, struct block_define block) {
	struct block_output output;
	string content = input.content;
	cout << content;
	output.next_block_id = block.block_relation[input.block_id][0];                     ///待定
	output.task_id = input.task_id;
	return output;
}

struct block_output hidden_block(struct block_input input, struct slot_define& slot, struct block_define block,struct entity_define entity) {
	struct block_output output;
	slot_filling(input.query, slot,entity);    ////input.slot明确哪个词槽需要填充
	output.task_id = input.task_id;
	output.next_block_id = block.block_relation[input.block_id][0];      

	return output;
}
*/