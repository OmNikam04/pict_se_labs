# Assignment 8

1. Display all the Purchase orders of a specific Customer.
    
    ```sql
    create view v_purchase_order as
    select p.name as "Product Name", p.price, o.quantity, 
    o.date_ordered, pay.amount, pay.date_paid
    from orders o 
    join customers c on o.customer_id = c.id
    join products p on o.product_id = p.id
    join payment pay on pay.order_id = o.id
    where c.name = "John Doe";
    
    select * from v_purchase_order;
    +--------------+-------+----------+--------------+--------+------------+
    | Product Name | price | quantity | date_ordered | amount | date_paid  |
    +--------------+-------+----------+--------------+--------+------------+
    | Product A    | 19.99 |        2 | 2023-05-01   |  39.98 | 2023-05-01 |
    | Product B    | 24.99 |        1 | 2023-05-02   |  24.99 | 2023-05-02 |
    +--------------+-------+----------+--------------+--------+------------+
    2 rows in set (0.00 sec)
    ```
    
2. List the Purchase Orders in descending order as per total.
    
    ```sql
    create view v_orders_desc as 
    select c.name as "customer", p.name as "product", o.quantity, 
    pay.amount as "Amount Paid" 
    from orders o 
    join customers c on o.customer_id = c.id
    join products p on o.product_id = p.id
    join payment pay on pay.order_id = o.id
    order by pay.amount desc;
    
    select * from v_orders_desc;
    +---------------+-----------+----------+-------------+
    | customer      | product   | quantity | Amount Paid |
    +---------------+-----------+----------+-------------+
    | Jane Doe      | Product C |        3 |       89.97 |
    | John Doe      | Product A |        2 |       39.98 |
    | Bob Smith     | Product D |        2 |       29.98 |
    | John Doe      | Product B |        1 |       24.99 |
    | Alice Johnson | Product E |        1 |        9.99 |
    +---------------+-----------+----------+-------------+
    5 rows in set (0.00 sec)
    ```
    
3. Customers whose purchase amount is greatest above rest customers.
    
    ```sql
    create view v_mostPurchasedCustomers as 
    select c.name, sum(pay.amount) as "total spend"
    from orders o
    join customers c on o.customer_id = c.id
    join payment pay on pay.order_id = o.id
    group by c.id
    order by sum(pay.amount) desc;
    
    select * from v_mostPurchasedCustomers;
    +-----------+-------------+
    | name      | total spend |
    +-----------+-------------+
    | Jane Doe  |       85.47 |
    | John Doe  |       62.97 |
    | Bob Smith |       29.98 |
    +-----------+-------------+
    3 rows in set (0.00 sec)
    ```
    
4. Get Customer and Data Item Information for a Specific Purchase Order.
    
    ```sql
    create or replace view v_orderDetails as 
    select c.name as "customer name",c.email, p.name as "product name",
     p.price, o.quantity, pay.amount
    from orders o
    join customers c on o.customer_id = c.id
    join products p on o.product_id = p.id
    join payment pay on pay.order_id = o.id;
    
    select * from v_orderDetails;
    +---------------+--------------------------+--------------+-------+----------+--------+
    | customer name | email                    | product name | price | quantity | amount |
    +---------------+--------------------------+--------------+-------+----------+--------+
    | John Doe      | johndoe@example.com      | Product A    | 19.99 |        2 |  37.98 |
    | John Doe      | johndoe@example.com      | Product B    | 24.99 |        1 |  24.99 |
    | Jane Doe      | janedoe@example.com      | Product C    | 29.99 |        3 |  85.47 |
    | Bob Smith     | bobsmith@example.com     | Product D    | 14.99 |        2 |  29.98 |
    | Alice Johnson | alicejohnson@example.com | Product E    |  9.99 |        1 |   9.99 |
    +---------------+--------------------------+--------------+-------+----------+--------+
    5 rows in set (0.00 sec)
    ```
    
5. Display order details of customer whose city name is “Pune” and purchase
date is “22/08/2016” (Boolean Operators: and, or)
    
    ```sql
    create or replace view v_specific_order_details
    SELECT o.id, o.quantity, p.name AS product_name,
     c.name AS customer_name, c.city, o.date_ordered, pay.amount, pay.date_paid
    FROM orders o
    JOIN customers c ON o.customer_id = c.id
    JOIN products p ON o.product_id = p.id
    JOIN payment pay ON o.id = pay.order_id
    WHERE c.city = 'Pune' AND o.date_ordered = '2023-05-01';
    
    select * from v_specific_order_details;
    +----+----------+--------------+---------------+------+--------------+--------+------------+
    | id | quantity | product_name | customer_name | city | date_ordered | amount | date_paid  |
    +----+----------+--------------+---------------+------+--------------+--------+------------+
    |  1 |        2 | Product A    | John Doe      | pune | 2023-05-01   |  39.98 | 2023-05-01 |
    +----+----------+--------------+---------------+------+--------------+--------+------------+
    1 row in set (0.00 sec)
    ```
    

### Inserting data into base table through views:

To insert data into a base table using a view, the view must meet the following requirements:

- It must not contain any derived columns, such as expressions or functions.
- It must not contain multiple tables.
- It must not use the GROUP BY or HAVING clause.
- It must not use the DISTINCT keyword.

```sql
mysql> select * from customers;
+----+---------------+--------------------------+----------+--------+
| id | name          | email                    | phone    | city   |
+----+---------------+--------------------------+----------+--------+
|  1 | John Doe      | johndoe@example.com      | 555-1234 | pune   |
|  2 | Jane Doe      | janedoe@example.com      | 555-5678 | Nashik |
|  3 | Bob Smith     | bobsmith@example.com     | 555-2468 | Nagpur |
|  4 | Alice Johnson | alicejohnson@example.com | 555-1357 | Sangli |
|  5 | Tom Jones     | tomjones@example.com     | 555-3691 | Mumbai |
|  6 | Kate williums | kate@gmail.com           | 666-2352 | Nashik |
+----+---------------+--------------------------+----------+--------+
6 rows in set (0.00 sec)

mysql> create or replace view v_customers as select * from customers;
Query OK, 0 rows affected (0.01 sec)

mysql> insert into v_customers values(7,"Justin bieber","justin@gmail.com","688-235","Kolhapur");
Query OK, 1 row affected (0.01 sec)

mysql> select * from customers;
+----+---------------+--------------------------+----------+----------+
| id | name          | email                    | phone    | city     |
+----+---------------+--------------------------+----------+----------+
|  1 | John Doe      | johndoe@example.com      | 555-1234 | pune     |
|  2 | Jane Doe      | janedoe@example.com      | 555-5678 | Nashik   |
|  3 | Bob Smith     | bobsmith@example.com     | 555-2468 | Nagpur   |
|  4 | Alice Johnson | alicejohnson@example.com | 555-1357 | Sangli   |
|  5 | Tom Jones     | tomjones@example.com     | 555-3691 | Mumbai   |
|  6 | Kate williums | kate@gmail.com           | 666-2352 | Nashik   |
|  7 | Justin bieber | justin@gmail.com         | 688-235  | Kolhapur |
+----+---------------+--------------------------+----------+----------+
7 rows in set (0.00 sec)
```

### Updating base table through views:

To update a base table using a view, the view must meet the following requirements:

- The view must not contain any derived columns, such as expressions or functions.
- The view must only reference a single base table.
- The view must not use the GROUP BY or HAVING clause.
- The view must not use the DISTINCT keyword.

```sql
mysql> update v_customers set email="jb@gmail.com" where name="Justin bieber";
Query OK, 1 row affected (0.01 sec)
Rows matched: 1  Changed: 1  Warnings: 0

mysql> select * from customers;
+----+---------------+--------------------------+----------+----------+
| id | name          | email                    | phone    | city     |
+----+---------------+--------------------------+----------+----------+
|  1 | John Doe      | johndoe@example.com      | 555-1234 | pune     |
|  2 | Jane Doe      | janedoe@example.com      | 555-5678 | Nashik   |
|  3 | Bob Smith     | bobsmith@example.com     | 555-2468 | Nagpur   |
|  4 | Alice Johnson | alicejohnson@example.com | 555-1357 | Sangli   |
|  5 | Tom Jones     | tomjones@example.com     | 555-3691 | Mumbai   |
|  6 | Kate williums | kate@gmail.com           | 666-2352 | Nashik   |
|  7 | Justin bieber | jb@gmail.com             | 688-235  | Kolhapur |
+----+---------------+--------------------------+----------+----------+
7 rows in set (0.00 sec)
```

### Delete base table rows from views:

```sql
mysql> delete from v_customers where id = 6;
Query OK, 1 row affected (0.01 sec)

mysql> select * from customers;
+----+---------------+--------------------------+----------+----------+
| id | name          | email                    | phone    | city     |
+----+---------------+--------------------------+----------+----------+
|  1 | John Doe      | johndoe@example.com      | 555-1234 | pune     |
|  2 | Jane Doe      | janedoe@example.com      | 555-5678 | Nashik   |
|  3 | Bob Smith     | bobsmith@example.com     | 555-2468 | Nagpur   |
|  4 | Alice Johnson | alicejohnson@example.com | 555-1357 | Sangli   |
|  5 | Tom Jones     | tomjones@example.com     | 555-3691 | Mumbai   |
|  7 | Justin bieber | jb@gmail.com             | 688-235  | Kolhapur |
+----+---------------+--------------------------+----------+----------+
6 rows in set (0.00 sec)
```

### Altering base table through views:

We cannot use the **`ALTER`** command directly on a view to update the underlying base table. A view is simply a virtual table that is derived from one or more tables, and it does not store any data on its own. Instead, it provides a logical representation of the data in the underlying table(s).

```sql
mysql> alter table customers add column royalty_level varchar(20) default "bronze";
Query OK, 0 rows affected (0.05 sec)
Records: 0  Duplicates: 0  Warnings: 0

mysql> select * from customers;
+----+---------------+--------------------------+----------+----------+---------------+
| id | name          | email                    | phone    | city     | royalty_level |
+----+---------------+--------------------------+----------+----------+---------------+
|  1 | John Doe      | johndoe@example.com      | 555-1234 | pune     | bronze        |
|  2 | Jane Doe      | janedoe@example.com      | 555-5678 | Nashik   | bronze        |
|  3 | Bob Smith     | bobsmith@example.com     | 555-2468 | Nagpur   | bronze        |
|  4 | Alice Johnson | alicejohnson@example.com | 555-1357 | Sangli   | bronze        |
|  5 | Tom Jones     | tomjones@example.com     | 555-3691 | Mumbai   | bronze        |
|  7 | Justin bieber | jb@gmail.com             | 688-235  | Kolhapur | bronze        |
+----+---------------+--------------------------+----------+----------+---------------+
6 rows in set (0.00 sec)

mysql> update customers set loyalty_level = "gold" where id=1;
Query OK, 1 row affected (0.01 sec)
Rows matched: 1  Changed: 1  Warnings: 0

mysql> select * from customers;
+----+---------------+--------------------------+----------+----------+---------------+
| id | name          | email                    | phone    | city     | loyalty_level |
+----+---------------+--------------------------+----------+----------+---------------+
|  1 | John Doe      | johndoe@example.com      | 555-1234 | pune     | gold          |
|  2 | Jane Doe      | janedoe@example.com      | 555-5678 | Nashik   | bronze        |
|  3 | Bob Smith     | bobsmith@example.com     | 555-2468 | Nagpur   | bronze        |
|  4 | Alice Johnson | alicejohnson@example.com | 555-1357 | Sangli   | bronze        |
|  5 | Tom Jones     | tomjones@example.com     | 555-3691 | Mumbai   | bronze        |
|  7 | Justin bieber | jb@gmail.com             | 688-235  | Kolhapur | bronze        |
+----+---------------+--------------------------+----------+----------+---------------+
6 rows in set (0.00 sec)
```

### Dropping a view:

```sql
mysql> select * from v_purchase_order;
+--------------+-------+----------+--------------+--------+------------+
| Product Name | price | quantity | date_ordered | amount | date_paid  |
+--------------+-------+----------+--------------+--------+------------+
| Product A    | 19.99 |        2 | 2023-05-01   |  37.98 | 2023-05-01 |
| Product B    | 24.99 |        1 | 2023-05-02   |  24.99 | 2023-05-02 |
+--------------+-------+----------+--------------+--------+------------+
2 rows in set (0.00 sec)

mysql> drop view v_purchase_order;
Query OK, 0 rows affected (0.01 sec)
```

### Some additional queries for views:

```sql
mysql> create or replace view v_nashikCustomers as select * from customers where city="Nashik";
Query OK, 0 rows affected (0.01 sec)

mysql> select * from v_nashikCustomers;
+----+---------------+---------------------+----------+--------+---------------+
| id | name          | email               | phone    | city   | loyalty_level |
+----+---------------+---------------------+----------+--------+---------------+
|  2 | Jane Doe      | janedoe@example.com | 555-5678 | Nashik | bronze        |
|  7 | Justin bieber | jb@gmail.com        | 688-235  | Nashik | bronze        |
+----+---------------+---------------------+----------+--------+---------------+
2 rows in set (0.00 sec)

mysql> select * from v_nashikCustomers where id = 2;
+----+----------+---------------------+----------+--------+---------------+
| id | name     | email               | phone    | city   | loyalty_level |
+----+----------+---------------------+----------+--------+---------------+
|  2 | Jane Doe | janedoe@example.com | 555-5678 | Nashik | bronze        |
+----+----------+---------------------+----------+--------+---------------+
1 row in set (0.00 sec)

mysql> select * from v_nashikCustomers where name like "J%";
+----+---------------+---------------------+----------+--------+---------------+
| id | name          | email               | phone    | city   | loyalty_level |
+----+---------------+---------------------+----------+--------+---------------+
|  2 | Jane Doe      | janedoe@example.com | 555-5678 | Nashik | bronze        |
|  7 | Justin bieber | jb@gmail.com        | 688-235  | Nashik | bronze        |
+----+---------------+---------------------+----------+--------+---------------+
2 rows in set (0.00 sec)

mysql> select * from v_nashikCustomers where name like "_____D%";
+----+----------+---------------------+----------+--------+---------------+
| id | name     | email               | phone    | city   | loyalty_level |
+----+----------+---------------------+----------+--------+---------------+
|  2 | Jane Doe | janedoe@example.com | 555-5678 | Nashik | bronze        |
+----+----------+---------------------+----------+--------+---------------+
1 row in set (0.00 sec)
```
