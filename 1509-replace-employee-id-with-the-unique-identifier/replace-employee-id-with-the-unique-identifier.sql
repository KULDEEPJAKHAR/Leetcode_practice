# Write your MySQL query statement below
SELECT Employees.name,
EmployeeUni.unique_id
FROM Employees
LEFT JOIN EmployeeUNI ON Employees.id = EmployeeUNI.id;