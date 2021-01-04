---
title: Customers Who Never Order
date: 2021-01-04
---
Suppose that a website contains two tables, the Customers table and the Orders table. Write a SQL query to find all customers who never order anything.

```
Table: Customers.

+----+-------+
| Id | Name  |
+----+-------+
| 1  | Joe   |
| 2  | Henry |
| 3  | Sam   |
| 4  | Max   |
+----+-------+

Table: Orders.

+----+------------+
| Id | CustomerId |
+----+------------+
| 1  | 3          |
| 2  | 1          |
+----+------------+

Using the above tables as example, return the following:

+-----------+
| Customers |
+-----------+
| Henry     |
| Max       |
+-----------+
```

#### Solutions

1. ##### left join

```sql
SELECT c.Name as Customers FROM
    Customers as c LEFT JOIN Orders as o
    ON c.Id = o.CustomerId
    WHERE o.Id is  NULL;
```

2. ##### not in


```sql
SELECT c.Name as Customers
    FROM Customers as c
    WHERE c.Id not in
    (SELECT DISTINCT o.CustomerId FROM Orders as o);
```

3. ##### not exists

```sql
SELECT c.Name AS Customers
    FROM Customers AS c
    WHERE not EXISTS(SELECT o.CustomerId
                     FROM Orders AS o
                     WHERE c.Id = o.CustomerId);
```