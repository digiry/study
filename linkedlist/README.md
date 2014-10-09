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

createLinkedList(LINKEDLIST *self)

destroyLinkedList(LINKEDLIST *self)

appendLinkedList(LINKEDLIST *self, personalInfo *p_info)

insertLinkedList(LINKEDLIST *self, int index, personalInfo *p_info)

deleteLinkedList(LINKEDLIST *self, int index)

deleteAllLinkedList(LINKEDLIST *self)

viewAtLinkedList(LINKEDLIST *self, int index) : personalInfo

moveFirstLinkedList(LINKEDLIST *self) : NODE*

moveLastLinkedList(LINKEDLIST *self) : NODE*

nextLinkedList(LINKEDLIST *self) : NODE*

isTailLinkedList(LINKEDLIST *self) : int

getLengthLinkedList(LINKEDLIST *self) : int

findNameLinkedList(LINKEDLIST *self, NODE *beginNode, char *p_name) : NODE*
