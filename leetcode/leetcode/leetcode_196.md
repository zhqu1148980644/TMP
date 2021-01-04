---
title: Delete Duplicate Emails
date: 2021-01-04
---
#### Write a SQL query to delete all duplicate email entries in a table named Person, keeping only unique emails based on its smallest Id.

```
+----+------------------+
| Id | Email            |
+----+------------------+
| 1  | john@example.com |
| 2  | bob@example.com  |
| 3  | john@example.com |
+----+------------------+
Id is the primary key column for this table.

For example, after running your query, the above Person table should have the following rows:

+----+------------------+
| Id | Email            |
+----+------------------+
| 1  | john@example.com |
| 2  | bob@example.com  |
+----+------------------+
```

#### Note:

Your output is the whole Person table after executing your sql. Use delete statement.

#### Solutions

1. ##### not in

```sql
DELETE FROM Person
    WHERE Id not in
    (SELECT gp.Id FROM
        (SELECT MIN(Id) as Id, Email FROM Person GROUP BY EMAIL) as gp
    );
```

2. ##### self join

```sql
DELETE p1 
    FROM Person AS p1, Person AS p2
    WHERE p1.Email = p2.Email AND p1.Id > p2.Id; 
```