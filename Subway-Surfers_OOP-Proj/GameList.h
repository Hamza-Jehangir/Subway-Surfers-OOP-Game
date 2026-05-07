#pragma once

template <typename T>
class GameList {
private:
    static const int CAPACITY = 100; // Max objects per list
    T data[CAPACITY];
    int count;

public:
    GameList() {
        count = 0;
        for (int i = 0; i < CAPACITY; i++) {
            data[i] = nullptr;
        }
    }

    bool add(T item) {
        if (count < CAPACITY) {
            data[count] = item;
            count++;
            return true;
        }
        return false;
    }

    void removeAt(int index) {
        if (index < 0 || index >= count) return;
       
        // Shift elements left
        for (int i = index; i < count - 1; i++) {
            data[i] = data[i + 1];
        }
       
        data[count - 1] = nullptr;
        count--;
    }

    T get(int index) const {
        if (index >= 0 && index < count) {
            return data[index];
        }
        return nullptr;
    }

    int size() const {
        return count;
    }

    void clear() {
        count = 0;
        for (int i = 0; i < CAPACITY; i++) {
            data[i] = nullptr;
        }
    }
};
