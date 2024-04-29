#include "../include/dependencies.hxx"

int main(int argc, char** argv)
{
    {
        custom_list<std::string> list_str;

        list_str.push_back("first");
        list_str.push_back("second");
        list_str.push_back("third");
        list_str.push_back("fourth");
        list_str.push_back("fifth");
        list_str.push_back("sixth");

        try
        {
            std::cout << list_str[1] << std::endl;

            std::cout << list_str.length() << std::endl;
            std::cout << list_str.last() << std::endl;

            list_str.pop();

            std::cout << list_str.length() << std::endl;
            std::cout << list_str.last() << std::endl;

            std::cout << "\n***********************************************************\n\n";

            std::cout << list_str.length() << std::endl;
            std::cout << list_str.first() << std::endl;

            list_str.pop_front();

            std::cout << list_str.length() << std::endl;
            std::cout << list_str.first() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    custom_list<int> int_list;

    try
    {
        for (int i = 0; i < 1'000'000; ++i)
        {
            int_list.push_back(i);
        }
        
        std::cout << int_list[685'678] << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

#ifdef _WIN32
    system("pause");
#endif

    return 0;
}