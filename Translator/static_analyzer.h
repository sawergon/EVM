//
// Created by Alex on 16.11.2023.
//

#ifndef STATICANALYZER_STATIC_ANALYZER_H_
#define STATICANALYZER_STATIC_ANALYZER_H_

/*
 *
 *
 *
 * |------------------------------------------------|-----------------|---------------------|---------------------|
 * | грамматика                                     | перв            | след                | выбор               |
 * |------------------------------------------------|-----------------|---------------------|---------------------|
 * |  1. <S> ----------> <op><am op>                | {if, I, repeat} | not used            | {if, I, repeat}     |
 * |  2. <am op> ------> <op><am op>                | {if, I, repeat} | not used            | {if, I, repeat}     |
 * |  3. <am op> ------> E                          | {}              | {-|, else, until}   | {-|, else, until}   |
 * |  4. <op> ---------> if(<logic>)<am op><end if> | {if}            | not used            | {if}                |
 * |  5. <end if> -----> else<op>                   | {else}          | not used            | {else}              |
 * |  6. <end if> -----> E                          | {}              | {-|, if, I, repeat} | {-|, if, I, repeat} |
 * |  7. <op> ---------> I:=<arith>;                | {I}             | not used            | {I}                 |
 * |  8. <op> ---------> repeat<am op>until<logic>; | {repeat}        | not used            | {repeat}            |
 * |  9. <arith> ------> <T><arith list>            | {I, N}          | not used            | {I, N}              |
 * | 10. <arith list> -> +<T><arith list>           | {+}             | not used            | {+}                 |
 * | 11. <arith list> -> E                          | {}              | {-|, ;}             | {-|, ;}             |
 * | 12. <T> ----------> <F><T list>                | {I, N}          | not used            | {I, N}              |
 * | 13. <T list>------> *<F><T list>               | {*}             | not used            | {*}                 |
 * | 14. <T list> -----> E                          | {}              | {-|, +, ;}          | {-|, +, ;}          |
 * | 15. <F> ----------> I                          | {I}             | not used            | {I}                 |
 * | 16. <F> ----------> N                          | {N}             | not used            | {N}                 |
 * | 17. <logic> ------> <F><logic list>            | {I, N}          | not used            | {I, N}              |
 * | 18. <logic list> -> =<F>                       | {=}             | not used            | {=}                 |
 * | 19. <logic list> -> !=<F>                      | {!=}            | not used            | {!=}                |
 * |------------------------------------------------|-----------------|---------------------|---------------------|
 *
 * множества выбора с одинаковыми левыми частями попарно не пересекаются
 *
 * |--------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * |              |  I   |   N  |  if  |  else  |  repeat  |  until  |   *  |   +  |   =  |  !=  |  :=  |  -|  |  (   |  )   |  ;   |
 * |--------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | <S>          |  #1  |  re  |  #1  |   re   |    #1    |   re    |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |
 * |--------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | <am op>      |  #2  |  re  |  #2  |   #3   |    #2    |   #3    |  re  |  re  |  re  |  re  |  re  |  #3  |  re  |  re  |  re  |
 * |--------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | <op>         |  #7  |  re  |  #4  |   re   |    #8    |   re    |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |
 * |--------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | <end if>     |  #6  |  re  |  #6  |   #5   |    #6    |   re    |  re  |  re  |  re  |  re  |  re  |  #6  |  re  |  re  |  re  |
 * |--------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | <arith>      |  #9  |  #9  |  re  |   re   |    re    |   re    |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |
 * |--------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | <arith list> |  re  |  re  |  re  |   re   |    re    |   re    |  re  |  #10 |  re  |  re  |  re  |  re  |  re  |  re  |  #11 |
 * |--------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | <T>          |  #12 |  #12 |  re  |   re   |    re    |   re    |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |
 * |--------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | <T list>     |  re  |  re  |  re  |   re   |    re    |   re    |  #13 |  #14 |  re  |  re  |  re  |  re |  re  |  re  |  #14 |
 * |--------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | <F>          |  #15 |  #16 |  re  |   re   |    re    |   re    |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |
 * |--------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | <logic>      |  #17 |  #17 |  re  |   re   |    re    |   re    |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |
 * |--------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | <logic list> |  re  |  re  |  re  |   re   |    re    |   re    |  re  |  re  |  #18 |  #19 |  re  |  re  |  re  |  re  |  re  |
 * |--------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * |  (           |  re  |  re  |  re  |   re   |    re    |   re    |  re  |  re  |  re  |  re  |  re  |  re  |  #20 |  re  |  re  |
 * |--------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * |  )           |  re  |  re  |  re  |   re   |    re    |   re    |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  #21 |  re  |
 * |--------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * |  ;           |  re  |  re  |  re  |   re   |    re    |   re    |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  #22 |
 * |--------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * |  :=          |  re  |  re  |  re  |   re   |    re    |   re    |  re  |  re  |  re  |  re  | #23  |  re  |  re  |  re  |  re  |
 * |--------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * |  until       |  re  |  re  |  re  |   re   |    re    |   #24   |  re  |  re  |  re  |  re  | re   |  re  |  re  |  re  |  re  |
 * |--------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | delta        |  re  |  re  |  re  |   re   |    re    |   re    |  re  |  re  |  re  |  re  |  re  | asse |  re  |  re  |  re  |
 * |--------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 *
 *
 * #01 Зам(<op><am op>), Держать
 * #02 Зам(<op><am op>), Держать
 * #03 Вытолкнуть, Держать
 * #04 Зам((<logic>)<am op><end if>), Сдвиг
 * #05 Зам(<am op>), Сдвиг
 * #06 Вытолкнуть, Держать
 * #07 Зам(:=<arith>;), Сдвиг
 * #08 Зам(<am op>until<logic>;), Сдвиг
 * #09 Зам(<T><arith list>), Держать
 * #10 Зам(<T><arith list>), Сдвиг
 * #11 Вытолкнуть, Держать
 * #12 Зам(<F><T list>), Держать
 * #13 Зам(<F><T list>), Сдвиг
 * #14 Вытолкнуть, Держать
 * #15 Вытолкнуть, Сдвиг
 * #16 Вытолкнуть, Сдвиг
 * #17 Зам(<F><logic list>), Держать
 * #18 Зам(<F>;), Сдвиг
 * #19 Зам(<F>;), Сдвиг
 * #20 Вытолкнуть, Сдвиг
 * #21 Вытолкнуть, Сдвиг
 * #22 Вытолкнуть, Сдвиг
 * #23 Вытолкнуть, Сдвиг
 * #24 Вытолкнуть, Сдвиг
 *
 * | Транслирующая грамматика
 * |---------------------------------------------------------------------------|
 * |  1. <S> ----------> <op><am op>
 * |  2. <am op> ------> <op><am op>
 * |  3. <am op> ------> E
 * |  4. <op> ---------> if(<logic>{cond. go to 0})<am op><end if>
 * |  5. <end if> -----> else{non cond. go to}{label}<am op>{label}
 * |  6. <end if> -----> {label}
 * |  7. <op> ---------> I:=<arith>{set};
 * |  8. <op> ---------> repeat{label}<am op>until<logic>{comp. go to};
 * |  9. <arith> ------> <T><arith list>
 * | 10. <arith list> -> +<T>{sum}<arith list>
 * | 11. <arith list> -> E
 * | 12. <T> ----------> <F><T list>
 * | 13. <T list>------> *<F>{mul}<T list>
 * | 14. <T list> -----> E
 * | 15. <F> ----------> I
 * | 16. <F> ----------> N
 * | 17. <logic> ------> <F><logic list>
 * | 18. <logic list> -> =<F>{eq}
 * | 19. <logic list> -> !=<F>{ne}
 * |
 * | Атрибутная транслирующая грамматика
 * |--------------------------------------------------------------------------|
 * |  1. <S> ----------> <op><am op>
 * |  2. <am op> ------> <op><am op>
 * |  3. <am op> ------> E
 * |  4. <op> ---------> if(<logic>_p1{cond. go to 0 -p2,z1})<am op><end if>_z2
 * |  (z1, z2) <- NewL, p2 <- p1
 * |  5. <end if_z1> -----> else{non cond. go to w1}{label z2}<am op>{label w2}
 * |  z2 <- z1, (w1, w2) <- NewL
 * |  6. <end if_z1> -----> {label z2}
 * |  z2 <- z1
 * |  7. <op> ---------> I_p1:=<arith>_p2{set q1, q2};
 * |  q1 <- p1, q2 <- p2
 * |  8. <op> ---------> repeat{label z1}<am op>until<logic p1>{comp. go to p2 w1};
 * |  (z1, w1) <- NewL, p2 <- p1
 * |  9. <arith>_r1 ------> <T>_p1<arith list>_q1_q2
 * |  r1 <- q1, p1 <- q2
 * | 10. <arith list>_r1_p1 -> +<T>_p2{sum q1, q2, r2}<arith list>_r3_p3
 * |  r1 <- r3, r2 <- New, q1 <- p1, q2 <- p2, p3 <- r2
 * | 11. <arith list>_r1_p1 -> E
 * |  r1 <- p1
 * | 12. <T>_r1 ----------> <F>_p1<T list>_r2_p2
 * |  r1 <- r2, p2 <- p1
 * | 13. <T list>_r1_p1------> *<F>_p2{mul q1, q2, r2}<T list>_r3_p3
 * |  r1 <- r3, r2 <- New, q1 <- p1, q2 <- p2, p3 <- r2
 * | 14. <T list>_r1_p1 -----> E
 * |  r1 <- p1
 * | 15. <F>_p1 ----------> I_p2
 * | p1 <- p2
 * | 16. <F>_p1 ----------> N_p2
 * | p1 <- p2
 * | 17. <logic_t2> ------> <F>_p1<logic list>_p2_t1
 * |  p2 <- p1, t2<-t1
 * | 18. <logic list>_p1_t2 -> =<F>_q1{eq p2, q2, t1}
 * |  (t1, t2) <- New, p2 <- p1, q2 <- q1
 * | 19. <logic list_p1_t2> -> !=<F>_q1{ne p2, q2, t1}
 * |  (t1, t2) <- New, p2 <- p1, q2 <- q1
 * a:=1;repeat a:=a+1;until a!=4;
 *
 *             |---------|                  |---------|
 * |-----|     |  <op>   |   |---------|    |  <op>   |
 * | <S> | ->  |---------|   | <am op> | -> |---------| || E
 * |-----|     | <am op> |   |---------|    | <am op> |
 *             |---------|                  |---------|
 *
 *
 *             |-----------------|               |----------|      |---------|
 *             |       (         |               | <end if> |      | {label} |
 *             |-----------------|               |__________|  ->  |_________|
 *             |    <logic>      |               |    z     |      |    z    | z2
 *             |_________________|               |----------|      |---------|
 *             |       p1        | ------|
 *             |-----------------|       |
 *             | {cond. go to 0} |       |                         |-------------------|
 *             |_________________|       |                         |       else        |
 * |------|    |       p2        | <-----|                         |-------------------|
 * | <op> | -> |_________________|                   w <- New      | {non cond. go to} |
 * |------|    |       z         | z1                              |___________________|
 *             |-----------------|     z <- New                    |         w         | w1
 *             |       )         |               |----------|      |-------------------|
 *             |-----------------|               | <end if> |      |      {label}      |
 *             |     <am op>     |               |__________|  ->  |___________________|
 *             |-----------------|               |    z     |      |         z         | z2
 *             |    <end if>     |               |----------|      |-------------------|
 *             |_________________|                                 |      <am op>      |
 *             |      z          | z2                              |-------------------|
 *             |-----------------|                                 |      {label}      |
 *                                                                 |___________________|
 *                                                                 |         w         | w2
 *                                                                 |-------------------|
 *
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * |                   |  I   |   N  |  if  |  else  |  repeat  |  until  |   *  |   +  |   =  |  !=  |  :=  |  -|  |  (   |  )   |  ;   |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | <S>               |  #1  |  re  |  #1  |   re   |    #1    |   re    |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | <am op>           |  #2  |  re  |  #2  |   #3   |    #2    |   #3    |  re  |  re  |  re  |  re  |  re  |  #3  |  re  |  re  |  re  |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | <op>              |  #7  |  re  |  #4  |   re   |    #8    |   re    |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | <end if>          |  #6  |  re  |  #6  |   #5   |    #6    |   re    |  re  |  re  |  re  |  re  |  re  |  #6  |  re  |  re  |  re  |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | <arith>           |  #9  |  #9  |  re  |   re   |    re    |   re    |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | <arith list>      |  re  |  re  |  re  |   re   |    re    |   re    |  re  |  #10 |  re  |  re  |  re  |  #11 |  re  |  re  |  #11 |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | <T>               |  #12 |  #12 |  re  |   re   |    re    |   re    |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | <T list>          |  re  |  re  |  re  |   re   |    re    |   re    |  #13 |  #14 |  re  |  re  |  re  |  #14 |  re  |  re  |  #14 |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | <F>               |  #15 |  #16 |  re  |   re   |    re    |   re    |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | <logic>           |  #17 |  #17 |  re  |   re   |    re    |   re    |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | <logic list>      |  re  |  re  |  re  |   re   |    re    |   re    |  re  |  re  |  #18 |  #19 |  re  |  re  |  re  |  re  |  re  |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * |  (                |  re  |  re  |  re  |   re   |    re    |   re    |  re  |  re  |  re  |  re  |  re  |  re  |  #20 |  re  |  re  |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * |  )                |  re  |  re  |  re  |   re   |    re    |   re    |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  #21 |  re  |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * |  ;                |  re  |  re  |  re  |   re   |    re    |   re    |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  #22 |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * |  :=               |  re  |  re  |  re  |   re   |    re    |   re    |  re  |  re  |  re  |  re  | #23  |  re  |  re  |  re  |  re  |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * |  until            |  re  |  re  |  re  |   re   |    re    |   #24   |  re  |  re  |  re  |  re  | re   |  re  |  re  |  re  |  re  |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | delta             |  re  |  re  |  re  |   re   |    re    |   re    |  re  |  re  |  re  |  re  |  re  | asse |  re  |  re  |  re  |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | {set}             |          Вытолкнуть, Держать, Выдать команду(set)                                                               |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | {sum}             |          Вытолкнуть, Держать, Выдать команду(sum)                                                               |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | {mul}             |          Вытолкнуть, Держать, Выдать команду(mul)                                                               |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | {eq}              |          Вытолкнуть, Держать, Выдать команду(eq)                                                                |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | {ne}              |          Вытолкнуть, Держать, Выдать команду(ne)                                                                |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | {cond. go to 0}   |          Вытолкнуть, Держать, Выдать команду(cond. go to 0)                                                     |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | {comp. go to}     |          Вытолкнуть, Держать, Выдать команду(cond. go to)                                                       |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | {non cond. go to} |          Вытолкнуть, Держать, Выдать команду(non cond. go to)                                                   |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | {label}           |          Вытолкнуть, Держать                                                                                    |
 * |-------------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 *
 * #01 Зам(<op><am op>), Держать
 * #02 Зам(<op><am op>), Держать
 * #03 Вытолкнуть, Держать
 * #04 Зам((<logic>{cond. go to 0})<am op><end if>), Сдвиг
 * #05 Зам({non cond. go to}{label}<am op>{label}), Сдвиг
 * #06 Зам({label}), Держать
 * #07 Зам(I:=<arith>{set};), Сдвиг
 * #08 Зам({label}<am op>until<logic>{comp. go to};), Сдвиг
 * #09 Зам(<T><arith list>), Держать
 * #10 Зам(<T>{sum}<arith list>), Сдвиг
 * #11 Вытолкнуть, Держать
 * #12 Зам(<F><T list>), Держать
 * #13 Зам(<F>{mul}<T list>), Сдвиг
 * #14 Вытолкнуть, Держать
 * #15 Вытолкнуть, Сдвиг
 * #16 Вытолкнуть, Сдвиг
 * #17 Зам(<F><logic list>), Держать
 * #18 Зам(<F>{eq}), Сдвиг
 * #19 Зам(<F>{ne}), Сдвиг
 * #20 Вытолкнуть, Сдвиг
 * #21 Вытолкнуть, Сдвиг
 * #22 Вытолкнуть, Сдвиг
 * #23 Вытолкнуть, Сдвиг
 * #24 Вытолкнуть, Сдвиг
 * */

#include "Analyzer.h"
#include "Stack.h"
#include <cstring>
//#include "avlTree.h"

#define AN_START 1
#define AN_OPERATOR 2
#define AN_AMOUNT_OPERATOR 3
#define AN_SET 5
#define AN_END_IF 7
#define AN_ARITHMETIC 8
#define AN_ARITHMETIC_LIST 9
#define AN_ARITHMETIC_END 10
#define AN_ARITHMETIC_END_LIST 11
#define AN_LOGIC 12
#define AN_LOGIC_LIST 13
#define AN_F 14
#define AN_LEFT 15
#define AN_RIGHT 16
#define AN_BREAK 17
#define AN_UNTIL 18

#define AN_C_SET 19
#define AN_C_SUM 20
#define AN_C_MUL 21
#define AN_C_COND_GO_TO_0 22
#define AN_C_COMP_GO_TO 23
#define AN_C_NON_COND_GO_TO 24
#define AN_C_LABEL 25
#define AN_C_EQ 26
#define AN_C_NE 27

#define AN_C_LEN_SET 2
#define AN_C_LEN_SUM 3
#define AN_C_LEN_MUL 3
#define AN_C_LEN_COND_GO_TO_0 2
#define AN_C_LEN_COMP_GO_TO 2
#define AN_C_LEN_NON_COND_GO_TO 1
#define AN_C_LEN_LABEL 1
#define AN_C_LEN_EQ 3
#define AN_C_LEN_NE 3

#define AN_END_STACK 0

#define AN_COMMAND_ACCEPT (-2)
#define AN_COMMAND_REJECT (-3)
#define AN_COMMAND_KEEP (-4)
#define AN_COMMAND_NEXT (-5)

#define SIZE_FIELD 1000
namespace global {
extern int data_end, command_end, label_end;
extern int data_field[SIZE_FIELD], command_field[SIZE_FIELD], label_table[SIZE_FIELD];

extern node *var_table;
}

int translator(char *source, int len_source);

int analyze(char *source, int len_source);

int an_start_action(Stack &stack, lexeme &lx);
int an_amount_operator_action(Stack &stack, lexeme &lx);
int an_operator_action(Stack &stack, lexeme &lx);
int an_end_if_action(Stack &stack, lexeme &lx);
int an_arithmetic_action(Stack &stack, lexeme &lx);
int an_arithmetic_list_action(Stack &stack, lexeme &lx);
int an_arithmetic_end_action(Stack &stack, lexeme &lx);
int an_arithmetic_end_list_action(Stack &stack, lexeme &lx);
int an_f_action(Stack &stack, lexeme &lx);
int an_logic_action(Stack &stack, lexeme &lx);
int an_logic_list_action(Stack &stack, lexeme &lx);
int an_left_action(Stack &stack, lexeme &lx);
int an_right_action(Stack &stack, lexeme &lx);
int an_break_action(Stack &stack, lexeme &lx);
int an_set_action(Stack &stack, lexeme &lx);
int an_until_action(Stack &stack, lexeme &lx);
int an_end_stack_action(Stack &stack, lexeme &lx);
int an_make_set_action(Stack &stack, lexeme &lx);
int an_make_sum_action(Stack &stack, lexeme &lx);
int an_make_mul_action(Stack &stack, lexeme &lx);
int an_make_eq_action(Stack &stack, lexeme &lx);
int an_make_ne_action(Stack &stack, lexeme &lx);
int an_make_label_action(Stack &stack, lexeme &lx);
int an_make_cond_go_to_0_action(Stack &stack, lexeme &lx);
int an_make_non_cond_go_to_action(Stack &stack, lexeme &lx);
int an_make_comp_go_to_action(Stack &stack, lexeme &lx);

int rule_1(Stack &stack);
int rule_2(Stack &stack);
int rule_3(Stack &stack);
int rule_4(Stack &stack);
int rule_5(Stack &stack);
int rule_6(Stack &stack);
int rule_7(Stack &stack, int var);
int rule_8(Stack &stack);
int rule_9(Stack &stack, lexeme &lx);
int rule_10(Stack &stack);
int rule_11(Stack &stack);
int rule_12(Stack &stack);
int rule_13(Stack &stack);
int rule_14(Stack &stack);
int rule_15(Stack &stack, lexeme &lx);
int rule_16(Stack &stack, lexeme &lx);
int rule_17(Stack &stack);
int rule_18(Stack &stack);
int rule_19(Stack &stack);
int rule_20(Stack &stack);
int rule_21(Stack &stack);
int rule_22(Stack &stack);
int rule_23(Stack &stack);
int rule_24(Stack &stack);

int new_data();
int new_label();
void set_label(int label, int pos);
int get_label(int label);

#endif //STATICANALYZER_STATIC_ANALYZER_H_
