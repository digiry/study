# create table

```sql
CREATE TABLE addressbook (
	id INT PRIMARY KEY AUTO_INCREMENT,
	name VARCHAR(6) UNIQUE NOT NULL,
	phone VARCHAR(11) DEFAULT NULL,
	address VARCHAR(50) DEFAULT NULL
);
```

# insert data

```sql
INSERT INTO addressbook (name, phone, address) VALUES (
	'aaa', '00011110000', 'zxcv'
);

INSERT INTO addressbook (name, phone, address) VALUES (
	'bbb', '00022220000', 'asdf'
);

INSERT INTO addressbook (name, phone, address) VALUES (
	'ccc', '00033330000', 'qwer'
);
```

# get all data

```sql
SELECT * FROM addressbook;
```

# delete all data

```sql
DELETE FROM addressbook;
```

## delete data with 'ccc' name

```sql
DELETE FROM addressbook WHERE name = 'ccc';
```
