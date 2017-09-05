;-----------------------------------------------------------
;
;  File:   VGAQUERY.ASM
;
;  Desc:   Functions for detecting various VGA compatible
;          displays and display modes
;
;-----------------------------------------------------------

.model large

; argument addressing - 16-bit far calls

arg1  equ  [bp+6]
arg2  equ  [bp+8]

public _is_vga, _is_ati, _test_mode

.data

; ROM signature of all ATI cards
ati_size  dw  9
ati_sign  db  '761295520'

.code

;-----------------------------------------------------------
;  Desc:  Test if a specified video mode is supported
;  Use:   int test_mode( int mode );
;  Ret:   0 - Not supported
;         mode - Mode is supported
;-----------------------------------------------------------

_test_mode proc far

     push bp
     mov  bp, sp

     ; get current video mode and save
     mov  ah, 0Fh
     int  10h
     push ax

     ; set passed mode
     mov  ax, arg1
     xor  ah, ah
     mov  dx, ax    ; dx = passed mode
     int  10h

     ; get current mode again
     mov  ah, 0Fh
     int  10h
     xor  ah, ah
     xor  dx, ax    ; dx=0 -> mode supported

     ; restore previous mode
     pop  ax
     xor  ah, ah
     int  10h

     ; set return code
     xor   ax, ax
     or    dx, dx
     jnz   test_mode_1
     mov   ax, arg1

   test_mode_1:
     pop  bp
     ret

_test_mode endp

;-----------------------------------------------------------
;  Desc:  Test for standard VGA adapter and display
;  Use:   int is_vga( void );
;  Ret:   0 - Not a VGA
;         1 - Monochrome VGA
;         2 - Color VGA
;-----------------------------------------------------------

_is_vga proc far

     push bx

     ; get active display
     mov  ax, 1A00h
     mov  bl, 99h
     int  10h

     ; bl = active display
     cmp  bl, 07h
     je   is_vga_1
     cmp  bl, 08h
     je   is_vga_2
     xor  ax, ax
     jmp short is_vga_3

   is_vga_1:
     mov  ax, 1
     jmp short is_vga_3

   is_vga_2:
     mov  ax, 2
     jmp short is_vga_3

   is_vga_3:
     pop  bx
     ret

_is_vga endp

;-----------------------------------------------------------
;  Desc:  Test for presence of an ATI adapter
;  Use:   int is_ati( void );
;  Ret:   0 - Not an ATI
;         1 - Is an ATI
;-----------------------------------------------------------

_is_ati proc far

     push es
     push di
     push si
     push cx

     xor  ax, ax
     mov  si, offset DGROUP:ati_sign
     mov  di, 0C000h
     mov  es, di
     mov  di, 0031h
     mov  cx, ati_size
     cld
     repz cmpsb
     or   cx, cx
     jnz  is_ati_1
     inc  ax
   is_ati_1:
     pop  cx
     pop  si
     pop  di
     pop  es
     ret

_is_ati endp

;-----------------------------------------------------------
;  Desc:  Test for presence of a Tseng chip set
;  Use:   int is_tseng( void );
;  Ret:   0 - Not a Tseng
;         1 - Is a Tseng
;-----------------------------------------------------------

_is_tseng proc far

     ; check for Tseng by testing support
     ; for a known Tseng super vga mode
     mov  ax, 29h
     call _test_mode
     or   ax, ax
     jz   is_tseng_1
     mov  ax, 1
   is_tseng_1:
     ret

_is_tseng endp

end
