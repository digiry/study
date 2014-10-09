# 주소정보 리스트

## data 설계

주소정보 personalInfo

* 이름 : name : char(5)
* 전화번호 : phone : char(14)
* 주소 : address : char(50)

List Node : NODE

* info : personalInfo* : 주소정보
* next : NODE* : 다음 node 주소

List : LINKEDLIST

* head : NODE* : head 주소
* tail : NODE* : tail 주소
* pos : NODE* : 최근 사용 node 주소
* length : int : list 의 node 개수

## 기능

createLinkedList(NODE* self)

destroyLinkedList(NODE* self)

appendLinkedList(NODE* self, personalInfo* p_info)

insertLinkedList(NODE* self, int index, personalInfo* p_info)

deleteLinkedList(NODE* self, int index)

deleteAllLinkedList(NODE* self)

viewAtLinkedList(NODE* self, int index) : personalInfo*

moveFirstLinkedList(NODE* self) : NODE*

moveLastLinkedList(NODE* self) : NODE*

nextLinkedList(NODE* self) : NODE*

isTailLinkedList(NODE* self) : int

isHeadLinkedList(NODE* self) : int

getLengthLinkedList(NODE* self) : int

findNameLinkedList(NODE* self, NODE* beginNode, char* p_name) : NODE*
