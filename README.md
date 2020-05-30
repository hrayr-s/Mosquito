# Database
Database application on C++ for Course work of Magestry second semester

Commands to use:
## SELECT
```
  SELECT ['*' |  `column_1`, `column_2`, ..., `column_N`] FROM table_name 
    WHERE column_x [
      [!]= ['text' | 25]
      |
      [NOT] IN [('text1', 'text2', ..., 'textN') | (1, 5, 3, ..., N)]
      |
      [NOT] LIKE '%search query%'
    ];
```

## INSERT
```
  INSERT INTO `table_name` (`col1`, `col2`, `col3`, ..., `colN`) 
      VALUES('col1_val', 'col2_val', 'col3_val', ..., 'colN_val'),
            ('col1_val', 'col2_val', 'col3_val', ..., 'colN_val'),
            ('col1_val', 'col2_val', 'col3_val', ..., 'colN_val');
```
        
## DELETE
```
  DELETE FROM `table_name` [WHERE {USE WHERE SINTACSIS US IN SELECT}];
```
  
## UPDATE
```
  UPDATE `table_name` SET `col1`='col_val1', `col2`='col_val2', ..., `colN`='col_valN'
      [WEHERE {USE WHERE SINTACSIS US IN SELECT}];
```
      
## CREATE
```
  CREATE TABLE `table_name` (
    'col_1' INT,
    'col_2' VARCHAR(286),
    'col_3' TEXT,
    ...
    'col_N' {COLUMN_TYPE}
  );
```
  
## DROP
```
  DROP TABLE `table_name`;
```
