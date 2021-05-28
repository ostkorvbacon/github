
/*Reader*/

  read_in(File,[W|Ws]) :- see(File), get0(C),
                          readword(C, W, C1), restsent(W, C1, Ws), nl, seen.
  /******************************************************************************/
  /* Given a word and the character after it, read in the rest of the sentence  */
  /******************************************************************************/

  restsent(W, _, [])         :- W = -1.
  /* added EOF handling */
  restsent(W, _, [])         :- lastword(W).
  restsent(_, C, [W1 | Ws ]) :- readword(C, W1, C1), restsent(W1, C1, Ws).

  /******************************************************************************/
  /* Read in a single word, given an initial character,                         */
  /* and remembering what character came after the word (NB!)                   */
  /******************************************************************************/

  readword(C, W, _)  :- C = -1, W = C.                    /* added EOF handling */
  readword(C, W, C1) :- single_character( C ), name(W, [C]), get0(C1).
  readword(C, W, C2) :-
     in_word(C, NewC ),
     get0(C1),
     restword(C1, Cs, C2),
     name(W, [NewC|Cs]).

  readword(_, W, C2) :- get0(C1), readword(C1, W, C2).

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
  single_character(46).                  /* . */
  single_character(59).                  /* ; */
  single_character(58).                  /* : */
  single_character(61).                  /* = */

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

/*Lexer*/
  lexer([ ], [ ]).
  lexer([H|T], [F|S]) :- match(H, F), lexer(T,S).


  match(L, F) :- L ='program', F is 256.
  match(L, F) :- L ='input', F is 257.
  match(L, F) :- L ='output', F is 258.
  match(L, F) :- L ='var', F is 259.
  match(L, F) :- L ='begin', F is 260.
  match(L, F) :- L ='end', F is 261.
  match(L, F) :- L ='boolean', F is 262.
  match(L, F) :- L ='integer', F is 263.
  match(L, F) :- L ='real', F is 264.
  match(L, F) :- L =':=', F is 271.


  match(L, F) :- L ='$', F is 49.
  match(L, F) :- L ='(', F is 40.
  match(L, F) :- L =')', F is 41.
  match(L, F) :- L ='*', F is 42.
  match(L, F) :- L ='+', F is 43.
  match(L, F) :- L =',', F is 44.
  match(L, F) :- L ='-', F is 45.
  match(L, F) :- L ='.', F is 46.
  match(L, F) :- L ='/', F is 47.
  match(L, F) :- L =':', F is 58.
  match(L, F) :- L =';', F is 59.
  match(L, F) :- L ='=', F is 60.

  match(L, F) :- name(L, [T|S]), char_type(T, alpha), match_alfanum(S), F is 269.
  match(L, F) :- name(L, [T|S]), char_type(T, digit), match_digit(S), F is 270.
  match(L, F) :- char_type(L, ascii), F is 272.
  match(L, F) :- char_type(L, end_of_file), F is 273.

  match_alfanum([ ]).
  match_alfanum([H|T]) :- char_type(H, alnum), match_alfanum(T).
  match_digit([ ]).
  match_digit([H|T]) :- char_type(H, digit), match_digit(T).


/*Parser*/
  parser(Tokens, Result) :- (prog(Tokens, Result), write('Parse OK!'), nl, Result = []);
  write('Parse Fail!'), nl.

  prog --> prog_header, var_part, stat_part.
  prog_header --> program, id, lp, input, comma, output, rp, scolon.

  var_part --> var, var_dec_lst.
  var_dec_lst --> var_dec | var_dec, var_dec_lst.
  var_dec --> id_lst, colon, type, scolon.
  id_lst --> id | id, comma, id_lst.
  type --> integer | boolean | real.

  stat_part     --> begin, stat_lst, end, fstop.
  stat_lst --> stat| stat, scolon, stat_lst.
  stat --> assign_stat.
  assign_stat --> id, assign, expr.
  expr --> term | term, plus, expr.
  term --> factor | factor, mult, term.
  factor --> lp, expr, rp | operand.
  operand --> id | numbr.

  lp -->  [40].       /*(*/
  rp -->  [41].       /*)*/
  mult -->  [42].     /***/
  plus -->  [43].     /*+*/
  comma -->  [44].    /*,*/
  fstop -->  [46].    /*.*/
  colon -->  [58].    /*:*/
  scolon -->  [59].   /*;*/
  program --> [256].
  input --> [257].
  output --> [258].
  var --> [259].
  begin --> [260].
  end --> [261].
  boolean --> [262].
  integer --> [263].
  real --> [264].
  id --> [269].
  numbr --> [270].
  assign --> [271].

/*start*/
  parseall:-
    tell('parser.out'),
    write('Testing OK programs '), nl, nl,
    parseFiles([
      'testfiles/testok1.pas', 'testfiles/testok2.pas', 'testfiles/testok3.pas',
      'testfiles/testok4.pas','testfiles/testok5.pas', 'testfiles/testok6.pas',
      'testfiles/testok7.pas']),
    write('Testing a-z programs '), nl, nl,
    parseFiles([
      'testfiles/testa.pas',
      'testfiles/testb.pas', 'testfiles/testc.pas', 'testfiles/testd.pas',
      'testfiles/teste.pas', 'testfiles/testf.pas', 'testfiles/testg.pas',
      'testfiles/testh.pas', 'testfiles/testi.pas', 'testfiles/testj.pas',
      'testfiles/testk.pas', 'testfiles/testl.pas', 'testfiles/testm.pas',
      'testfiles/testn.pas', 'testfiles/testo.pas', 'testfiles/testp.pas',
      'testfiles/testq.pas', 'testfiles/testr.pas', 'testfiles/tests.pas',
      'testfiles/testt.pas', 'testfiles/testu.pas', 'testfiles/testv.pas',
      'testfiles/testw.pas', 'testfiles/testx.pas', 'testfiles/testy.pas',
      'testfiles/testz.pas']),
    write('Testing fun programs '), nl, nl,
    parseFiles([
      'testfiles/fun1.pas', 'testfiles/fun2.pas', 'testfiles/fun3.pas',
      'testfiles/fun4.pas', 'testfiles/fun5.pas']),
    write('Testing sem programs '), nl, nl,
    parseFiles([
      'testfiles/sem1.pas', 'testfiles/sem2.pas', 'testfiles/sem3.pas',
      'testfiles/sem4.pas', 'testfiles/sem5.pas']),
    told.


  parseFiles([]).
  parseFiles([H|T]) :-
    write('Testing: '), write(H), nl,
    read_in(H,L),
    lexer(L, Tokens),
    parser(Tokens, []), write(L), nl, write(Tokens),
    nl, write(H), write(' end'), nl, nl,
    parseFiles(T).
