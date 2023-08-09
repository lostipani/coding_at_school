#include <iostream>
#include <string>
#include <new>


// class declaration
class Singleton{
    
    protected:
        std::string _val;
        Singleton(const std::string& val): _val(val) { }
        static Singleton* _sing;
    
    public:
        Singleton(const Singleton&) = delete;
        Singleton& operator= (const Singleton&) = delete;
        void show(void) const { std::cout << _val << std::endl; }
        static Singleton* getInstance(void);
};


// static members initialization
Singleton* Singleton::_sing = nullptr;

Singleton* Singleton::getInstance(void){
    if (_sing == nullptr){
        std::cout << "init singleton instance" << std::endl;
        _sing = new Singleton("done"); // call protected constructor
    }
    return _sing;
}


int main()
{
    std::cout << Singleton::getInstance() << std::endl;
    std::cout << Singleton::getInstance() << std::endl;
    Singleton::getInstance()->show();
    return 0;
}
