
#include "test.h"

void test(const string& name, string bit) {
    bit = trim(bit);

    stringstream tmp(to_double_hand(bit));

    Node node;
    tmp >> node.x;

    string bit_cs = bitset<64>(node.y).to_string();

    cout << "        测试类型: " << name << endl;
    cout << "    测试的二进制: " << to_bit(bit) << endl;
    cout << "    存储的二进制: " << to_bit(bit_cs) << endl;
    cout << "          手动值: " << to_double_hand(bit) << endl;
    cout << "          存储值: " << to_double_cs(bit_cs) << "(精确值)" << endl;
    cout << endl;
}

void test() {
    std::cout << "测试存储时的四舍六入五取偶" << std::endl << std::endl;

    std::cout << "        舍入方向: " << dict_round[fegetround()] << std::endl;

    test("测试 最后一位是 0, 多余位是 00(舍)",
         "0100001100110000000000000000000000000000000000000000000000000000 00");

    test("测试 最后一位是 0, 多余位是 01(舍)",
         "0100001100110000000000000000000000000000000000000000000000000000 01");

    test("测试 最后一位是 0, 多余位是 10(舍, 取偶)",
         "0100001100110000000000000000000000000000000000000000000000000000 10");

    test("测试 最后一位是 0, 多余位是 11(入)",
         "0100001100110000000000000000000000000000000000000000000000000000 11");

    test("测试 最后一位是 1, 多余位是 00(舍)",
         "0100001100110000000000000000000000000000000000000000000000000001 00");

    test("测试 最后一位是 1, 多余位是 01(舍)",
         "0100001100110000000000000000000000000000000000000000000000000001 01");

    test("测试 最后一位是 1, 多余位是 10(入, 取偶)",
         "0100001100110000000000000000000000000000000000000000000000000001 10");

    test("测试 最后一位是 1, 多余位是 11(入)",
         "0100001100110000000000000000000000000000000000000000000000000001 11");
}

int main() {
    init();
    test();
    return 0;
}
