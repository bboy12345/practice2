#include <iostream>
#include <algorithm>
using namespace std;

class HashMap{
public:
    // ����????ֵ???��Ϊ�����????��ȡ��???��key��������int��value��������string
    HashMap(const int key, const string value);
    // ��������
    ~HashMap();
    // ���ϣ��????�洢????ֵ???
    void Push(const int key, const string value);
    // ����keyֵ�õ�value????
    string Get(const int key);

private:
    //����һ????�洢��???����ָ�����飬�����ͻ�İ취����������������ָ��
    typedef struct HashTable{
        struct HashTable *next;  // 
        int key;            // �ؼ�????
        string value;          // �ؼ���key��Ӧ��value
        bool is_occupied;    // �˽���Ƿ�???ռ�ã�Ĭ��Ϊ����????
    }Hash_node;
    Hash_node *hash_table[20];
};

// ���캯����ʹ��TransformKey������keyֵת���󣬽�����뵽��Ӧ���±�???
HashMap::HashMap(const int key, const string value){
    //  ��???��
    for(int i=0; i<20; i++){
        hash_table[i] = new Hash_node;
        hash_table[i]->is_occupied = false;
        hash_table[i]->key = 0;
        hash_table[i]->value = "";
        hash_table[i]->next = NULL;
    }
    // ����Push��������key��value����ڵ�????
    Push(key, value);
}

// ��������
HashMap::~HashMap(){
    for(int i=0; i<20; i++){
        delete hash_table[i];
    }
}

// ���ϣ��????�洢????ֵ???
void HashMap::Push(const int key, const string value){
    int new_key = key % 20;
    // �жϹ�ϣ��map????�±�Ϊnew_key????��Ϊ�գ���Ϊ����������
    Hash_node *temp = this->hash_table[new_key];
    if(!temp->is_occupied){
        // ��key��value������ʱ�ڵ�????
        temp->key = key;
        temp->is_occupied = true;
        temp->value = value;
        // ����ָ��ָ��
        temp->next = NULL;
    }else{
        while(temp->next){
            temp = temp->next;
        }
        // �����µ�Hash_node�ڴ�ռ�
        Hash_node* temp_node = new Hash_node;
        // ��key��value������ʱ�ڵ�????
        temp_node->key = key;
        temp_node->value = value;
        temp_node->is_occupied = true;
        // ����ָ��ָ��
        temp_node->next = NULL;
        temp->next = temp_node;
    }
}

// ����keyֵ�õ�value????
string HashMap::Get(const int key){
        int new_key = key % 20;  // �õ�hash_table????��key????
        Hash_node *temp = hash_table[new_key];
        if(!temp->is_occupied){
            // ����????????keyֵ��????ֵ???
            return "����????";
        }else{
            while(temp){
                if(temp->key == key){
                    return temp->value;
                }
                temp = temp->next;
            }
            return "������";
        }
}

int main(){
    // system("chcp 65001");
    HashMap hash_map(10, "test1");
    hash_map.Push(30, "����2");
    string str = hash_map.Get(30); // ���ܵõ����ַ�����???�������ڷ��ء������ڡ��ַ���
    cout<<str;
}