/*
* 名称: 类测试3
* 
* 收获: 
* 1、静态成员相当于与所有对象独立，但所有对象都可以调用它
* 2、静态成员函数也独立于所有对象，因此没有this指针，静态成员函数只可以调用静态的成员和函数，
*   但是它有特权可以直接调用外部的函数!
* 3、对于this指针，真的就是如其名，就是这个对象自己的指针，所以有 this == &对象名
*/

#include <iostream>
#define DEBUG
#ifdef DEBUG
std::string debug_str;
#endif // DEBUG


class Line_class
{
public:
    int bigger(Line_class temp);
    Line_class* get_this_address(void);

    Line_class(double len);

    static int test_static_fun(void);

    double length;
// private:         //注释掉会报错，说明访问修饰符对它也是有效的
    static int object_count;
};
int Line_class::object_count = 0;
void exterior_fun(void);

void this_test(void);
void class_pointer_test(void);
void static_variable_test(void);

int main()
{
    //this_test();
    //class_pointer_test();
    static_variable_test();



    std::cout << "\n测试完成\n";
    return 0;
}

int Line_class::bigger(Line_class temp)
{
#ifdef DEBUG
    debug_str = "bigger";
    std::clog << "--LOG: running: " + debug_str + "()" << std::endl;
#endif // DEBUG

    if (length > temp.length)           //this可以不写
 //   if (this->length > temp.length)
    {
        return 1;
    }
    else {
        return 0;
    }
}

Line_class::Line_class(double len) : length(len)
{
#ifdef DEBUG
    debug_str = "Line_class";
    std::clog << "--LOG: running: " + debug_str + "()" << std::endl;
#endif // DEBUG
    object_count++;                 //通过静态成员计数对象创建数
}

Line_class* Line_class::get_this_address(void)
{
#ifdef DEBUG
    debug_str = "get_this_address";
    std::clog << "--LOG: running: " + debug_str + "()" << std::endl;
#endif // DEBUG
    return this;
}

int Line_class::test_static_fun(void)
{
    exterior_fun();
    return object_count;
}

void exterior_fun(void)
{
    std::cout << "外部函数成功被调用!" << std::endl;
}


void this_test(void)
{
    Line_class line_1(11), line_2(12);

    if (line_1.bigger(line_2))
    {
        std::cout << "line_1 > line_2" << std::endl;
    }
    else {
        std::cout << "line_1 < line_2" << std::endl;
    }

    std::cout << "&line_1 = " << &line_1
        << "\tline_1.get_this_address = " << line_1.get_this_address()
        << std::endl;

}

void class_pointer_test(void)
{
    std::cout << "创建对象以及指针：" << std::endl;

    Line_class line_test(1112), * p_line_test = &line_test;
    Line_class* p_this = line_test.get_this_address();


    std::cout << "&line = " << &line_test 
        << "\tp_line = " << p_line_test 
        << "\tp_this = " << p_this
        << std::endl;

    std::cout << "line.length = " << line_test.length
        << "\tp_line->length = " << p_line_test->length
        << "\tp_this->length = " << p_this->length
        << std::endl;


    std::cout << "测试通过外部调用this指针修改值：" << std::endl;
    p_this->length += 1;

    std::cout << "line.length = " << line_test.length
        << "\tp_line->length = " << p_line_test->length
        << "\tp_this->length = " << p_this->length
        << std::endl;


    std::cout << "测试通过调用对象指针修改值：" << std::endl;
    p_line_test->length += 1;

    std::cout << "line.length = " << line_test.length
        << "\tp_line->length = " << p_line_test->length
        << "\tp_this->length = " << p_this->length
        << std::endl;

}

void static_variable_test(void)
{
    std::cout << "count = " << Line_class::object_count << std::endl;

    Line_class line_1(1);  

    std::cout << "count = " << line_1.object_count << std::endl;

    Line_class line_2(1), *p_line_1 = &line_1;  

    std::cout << "count = " << p_line_1->object_count << std::endl;

    Line_class line_3(1);

    std::cout << "count = " << Line_class::test_static_fun() << std::endl;

}
