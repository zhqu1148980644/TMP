---
title: Reformat Department Table
date: 2021-01-04
---
SQL架构
Table: Department

+---------------+---------+
| Column Name   | Type    |
+---------------+---------+
| id            | int     |
| revenue       | int     |
| month         | varchar |
+---------------+---------+
(id, month) is the primary key of this table.
The table has information about the revenue of each department per month.
The month has values in ["Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"].
 

Write an SQL query to reformat the table such that there is a department id column and a revenue column for each month.

The query result format is in the following example:

Department table:
+------+---------+-------+
| id   | revenue | month |
+------+---------+-------+
| 1    | 8000    | Jan   |
| 2    | 9000    | Jan   |
| 3    | 10000   | Feb   |
| 1    | 7000    | Feb   |
| 1    | 6000    | Mar   |
+------+---------+-------+

Result table:
+------+-------------+-------------+-------------+-----+-------------+
| id   | Jan_Revenue | Feb_Revenue | Mar_Revenue | ... | Dec_Revenue |
+------+-------------+-------------+-------------+-----+-------------+
| 1    | 8000        | 7000        | 6000        | ... | null        |
| 2    | 9000        | null        | null        | ... | null        |
| 3    | null        | 10000       | null        | ... | null        |
+------+-------------+-------------+-------------+-----+-------------+

Note that the result table has 13 columns (1 for the department id + 12 for the months).

#### Solutions

1. #### GROUP BY

```sql
select id,
    max(case when month='jan' then revenue else null end) as Jan_revenue,
    max(case when month='feb' then revenue else null end) as Feb_revenue,
    max(case when month='mar' then revenue else null end) as Mar_revenue,
    max(case when month='apr' then revenue else null end) as Apr_revenue,
    max(case when month='may' then revenue else null end )as May_revenue,
    max(case when month='jun' then revenue else null end )as Jun_revenue,
    max(case when month='jul' then revenue else null end )as Jul_revenue,
    max(case when month='aug' then revenue else null end )as Aug_revenue,
    max(case when month='sep' then revenue else null end )as Sep_revenue,
    max(case when month='oct' then revenue else null end )as Oct_revenue,
    max(case when month='nov' then revenue else null end )as Nov_revenue,
    max(case when month='dec' then revenue else null end )as Dec_revenue
    from department
    group by id
```