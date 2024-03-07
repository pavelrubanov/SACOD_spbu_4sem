#include "../src/libBigInt.h"
#include "../src/utils.h"
#include "minunit.h"

MU_TEST(str_tests)
{
    BigInt *a = read_from_str("1234");
    char *str = to_str(a);
    mu_assert_string_eq("1234", str);
    mu_check(a->sign == 1);
    mu_check(a->n == 4);

    a = read_from_str("-1234");
    str = to_str(a);
    mu_assert_string_eq("-1234", str);
    mu_check(a->sign == -1);
    mu_check(a->n == 4);

    BigInt_free(a);
}

MU_TEST(length_tests)
{
    size_t size_0 = 0;
    size_t size_1000 = 1000;

    BigInt *a = BigInt_init(size_0);
    BigInt *b = BigInt_init(size_1000);

    mu_check(a->n == 0);
    mu_check(b->n == 1000);

    BigInt_free(a);
    BigInt_free(b);
}

MU_TEST(normalize_tests)
{
    BigInt *a = read_from_str("0000123");
    normalize(a);
    mu_assert_int_eq(3, a->n);
    mu_assert_string_eq("123", to_str(a));

    a = read_from_str("-0000123");
    normalize(a);
    mu_assert_int_eq(3, a->n);
    mu_assert_string_eq("-123", to_str(a));

    BigInt_free(a);
}

MU_TEST(read_from_int_tests)
{
    BigInt *a;

    a = read_from_int(12345);
    mu_assert_string_eq("12345", to_str(a));
    mu_assert_int_eq(1, a->sign);

    a = read_from_int(-12345);
    mu_assert_string_eq("-12345", to_str(a));
    mu_assert_int_eq(-1, a->sign);

    a = read_from_int(0);
    mu_assert_string_eq("0", to_str(a));
    mu_assert_int_eq(0, a->sign);

    BigInt_free(a);
}

MU_TEST(to_int_tests)
{
    BigInt *a;

    a = read_from_str("12345");
    mu_assert_int_eq(12345, to_int(a));

    a = read_from_str("-12345");
    mu_assert_int_eq(-12345, to_int(a));

    a = read_from_str("0");
    mu_assert_int_eq(0, to_int(a));

    BigInt_free(a);
}

MU_TEST(sum_tests)
{
    BigInt *a = read_from_str("12345");
    BigInt *b = read_from_str("23456");

    const char *ans1 = "35801";
    BigInt *res = addition(a, b);

    mu_assert_int_eq(5, res->n);
    mu_assert_string_eq(ans1, to_str(res));

    a = read_from_str("-12345");
    b = read_from_str("-23456");

    const char *ans2 = "-35801";
    res = addition(a, b);

    mu_assert_int_eq(5, res->n);
    mu_assert_string_eq(ans2, to_str(res));

    a = read_from_str("12345");
    b = read_from_str("1");

    const char *ans3 = "12346";
    res = addition(a, b);

    mu_assert_int_eq(5, res->n);
    mu_assert_string_eq(ans3, to_str(res));

    a = read_from_str("-12345");
    b = read_from_str("-1");

    const char *ans4 = "-12346";
    res = addition(a, b);

    mu_assert_int_eq(5, res->n);
    mu_assert_string_eq(ans4, to_str(res));

    BigInt_free(a);
    BigInt_free(b);
    BigInt_free(res);
}

MU_TEST(sub_tests)
{
    BigInt *a = read_from_str("12345");
    BigInt *b = read_from_str("11111");

    BigInt *res = subtraction(a, b);
    mu_assert_string_eq("1234", to_str(res));

    a = read_from_str("12345");
    b = read_from_str("3456");

    res = subtraction(a, b);
    mu_assert_string_eq("8889", to_str(res));

    a = read_from_str("-12345");
    b = read_from_str("3456");

    res = subtraction(a, b);
    mu_assert_string_eq("-15801", to_str(res));

    a = read_from_str("3456");
    b = read_from_str("12345");

    mu_assert_int_eq(0, is_bigger(a, b));

    res = subtraction(a, b);

    mu_assert_string_eq("-8889", to_str(res));

    a = read_from_str("-12345");
    b = read_from_str("-3456");

    res = subtraction(a, b);
    mu_assert_string_eq("-8889", to_str(res));

    BigInt_free(a);
    BigInt_free(b);
    BigInt_free(res);
}

MU_TEST(mult_tests)
{
    BigInt *a, *b, *res;
    char *str_res;

    a = read_from_str("12345");
    b = read_from_str("123");
    res = multiplication(a, b);
    str_res = to_str(res);
    mu_assert_string_eq("1518435", str_res);

    a = read_from_str("-12345");
    b = read_from_str("123");
    res = multiplication(a, b);
    str_res = to_str(res);
    mu_assert_string_eq("-1518435", str_res);

    a = read_from_str("-12345");
    b = read_from_str("-123");
    res = multiplication(a, b);
    str_res = to_str(res);
    mu_assert_string_eq("1518435", str_res);

    a = read_from_str("999");
    b = read_from_str("999");
    res = multiplication(a, b);
    str_res = to_str(res);
    mu_assert_string_eq("998001", str_res);

    free(str_res);
    BigInt_free(a);
    BigInt_free(b);
    BigInt_free(res);
}

MU_TEST(div_by_2_tests)
{
    BigInt *a, *res;

    a = read_from_str("1234");
    res = div_by_2(a);
    mu_assert_string_eq("617", to_str(res));

    a = read_from_str("1235");
    res = div_by_2(a);
    mu_assert_string_eq("617", to_str(res));

    BigInt_free(a);
    BigInt_free(res);
}

MU_TEST(division_tests)
{
    BigInt *a, *b, *res;

    a = read_from_str("12345");
    b = read_from_str("11111");
    res = division(a, b);
    mu_assert_string_eq("1", to_str(res));

    a = read_from_str("12345678");
    b = read_from_str("123");
    res = division(a, b);
    mu_assert_string_eq("100371", to_str(res));

    a = read_from_str("-12345");
    b = read_from_str("11111");
    res = division(a, b);
    mu_assert_string_eq("-1", to_str(res));

    a = read_from_str("-12345");
    b = read_from_str("-11111");
    res = division(a, b);
    mu_assert_string_eq("1", to_str(res));

    BigInt_free(a);
    BigInt_free(b);
    BigInt_free(res);
}

static BigInt *factorial(const unsigned int n) 
{
  BigInt *resp, *tmp, *factor;
  unsigned int p;

  resp = read_from_int(1);

  if ((n == 0) || (n == 1)) 
  {
    return resp;
  }

  for (p = 2; p <= n; ++p) {
    factor = read_from_int(p);
    tmp = multiplication(resp, factor);
    BigInt_free(factor);
    BigInt_free(resp);
    resp = tmp;
  }

  return resp;
}

MU_TEST(factorial_tests)
{
    BigInt* myfact = factorial(1000);
    char* res = 
      "402387260077093773543702433923003985719374864210714632543799910429938512"
      "398629020592044208486969404800479988610197196058631666872994808558901323"
      "829669944590997424504087073759918823627727188732519779505950995276120874"
      "975462497043601418278094646496291056393887437886487337119181045825783647"
      "849977012476632889835955735432513185323958463075557409114262417474349347"
      "553428646576611667797396668820291207379143853719588249808126867838374559"
      "731746136085379534524221586593201928090878297308431392844403281231558611"
      "036976801357304216168747609675871348312025478589320767169132448426236131"
      "412508780208000261683151027341827977704784635868170164365024153691398281"
      "264810213092761244896359928705114964975419909342221566832572080821333186"
      "116811553615836546984046708975602900950537616475847728421889679646244945"
      "160765353408198901385442487984959953319101723355556602139450399736280750"
      "137837615307127761926849034352625200015888535147331611702103968175921510"
      "907788019393178114194545257223865541461062892187960223838971476088506276"
      "862967146674697562911234082439208160153780889893964518263243671616762179"
      "168909779911903754031274622289988005195444414282012187361745992642956581"
      "746628302955570299024324153181617210465832036786906117260158783520751516"
      "284225540265170483304226143974286933061690897968482590125458327168226458"
      "066526769958652682272807075781391858178889652208164348344825993266043367"
      "660176999612831860788386150279465955131156552036093988180612138558600301"
      "435694527224206344631797460594682573103790084024432438465657245014402821"
      "885252470935190620929023136493273497565513958720559654228749774011413346"
      "962715422845862377387538230483865688976461927383814900140767310446640259"
      "899490222221765904339901886018566526485061799702356193897017860040811889"
      "729918311021171229845901641921068884387121855646124960798722908519296819"
      "372388642614839657382291123125024186649353143970137428531926649875337218"
      "940694281434118520158014123344828015051399694290153483077644569099073152"
      "433278288269864602789864321139083506217095002597389863554277196742822248"
      "757586765752344220207573630569498825087968928162753848863396909959826280"
      "956121450994871701244516461260379029309120889086942028510640182154399457"
      "156805941872748998094254742173582401063677404595741785160829230135358081"
      "840096996372524230560855903700624271243416909004153690105933983835777939"
      "410970027753472000000000000000000000000000000000000000000000000000000000"
      "000000000000000000000000000000000000000000000000000000000000000000000000"
      "000000000000000000000000000000000000000000000000000000000000000000000000"
      "000000000000000000000000000000000000000000000000";

      mu_assert_string_eq(res, to_str(myfact));
}
int main()
{
    MU_RUN_TEST(str_tests);
    MU_RUN_TEST(length_tests);
    MU_RUN_TEST(normalize_tests);
    MU_RUN_TEST(read_from_int_tests);
    MU_RUN_TEST(to_int_tests);
    MU_RUN_TEST(sum_tests);
    MU_RUN_TEST(sub_tests);
    MU_RUN_TEST(mult_tests);
    MU_RUN_TEST(div_by_2_tests);
    MU_RUN_TEST(division_tests);
    MU_RUN_TEST(factorial_tests);

    MU_REPORT();

    return MU_EXIT_CODE;
}

void test(BigInt *a)
{
    printf("\nn: %ld\n", a->n);
    printf("sign: %d\n", a->sign);
    printf("strlen: %ld\n", strlen(a->digits));
    for (int i = 0; i < a->n; i++)
    {
        printf("%d ", a->digits[i]);
    }
    printf("\nto_str: %s\n", to_str(a));
}