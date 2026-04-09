#pragma once

#include <cstddef>

template <class T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;

        explicit Node(const T& value)
            : data(value), next(nullptr) {
        }
    };

    Node* head_;
    Node* tail_;
    std::size_t size_;

    Node* findNode(const T& key) {
        Node* current = head_;
        while (current) {
            if (current->data == key) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    const Node* findNode(const T& key) const {
        const Node* current = head_;
        while (current) {
            if (current->data == key) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

public:
    LinkedList()
        : head_(nullptr), tail_(nullptr), size_(0) {
    }

    LinkedList(const LinkedList& other)
        : head_(nullptr), tail_(nullptr), size_(0) {
        const Node* current = other.head_;
        while (current) {
            pushBack(current->data);
            current = current->next;
        }
    }

    LinkedList(LinkedList&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            const Node* current = other.head_;
            while (current) {
                pushBack(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    ~LinkedList() {
        clear();
    }

    void clear() {
        while (head_) {
            Node* next = head_->next;
            delete head_;
            head_ = next;
        }
        tail_ = nullptr;
        size_ = 0;
    }

    bool empty() const {
        return head_ == nullptr;
    }

    std::size_t size() const {
        return size_;
    }

    void pushBack(const T& value) {
        Node* node = new Node(value);
        if (tail_) {
            tail_->next = node;
            tail_ = node;
        }
        else {
            head_ = node;
            tail_ = node;
        }
        ++size_;
    }

    T* find(const T& key) {
        Node* node = findNode(key);
        return node ? &node->data : nullptr;
    }

    const T* find(const T& key) const {
        const Node* node = findNode(key);
        return node ? &node->data : nullptr;
    }

    bool removeFirst(const T& key) {
        Node* previous = nullptr;
        Node* current = head_;

        while (current) {
            if (current->data == key) {
                break;
            }
            previous = current;
            current = current->next;
        }

        if (!current) {
            return false;
        }

        if (previous) {
            previous->next = current->next;
        }
        else {
            head_ = current->next;
        }

        if (tail_ == current) {
            tail_ = previous;
        }

        delete current;
        --size_;
        return true;
    }

    bool extractFirst(const T& key, T& extracted) {
        Node* previous = nullptr;
        Node* current = head_;

        while (current) {
            if (current->data == key) {
                break;
            }
            previous = current;
            current = current->next;
        }

        if (!current) {
            return false;
        }

        extracted = current->data;

        if (previous) {
            previous->next = current->next;
        }
        else {
            head_ = current->next;
        }

        if (tail_ == current) {
            tail_ = previous;
        }

        delete current;
        --size_;
        return true;
    }

    bool insertAfter(const T& key, const T& value) {
        Node* keyNode = findNode(key);
        if (!keyNode) {
            return false;
        }

        Node* node = new Node(value);
        node->next = keyNode->next;
        keyNode->next = node;
        if (tail_ == keyNode) {
            tail_ = node;
        }
        ++size_;
        return true;
    }

    template <class Fn>
    void forEach(Fn fn) const {
        const Node* current = head_;
        while (current) {
            fn(current->data);
            current = current->next;
        }
    }
};
