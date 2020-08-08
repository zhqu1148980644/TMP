SQL架构
Table: Traffic

+---------------+---------+
| Column Name   | Type    |
+---------------+---------+
| user_id       | int     |
| activity      | enum    |
| activity_date | date    |
+---------------+---------+
There is no primary key for this table, it may have duplicate rows.
The activity column is an ENUM type of ('login', 'logout', 'jobs', 'groups', 'homepage').
 

Write an SQL query that reports for every date within at most 90 days from today, the number of users that logged in for the first time on that date. Assume today is 2019-06-30.

The query result format is in the following example:

Traffic table:
+---------+----------+---------------+
| user_id | activity | activity_date |
+---------+----------+---------------+
| 1       | login    | 2019-05-01    |
| 1       | homepage | 2019-05-01    |
| 1       | logout   | 2019-05-01    |
| 2       | login    | 2019-06-21    |
| 2       | logout   | 2019-06-21    |
| 3       | login    | 2019-01-01    |
| 3       | jobs     | 2019-01-01    |
| 3       | logout   | 2019-01-01    |
| 4       | login    | 2019-06-21    |
| 4       | groups   | 2019-06-21    |
| 4       | logout   | 2019-06-21    |
| 5       | login    | 2019-03-01    |
| 5       | logout   | 2019-03-01    |
| 5       | login    | 2019-06-21    |
| 5       | logout   | 2019-06-21    |
+---------+----------+---------------+

Result table:
+------------+-------------+
| login_date | user_count  |
+------------+-------------+
| 2019-05-01 | 1           |
| 2019-06-21 | 2           |
+------------+-------------+
Note that we only care about dates with non zero user count.
The user with id 5 first logged in on 2019-03-01 so he's not counted on 2019-06-21.

#### Solutions

1. ##### sub query

```sql
# Write your MySQL query statement below

SELECT login_date, COUNT(user_id) as user_count
    FROM (
        SELECT user_id, MIN(activity_date) as login_date FROM Traffic
        WHERE activity = "login"
        GROUP BY user_id
    ) t
    WHERE DATEDIFF("2019-06-30", login_date) <= 90
    GROUP BY login_date
    ORDER BY login_date
```


or

```sql
# Write your MySQL query statement below

SELECT activity_date  as login_date, COUNT(DISTINCT user_id) as user_count
    FROM (SELECT user_id, activity_date, RANK() 
                    OVER(PARTITION BY user_id ORDER BY activity_date) as r 
                FROM Traffic
                WHERE activity = "login") t
    WHERE t.r = 1 AND DATEDIFF("2019-06-30", activity_date) <= 90
    GROUP BY activity_date
```

or

```sql
# Write your MySQL query statement below

SELECT activity_date  as login_date, COUNT(*) as user_count
    FROM (SELECT user_id, activity_date, ROW_NUMBER() 
                    OVER(PARTITION BY user_id ORDER BY activity_date) as r 
                FROM Traffic
                WHERE activity = "login") t
    WHERE t.r = 1 AND DATEDIFF("2019-06-30", activity_date) <= 90
    GROUP BY activity_date

```