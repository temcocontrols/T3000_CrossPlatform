;-----------------------------------------------------------
;
;  File:   REVWORD.ASM
;
;  Desc:   Functions to reverse the byte order of word
;          (16-bit) and double word (32-bit) quantities
;
;-----------------------------------------------------------

.model large

; argument addressing - 16-bit far calls

arg1  equ  [bp+6]
arg2  equ  [bp+8]

public _rev_word, _rev_dword

.code

;-----------------------------------------------------------
;  Desc:  Reverses byte order in a word value
;  Use:   unsigned short rev_word( unsigned short );
;-----------------------------------------------------------

_rev_word proc far
     push bp
     mov  bp, sp
     mov  ax, arg1
     xchg ah, al
     pop  bp
     ret
_rev_word endp

;-----------------------------------------------------------
;  Desc:  Reverses byte order in a double word value
;  Use:   unsigned long rev_dword( unsigned long );
;-----------------------------------------------------------

_rev_dword proc far
     push bp
     mov  bp, sp
     mov  ax, arg1
     mov  dx, arg2
     xchg dh, al
     xchg dl, ah
     pop  bp
     ret
_rev_dword endp

end
