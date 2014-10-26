## 기능설계

### 함수명

createLinkedList()

### 정의

주소정보 linked list 를 생성한다.

### 반환

self : LINKEDLIST* : linked list

### 입력

self : LINKEDLIST* : linked list

### 처리과정

```
1. linked list 구조체를 생성한다.
2. list의 head next 를 tail 에 연결한다.
3. list의 tail next 를 null 로 할당한다.
4. pos 를 head 로 연결한다.
5. length 를 초기화한다.
```


### 함수명

destroyLinkedList()

### 정의

주소정보 linked list 를 소멸시킨다.

### 반환

x

### 입력

self : LINKEDLIST* : 생성할 linked list

### 처리과정

```
1. list 가 비어 있지 않은지 검사한다.
	1.1. YES: list 의 모든 node 를 삭제한다.
2. linked list 를 해제한다.
```


### 함수명

appendLinkedList()

### 정의

list 마지막 주소정보 node 를 추가한다.

### 반환

self : LINKEDLIST* : linked list

### 입력

self : LINKEDLIST* : linked list
p_info : personalInfo* : 추가할 주소정보

### 처리과정

```
1. list 의 끝으로 이동한다.
2. node 를 생성한다.
3. node 에 주소정보를 저장한다.
4. node 를 list 마지막 node로 밀어 넣는다.
6. length 를 하나 증가시킨다.
```

### 함수명

insertLinkedList()

### 정의

index 위치에 주소정보를 삽입한다.

### 반환

self : LINKEDLIST* : linked list

### 입력

self : LINKEDLIST* : linked list
index : int : 추가할 list index
p_info : personalInfo* : 추가할 주소정보

### 처리과정

```
1. list 작업 node를 index 로 이동한다.
2. node 를 생성한다.
3. node 에 주소정보를 저장한다.
4. node 를 index 위치의 node 를 다음으로 밀고 추가한다.
6. length 를 하나 증가시킨다.
```


### 함수명

deleteLinkedList()

### 정의

index 위치에 주소정보를 삭제한다.

### 반환

self : LINKEDLIST* : 생성된 linked list

### 입력

self : LINKEDLIST* : 생성할 linked list
index : int : 삭제한 index

### 처리과정

```
1. list 작업 node를 index 로 이동한다.
2. index node 를 제거한다.
3. length 를 하나 줄인다.
```

### 함수명

deleteAllLinkedList()

### 정의

모든 주소정보를 삭제한다.

### 반환

self : LINKEDLIST* : linked list

### 입력

self : LINKEDLIST* : linked list

### 처리과정

```
1. list 가 비어있는지 검사한다.
	1.1. YES: linked list 를 반환한다.
2. list 처음으로 이동한다.
3. list 마지막까지 반복한다.
	3.1. node 를 삭제한다.
	3.2. length 를 하나 감소한다.
```

### 함수명

viewAtLinkedList(NODE* self, int index) : personalInfo

### 정의

index 위치의 주소정보를 반환한다.

### 반환

info : personalInfo : 주소정보
self : LINKEDLIST* : linked list

### 입력

self : LINKEDLIST* : linked list
index : int : 조회할 index

### 처리과정

```
1. list 를 index 위치로 이동한다
2. index 의 주소정보를 반환한다.
```


### 함수명

moveFirstLinkedList()

### 정의

list 의 작업 node를 처음 node 로 이동하고 해당 node 를 반환한다.

### 반환

self : LINKEDLIST* : linked list
node : NODE* : list 첫 node

### 입력

self : LINKEDLIST* : linked list

### 처리과정

```
1. 작업 node를 처음 node 로 이동한다.
2. 작업 node 를 반환한다.
```

### 함수명

moveLastLinkedList()

### 정의

list 의 작업 node를 마지막 node 로 이동하고 해당 node 를 반환한다.

### 반환

self : LINKEDLIST* : linked list
node : NODE* : list 첫 node

### 입력

self : LINKEDLIST* : linked list

### 처리과정

```
1. 작업 node를 마지막 node 로 이동한다.
2. 작업 node 를 반환한다.
```


### 함수명

nextLinkedList()

### 정의

list 의 작업 node 를 다음 node 로 이동하고 반환한다.

### 반환

self : LINKEDLIST* : linked list
node : NODE* : list 첫 node

### 입력

self : LINKEDLIST* : linked list

### 처리과정

```
1. 작업 node 의 next 로 작업 node 를 이동한다.
2. 작업 node 를 반환한다.
```

### 함수명

isTailLinkedList()

### 정의

작업 node 가 tail 인지 검사한다.

### 반환

isTail : boolean : tail 여부
self : LINKEDLIST* : linked list

### 입력

self : LINKEDLIST* : linked list

### 처리과정

```
1. 작업 node 의 next 가 NULL 인지 검사한다.
	1.1. YES: true 를 반환한다.
	1.2. NO : false 를 반환한다.
```

### 함수명

getLengthLinkedList()

### 정의

list 의 node 개수를 반환한다.

### 반환

self : LINKEDLIST* : linked list
length : int : node 개수

### 입력

self : LINKEDLIST* : linked list

### 처리과정

```
1. length 를 반환한다.
```

### 함수명

findNameLinkedList(NODE* self, NODE* beginNode, char* p_name) : NODE*

### 정의

입력된 시작 node 부터 순회하면서 입력된 이름과 처음 일치하게되는 node 를 반환한다.

### 반환

self : LINKEDLIST* : linked list
node : NODE* : 검색된 node

### 입력

self : LINKEDLIST* : linked list
beginNode : NODE* : 검색 시작 node
p_name : char* : 검색할 이름

### 처리과정

```
1. 작업 node 를 beginNode 로 설정한다.
2. Tail 까지 순회한다.
	2.1. 작업node 의 주소정보 이름과 동일한지 검사한다.
		2.1.1. YES: 순회를 종료한다.
3. 작업 node 를 반환한다.
```
