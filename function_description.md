## 함수 설계

#### 함수명

main()

#### 정의

menu 화면을 호출하고 사용자로부터 메뉴를 입력받아 해당 menu 를 실행한다.

#### 반환

x

#### 입력

x

#### 처리과정

```
<?xml version="1.0" encoding="UTF-8"?>
<root xmlns:nsd="http://structorizer.fisch.lu/" text="&#34;main()&#34;" comment="&#34;&#34;" color="ffffff" type="program" style="nice">
	<children>
		<while text="&#34;WHILE ( ( 0 &#60;= menu ) AND ( 5 &#60;= menu ) )&#34;" comment="&#34;&#34;" color="ffffff">
			<qWhile>
				<instruction text="&#34;menu 화면을 출력한다.&#34;" comment="&#34;&#34;" color="ffffff" rotated="0"></instruction>
				<instruction text="&#34;menu 를 입력받는다.&#34;" comment="&#34;&#34;" color="ffffff" rotated="0"></instruction>
				<instruction text="&#34;menu 항목에 맞는 함수를 호출한다.&#34;" comment="&#34;&#34;" color="ffffff" rotated="0"></instruction>
			</qWhile>
		</while>
	</children>
</root>
```
