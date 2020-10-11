// Programa de exemplo do simulador de Máquina Norma

// Comentários de linha começam com '//'

// Registradores são strings começando com 
// letras maiúsculas. Ex: X,Y,A,B,Abc,A1,B_2 ...

// Rótulos são strings começando com 
// números ou minúsculas. Ex: 1, 1a, ab1, a_2 ...

// Comandos disponíveis 
// inc R              (R:=R+1)
// dec R              (R:=R-1)
// add R n            (R:=R+n)
// sub R n            (R:=R-n)
// foo(R1,R2,...,Rn)  chamada de subrotina de operação

// Testes disponíveis 
// zero R             (R=0)
// cmp  R n           (R=n)
// foo(R1,R2,...,Rn)  chamada de subrotina de teste

// Definição de subrotina de operação:
// Rótulo inicial = rótulo da primeira instrução       (1 por convenção)
// Rótulo final   = referência a rótulo que não ocorre (0 por convenção)
// Parâmetros     = nomes de registradores, separados por vírgula

// Exemplo: A:=A+B usando C
operation soma(A,B,C){
  1: if zero B then goto 5 else goto 2
  2: do dec  B goto 3
  3: do inc  A goto 4
  4: do inc  C goto 1
  5: if zero C then goto 0 else goto 6
  6: do dec  C goto 7
  7: do inc  B goto 5
}

// Definição de subrotina de teste:
// Rótulo inicial = rótulo da primeira instrução       (1 por convenção)
// Rótulo final   = true ou false, obrigatoriamente
// Parâmetros     = nomes de registradores, separados por vírgula

// testa se A e B contém ambos o valor zero
test ambosZero(A,B) {
  1: if zero A then goto 2    else goto false
  2: if zero B then goto true else goto false
}

//-----------------------------------------------------------------

// limpa variável
operation clear(A){
 1: if zero A then goto 0 else goto 2
 2: do dec A goto 1
}

// A:=A+B (soma destrutiva)
operation soma(A,B){
  1: if zero B then goto 0 else goto 2
  2: do dec B goto 3
  3: do inc A goto 1
}

// A:=A+B (soma não-destrutiva)
operation soma(A,B,C){
  1: if zero B then goto 5 else goto 2
  2: do dec B goto 3
  3: do inc A goto 4
  4: do inc C goto 1
  5: if zero C then goto 0 else goto 6
  6: do dec C goto 7
  7: do inc B goto 5
}

// A:=B (atribuição destrutiva)
operation load(A,B){
  1: do clear(A) goto 2
  2: do soma(A,B) goto 0
}

// A:=B usando C (atribuição não-destrutiva)
operation load(A,B,C){
  1: do clear(A) goto 2
  2: do soma(A,B,C) goto 0
}

// A:=A div 2 usando C (divisão inteira por 2)
operation div2(A,C){
  1: do load(C,A) goto 2
  2: if zero C then goto 0 else goto 3
  3: do dec C goto 4
  4: if zero C then goto 0 else goto 5
  5: do dec C goto 6
  6: do inc A goto 2
}

// A divisivel_por_2 usando C (teste se multiplo de 2)
test divBy2(A,C){
  1: do load(C,A) goto 2
  2: if zero C then goto true else goto 3
  3: do dec C goto 4
  4: do inc A goto 5
  5: if zero C then goto false else goto 6
  6: do inc A goto 7
  7: do dec C goto 2
}

// A:=fst(B) usando C,D (extrai o primeiro componente do par)
operation fst(A,B,C,D){
  1: do clear(A) goto 2
  2: do load(C,B,D) goto 3
  3: if divBy2(C,D) then goto 4 else goto 6
  4: do div2(C,D) goto 5
  5: do inc A goto 3
  6: do clear(C) goto 0
}

// A:=A div 3 usando C (divisão inteira por 3)
operation div3(A,C){
  1: do load(C,A) goto 2
  2: if zero C then goto 0 else goto 3
  3: do dec C goto 4
  4: if zero C then goto 0 else goto 5
  5: do dec C goto 6
  6: if zero C then goto 0 else goto 7
  7: do dec C goto 8
  8: do inc A goto 2
}

// A divisivel_por_3 usando C (teste se múltiplo de 3)
test divBy3(A,C){
  1: do load(C,A) goto 2
  2: if zero C then goto true else goto 3
  3: do dec C goto 4
  4: do inc A goto 5
  5: if zero C then goto false else goto 6
  6: do inc A goto 7
  7: do dec C goto 8
  8: if zero C then goto false else goto 9
  9: do dec C goto 10
 10: do inc A goto 2
}

// A:=snd(B) usando C,D (extrai o segundo componente do par)
operation snd(A,B,C,D){
  1: do clear(A) goto 2
  2: do load(C,B,D) goto 3
  3: if divBy3(C,D) then goto 4 else goto 6
  4: do div3(C,D) goto 5
  5: do inc A goto 3
  6: do clear(C) goto 0
}

//-------------------------------------------------------------------------------------------------------

//A = A-B (nao destrutiva)
operation subtracao(A,B,C){
  1:if zero B then goto 5 else goto 2
  2:do dec B goto 3
  3:do dec A goto 4
  4:do inc C goto 1

  5:if zero C then goto 0 else goto 6
  6: do dec  C goto 7
  7: do inc  B goto 5
}


//A = A * X
operation multiplicacao(Nro,Mul){
   1:if zero Mul then goto 0 else goto 2
   2:do soma(Rmul,Nro,C) goto 3
   3:do dec Mul goto 1
}

//EXERCICIO 1 - contar digitos - FUNCIONA QUE OOOH, UMA BELEZA SEM TAMANHO
operation conta_digito(Numero){
   1:do add Base 10 goto 2
   2:do add Exp 1 goto 3
   3:do load(Cnumero, Numero, C) goto 4
   4:do sub Cnumero 9 goto 5
   5:do inc Y goto 6
   6:if zero Cnumero then goto 0 else goto 7
   7:do load(Cnumero,Numero,C) goto 8
   8:do multiplicacao(Base,Exp) goto 9
   9:do load(Exp, Rmul) goto 10
   10:do subtracao(Cnumero,Exp,C) goto 5
   
}

//Exercicio 2 - Fatorial --------- FUNCIONOU, OLHA ISSOOOOOOOOOOOOOOO----------------------
//Algumas regras basicas de fatorial a definir
//0! = 1 = 1!
//f(x) = x * (x-1)!; x > 1

test zeroum(Valor){
	1:do sub Valor 1 goto 2
    2:if zero Valor then goto true else goto false
}


operation fatorial(Numerofat){
	1:if zeroum(Numerofat) then goto 13 else goto 2
	2:do inc Numerofat goto 3
	3:do load(Var1,Numerofat,C) goto 4
	4:do dec Numerofat goto 5
	5:do multiplicacao(Numerofat,Var1) goto 6
	6:do load(Y,Rmul,C) goto 7
	7:do dec Numerofat goto 8
	8:if zero Numerofat then goto 0 else goto 9
	9:do load(Var1, Numerofat, C) goto 10
	10:do multiplicacao(Y,Var1) goto 11
	11:do dec Numerofat goto 8
		
    13:do inc Y goto 0
}

//Exercicio 4 - Seq de Fibonacci
//f(0) = 0; f(1) = 1; f(2) = 1; f(3) = 2; f(4) = 3 e f(5) = 5
//Valor do termo corrente sempre em J. Se J nao for exibido, entao J=0
test iguais(N1,N2){
  1:do load(Ax1,N1,C) goto 2
  2:do load(Ax2,N2,C) goto 3
  3:do subtracao(Ax1,Ax2,C) goto 4
  4:do load(T1,Ax1) goto 5
  5:do load(Ax1,N1,C) goto 6
  6:do subtracao(Ax2,Ax1,C) goto 7
  7:do load(T2,Ax2) goto 8
  8:if ambosZero(T1,T2) then goto true else goto false
}

operation fib(Termo){
  1:if zero Termo then goto 0 else goto 2
  2:do inc I goto 3
  3:do dec Y goto 6
  6:if iguais(K,Termo) then goto 0 else goto 7
  7:do soma(I,Y,C) goto 8
  8:do load(T,I) goto 9
  9:do load(I,Y) goto 10
  10:do load(Y,T) goto 11
  11:do inc K goto 6
}

//Exercicio 02 - Contar numero de 1's na conversão binária de X
//Exemplos: f(2) = 1, f(6) = 2, f(11) = 3 e f(15) = 4.

// A:=A div 2 e Aux_div:= A mod 2
operation div2_resto(Divide,C){
  1:do load(Resto, Divide,C) goto 2
  2: do load(C,Divide) goto 3
  3: if zero C then goto 8 else goto 4
  4: do dec C goto 5
  5: if zero C then goto 8 else goto 6
  6: do dec C goto 7
  7: do inc Divide goto 3
  8: do load(Quoc,Divide,C) goto 9
  9: do add Dois 2 goto 10
  10:do multiplicacao(Divide,Dois) goto 11
  11:do load(Aux_divisao2, Rmul) goto 12
  12:do subtracao(Resto,Aux_divisao2,C) goto 0
}

//Se true -> A <= B senão -> A > B 
test verifica_maior_igual(Valor1,Valor2){
	1:do load(Check_nro_a, Valor1,C) goto 2
	2:do load(Check_nro_b, Valor2, C) goto 3
	3:do dec Check_nro_b goto 4
	4:do dec Check_nro_a goto 5
	5:if zero Check_nro_b then goto 6 else goto 3
	6:if zero Check_nro_a then goto true else goto false
}

//Aqui começa a função conta_bit
//Retorno em Y ------ TA FUNFANDO KRLLLLLLL
operation conta_bit(Numero){
	1:if zero Numero then goto 0 else goto 2
	2:do add Dois_bit 2 goto 3
	3:if verifica_maior_igual(Numero,Dois_bit) then goto 12 else goto 4
	4:do div2_resto(Numero, C) goto 5
	5:if zero Resto then goto 7 else goto 6
	6:do soma(Y,Resto) goto 7
	7:if verifica_maior_igual (Quoc,Dois_bit) then goto 12 else goto 8
	8:do load(New_div,Quoc) goto 9
	9:do div2_resto(New_div,C) goto 10
	10:if zero Resto then goto 7 else goto 11
	11:do soma(Y,Resto) goto 7
	12:do inc Y goto 0
}

//Exercicio 5(e) - Contar assinaturas de um numero
//se x < 10, então a assinatura de x
// é o próprio x; se x ≥ 10, então a assinatura de x é igual à assinatura do número que
// resulta da soma dos dígitos que compõem x. Por exemplo, f(4) = 4, f(7) = 7,
// f(10) = f(1) = 1 e f(23499) = f(27) = f(9) = 9

test verifica_um(Numero){
	1:do load(V1,Numero,C) goto 2
	2:do dec V1 goto 3
	3:if zero V1 then goto true else goto false
}

//Se true -> A <= B senão -> A > B 
test verifica_menor_igual(Valor1,Valor2){
	1:do load(Check_nro_a, Valor1,C) goto 2
	2:do load(Check_nro_b, Valor2, C) goto 3
	3:do dec Check_nro_b goto 4
	4:do dec Check_nro_a goto 5
	5:if zero Check_nro_b then goto 6 else goto 3
	6:if zero Check_nro_a then goto true else goto false
}


//Multiplicacao nao destrutiva usando C
operation multiplicacao(Nro,Mul,C){
   1:do clear(Rmul) goto 2
   2:do load(C,Mul) goto 3
   3:if zero C then goto 0 else goto 4
   4:do soma(Rmul,Nro,D) goto 5
   5:do dec C goto 6
   6:do inc Mul goto 3
}

//Funcao auxiliar de potenciacao. Retorno em Potencia
operation potencia(Base,Expoente){
  1:do clear(Potencia) goto 2
  2:do add Potencia 1 goto 3
  3:do load (C_exp,Expoente,C) goto 4
  4:if zero C_exp then goto 0 else goto 5
  5:do multiplicacao(Potencia,Base,C) goto 6
  6:do load(Potencia,Rmul) goto 7
  7:do dec C_exp goto 4
}

//Se A>=B retorna true senao A<B retorna false
test menor_que(V1,V2){
	1:do load(Nro_a, Valor1,C) goto 2
	2:do load(Nro_b, Valor2, C) goto 3
	3:if zero Nro_a then goto 6 else goto 4
	4:do dec Nro_a goto 5
	5:do dec Nro_b goto 3
	6:if zero Nro_b then goto false else goto true
}


operation div_xy_resto(Dividendo, Divisor, C_div){
	1:do clear(T_div) goto 2
	2:if zero Divisor then goto 0 else goto 3
	3:if zero Dividendo then goto 0 else goto 4
	4:do load(C_div,Dividendo,C) goto 5
	5:do load(R_div, Dividendo) goto 6
	6:if zero C_div then goto 0 else goto 7
	7:do dec C_div goto 8
	8:do inc Dividendo goto 9
	9:do inc T_div goto 10
	10: if iguais (Divisor,T_div) then goto 11 else goto 6
	11:do inc Quoc goto 12
	12:do subtracao(R_div, Divisor, C) goto 13
	13:do clear (T_div) goto 6
}



//PARTE 2 DA DEF DO TRABALHO - Pares Ordenados

//2.b f(x,y) = x/y (retorne o quociente da divisao inteira de x por y)
//Por exemplo, f(5, 3) = 1, f(139, 24) = 5 e f(88, 0) = 0.
//Dois algoritmos de exemplo

//--------------------AQUI EU PARO A GAMBIARRA E TESTO ESSA PORCARIA
main{
	1:do add Numerador 5 goto 2
    2:do add Denominador 2 goto 3
	3:do div_xy_resto(Numerador,Denominador,C_div) goto 0
}