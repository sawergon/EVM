//
// Created by Alex on 16.11.2023.
//

#ifndef STATICANALYZER_STATIC_ANALYZER_H_
#define STATICANALYZER_STATIC_ANALYZER_H_

/*
 * |------------------------------------------------|-----------------|---------------------|---------------------|
 * | грамматика                                     | перв            | след                | выбор               |
 * |------------------------------------------------|-----------------|---------------------|---------------------|
 * |  1. <S> ----------> <op><am op>                | {if, I, repeat} | not used            | {if, I, repeat}     |
 * |  2. <am op> ------> <op><am op>                | {if, I, repeat} | not used            | {if, I, repeat}     |
 * |  3. <am op> ------> E                          | {}              | {-|, else, until}   | {-|, else, until}   |
 * |  4. <op> ---------> if(<logic>)<am op><end if> | {if}            | not used            | {if}                |
 * |  5. <end if> -----> else<am op>                | {else}          | not used            | {else}              |
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
 * | <arith list> |  re  |  re  |  re  |   re   |    re    |   re    |  re  |  #10 |  re  |  re  |  re  |  #11 |  re  |  re  |  #11 |
 * |--------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | <T>          |  #12 |  #12 |  re  |   re   |    re    |   re    |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |  re  |
 * |--------------|------|------|------|--------|----------|---------|------|------|------|------|------|------|------|------|------|
 * | <T list>     |  re  |  re  |  re  |   re   |    re    |   re    |  #13 |  #14 |  re  |  re  |  re  |  #14 |  re  |  re  |  #14 |
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
 * */

#include "Analyzer.h"
#include "Stack.h"

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

#define AN_END_STACK 0

#define AN_COMMAND_ACCEPT (-2)
#define AN_COMMAND_REJECT (-3)
#define AN_COMMAND_KEEP (-4)
#define AN_COMMAND_NEXT (-5)

int analyze(char *source, int len_source);

int an_start_action(Stack &stack, lexeme lx);
int an_amount_operator_action(Stack &stack, lexeme lx);
int an_operator_action(Stack &stack, lexeme lx);
int an_end_if_action(Stack &stack, lexeme lx);
int an_arithmetic_action(Stack &stack, lexeme lx);
int an_arithmetic_list_action(Stack &stack, lexeme lx);
int an_arithmetic_end_action(Stack &stack, lexeme lx);
int an_arithmetic_end_list_action(Stack &stack, lexeme lx);
int an_f_action(Stack &stack, lexeme lx);
int an_logic_action(Stack &stack, lexeme lx);
int an_logic_list_action(Stack &stack, lexeme lx);
int an_left_action(Stack &stack, lexeme lx);
int an_right_action(Stack &stack, lexeme lx);
int an_break_action(Stack &stack, lexeme lx);
int an_set_action(Stack &stack, lexeme lx);
int an_until_action(Stack &stack, lexeme lx);
int an_end_stack_action(Stack &stack, lexeme lx);

int rule_1(Stack& stack);
int rule_2(Stack& stack);
int rule_3(Stack& stack);
int rule_4(Stack& stack);
int rule_5(Stack& stack);
int rule_6(Stack& stack);
int rule_7(Stack& stack);
int rule_8(Stack& stack);
int rule_9(Stack& stack);
int rule_10(Stack& stack);
int rule_11(Stack& stack);
int rule_12(Stack& stack);
int rule_13(Stack& stack);
int rule_14(Stack& stack);
int rule_15(Stack& stack);
int rule_16(Stack& stack);
int rule_17(Stack& stack);
int rule_18(Stack& stack);
int rule_19(Stack& stack);
int rule_20(Stack& stack);
int rule_21(Stack& stack);
int rule_22(Stack& stack);
int rule_23(Stack& stack);
int rule_24(Stack& stack);

#endif //STATICANALYZER_STATIC_ANALYZER_H_
