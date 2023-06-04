#include <iostream>
#include <vector>
#include <algorithm>

// Was helped by chatGPT for all. 
namespace ariel {
    class MagicalContainer {
    private:
        std::vector<int> elements;

    public:

        void addElement(int value) {
            elements.push_back(value);
        }

        void removeElement(int value) {
            elements.erase(std::remove(elements.begin(), elements.end(), value), elements.end());
        }

        int size() const {
            return elements.size();
        }

        class AscendingIterator {
        private:
            const std::vector<int>& elements;
            std::vector<int> sortedElements;

        public:
            AscendingIterator(const MagicalContainer& container)
                : elements(container.elements), sortedElements(container.elements) {
                std::sort(sortedElements.begin(), sortedElements.end());
            }

            class Iterator {
            private:
                std::vector<int>::const_iterator current;

            public:
                Iterator(const std::vector<int>::const_iterator& it)
                    : current(it) {
                }

                int operator*() const {
                    return *current;
                }

                Iterator& operator++() {
                    ++current;
                    return *this;
                }

                bool operator!=(const Iterator& other) const {
                    return current != other.current;
                }
            };

            Iterator begin() const {
                return Iterator(sortedElements.begin());
            }

            Iterator end() const {
                return Iterator(sortedElements.end());
            }
        };
            
        class SideCrossIterator {
        private:
            const std::vector<int>& elements;
            std::vector<int> sortedElements;


        public:
            SideCrossIterator(const MagicalContainer& container)
                : elements(container.elements), sortedElements(container.elements) {
                    std::sort(sortedElements.begin(), sortedElements.end());
            }

            class Iterator {
            private:
                const std::vector<int>& elements;
                std::vector<int>::const_iterator current;
                bool fromStart;

            public:
                Iterator(const std::vector<int>::const_iterator& it, bool startFromBeginning, const std::vector<int>& elems)
                    : elements(elems), current(it), fromStart(startFromBeginning) {
                }

                int operator*() const {
                    return *current;
                }

                Iterator& operator++() {
                    if (fromStart) {
                        current = std::next(current);
                        if (current == elements.end()){
                            fromStart = false;
                        }
                    } else {
                        current = std::prev(current);
                        if (current == elements.begin()){
                            fromStart = true;
                        }
                    }
                    return *this;
                }

                bool operator!=(const Iterator& other) const {
                    return current != other.current || fromStart != other.fromStart;
                }
            };

            Iterator begin() const {
                return Iterator(elements.begin(), true, elements);
            }

            Iterator end() const {
                return Iterator(elements.end(), false, elements);
            }
        };

        class PrimeIterator {
        private:
            const std::vector<int>& elements;

            static bool isPrime(int num) {
                if (num < 2){
                    return false;
                }
                for (int i = 2; i * i <= num; ++i) {
                    if (num % i == 0){
                        return false;
                    }    
                }
                return true;
            }

        public:
            PrimeIterator(const MagicalContainer& container)
                : elements(container.elements) {
            }

            class Iterator {
            private:
                const std::vector<int>& elements;
                std::vector<int>::const_iterator current;

            public:
                Iterator(const std::vector<int>::const_iterator& it, const std::vector<int>& elems)
                    : elements(elems), current(it) {
                    while (current != elements.end() && !isPrime(*current)) {
                        ++current;
                    }
                }

                int operator*() const {
                    return *current;
                }
                 Iterator& operator++() {
                    ++current;
                    while (current != elements.end() && !isPrime(*current)) {
                        ++current;
                    }
                    return *this;
                }

                bool operator!=(const Iterator& other) const {
                    return current != other.current;
                }
            };

            Iterator begin() const {
                auto it = std::find_if(elements.begin(), elements.end(), [this](int num) {
                    return isPrime(num);
                });
                return Iterator(it, elements);
            }

            Iterator end() const {
                return Iterator(elements.end(), elements);
            }
        }; //primeIterator
    }; //magicalContainer
} // namespace ariel

               
