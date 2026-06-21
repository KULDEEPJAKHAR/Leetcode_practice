# Write your MySQL query statement below
Select visits.customer_id,
    COUNT(*) AS count_no_trans
FROM Visits
Left Join Transactions 
ON Visits.visit_id = Transactions.visit_id
Where Transactions.transaction_id IS NULL
Group By Visits.customer_id;