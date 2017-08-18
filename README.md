# N-Puzzle-Solver
Description:<br/>
A 3/4-Puzzle solver written in C++, uses A*/IDA* uses misplaced tiles, linear conflict and pattern database as heuristics.<br/>
<br/>
Most part of the input is hardcoded and the pattern database generator program is extremely inefficient but gets the job done
after the database is created.<br/>
The codes are completely unrefined and might be difficult to follow/use, still there are comments, which very well document the code.
<br/>
<br/>
Usage:<br/>
->The Pattern database generator is to be used to create the 6-6-3 database, once the database is created use N-Puzzle(IDA*)<br/>
&nbsp;&nbsp;&nbsp;&nbsp;program to solve the problem using pattern database heuristic and make sure that the database and the progrm are in &nbsp;&nbsp;&nbsp;&nbsp;the same folder.<br/>
->The database generator can take a couple upto a myriad of minutes to generate depending on the processing &nbsp;&nbsp;&nbsp;&nbsp;power and RAM.<br/>
->The other heuristic programs are straightforward and easy to use.
