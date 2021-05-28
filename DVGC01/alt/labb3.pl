%Erik Svensson
%Reader

read_in(File,[W|Ws]) :- see(File), get0(C),
                        readword(C, W, C1), restsent(W, C1, Ws), nl, seen.

/******************************************************************************/
/* Given a word and the character after it, read in the rest of the sentence  */
/******************************************************************************/

restsent(W, _, [])         :- W = -1.                /* added EOF handling */
restsent(W, _, [])         :- lastword(W).
restsent(_, C, [W1 | Ws ]) :- readword(C, W1, C1), restsent(W1, C1, Ws).

/******************************************************************************/
/* Read in a single word, given an initial character,                         */
/* and remembering what character came after the word (NB!)                   */
/******************************************************************************/

readword(C, W, _)  :- C = -1, W = C.                    /* added EOF handling */

readword(C,W,C2) :- C=58, get0(C1), readaux1(C,W,C1,C2).
readword(C, W, C2) :- C<58, C>47, name(W, [C]), get0(C2).
readword(C, W, C1) :- single_character( C ), name(W, [C]), get0(C1).
readword(C, W, C2) :-
   in_word(C, NewC ),
   get0(C1),
   restword(C1, Cs, C2),
   name(W, [NewC|Cs]).

readword(_, W, C2) :- get0(C1), readword(C1, W, C2).

readaux1(C,W,C1,C2) :- C1 = 61, name(W,[C,C1]), get0(C2).

readaux1(C,W,C1,C2) :- C1 \= 61, name(W,[C]), C1=C2.

restword(C, [NewC|Cs], C2) :-
   in_word(C, NewC),
   get0(C1),
   restword(C1, Cs, C2).

restword(C, [ ], C).

/******************************************************************************/
/* These characters form words on their own                                   */
/******************************************************************************/

single_character(40).                  /* ( */
single_character(41).                  /* ) */
single_character(42).                  /* + */
single_character(43).                  /* * */
single_character(44).                  /* , */
single_character(59).                  /* ; */
single_character(58).                  /* : */
single_character(61).                  /* = */
single_character(46).                  /* . */
single_character(45).		               /* - */
/******************************************************************************/
/* These characters can appear within a word.                                 */
/* The second in_word clause converts character to lower case                 */
/******************************************************************************/

in_word(C, C) :- C>96, C<123.             /* a b ... z */
in_word(C, L) :- C>64, C<91, L is C+32.   /* A B ... Z */
in_word(C, C) :- C>47, C<58.              /* 1 2 ... 9 */

/******************************************************************************/
/* These words terminate a sentence                                           */
/******************************************************************************/
lastword('.').

%Lexer

lexer([],[]).
lexer([H|T],[I|J]) :- match(H,I),lexer(T,J).

match(H,T):- H ='program'  , T is 256.
match(H,T):- H = 'input'   , T is 257.
match(H,T):- H = 'output'  , T is 258.
match(H,T):- H = 'var'     , T is 259.
match(H,T):- H = 'integer' , T is 260.
match(H,T):- H = 'begin'   , T is 261.
match(H,T):- H = 'end'     , T is 262.
match(H,T):- H = 'boolean' , T is 263.
match(H,T):- H = 'real'    , T is 264.
match(H,T):- H = ':='      , T is 271.
match(H,T):- H = '('       , T is 40.
match(H,T):- H = ')'       , T is 41.
match(H,T):- H = '*'       , T is 42.
match(H,T):- H = '+'       , T is 43.
match(H,T):- H = ','       , T is 44.
match(H,T):- H = '.'       , T is 46.
match(H,T):- H = ':'       , T is 58.
match(H,T):- H = ';'       , T is 59.


match(L,T) :- name(L, [H|T2]), char_type(H, alpha), match_id(T2), T is 270.

match(L,T) :- name(L, [H|T2]), char_type(H,digit), match_num(T2), T is 272.

match(L,T) :-  char_type(L, end_of_file), T is 275.
match(L,T) :- char_type(L, ascii)  , T is 273.

match_id([]).
match_id([H|T]) :- char_type(H, alnum), match_id(T).

match_num([]).
match_num([H|T]) :- char_type(H,digit), match_num(T).

%Parser
prog       --> prog_head, var_part, stat_part.

%Program Header
prog_head     --> program, id, lpar, input, comma, output,rpar, scolon.

%Var part
var_part      --> var, var_dec_list.
var_dec_list  --> var_dec | var_dec, var_dec_list.
var_dec       --> id_list, colon, type, scolon.
id_list       --> id | id, comma, id_list.
type          --> integer | boolean | real.

%Stat part
stat_part     --> begin, stat_list, end,fstop.
stat_list     --> stat| stat, scolon,stat_list.
stat          --> assign_stat.
assign_stat   --> id,assign,expr.
expr          --> term | term, add, expr.
term          --> factor | factor, mult, term.
factor        --> lpar, expr, rpar | operand.
operand       --> id | number.

lpar    -->  [40].  % (
rpar    -->  [41].  % )
mult    -->  [42].  % *
add     -->  [43].  % +
comma   -->  [44].  % ,
fstop   -->  [46].  % .
colon   -->  [58].  % :
scolon  -->  [59].  % ;

program --> [256].  % program
input   --> [257].  % input
output  --> [258].  % output
var     --> [259].  % var
integer --> [260].  % integer
begin   --> [261].  % begin
end     --> [262].  % end
boolean --> [263].  % boolean
real    --> [264].  % real
id      --> [270].  % id

assign  --> [271].  % assign
number  --> [272].  % number


testall :- tell('tests.out'),
	write('Testing OK programs '), nl, nl,

  parseFiles(['testfiles/testok1.pas', 'testfiles/testok2.pas', 'testfiles/testok3.pas', 'testfiles/testok4.pas',

        'testfiles/testok5.pas', 'testfiles/testok6.pas', 'testfiles/testok7.pas']),

 write('Testing a-z programs '), nl, nl,

 parseFiles(['testfiles/testa.pas', 'testfiles/testb.pas', 'testfiles/testc.pas', 'testfiles/testd.pas', 'testfiles/teste.pas',

	     'testfiles/testf.pas', 'testfiles/testg.pas', 'testfiles/testh.pas', 'testfiles/testi.pas', 'testfiles/testj.pas',
	     'testfiles/testk.pas', 'testfiles/testl.pas', 'testfiles/testm.pas', 'testfiles/testn.pas', 'testfiles/testo.pas',
	     'testfiles/testp.pas', 'testfiles/testq.pas', 'testfiles/testr.pas', 'testfiles/tests.pas', 'testfiles/testt.pas',
		   'testfiles/testu.pas', 'testfiles/testv.pas', 'testfiles/testw.pas', 'testfiles/testx.pas', 'testfiles/testy.pas',
		   'testfiles/testz.pas']),

 write('Testing fun programs '), nl, nl,

 parseFiles(['testfiles/fun1.pas', 'testfiles/fun2.pas', 'testfiles/fun3.pas', 'testfiles/fun4.pas', 'testfiles/fun5.pas']),

 write('Testing sem programs '), nl, nl,

 parseFiles(['testfiles/sem2.pas', 'testfiles/sem3.pas', 'testfiles/sem4.pas', 'testfiles/sem5.pas']),told.
 testfun :- parseFiles(['testfiles/fun1.pas', 'testfiles/fun2.pas']).
 parseFiles([]).
 parseFiles([H|T]) :-  write('Testing '), write(H), nl,
                       read_in(H,L), lexer(L, Tokens),
                       write(L), nl, write(Tokens), nl,
                       parser(Tokens, []), nl,
                       write(H), write(' end of parse'), nl, nl,
                       parseFiles(T).

 parser(Tokens, Res) :- (prog(Tokens, Res), Res = [], write('Parse OK!'));
                         write('Parse Fail!').

/******************************************************************************/
/* End of program                                                             */
/******************************************************************************/
