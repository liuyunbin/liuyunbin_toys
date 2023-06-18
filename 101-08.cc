
#include "log.h"

void test(const std::string& name, double x) {
    Double d(x);
    std::cout << std::endl;
    std::cout << "          测试类型: " << name << std::endl;
    std::cout << "            二进制: " << d.bit << std::endl;
    std::cout << "        计算机存储: " << d.double_by_cs << std::endl;
    std::cout << "          手动计算: " << d.double_by_hand << std::endl;
}

void test(const std::string& name, double x, const std::string& bit) {
    Double d(bit);
    std::cout << std::endl;
    std::cout << "          测试类型: " << name << std::endl;
    std::cout << "            二进制: " << d.bit_by_cs << std::endl;
    std::cout << "        计算机存储: " << d.double_by_cs << std::endl;
    std::cout << "原浮点数(  二进制): " << d.bit_by_test << std::endl;
    std::cout << "原浮点数(手动计算): " << d.double_by_hand << std::endl;
}

int main() {
    double x;

    x = std::nextafter(0.1, std::numeric_limits<double>::lowest());
    test("0.1 的前一个数", x);

    x = 0.1;
    test("0.1", x);

    x = std::nextafter(0.1, std::numeric_limits<double>::max());
    test("0.1 的后一个数", x);

    test("0.1", 0.1,
         "0 01111111011 1001100110011001100110011001100110011001100110011010");

    test(
        "0.1 的下限(进, 含)",
        0.099999999999999998612221219218554324470460414886474609375,
        "0 01111111011 1001100110011001100110011001100110011001100110011001 1");

    test(
        "0.1 的上限(舍, 含)",
        0.100000000000000012490009027033011079765856266021728515625,
        "0 01111111011 1001100110011001100110011001100110011001100110011010 1");

    test("测试 4503599627370496", 4503599627370496,
         "0 10000110011 0000000000000000000000000000000000000000000000000000");

    test(
        "测试 4503599627370496 的下限(进, 含)", 4503599627370496,
        "0 10000110010 1111111111111111111111111111111111111111111111111111 1");

    test(
        "测试 4503599627370496 的上限(舍, 含)", 4503599627370496.5,
        "0 10000110011 0000000000000000000000000000000000000000000000000000 1");

    test("测试 4503599627370497", 4503599627370497,
         "0 10000110011 0000000000000000000000000000000000000000000000000001");

    test(
        "测试 4503599627370497 的下限(舍, 不含)", 4503599627370496.5,
        "0 10000110011 0000000000000000000000000000000000000000000000000000 1");

    test(
        "测试 4503599627370497 的上限(进, 不含)", 4503599627370497.5,
        "0 10000110011 0000000000000000000000000000000000000000000000000001 1");
    return 0;
}
