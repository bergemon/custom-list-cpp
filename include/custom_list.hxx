#include <cstdint>

template<typename T>
class custom_list
{
    template<typename T>
    class list_container
    {
        friend class custom_list<T>;

        T m_data;

        list_container<T>* m_next = nullptr;
        list_container<T>* m_prev = nullptr;

        // Constructor
        list_container(T data): m_data(data) { }

        T& data() { return m_data; }

        list_container<T>* get_next() { return m_next; }

        list_container<T>* get_prev() { return m_prev; }

        void set_next(list_container<T>* next)
        {
            m_next = next;
        }
        void set_prev(list_container<T>* prev)
        {
            m_prev = prev;
        }
    };

    list_container<T>* m_first = nullptr;
    list_container<T>* m_medial = nullptr;
    list_container<T>* m_last = nullptr;
    size_t m_length = 0;

    friend class list_container<T>;

public:
    uint64_t length() { return m_length; }

    T& first() { return m_first->data(); }

    T& last() { return m_last->data(); }

    [[nodiscard]] T& operator[] (int index)
    {
        if (index >= m_length)
        {
            throw std::runtime_error("Provided index is greater than list length");
        }

        list_container<T>* current = m_first;

        // if index is closer to the beginning
        if (index < m_length / 4)
        {
            for (uint64_t i = 0; i < index; ++i)
            {
                current = current->get_next();
            }
        }

        // if index is closer to medial element
        if(
            index > m_length / 4
            && index > m_length / 2
            && index < m_length - (m_length / 4)
        )
        {
            current = m_medial;

            // -1 because index starts from 0
            uint64_t start_index = (m_length % 2 == 1 ? (m_length / 2 + 1) : (m_length / 2)) - 1;

            for (uint64_t i = start_index; i < index; ++i)
            {
                current = current->get_next();
            }
        }

        // if index is closer to the end
        if (index > m_length - (m_length / 4))
        {
            current = m_last;

            for (uint64_t i = m_length - 1; i > index; --i)
            {
                current = current->get_prev();
            }
        }

        return current->data();
    }

    void push_back(T data)
    {
        if (!m_length)
        {
            m_first = new list_container(data);
            m_medial = m_first;
            m_last = m_first;
            m_length++;

            // First container will have two pointers that point to the first container
            m_first->set_next(m_first);
            m_first->set_prev(m_first);

            return;
        }
        else
        {
            // Temporary pointer that contains reference to newly created container
            list_container<T>* new_container = new list_container(data);

            // Set next pointer for previous last container to newly created container
            m_last->set_next(new_container);
            
            // Temporary pointer to previous last list container
            list_container<T>* temp_last = m_last;

            // Now set pointer to new container
            m_last = new_container;
        
            // New container must have pointer to previous container
            m_last->set_prev(temp_last);

            // Last container must have pointer to the first container
            m_last->set_next(m_first);

            // First container must have pointer to last container as previous
            m_first->set_prev(m_last);

            m_length++;

            if (m_length % 2 == 1)
            {
                m_medial = m_medial->get_next();
            }
        }
    }

    void pop_front() { this->set_first(nullptr); }

    void pop() { this->set_last(nullptr); }

    void set_first(list_container<T>* first)
    {
        if (first == nullptr)
        {
            list_container<T>* second = m_first->get_next();

            delete m_first;

            m_first = second;

            --m_length;

            if (m_length % 2 == 0)
            {
                m_medial = m_medial->get_prev();
            }
        }
        else
        {
            list_container<T>* second = m_first->get_next();

            delete m_first;

            m_first = first;

            first->set_next(second);

            first->set_prev(m_last);
        }
    }

    void set_last(list_container<T>* last)
    {
        if (last == nullptr)
        {
            list_container<T>* penultimate = m_last->get_prev();

            delete m_last;

            m_last = penultimate;

            --m_length;

            if (m_length % 2 == 0)
            {
                m_medial = m_medial->get_prev();
            }
        }
        else
        {
            list_container<T>* penultimate = m_last->get_prev();

            delete m_last;

            m_last = last;

            m_last->set_next(m_first);

            m_last->set_prev(penultimate);
        }
    }

    // Destructor
    ~custom_list()
    {
        list_container<T>* next = m_first;

        for (uint64_t i = 0; i < m_length; ++i)
        {
            list_container<T>* prev = next;
            next = prev->get_next();
            delete prev;
        }
    }
};