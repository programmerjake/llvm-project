/* RUN: %clang_cc1 -verify -pedantic -std=c99 %s
   RUN: %clang_cc1 -verify=c89 -pedantic -std=c89 %s
   expected-no-diagnostics
 */

/* WG14 ???: Yes
 * Conversion of array to pointer not limited to lvalues
 *
 * NB: the original paper number is unknown, this was gleaned from the editor's report
 * in the C99 foreword. The C99 rationale document did not shed much light on
 * the situation either, mostly talking about user confusion between lvalue and
 * modifiable lvalue. However, the crux of the change was C89 changing:
 *
 * C89 3.2.2.1: Except when it is the operand of ..., an lvalue that has type
 * 'array of type' is converted to an expression that has type 'pointer to
 * type' that points to the initial element of the array object and is not an
 * lvalue.
 *
 * C99 6.3.2.1p3: Except when it is the operand of ..., an expression that has
 * type 'array of type' is converted to an expression with type 'pointer to
 * type' that points to the initial element of the array object and is not an
 * lvalue.
 */

struct S {
  char arr[100];
};

struct S f(void);

void func(void) {
  char c;
  /* The return from f() is an rvalue, so this code is not valid in C89, but is
   * valid in C99.
   */
  c = f().arr[10]; /* c89-warning {{ISO C90 does not allow subscripting non-lvalue array}} */
}

