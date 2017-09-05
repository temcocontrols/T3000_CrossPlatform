;-----------------------------------------------------------
;
;  File:   ISCALE.ASM
;
;  Desc:   Function to perform 16-bit integer scaling
;          using a scale define as the fraction n/d
;
;-----------------------------------------------------------

.model large

; argument addressing - 16-bit far calls

arg1  equ  [bp+6]
arg2  equ  [bp+8]
arg3  equ  [bp+10]

public _iscale

.code

;-----------------------------------------------------------
;  Desc:  Perform 16-bit integer scaling
;  Use:   int iscale( int i, int n, int d );
;  Ret:   The quantity  (i * n) / d
;-----------------------------------------------------------

_iscale proc far
       push  bp
       mov   bp, sp
       push  bx

       mov   ax, arg1
       imul  word ptr arg2
       mov   bx, arg3
       idiv  bx
       shl   dx, 1
       inc   dx
       sub   bx, dx
       adc   ax, 0

       pop   bx
       pop   bp
       ret
_iscale endp

end
