#pragma once


namespace bbg {


class Singleton
{
public:
	Singleton(void);
	~Singleton(void);
	static Singleton* Instance();
private:
    static Singleton* m_Instance;
};


Singleton* Singleton::m_Instance = 0;


Singleton* Singleton::Instance() {
    if (m_Instance == 0) {
        m_Instance = new Singleton();
    }
    return m_Instance;
}


Singleton::Singleton(void)
{
}


Singleton::~Singleton(void)
{
}



}