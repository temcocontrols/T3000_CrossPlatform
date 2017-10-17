;-----------------------------------------------------------
;
;  File:   XMS.ASM
;
;  Desc:   Minimal function set required to utilize
;          XMS memory from DOS real mode application
;
;-----------------------------------------------------------

.model large

; argument addressing - 16-bit far calls

arg1  equ  [bp+6]
arg2  equ  [bp+8]
arg3  equ  [bp+10]
arg4  equ  [bp+12]
arg5  equ  [bp+14]

public _XMS_installed, _XMS_alloc, _XMS_free, _XMS_move

.data

XMSctl label dword
             dw ?
             dw ?

.code

;-----------------------------------------------------------
;  Desc:  Test for presence of XMS driver.
;  Use:   int XMS_installed( void );
;  In:    Nothing
;  Out:   Returns 1 if found, 0 otherwise
;-----------------------------------------------------------

_XMS_installed proc far

     mov  ax, 4300h
     int  2Fh
     cmp  al, 80h
     jne  XMS_installed_1
     mov  ax, 1
     jmp short XMS_installed_2
   XMS_installed_1:
     xor  ax, ax
   XMS_installed_2:
     ret

_XMS_installed endp

;-----------------------------------------------------------
;  Desc:  Allocate XMS memory.
;  Use:   unsigned XMS_alloc( int nKBytes );
;  In:    Number of KB to allocate
;  Out:   XMS handle (0 implies failure)
;-----------------------------------------------------------

_XMS_alloc proc far

     push bp
     mov  bp, sp
     push es
     push bx

     ; get control function address
     mov  ax, 4310h
     int  2Fh
     mov  word ptr [XMSctl], bx
     mov  word ptr [XMSctl+2], es

     ; make alloc request
     mov  dx, arg1
     mov  ah, 09h
     call [XMSctl]

     ; check for failure
     or   ax, ax
     jz   XMS_alloc_1

     ; all is well
     mov  ax, dx

   XMS_alloc_1:
     pop  bx
     pop  es
     pop  bp
     ret

_XMS_alloc endp

;-----------------------------------------------------------
;  Desc:  Free XMS memory.
;  Use:   void XMS_free( unsigned XMShand );
;  In:    Handle returned by XMS_alloc()
;  Out:   Nothing
;-----------------------------------------------------------

_XMS_free proc far

     push bp
     mov  bp, sp
     push es
     push bx

     ; get control function address
     mov  ax, 4310h
     int  2Fh
     mov  word ptr [XMSctl], bx
     mov  word ptr [XMSctl+2], es

     ; make free request
     mov  dx, arg1
     mov  ah, 0Ah
     call [XMSctl]

     pop  bx
     pop  es
     pop  bp
     ret

_XMS_free endp

;-----------------------------------------------------------
;  Desc:  Move XMS memory block
;  Use:   int XMS_move( XMSmovestruct *ms );
;  In:    Pointer to an XMS move structure
;  Out:   0 -> success
;-----------------------------------------------------------

_XMS_move proc far

     push bp
     mov  bp, sp
     push bx
     push es
     push ds
     push si

     ; get control function address
     mov  ax, 4310h
     int  2Fh
     mov  word ptr [XMSctl], bx
     mov  word ptr [XMSctl+2], es

     ; make move request
     xor  bx, bx
     mov  si, ds
     mov  es, si
     mov  si, arg2
     mov  ds, si
     mov  si, arg1
     mov  ah, 0Bh
     call es:[XMSctl]

     ; set return code
     xor  ax, ax
     mov  al, bl

   XMS_move_1:
     pop  si
     pop  ds
     pop  es
     pop  bx
     pop  bp
     ret

_XMS_move endp

end
