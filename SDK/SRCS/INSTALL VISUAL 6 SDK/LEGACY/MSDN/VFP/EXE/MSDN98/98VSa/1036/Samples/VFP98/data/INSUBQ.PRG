*!*	This subquery uses the In comparison test. The inner query is computed first.
*!*	The query results are treated as constants from that point forward,
*!*	and the inner query is not rerun. This increases the
*!*	overall performance of an IN subquery.
*!*	The results are evaluated against each new row in
*!*	the main query. When the column value is found to
*!*	match, or not match when a NOT IN is used, the row is 
*!*	included in the result. If there is a non match, the row 
*!*	is excluded.
