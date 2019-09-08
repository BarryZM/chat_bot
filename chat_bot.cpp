#include<cstdio>
#include<cstring>

const int maxsize = 10;
const int intent_total_num = 2;
struct message{
    string msg;
};

struct intent{
    int intent_num;
    string str[maxsize];
    string re_str[maxsize];
    string msg[maxsize];
    string intent_name;
};

void init_msg_conver(int intent_num){
    struct intent str_record_1;
    struct intent str_record_2;
    str_record_1.str = {"今天天气怎么样","你今天吃的什么","你今天几点睡觉呀","你在干嘛呀"};
    str_record_1.re_str = {"今天天气很好呀","我今天吃的烤鱼","我今天晚上十点就要睡觉","我在跳舞"};
    str_record_1.msg = {"你好，欢迎来到巍巍机器人,这里是日常生活板块","对话结束啦,欢迎再次使用"};
    str_record_2.str = {"股票收益怎么样","房产收益怎么样","存款收益怎么样","贷款情况怎么样"};
    str_record_2.re_str = {"今天天气很好呀","我今天吃的烤鱼","我今天晚上十点就要睡觉","我在跳舞"};
    str_record_2.msg = {"你好，欢迎来到巍巍机器人,这里是财务状况板块","对话结束啦,欢迎再次使用"};
    str_record_1.intent_name = "生活";
    str_record_2.intent_name = "财务";
    if(intent_num == 1){
        return str_record_1;
    }
    if(intent_num == 2){
        return str_record_2;.
    }
    else{
        struct intent str_record_3;
        return str_record_3;
    }
}

////////意图识别，返回分数较高的值
int intent_detect(string msg_input){
    float score1;
    float score2;
    score1 = sim_cal(msg_input,1);
    score2 = sim_cal(msg_input,2);
    if(score1 >= score2){
        return 1;
    }
    else{
        return 2;
    }
}

/////// 消息通知单元
class msg_unit{
    public:
        ////// 消息通知单元主函数        
        void msg_handle(int pos,int intent_num){
            struct intent str_record;
            str_record = init_msg_conver(intent_num);
            printf("%s",str_record.msg[pos]);            /////pos可能越界
            printf("\n");
        }
}

//////基于一对一匹配的问答模型
class conver_unit{
    public:
        /////问答语句匹配
        struct message conver_match(string msg_input,int intent_num){
            struct message msg_out;
            bool flag = false;
            int msg;
            struct intent str_record;
            str_record = init_msg_conver(intent_num);
            for(int i=0;i<maxsize;i++){
                if(msg_input == str_record.str[i]){
                    msg = str_record.re_str[i];
                    flag = true;
                    break;
                }
            }
            if(flag == false){
                msg = 'sorry,the msg is not in the database';
            }
            msg_out.msg = msg;
            return msg_out;
        }

        /////问答单元主函数
        struct message conver_handle(int intent_num_ori){
            string msg_input;
            scanf("%s",&msg_input);
            string msg_output;
            struct message msg_out;
            int intent_num;
            intent_num = intent_detect(msg_input);                                             /////先做意图识别跳转
            msg_output = conver_match(msg_input,intent_num);        /////再做机器人回复
            printf("%s",msg_output.msg);
            return msg_out;
        }
}

int main{
    string msg_input;
    int pos = 0;
    int unit_num;
    int unit_label[maxsize];
    struct message msg_output;
    msg_unit msg_example;
    conver_unit conver_example;
    int intent_num = 1;  //////////初始intent_num为1

    printf("what structrue do you want?");
    scanf("%d",&unit_num);
    //////1代表消息单元
    //////2代表对话单元
    for(int i=0;i<unit_num;i++){
        scanf("%d",unit_label[i]);
    }
    for(int i=0;i<unit_num;i++){
        if(unit_label[i] == 1){
            msg_example.message_handle(pos,intent_num);
            pos += 1;
        }
        else if(unit_label[i] == 2){
            conver_example.conver_handle(intent_num);
        }
        else{
            printf("the task is wrong , because the label number is inavailable");
        }
    }
    return 0;
}




