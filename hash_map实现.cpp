#include <iostream>
#include <algorithm>
using namespace std;

class HashMap{
public:
    // 输入????值???，为方便后????的取余???理，key的类型是int，value的类型是string
    HashMap(const int key, const string value);
    // 析构函数
    ~HashMap();
    // 向哈希表????存储????值???
    void Push(const int key, const string value);
    // 利用key值得到value????
    string Get(const int key);

private:
    //定义一????存储字???串的指针数组，解决冲突的办法是拉链法，所以用指针
    typedef struct HashTable{
        struct HashTable *next;  // 
        int key;            // 关键????
        string value;          // 关键字key对应的value
        bool is_occupied;    // 此结点是否???占用，默认为法拉????
    }Hash_node;
    Hash_node *hash_table[20];
};

// 构造函数，使用TransformKey函数将key值转换后，将其加入到对应的下标???
HashMap::HashMap(const int key, const string value){
    //  初???化
    for(int i=0; i<20; i++){
        hash_table[i] = new Hash_node;
        hash_table[i]->is_occupied = false;
        hash_table[i]->key = 0;
        hash_table[i]->value = "";
        hash_table[i]->next = NULL;
    }
    // 调用Push函数，将key和value存入节点????
    Push(key, value);
}

// 析构函数
HashMap::~HashMap(){
    for(int i=0; i<20; i++){
        delete hash_table[i];
    }
}

// 向哈希表????存储????值???
void HashMap::Push(const int key, const string value){
    int new_key = key % 20;
    // 判断哈希表map????下标为new_key????否为空，不为空则向后添加
    Hash_node *temp = this->hash_table[new_key];
    if(!temp->is_occupied){
        // 将key和value存入临时节点????
        temp->key = key;
        temp->is_occupied = true;
        temp->value = value;
        // 设置指针指向
        temp->next = NULL;
    }else{
        while(temp->next){
            temp = temp->next;
        }
        // 创建新的Hash_node内存空间
        Hash_node* temp_node = new Hash_node;
        // 将key和value存入临时节点????
        temp_node->key = key;
        temp_node->value = value;
        temp_node->is_occupied = true;
        // 设置指针指向
        temp_node->next = NULL;
        temp->next = temp_node;
    }
}

// 利用key值得到value????
string HashMap::Get(const int key){
        int new_key = key % 20;  // 得到hash_table????的key????
        Hash_node *temp = hash_table[new_key];
        if(!temp->is_occupied){
            // 不存????????key值的????值???
            return "不存????";
        }else{
            while(temp){
                if(temp->key == key){
                    return temp->value;
                }
                temp = temp->next;
            }
            return "不存在";
        }
}

int main(){
    // system("chcp 65001");
    HashMap hash_map(10, "test1");
    hash_map.Push(30, "测试2");
    string str = hash_map.Get(30); // 接受得到的字符串，???果不存在返回”不存在“字符串
    cout<<str;
}