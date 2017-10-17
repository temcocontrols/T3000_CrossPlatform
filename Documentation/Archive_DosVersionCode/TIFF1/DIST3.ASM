;-----------------------------------------------------------
;
;  File:  DIST3.ASM
;
;  Desc:  Function to compute distance-squared between two
;         integer triples, such as two RGB's.
;
;-----------------------------------------------------------

.model large

; argument addressing - 16-bit far calls

arg1  equ  [bp+6]
arg2  equ  [bp+8]
arg3  equ  [bp+10]
arg4  equ  [bp+12]
arg5  equ  [bp+14]
arg6  equ  [bp+16]

; local temporaries

tmp1  equ  [bp-2]
tmp2  equ  [bp-4]
tmp3  equ  [bp-6]
tmp4  equ  [bp-8]

ntmp  equ  8

public _dist3

.code

;-----------------------------------------------------------
;  Desc: Compute sum of deltas squared
;  Use:  long dist3( int r1, int r2, int g1, int g2,
;                    int b1, int b2 );
;  Ret:   (r1-r2)^2 + (g1-g2)^2 + (b1-b2)^2
;-----------------------------------------------------------


_dist3 proc far

       push  bp
       mov   bp, sp
       push  bx
       push  cx

       ; accumulate result in cx:bx
       xor  bx, bx
       xor  cx, cx

       mov   ax, arg1
       sub   ax, arg2
       imul  ax
       add   bx, ax
       adc   cx, dx

       mov   ax, arg3
       sub   ax, arg4
       imul  ax
       add   bx, ax
       adc   cx, dx

       mov   ax, arg5
       sub   ax, arg6
       imul  ax
       add   bx, ax
       adc   cx, dx

       ; set dx:ax = cx:bx
       xchg  ax, bx
       xchg  dx, cx

       pop   cx
       pop   bx
       pop   bp
       ret

_dist3 endp

end
