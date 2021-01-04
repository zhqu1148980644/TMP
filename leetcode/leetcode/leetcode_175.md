---
title: Combine Two Tables
date: 2021-01-04
---
```
Table: Person

+-------------+---------+
| Column Name | Type    |
+-------------+---------+
| PersonId    | int     |
| FirstName   | varchar |
| LastName    | varchar |
+-------------+---------+
PersonId is the primary key column for this table.

Table: Address

+-------------+---------+
| Column Name | Type    |
+-------------+---------+
| AddressId   | int     |
| PersonId    | int     |
| City        | varchar |
| State       | varchar |
+-------------+---------+
AddressId is the primary key column for this table.
```

 

Write a SQL query for a report that provides the following information for each person in the Person table, regardless if there is an address for each of those people:

```
FirstName, LastName, City, State
```


#### Solutions

1. ##### left join

```sql
SELECT FirstName, LastName, City, State
    FROM Person left join Address
    ON Person.PersonId = Address.PersonId;
```

Or

```sql
SELECT P.FirstName, P.LastName, A.City, A.State
    FROM Person  AS P left join Address AS A
    ON P.PersonId = A.PersonId;
```
