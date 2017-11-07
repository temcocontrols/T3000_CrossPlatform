# Release Files
The latest release notes, windows and linux release files are stored here

#### RevNotes Follow here, most recent at the top


## Testing of Assigments and Expressions + Minor Corrections: 20171103.175500
Working on Issue #2: 
Pending: INTERVAL WR-ON and WR-OFF unknown last bytes.


## BUG FIXING: 20171031.192900
Working on Issue #2: 
Fixed: GENERIC CONTROL POINTS (NOT LABELS) NOT INCLUDED WHEN IN EXPRESSIONS

**Sample:**
```
Original Bytes = { 36 0 1 10 0 9 156 0 3 156 0 3 157 232 3 0 0 107 156 1 3 157 208 7 0 0 103 156 2 3 157 184 11 0 0 108 51 3 254 }

---------------------DEBUG STRINGS-----------------------

Code:
10 INIT = AVG ( INIT + 1 , VAR2 * 2 , VAR3 - 3 ) 
Tokens:
 LineNumberÂ· ASSIGNÂ· IdentifierÂ· IdentifierÂ· NumberÂ· PLUSÂ· IdentifierÂ· NumberÂ· MULÂ· IdentifierÂ· NumberÂ· MINUSÂ· AVGÂ· EOFÂ· EOFÂ·
Encoded Bytes = { 36 0 1 10 0 9 156 0 3 156 0 3 157 232 3 0 0 107 156 1 3 157 208 7 0 0 103 156 2 3 157 184 11 0 0 108 51 3 254 }
Original Bytes = { 36 0 1 10 0 9 156 0 3 156 0 3 157 232 3 0 0 107 156 1 3 157 208 7 0 0 103 156 2 3 157 184 11 0 0 108 51 3 254 }
```

## Updated 20171031.144500
Working on Issue #2: 
This release can save more complex assigments. (enclosed expressions, all functions defined in grammar, recursive expressions and list of subexpressions)
Here ends Encoding of Assigments and Expressions.
__Next Step, Commands!__


## Updated 20171028.104200
This release can save more complex assigments. (enclosed expressions, 10 functions, recursive expressions and list of subexpressions)
Working on Issue #2: 
Functions encoded so far: ABS AVG INTERVAL INT LN LN-1 SQR STATUS MAX MIN

**Sample:**
```
---------------------DEBUG STRINGS-----------------------

Code:
10 INIT = AVG ( INIT + 3 , 2 , 4 ) + INIT
Tokens:
 LineNumberÂ· ASSIGNÂ· IdentifierÂ· IdentifierÂ· NumberÂ· PLUSÂ· NumberÂ· NumberÂ· AVGÂ· IdentifierÂ· PLUSÂ· EOFÂ· EOFÂ·
Encoded Bytes = { 32 0 1 10 0 9 156 0 3 156 0 3 157 184 11 0 0 107 157 208 7 0 0 157 160 15 0 0 51 3 156 0 3 107 254 }

---------------------DEBUG STRINGS-----------------------

Code:
10 INIT = AVG ( ABS(INIT) + 3 , 2 , 4 ) + INIT
Tokens:
 LineNumberÂ· ASSIGNÂ· IdentifierÂ· IdentifierÂ· ABSÂ· NumberÂ· PLUSÂ· NumberÂ· NumberÂ· AVGÂ· IdentifierÂ· PLUSÂ· EOFÂ· EOFÂ·
Encoded Bytes = { 33 0 1 10 0 9 156 0 3 156 0 3 50 157 184 11 0 0 107 157 208 7 0 0 157 160 15 0 0 51 3 156 0 3 107 254 }
```



## Updated 20171024.110600
This release can save more complex assigments. (still pending to see how parenthesis affect postfix notation and encoding, also pending function calls in expressions.)
Working on Issue #2: 
### Encoding Expressions now uses infix to postfix converter.
### Must discover/learn how to encode function calls in expressions.
#### List<TokenInfo> GetExpression(from, cancel) is NOW the function responsible of getting full list of tokens for an expression in RPN (Postfix).

**Sample:**
```
---------------------DEBUG STRINGS-----------------------

Code:
10 INIT = INIT + PMPSPEED * 10 - INIT / 20
Tokens:
 LineNumberÂ· ASSIGNÂ· IdentifierÂ· IdentifierÂ· IdentifierÂ· NumberÂ· MULÂ· PLUSÂ· IdentifierÂ· NumberÂ· DIVÂ· MINUSÂ· EOFÂ·
Bytes = {30 0 1 10 0 9 156 0 3 156 0 3 156 1 3 157 16 39 0 0 103 107 156 0 3 157 32 78 0 0 104 108 254 }
```

## Updated 20171022.181700
~~Updated 20171022.103700~~
This release can save simple assigments. (see picture below)
New Issue #2 found: 
## Encoding Expressions needs full infix to postfix converter.
### It is also necessary to find all end-markers for expressions to stop parsing to postfix.
#### byte[] GetExpression(from,to) will be the function responsible of getting encoded a full expression with begin and end  markers as indexes.
#### ForEach(token) must be changed into For() to allow better control of current element.

![issue002]

##### Known markers so far:
Format: Begin/End

* *IF/THEN*
* *ASSIGN VAR/NL|EOF*
* *THEN/NL|EOF*
* *FOR/TO*
* *TO/STEP*




## Updated 20171020.153000
### Setup split into 32 bits and 64bits versions
![Setups](assets\img\setups.jpg)

CodeEditor and ProgramCode now includes:

* First statement saved to PRG.
* EncodeBytes() now returns a byte array.
	* REM Comment is ready.... next step: Assignments
* CodeEditor renumber lines
	* Validate semantic errors on undefined identifiers and line numbers.

## Updated 20171013.174300
### Added Installer for testing purposes

### **Warning:**

*__Setup is not fully tested!__* It contains a dependecy of .NET
Framework 4.6.x o newer. **Don't install it on a development enviroment system.** *To avoid any problem, you should use it ina a new system environment or virtual OS.*