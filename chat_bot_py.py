import requests

class intent:     
    #######意图名称，单元字典(每个单元是什么类型),关系字典（每个单元后面跟着什么单元）
    #######词槽字典（词槽名称以及定义实体值）,每个block对应接受词槽,回复字典（每个对话单元上内容是什么）
    def __init__(self,intent_list,intent_id,block_dict,relation_dict,slot_dict,block_slot,response_dict,hidden_dict):
        self.slot_dict = slot_dict
        self.intent_id = intent_id
        self.intent_list = intent_list
        self.block_dict = block_dict
        self.relation_dict = relation_dict
        self.block_slot = block_slot
        self.response_dict = response_dict
        self.slot_result = {}
        self.hidden_dict = hidden_dict
    
    def message_unit(self,block_id):                                 ############接口单元
        response = self.response_dict[str(block_id)]
        print(response)
        next_block_id = self.judge_next_block(block_id)
        return next_block_id
        
    def dia_unit(self,block_id):                                     #############对话单元
        response = self.response_dict[str(block_id)]
        print(response)
        query = input()   
        self.hidden_unit(query)
        qa_answer = qa_bot(query)
        if(qa_answer!=''):         
            print(qa_answer)
        now_intent = judge_intent(query,self.intent_list,self.intent_id)
        if now_intent == self.intent_id:
            pass
        else:
            return 0,now_intent
        slot = self.get_slot(block_id)
        slot_result = self.slots_filling(query,slot)   
        self.slot_result.update(slot_result)     ##########更新self.slot_result
        next_block_id = self.judge_next_block(block_id)

        return next_block_id,self.intent_id
    
    def hidden_unit(self,query):    #############隐藏单元，每次判断一下是否能填槽
        for key in self.hidden_dict:
            slot_name = self.hidden_dict[key]
            slot = {slot_name:self.slot_dict[slot_name]}
            slot_result = self.slots_filling(query,slot)
            self.slot_result.update(slot_result)
            
    def http_unit(self,url):
        r = requests.post(url)
        ##########self.slot_result.update()
        ##########利用返回值更新词槽结果
    
    def operate_unit(self,block_id,operate_dict):
        mode_type = operate_dict[str(block_id)][0]
        if mode_type == '1':                        ######重置词槽
            key = self.block_slot[str(block_id)]
            self.slot_result[key] = operate_dict[str(block_id)][1]
            return block_id+1
        if mode_type == '2':                        ######条件分支
            next_block_id = self.judge_next_block(block_id)
            return next_block_id

    
    def end_block(self,route):
        print('对话到此结束')
        print('词槽的收集结果为',self.slot_result)
        print('当前意图是',self.intent_list[self.intent_id])
        print('对话单元的路线是',route)
    
    def get_slot(self,block_id):
        if(self.block_dict[str(block_id)] == 'type2'):
            slot_name = self.block_slot[str(block_id)]
            slot = {slot_name:self.slot_dict[slot_name]}
            return slot
        else:
            return {'error':'not valid block type'}
        
    def slots_filling(self,query,slot):                              ####词槽填充
        for key in slot:
            value = slot[key]
            for entity in value:
                if entity in query:
                    return {key:entity}
        return {key:'no match'}
    
    def judge_next_block(self,block_id):
        next_block_dict = self.relation_dict[str(block_id)]
        if str(block_id) in self.block_slot:                         ##########如果是对话单元或运算单元   
            key = self.block_slot[str(block_id)]
            #print(self.slot_result)
            value = self.slot_result[key]                            ##########真实填槽的值
        else:                                                        ##########如果是消息单元，默认跳转
            value = ''                                               
        
        if value in next_block_dict:                                ###########有值则根据该值跳转，无值则默认跳转
            next_block_id = int(next_block_dict[value])
        else:
            next_block_id = int(next_block_dict['empty'])
        
        return next_block_id


def judge_intent(query,intent_list,now_intent):   #####意图识别
    for i,key in enumerate(intent_list):
        if key in query:
            return i
    return now_intent


def qa_bot(query):                       #########问答机器人
    return '可以触发问答'



def init():
    intent_list = ['购物','退款']
    block_slot_1 = {'3':'商品名称'}
    block_slot_2 = {'4':'商品名称'}
    block_slot_list = [block_slot_1,block_slot_2]
    hidden_dict_1 = {'2':'颜色'}
    hidden_dict_2 = {'3':'颜色'}
    hidden_dict_list = [hidden_dict_1,hidden_dict_2]
    http_dict = {'6':'https://passport.cnblogs.com/user/signin'}
    slot_dict = {'商品名称':['羽绒服','大衣','夹克'],'颜色':['红色','白色','黄色']}
    block_dict_1 = {'1':'type1','2':'type3','3':'type2','4':'type1','5':'type1'}
    block_dict_2 = {'1':'type1','2':'type1','3':'type3','4':'type2','5':'type1','6':'type1'}
    block_dict_list = [block_dict_1,block_dict_2]
    response_dict_1 = {'1':'欢迎来到张巍的小店','3':'请问有什么可以帮您','4':'您想买的是羽绒服呀','5':'到这就结束啦'}
    response_dict_2 = {'1':'欢迎咨询退款业务','2':'我是机器人张巍','4':'请问您要退款的物品是','5':'您要退款的是羽绒服','6':'您要退款的是其他'}
    response_dict_list = [response_dict_1,response_dict_2]
    relation_dict_1 = {'1':{'empty':'2'},'2':{'empty':'3'},'3':{'羽绒服':'4','empty':'5'},'4':{'empty':'6'},'5':{'empty':'6'}}
    relation_dict_2 = {'1':{'empty':'2'},'2':{'empty':'3'},'3':{'empty':'4'},'4':{'羽绒服':'5','empty':'6'},'5':{'empty':'7'},'6':{'empty':'7'}}         
    relation_dict_list = [relation_dict_1,relation_dict_2]
    
    out_dict = {'intent_list':intent_list,'block_slot_list':block_slot_list,'hidden_dict_list':hidden_dict_list,
                'http_dict':http_dict,'slot_dict':slot_dict,'block_dict_list':block_dict_list,
                'response_dict_list':response_dict_list,'relation_dict_list':relation_dict_list}
    
    return out_dict

def main():
    ###########init
    init_dict = init()
    intent_list = init_dict['intent_list']
    block_slot_list = init_dict['block_slot_list']
    hidden_dict_list = init_dict['hidden_dict_list']
    http_dict = init_dict['http_dict']
    slot_dict = init_dict['slot_dict']
    block_dict_list = init_dict['block_dict_list']
    response_dict_list = init_dict['response_dict_list']
    relation_dict_list = init_dict['relation_dict_list']
    
    ########运算单元临时放一下
    operate_dict = {'5':['1','']}     ####blockid:mode_type    1代表重置
    ########
    
    #now_intent记录当前意图,now_block记录当前block块，slot_dict记录词槽内容
    flag_list = [True,'']
    while(True):
        shop_intent_list = []
        for i in range(0,len(intent_list)):
            shop_intent = intent(intent_list, i,block_dict_list[i],relation_dict_list[i],slot_dict,block_slot_list[i],response_dict_list[i],hidden_dict_list[i])
            shop_intent_list.append(shop_intent)

        route_list = []        
        now_intent = 0
        now_block_id = 1
        if flag_list[0] == True:
            query = input()  #用户说话        #####只有阻塞单元才接受输入，目前的阻塞单元是对话单元
            answer = qa_bot(query)          #####先调用问答机器人
            if(answer!=''):
                print(answer)
                
            intent_id = judge_intent(query,intent_list,now_intent)     #####每句话先进行意图识别
            if(intent_id == now_intent):                    #####当前意图则继续
                pass
            else:                                             #####否则进行意图切换
                if(intent_id == 0):
                    now_intent = 0
                    now_block_id = 1
                if(intent_id == 1):
                    now_intent = 1
                    now_block_id = 1
        else:
            now_intent = flag_list[1]
            now_block_id = 1
        flag_list = [True,'']

        for i in range(0,len(intent_list)):           
            if(now_intent == i):                             
                while(True):
                    if(now_block_id == len(block_dict_list[i])+1):                    ######如果走到最后一个单元，结束
                        break
                    route_list.append(now_block_id)
                    if(shop_intent_list[i].block_dict[str(now_block_id)] == 'type1'): ######消息单元则打印消息
                        now_block_id = shop_intent_list[i].message_unit(now_block_id)
                        continue
                    if(shop_intent_list[i].block_dict[str(now_block_id)] == 'type2'): #####对话单元
                        now_block_id,now_intent = shop_intent_list[i].dia_unit(now_block_id)
                        if(now_block_id!=0):
                            continue
                        else:
                            flag_list[0] = False
                            flag_list[1] = now_intent
                            break
                    if(shop_intent_list[i].block_dict[str(now_block_id)] == 'type3'):  ######隐藏单元
                        now_block_id = now_block_id+1
                        continue
                    if(shop_intent_list[i].block_dict[str(now_block_id)] == 'type4'):  ######接口单元
                        url = http_dict[str(now_block_id)]
                        shop_intent_list[i].http_unit(url)
                        now_block_id = now_block_id+1
                        continue  
                    if(shop_intent_list[i].block_dict[str(now_block_id)] == 'type5'):  ######运算单元
                        now_block_id = shop_intent_list[i].operate_unit(now_block_id,operate_dict)
                        continue
                        
                if flag_list[0] == True:
                    shop_intent_list[i].end_block(route_list)
                break

if __name__ == '__main__':    
    main()        

            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
        