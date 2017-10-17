;-----------------------------------------------------------
;
;  File:   VMODE.ASM
;
;  Desc:   Functions to query and set the video mode
;          on a VGA or compatible display adapter
;
;-----------------------------------------------------------

.model large

; argument addressing - 16-bit far calls

arg1  equ  [bp+6]
arg2  equ  [bp+8]

public _getvideomode, _setvideomode

.code

;-----------------------------------------------------------
;  Desc:  Return current video mode
;  Use:   int getvideomode( void )
;  In:    Nothing
;  Out:   Current mode number
;-----------------------------------------------------------

_getvideomode proc far

     push bx
     mov  ah, 0Fh
     int  10h
     xor  ah, ah
     pop  bx
     ret

_getvideomode endp

;-----------------------------------------------------------
;  Desc:  Set current video mode
;  Use:   void setvideomode( int mode )
;  In:    Desired mode number
;  Out:   Nothing
;-----------------------------------------------------------

_setvideomode proc far

     push bp
     mov  bp, sp
     mov  ax, arg1
     xor  ah, ah
     int  10h
     pop  bp
     ret

_setvideomode endp

end
