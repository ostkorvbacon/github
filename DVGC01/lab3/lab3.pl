
/*Reader*/

  read_in(File,[W|Ws]) :- see(File), get0(C),
                          readword(C, W, C1), restsent(W, C1, Ws), nl, seen,
                          write('In Reader'), nl.

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
  single_character(59).                  /* ; */
  single_character(58).                  /* : */
  single_character(61).                  /* = */
  single_character(46).                  /* . */

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
  lexer([H|T], [F|S]) :-match(H, F), lexer(T,S). 



/*Parser*/
  parser(Tokens, Result) :- write('in parser'), nl, format("~w~n", [Tokens]),
  program(Tokens, Result).
  program       --> prog_head, var_part, stat_part.

  /******************************************************************************/
  /* Program Header                                                             */
  /******************************************************************************/
  prog_head     --> [program], id, ['('], [input], [','], [output], [')'], [';'].
  id            --> [a]|[b]|[c].

  /******************************************************************************/
  /* Var_part                                                                   */
  /******************************************************************************/
  var_part             --> var_part_todo.
  var_part_todo(_,_)   :-  write('var_part:  To Be Done'), nl.

  /******************************************************************************/
  /* Stat part                                                                  */
  /******************************************************************************/
  stat_part            -->  stat_part_todo.
  stat_part_todo(_,_)  :-   write('stat_part: To Be Done'), nl.

/*tjafs*/
    /******************************************************************************/
    /* Testing the system: this may be done stepwise in Prolog                    */
    /* below are some examples of a "bottom-up" approach - start with simple      */
    /* tests and buid up until a whole program can be tested                      */
    /******************************************************************************/
    /* Stat part                                                                  */
    /******************************************************************************/
    /*  op(['+'], []).                                                            */
    /*  op(['-'], []).                                                            */
    /*  op(['*'], []).                                                            */
    /*  op(['/'], []).                                                            */
    /*  addop(['+'], []).                                                         */
    /*  addop(['-'], []).                                                         */
    /*  mulop(['*'], []).                                                         */
    /*  mulop(['/'], []).                                                         */
    /*  factor([a], []).                                                          */
    /*  factor(['(', a, ')'], []).                                                */
    /*  term([a], []).                                                            */
    /*  term([a, '*', a], []).                                                    */
    /*  expr([a], []).                                                            */
    /*  expr([a, '*', a], []).                                                    */
    /*  assign_stat([a, assign, b], []).                                          */
    /*  assign_stat([a, assign, b, '*', c], []).                                  */
    /*  stat([a, assign, b], []).                                                 */
    /*  stat([a, assign, b, '*', c], []).                                         */
    /*  stat_list([a, assign, b], []).                                            */
    /*  stat_list([a, assign, b, '*', c], []).                                    */
    /*  stat_list([a, assign, b, ';', a, assign, c], []).                         */
    /*  stat_list([a, assign, b, '*', c, ';', a, assign, b, '*', c], []).         */
    /*  stat_part([begin, a, assign, b, '*', c, end, '.'], []).                   */
    /******************************************************************************/
    /* Var part                                                                   */
    /******************************************************************************/
    /* typ([integer], []).                                                        */
    /* typ([real], []).                                                           */
    /* typ([boolean], []).                                                        */
    /* id([a], []).                                                               */
    /* id([b], []).                                                               */
    /* id([c], []).                                                               */
    /* id_list([a], []).                                                          */
    /* id_list([a, ',', b], []).                                                  */
    /* id_list([a, ',', b, ',', c], []).                                          */
    /* var_dec([a, ':', integer], []).                                            */
    /* var_dec_list([a, ':', integer], []).                                       */
    /* var_dec_list([a, ':', integer, b, ':', real], []).                         */
    /* var_part([var, a, ':', integer], []).                                      */
    /******************************************************************************/
/*start*/

testa :- parseFiles(['testok1.pas','testok2.pas','testok3.pas']).
  parseFiles([]).
  parseFiles([H|T]) :-
    write('Testing: '), write(H), nl,
    read_in(H,L), format("~w~n", [L]),
    lexer(L, Tokens),
    parser(Tokens, Result),
    nl, write(H), write(' end'), nl, nl,
    parseFiles(T).
