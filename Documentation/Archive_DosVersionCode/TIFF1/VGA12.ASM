;-----------------------------------------------------------
;
;  File:   VGA12.ASM
;
;  Desc:   Functions to read and write scan lines in
;          VGA mode 12h (640 x 480 x 16-colors)
;
;-----------------------------------------------------------

;;.model large

; argument addressing - 16-bit far calls

arg1  equ  [bp+6]
arg2  equ  [bp+8]
arg3  equ  [bp+10]
arg4  equ  [bp+12]
arg5  equ  [bp+14]
arg6  equ  [bp+16]

_DATA      SEGMENT PARA PUBLIC
			  EXTRN _segA000
_DATA      ENDS


public _put_pixels_12, _get_pixels_12


_TEXT           SEGMENT BYTE PUBLIC 'CODE'

		ASSUME  DS:_DATA
		ASSUME  CS:_TEXT
;;.code

;-----------------------------------------------------------
;  Desc:  Compute video memory address and a pixel
;         bitmask from an (x,y) pixel coordinate
;  In:    CX = X, BX = Y
;  Out:   ES:DI = video address, BH = bitmask
;-----------------------------------------------------------

pixel_addr proc near

;;	  mov  ax, A000h
;;	  mov  es, ax       ; es = video seg addr
	  mov  ax, 80       ; bytes-per-row
	  mul  bx           ; ax = Y * bytes-per-row
	  mov  di, cx
	  shr  di, 1
	  shr  di, 1
	  shr  di, 1        ; di = row byte offset
	  add  di, ax       ; di = video offset
	  and  cx, 07h      ; cx = X % 8
	  mov  bh, 80h
	  shr  bh, cl       ; bh = pixel bitmask
;;	  pop  ds
	  ret

pixel_addr endp

;-----------------------------------------------------------
;  Desc:  Write scan line in VGA mode 12h
;  Use:   void put_pixels_12( unsigned char *pixels,
;                             int npixels, int x, int y );
;-----------------------------------------------------------

_put_pixels_12 proc far
     ; stack frame, save regs
     push bp
     mov  bp, sp
     push ds
     push es
     push di
     push si

     ; setup memory addressing
	  mov  si, arg2
     mov  ds, si
     mov  si, arg1     ; ds:si -> pixel array
     mov  bx, arg5     ; bx = Y
	  mov  cx, arg4     ; cx = X
	  mov  es, arg6     ; A000
	  call pixel_addr   ; es:di -> video buffer

	  ; initialize VGA controller
     mov  dx, 03CEh    ; dx = addr reg port
     mov  ax, 0A05h    ; RM=1, WM=2
	  out  dx, ax
		 mov  ax, 0003h    ; rot/func select
     out  dx, ax
     mov  ax, 0007h    ; color select
     out  dx, ax

     ; other setup
     mov  cx, arg3     ; cx = pixel count
     mov  al, 8        ; al = bmask reg no
     mov  ah, bh       ; ah = bitmask

		 ; loop
	 put_pixels_12_1:
		 mov  bh, ds:[si]  ; get pixel value
		 cmp bh,0
;		 cmp BYTE PTR ds:[si],0fh
		 jge c1
		 not bh
		 inc bh
		 inc bh
		 inc si
		 mov bl,bh
		 xor bh,bh
		 sub cx,bx
		 jge c4
		 add cx,bx
		 mov bx,cx
		 xor cx,cx
c4:		 inc cx
		 push ax
		 push cx
		 mov cl,bl
		 ror ah,cl
		 pop cx

		 shr bx,3
		 add di,bx
		 pop bx
		 cmp ah,bh
		 jbe c3
		 inc di
c3:		 loop put_pixels_12_1
		 jmp c2
c1:		 out  dx, ax       ; set bitmask reg
;		 mov  bh, ds:[si]  ; get pixel value
		 and  es:[di], bh  ; set pixel
		 inc  si           ; next pixel addr
		 ror  ah, 1        ; next bitmask
		 jnc  put_pixels_12_2
		 inc  di           ; next video byte
	 put_pixels_12_2:
		 loop put_pixels_12_1

		 ; restore VGA controller
c2:
		 mov  ax, 0FF08h
		 out  dx, ax
		 mov  ax, 0F07h
		 out  dx, ax
		 mov  ax, 0005h
		 out  dx, ax

		 ; restore regs
		 pop  si
		 pop  di
     pop  es
     pop  ds
     pop  bp
     ret
_put_pixels_12 endp

;-----------------------------------------------------------
;  Desc:  Read scan line in VGA mode 12h
;  Use:   void get_pixels_12( unsigned char *pixels,
;                             int npixels, int x, int y );
;-----------------------------------------------------------

_get_pixels_12 proc far
     ; stack frame, save regs
	  push bp
	  mov  bp, sp
     push ds
     push es
     push di
     push si

     ; zero the pixel buffer
     mov  di, arg2
     mov  es, di
     mov  di, arg1     ; es:di -> pixel array
     mov  cx, arg3     ; cx = pixel count
     xor  al, al
     cld
     rep  stosb

     ; initialize VGA controller
     mov  dx, 03CEh    ; dx = addr reg port
     mov  ax, 0005h    ; RM=0, WM=0
     out  dx, ax

	  ; bitplane number and mask
	  mov  bh, 3
     mov  bl, 08h

     ; loop for each bitplane
   get_pixels_12_1:
     push bx
     push bx

     ; select bitplane
     mov  dx, 03CEh    ; dx = addr reg port
     mov  al, 04h      ; al = map select reg
     mov  ah, bh
     out  dx, ax

     ; setup memory addressing
     mov  si, arg2
     mov  ds, si
     mov  si, arg1     ; ds:si -> pixel array
     mov  bx, arg5     ; bx = Y
     mov  cx, arg4     ; cx = X
     mov  es, arg6     ; A000
	  call pixel_addr   ; es:di -> video buffer

     ; other setup
     mov  ah, bh       ; ah = cur pixel mask
     pop  bx           ; bl = plane mask
     mov  cx, arg3     ; cx = pixel count

     ; loop for each pixel
   get_pixels_12_2:
     mov  bh, es:[di]  ; bh = plane latch
     and  bh, ah       ; isolate pixel bit
     jz   get_pixels_12_3
     or   ds:[si], bl
   get_pixels_12_3:
     inc  si           ; next pixel addr
     ror  ah, 1        ; next bitmask
     jnc  get_pixels_12_4
     inc  di           ; next video byte
   get_pixels_12_4:
     loop get_pixels_12_2

	  ; next bitplane
     pop  bx
     dec  bh
     ror  bl, 1
     jnc  get_pixels_12_1

     ; restore regs
     pop  si
     pop  di
     pop  es
     pop  ds
     pop  bp
     ret
_get_pixels_12 endp

_TEXT   ENDS
	  END

