  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #
  .data
  
  .global hexasc, delay,time2string
  
  .text
  
 hexasc: 
	andi $a0, $a0, 0xf
	addi $t1, $zero, 10
	slt $t0, $a0, $t1
	beq $t0, $zero, bokstav
	nop
	
	addi $v0, $a0, 48
	
	jr $ra
	nop
bokstav:
	addi $v0, $a0, 55
	
	jr $ra
	nop

delay: 
	addi $t0, $0, 0 	#integer i t0
	slt $t1, $t0, $a0	# if a0 (ms) störreän t0 then = while loop condition
	beq $t1, $t0, end
	nop
	
	then: 
	sub $a0, $a0, 1	
	
	loop:
	slti  $t1, $t0, 4711 #konstant
	beq $t1, $0, delay
	addi $t0 , $t0, 1
	j loop
	nop
	

end: 
	jr $ra
	nop
	
time2string:  
PUSH $ra
	#suprise check 
	andi $t0, $a1, 0xff
	beq $t0, $0, DING
	nop
	
	#kod block nr1 för första minut nibble närmast msb
		
	PUSH $a0 #minnes adressen skickas till stacken
	srl $a0,  $a1, 12 #de fyra valda minut bitarna läggs på lsb sidan och sparas i a0 som ska skickas till hexasc
	jal hexasc #jump link to hexaasc för att få sifran i ascii
	nop
	move $t0 , $v0 #värdet från hexasc spars i t0 
	POP $a0 # addressen hämtas från stacken
	sb $t0, 0($a0) #minut värdet i ascii sparas på a0 första addresen 
	
	#kod block nr2 för andra minut nibble närmast msb	
	
	PUSH $a0 #minnes adressen skickas till stacken
	srl $a0,  $a1, 8 #de fyra valda minut bitarna läggs på lsb sidan och sparas i a0 som ska skickas till hexasc
	andi $a0, $a0,0x0000000f #maskerar de sista 4 bitarna för allt annat tillhör inte den här minuten
	jal hexasc #jump link to hexaasc för att få sifran i ascii
	nop
	move $t0 , $v0 #värdet från hexasc spars i t0 
	POP $a0 # addressen hämtas från stacken
	sb $t0, 1($a0) #minut värdet i ascii sparas på a0 andra addresen
	
	#kod block nr3 för semikolon
	li $t0, 0x0000003a # Load :
	sb $t0, 2($a0) #sparar : i tredje adressen
	
	#kod block nr4 för första sekund nibble närmast msb
	
	PUSH $a0 #minnes adressen skickas till stacken
	srl $a0,  $a1, 4 #de fyra valda sekund bitarna läggs på lsb sidan och sparas i a0 som ska skickas till hexasc
	andi $a0, $a0,0x0000000f #maskerar de sista 4 bitarna för allt annat tillhör inte den här sekunden
	jal hexasc #jump link to hexaasc för att få sifran i ascii
	nop
	move $t0 , $v0 #värdet från hexasc spars i t0 
	POP $a0 # addressen hämtas från stacken
	sb $t0, 3($a0) #sekund värdet i ascii sparas på a0 4 addresen
	
	#kod block nr5 för sista sekund nibble närmast msb
	
	PUSH $a0 #minnes adressen skickas till stacken
	andi $a0, $a1,0x0000000f #maskerar och flyttar in de sista 4 bitarna i a0 för allt annat tillhör inte den här sekunden
	jal hexasc #jump link to hexaasc för att få sifran i ascii
	nop
	move $t0 , $v0 #värdet från hexasc spars i t0 
	POP $a0  #addressen hämtas från stacken
	sb $t0, 4($a0) #sekund värdet i ascii sparas på a0 4 addresen

	#sista kod blocket för att lägga in en NULL byte på 5 addressen
	li $t0, 0x00 # Load Null
	sb $t0, 5($a0) #sparar : i 5 adressen
			
POP $ra

jr $ra
nop

DING:	
	li $t0, 0x44
	sb $t0, 0($a0)
	
	li $t0, 0x49
	sb $t0, 1($a0)
	
	li $t0, 0x4E
	sb $t0, 2($a0)
	
	li $t0, 0x47
	sb $t0, 3($a0)
	
	li $t0, 0x00
	sb $t0, 4($a0)
	
POP $ra

jr $ra
nop

	
