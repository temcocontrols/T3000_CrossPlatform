;-----------------------------------------------------------
;
;  File:   VGAPAL.ASM
;
;  Desc:   Functions for reading and writing the VGA'a
;          adapter's palette and DAC registers
;
;-----------------------------------------------------------

.model large

; argument addressing - 16-bit far calls

arg1  equ  [bp+6]
arg2  equ  [bp+8]
arg3  equ  [bp+10]
arg4  equ  [bp+12]

public _get_vga_pal_reg, _set_vga_pal_reg
public _get_vga_dac_reg, _set_vga_dac_reg
public _get_vga_dac_256, _set_vga_dac_256

.code

;-----------------------------------------------------------
;  Desc:  Get the value of a VGA palette register
;  Use:   int get_vga_pal_reg( int reg_no );
;-----------------------------------------------------------

_get_vga_pal_reg proc far
     push bp
     mov  bp, sp
     push bx
     mov  bl, arg1       ; register number
     mov  ax, 1007h      ; func 10h, subfunc 07h
     int  10h
     xor  ax, ax
     mov  al, bh         ; ax = register value
     pop  bx
     pop  bp
     ret
_get_vga_pal_reg endp

;-----------------------------------------------------------
;  Desc:  Set the value of a VGA palette register
;  Use:   void set_vga_pal_reg( int reg_no, int reg_val );
;-----------------------------------------------------------

_set_vga_pal_reg proc far
     push bp
     mov  bp, sp
     push bx
     mov  ax, 1000h      ; func 10h subfunc 00h
     mov  bl, arg1       ; bl = register number
     mov  bh, arg2       ; bh = register value
     int  10h
     pop  bx
     pop  bp
     ret
_set_vga_pal_reg endp

;-----------------------------------------------------------
;  Desc:  Get the value of a VGA DAC register
;  Use:   long get_vga_dac_reg( int reg_no );
;-----------------------------------------------------------

_get_vga_dac_reg proc far
     push bp
     mov  bp, sp
	  push bx
	  push cx
	  mov  ax, 1015h      ; func 10h subfunc 15h
	  mov  bx, arg1       ; bl = register number
	  int  10h
	  xor  dl, dl
	  xchg dl, dh
	  mov  ax, cx         ; DX:AX = xRGB
	  pop  cx
	  pop  bx
	  pop  bp
	  ret
_get_vga_dac_reg endp

;-----------------------------------------------------------
;  Desc:  Set the value of a VGA DAC register
;  Use:   void set_vga_dac_reg( int reg_no,
;                               int r, int g, int b );
;-----------------------------------------------------------

_set_vga_dac_reg proc far
     push bp
     mov  bp, sp
	  push bx
	  push cx
	  mov  ax, 1010h      ; func 10h subfunc 10h
	  mov  bx, arg1       ; register number
	  mov  dh, arg2       ; red component
	  mov  ch, arg3       ; green component
	  mov  cl, arg4       ; blue component
	  int  10h
	  pop  cx
	  pop  bx
	  pop  bp
	  ret
_set_vga_dac_reg endp

;-----------------------------------------------------------
;  Desc:  Get all 256 VGA DAC registers
;  Use:   void set_vga_dac_256( unsigned char *colors );
;  Args:  colors is a 768-byte buffer
;-----------------------------------------------------------

_get_vga_dac_256 proc far
     push bp
     mov  bp, sp
     push es
     push bx
     push cx
     mov  ax, 1017h      ; func 10h subfunc 12h
     mov  bx, 0          ; bx = start index
     mov  cx, 256        ; cx = register count
     mov  dx, arg2
     mov  es, dx
     mov  dx, arg1       ; es:dx = pointer to block
     int  10h
     pop  cx
     pop  bx
     pop  es
     pop  bp
     ret
_get_vga_dac_256 endp

;-----------------------------------------------------------
;  Desc:  Set all 256 VGA DAC registers
;  Use:   void set_vga_dac_256( unsigned char *colors );
;  Args:  colors is a 768-byte buffer
;-----------------------------------------------------------

_set_vga_dac_256 proc far
     push bp
     mov  bp, sp
     push es
     push bx
     push cx
     mov  ax, 1012h      ; func 10h subfunc 12h
     mov  bx, 0          ; bx = start index
     mov  cx, 256        ; cx = register count
     mov  dx, arg2
     mov  es, dx
     mov  dx, arg1       ; es:dx = pointer to block
     int  10h
     pop  cx
     pop  bx
     pop  es
     pop  bp
     ret
_set_vga_dac_256 endp

end
