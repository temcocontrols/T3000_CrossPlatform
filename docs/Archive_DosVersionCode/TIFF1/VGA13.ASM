;-----------------------------------------------------------
;
;  File:   VGA13.ASM
;
;  Desc:   Functions to read and write scan lines in
;          VGA mode 13h (320 x 200 x 256-colors)
;
;-----------------------------------------------------------

.model large

; argument addressing - 16-bit far calls

arg1  equ  [bp+6]
arg2  equ  [bp+8]
arg3  equ  [bp+10]
arg4  equ  [bp+12]
arg5  equ  [bp+14]

public _put_pixels_13, _get_pixels_13

.code

;-----------------------------------------------------------
;  Desc:  Write scan line in VGA mode 13h
;  Use:   void put_pixels_13( unsigned char *pixels
;                             int npixels, int x, int y );
;-----------------------------------------------------------

_put_pixels_13 proc far
     ; stack frame, save regs
		 ret
_put_pixels_13 endp

;-----------------------------------------------------------
;  Desc:  Read scan line in VGA mode 13h
;  Use:   void get_pixels_13( unsigned char *pixels
;                             int npixels, int x, int y );
;-----------------------------------------------------------

_get_pixels_13 proc far
		 ; stack frame, save regs
		 ret
_get_pixels_13 endp

end
