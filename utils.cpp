#include<cstdio>
#include<string>
#include<iostream>
#include<vector>
#include<algorithm>
#include "chat_bot.h"
using namespace std;
/*
int intent_identify(string query, struct task_define task_list) {
	int task_id = 99;
	for (int i = 0; i < task_list.task_num; i++) {
		if (query.find(task_list.task_name[i]) != string::npos) {
			task_id = i;
		}
	}
	return task_id;
}

void slot_filling(string query, struct slot_define& slot,struct entity_define entity) {
	for (int i = 0; i < slot.slot_num; i++) {
		vector<string> tem = entity.entity_value[i];
		for (unsigned int j = 0; j < tem.size(); j++) {
			if (query.find(tem[j]) != string::npos) {
				slot.slot_value[i] = tem[j];
				break;
			}
		}
	}
}

/*
int judge_next_block(struct slot_define slot, struct judge_condition condition) {
	if (condition.is_judge == false) {
		return -1;
	}
	int slot_id = condition.slot_id;
	for (int i = 0; i < condition.judge_num - 1; i++) {
		if (slot.slot_value[slot_id] == condition.judge_value[i]) {  //////待改正：条件作为一个整体
			return condition.skip_block[i];
		}
	}
	return condition.skip_block[condition.judge_num - 1];    ///返回else部分的值
}
*/
