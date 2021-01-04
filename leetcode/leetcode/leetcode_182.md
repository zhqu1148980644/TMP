---
title: Duplicate Emails
date: 2021-01-04
---
Write a SQL query to find all duplicate emails in a table named Person.

```
+----+---------+
| Id | Email   |
+----+---------+
| 1  | a@b.com |
| 2  | c@d.com |
| 3  | a@b.com |
+----+---------+

For example, your query should return the following for the above table:

+---------+
| Email   |
+---------+
| a@b.com |
+---------+
```

Note: All emails are in lowercase.

#### Solutions

1. ##### Grouby by

```sql
SELECT Email FROM
    (SELECT Email, COUNT(*) AS num FROM Person GROUP BY Email) AS Counter
    WHERE num > 1;
```

Or

```sql
SELECT Email FROM Person GROUP BY EMAIL HAVING COUNT(Email) > 1;

```


2. ##### self join

```sql
SELECT DISTINCT a.Email FROM
    Person AS a, Person as b
    WHERE a.Email = b.Email AND a.Id != b.Id;
```