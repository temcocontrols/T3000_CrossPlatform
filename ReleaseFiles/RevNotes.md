# Release Files
The latest release notes, windows and linux release files are stored here

## Updated: 20180706.1828
### EDITOR Save and Load File (inside editor)
New Shortcut for Load File  = F6
New Shortcut for Save File  = F7
Menú for ProgramEditorForm rearranged.
####Pending TIME-OFF, TIME-ON two bytes argument info and struct.
New release files and binaries x86, x64

## Updated: 20180704.1146
### EDITOR New properties dialog and improved Identifier Info Dialog
New Shortcut for Settings (Properties) of Editor  = F4
New Shortcut for Identifier Settings = CTRL + SHIFT + I
Both dialogs rebuilded inside the editor: ShowIdentifierInfoDialog(SelectedText) and ShowProperties()
####Some fixing after testing the solution under Debian 9.
####Pending TIME-OFF, TIME-ON two bytes argument info and struct.
New release files and binaries x86, x64 and Linux (tar.gz)

## Updated: 20180628.0404
### EDITOR STYLES + IDENTIFIERS INFO DIALOG
Editor now supports all properties for TextStyles: Variables, Inputs, Outputs, Strings, Commments, Keywords, Inner Line Numbers. Editor using a local copy of Control Points Info + Improved IdentifierInfo form inside Editor (SHIFT+INS Shortcut on a selected identifier).
####Pending TIME-OFF, TIME-ON two bytes argument info and struct.
New release files and binaries

## Updated: 20180627.1304
### EDITOR STYLES
Editor now supports all properties for TextStyles: Variables, Inputs, Outputs, Strings, Commments, Keywords, Inner Line Numbers. Editor using a local copy of Control Points Info.
Next: Improve IdentifierInfo form inside Editor.
####Pending TIME-OFF, TIME-ON two bytes argument info and struct.
New release files and binaries


## Updated: 20180626.0318
### TIME FORMAT SUPPORT
Working on Editor Commands: Ctrl+Insert displays Identifier Info. Right now working outside the editor, directly from ProgramEditor Form, as its a bit hard to pass a copy of control points info to Editor. Will see how to workaround this.
Editor now supports 3 properties for TextStyles: VariablesColor, CommmentsColor and KeywordsColor. Inputs and Outpus not working right now 'cause editor, doesn't have a copy of Control Points yet.
####Pending TIME-OFF, TIME-ON two bytes argument info and struct.
New release files and binaries

## Updated: 20180619.0134
### TIME FORMAT SUPPORT
Revision to Encoder and Decoder Class: Static all functions and properties was a very bad idea. ControlPoints dissapears from scope.
BUG FOUND AND SOLVED: EQ was not recognized between expressions, Grammar was sending ASSIGMENT instead of EQ.
Editor has a debug assert for buffer overflow of Styles.
Helper methods extracted from Encoder for better maintenance of the code.
####Pending TIME-OFF, TIME-ON two bytes argument info and struct.
New release files and binaries


## Updated: 20180615.2052
### IF IF+ IF- THEN ELSE redesigned.
Tested against env14.prg
####Pending TIME-OFF, TIME-ON two bytes argument info and struct.
New release files and binaries

## Updated: 20180214.0100
### DECODER 90% Ready, BUG FIX: IF THEN ELSE Decoding with recursive calls of DecodeBytes()
#### 90% of Functions, 90% of Commands, IF+- Ready.  Still no info for some functions, commands and FOR
#### Same lack of info as in Encode Process.
Tested against T3000 C++ and Raspbian Jessie

## Updated: 20180103.2207
### New FastColoredTextBoxNS.IronyFCBT control (editor with syntax highlighting based on irony grammar)
#### Version 1.1 [COM VISIBLE And Registered for COM InterOP]
\ReleaseFiles\FastColoredTextBox.IronyFCTB.rar is a simple compressed release for this control to be tested in T3000 C++
plus documentation files (Basic API (word document) and Help File (.chm)


## Updated: 20171214.1452
### No more commands encoded, but a new version of FastColoredTextBoxNS.IronyFCBT control (editor with syntax highlighting based on irony grammar)
#### Version 1.1 [COM VISIBLE And Registered for COM InterOP]
\ReleaseFiles\setup\T3000 Raspbian.tar.gz is a simple compressed release for testing on raspbian with mono.
\ReleaseFiles\FastColoredTextBox.IronyFCBT.rar is a simple compressed release for this control to be tested in T3000 C++
Working on Issue #2:
 

## Updated: 20171213.1547OM
### Encoded RUN_MACRO CALL SET_PRINTER PRINT_AT ALARM_AT PHONE and others
### New tar.gz release for testing on raspbian with mono.
Tested against T3000 C++ and Raspbian Jessie
Working on Issue #2: 

## Updated: 20171204.121900
### Encoded DECLARE END
Tested against T3000 C++
Working on Issue #2: 

## Updated: 20171204.093200
### Encoded ENABLE DISABLE
Tested against T3000 C++
Working on Issue #2: 


## Updated: 20171112.194000
### Encoding Commands
#### Bug fixing:  Last bytes after expression within WAIT is now recognized and encoded as a counter with 4 bytes after a byte marking EOE

```
START.Rule = "START" + Designator;
STOP.Rule = "STOP" + Designator;
WAIT.Rule = "WAIT" + Expression;
CLEAR.Rule = ToTerm("CLEAR","CLEAR");
RETURN.Rule = ToTerm("RETURN", "RETURN");
HANGUP.Rule = ToTerm("HANGUP");
```

Tested against T3000 C++
Working on Issue #2: 

## Updated: 20171111
### IF IF+ IF- Encoded
#### Bug Fixed: ELSE now encoded.
Tested against T3000 C++
Working on Issue #2: 

## Updated: 20171110
### IF IF+ IF- Encoded
Working on Issue #2: 

## Updated: 20171106.120700
### ProgramEditor Assembly Made COM Visible + Registered for COM Interop
Working on Issue #2: 
Pending: INTERVAL WR-ON and WR-OFF unknown last bytes.
Research how to properly encode IF IF+ IF-

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
 LineNumber· ASSIGN· Identifier· Identifier· Number· PLUS· Identifier· Number· MUL· Identifier· Number· MINUS· AVG· EOF· EOF·
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
 LineNumber· ASSIGN· Identifier· Identifier· Number· PLUS· Number· Number· AVG· Identifier· PLUS· EOF· EOF·
Encoded Bytes = { 32 0 1 10 0 9 156 0 3 156 0 3 157 184 11 0 0 107 157 208 7 0 0 157 160 15 0 0 51 3 156 0 3 107 254 }

---------------------DEBUG STRINGS-----------------------

Code:
10 INIT = AVG ( ABS(INIT) + 3 , 2 , 4 ) + INIT
Tokens:
 LineNumber· ASSIGN· Identifier· Identifier· ABS· Number· PLUS· Number· Number· AVG· Identifier· PLUS· EOF· EOF·
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
 LineNumber· ASSIGN· Identifier· Identifier· Identifier· Number· MUL· PLUS· Identifier· Number· DIV· MINUS· EOF·
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

![issue002](https://phoenix.aimservices.tech:8082/uploads/c-programming/t3000/7d330df1cb/issue002.jpg)

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