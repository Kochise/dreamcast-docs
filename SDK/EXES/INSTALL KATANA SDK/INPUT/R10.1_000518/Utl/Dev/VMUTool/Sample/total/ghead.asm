chip	LC868700
world	external
; *-----------------------------------------------------*
; *	External header program Ver 1.00					*
; *					05/20-'98							*
; *-----------------------------------------------------*

public	fm_wrt_ex, fm_vrf_ex, fm_prd_ex

public	fm_wrt_ex_exit,fm_vrf_ex_exit
public	fm_prd_ex_exit,timer_ex_exit,_game_start,_game_end
other_side_symbol	fm_wrt_in,fm_vrf_in
other_side_symbol	fm_prd_in,timer_in,game_end

extern	main			;Symbol in the user program
extern	int_BaseTimer	;
extern	int_P3			;
extern	int_T0H			;

; *-----------------------------------------------------*
; *	Vector table										*
; *-----------------------------------------------------*
cseg
org	0000h
_game_start:
		jmpf	main		; main program jump

org	0003h					;** int_03 **
		clr1	I01CR,1
		reti

org	000bh					;** int_0b **
		reti

org	0013h					;** int_13 **
		reti

org	001bh					;** int_1b **
		jmpf	int_1b

org	0023h					;** int_23 **
		jmpf	int_T0H

org	002bh					;** int_2b **
		reti

org	0033h					;** int_33 **
		reti

org	003bh					;** int_3b **
		reti

org	0043h					;** int_43 **
		reti

org	004bh					;** int_4b **
		jmpf	int_P3

org	0100h
; *-----------------------------------------------------*
; *	flash memory write external program					*
; *-----------------------------------------------------*
fm_wrt_ex:
		change	fm_wrt_in
	fm_wrt_ex_exit:
		ret

org	0110h
; *-----------------------------------------------------*
; *	flash memory verify external program				*
; *-----------------------------------------------------*
fm_vrf_ex:
		change	fm_vrf_in
	fm_vrf_ex_exit:
		ret

org	0120h
; *-----------------------------------------------------*
; *	flash memory page read external program				*
; *-----------------------------------------------------*
fm_prd_ex:
		change	fm_prd_in
	fm_prd_ex_exit:
		ret

org	0130h
; *-----------------------------------------------------*
; *	flash memory => timer call external program			*
; *-----------------------------------------------------*
int_1b:
timer_ex:
		push	ie
		clr1	ie,7		;interrupt prohibition
		change	timer_in
	timer_ex_exit:
		callf	int_BaseTimer	;(User base timer interrupt processing)
		pop	ie
		reti

org	01f0h
; *-----------------------------------------------------*
_game_end:
		change	game_end
end
