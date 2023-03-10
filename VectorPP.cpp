#include <iostream>
template<typename T>
class Vector
{
private:
    T* m_ArrayPointer;

    int m_CurrentSize;
    int m_CurrentCapacity;

private:
    void MemAllocate(int Size);

public:
    const T& operator[](int i) const;
    T& operator[](int i);
    const T* begin() const;
    const T* end() const;

    Vector();
    Vector(size_t InitSize); 
    Vector(const Vector<T>& other);
    Vector(Vector<T>&& other);
    ~Vector();

    inline int Size() const { return m_CurrentSize; }
    inline int Capacity() const { return m_CurrentCapacity; }
    inline T* GetArrayPointer() const { return m_ArrayPointer; }
    inline T* GetArrayPointer(int i) const { return m_ArrayPointer[i]; }

    void Push_back(T&& Value);
    void Push_back(const T& Value);
    void Push_in(T&& Value, int Position);
    void Push_in(const T& Value, int Position);

    void Clear();

    void Erease(int iterator);
    void EreaseBlock(int Beg, int End);//Beggining and end included


};

template<typename T>
Vector<T>::Vector()
    :m_CurrentSize(0), m_CurrentCapacity(2)
{
    MemAllocate(0);
}

template<typename T>
Vector<T>::Vector(size_t InitSize)
    :m_CurrentSize(InitSize), m_CurrentCapacity(InitSize + InitSize / 2)
{
    MemAllocate(m_CurrentCapacity);
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other)
    :m_CurrentSize(other.Size()), m_CurrentCapacity(other.Capacity())
{
    m_ArrayPointer = new T[other.GetCurrentSize()];
    for (int i = 0; i < other.GetCurrentSize(); i++)
    {
        m_ArrayPointer[i] = other.GetArrayPointer(i);
    }
}

template<typename T>
Vector<T>::Vector(Vector<T>&& other)
    :m_CurrentSize(other.Size()), m_CurrentCapacity(other.Capacity()), m_ArrayPointer(std::move(other.GetArrayPointer()))
{
    other.GetArrayPointer() = nullptr;
}

template<typename T>
Vector<T>::~Vector()
{
    delete[] m_ArrayPointer;
}

template<typename T>
void Vector<T>::MemAllocate(int Size)
{   
    T* NewData = new T[m_CurrentCapacity + Size];
    for (size_t i = 0; i < m_CurrentSize; i++)
    {
        NewData[i] = std::move(m_ArrayPointer[i]);
    }
    if (m_CurrentSize != 0)
    {
        delete[] m_ArrayPointer;
    }
    m_ArrayPointer = NewData;
    m_CurrentCapacity = m_CurrentCapacity + Size;

    NewData = nullptr;
    delete[] NewData;
}

template<typename T>
void Vector<T>::Push_back(T&& Value)
{
    
    if (m_CurrentCapacity > m_CurrentSize)
    {
        m_ArrayPointer[m_CurrentSize] = std::move(Value);
    }
    else
    {
        MemAllocate(m_CurrentSize / 2);
        m_ArrayPointer[m_CurrentSize] = std::move(Value);
    }
    m_CurrentSize++;
}

template<typename T>
void Vector<T>::Push_back(const T& Value)
{
    
    if (m_CurrentCapacity > m_CurrentSize)
    {
        m_ArrayPointer[m_CurrentSize] = Value;
    }
    else
    {
        MemAllocate(m_CurrentSize / 2);
        m_ArrayPointer[m_CurrentSize] = Value;
    }
    m_CurrentSize++;
}

template<typename T>
void Vector<T>::Clear()
{
    m_CurrentSize = 0;
    m_CurrentCapacity = 2;
    delete m_ArrayPointer;
    m_ArrayPointer = new T[2];
}

template<typename T>
void Vector<T>::Erease(int iterator)
{    
    m_CurrentSize--;
    for (int i = iterator; i < m_CurrentSize; i++)
    {
        m_ArrayPointer[i] = m_ArrayPointer[i + 1];
    }
}


template<typename T>
const T& Vector<T>::operator[](int i) const
{
    return m_ArrayPointer[i];
}

template<typename T>
T& Vector<T>::operator[](int i)
{
    return m_ArrayPointer[i];
}

template<typename T>
const T* Vector<T>::begin() const
{
    const T* Elem = &m_ArrayPointer[0];
    return Elem;
}

template<typename T>
const T* Vector<T>::end() const
{
    const T* Elem = &m_ArrayPointer[m_CurrentSize];
    return Elem;
}



