#pragma once

#include <vector>
using namespace std;

namespace ariel{

    class MagicalContainer{
        private:
            std::vector<int> vec_container;
        
        public:
            MagicalContainer() = default;
            void addElement(int elem);
            void removeElement(int elem);

            size_t size() const;

            class AscendingIterator;
            class SideCrossIterator;
            class PrimeIterator;
            

            MagicalContainer& operator=(const MagicalContainer& other);

    };

    class MagicalContainer::AscendingIterator {
        private:
            const MagicalContainer& container;
            size_t index;
        
        public:
            AscendingIterator(const MagicalContainer& container , size_t index = 0) : container(container) , index(index){}
                   
            AscendingIterator begin()const;
            AscendingIterator end()const;

            AscendingIterator& operator++();
            int operator*() const;
            bool operator==(const AscendingIterator& other) const;
            bool operator!=(const AscendingIterator& other) const;
            bool operator<(const AscendingIterator& other) const;
            bool operator>(const AscendingIterator& other) const;

            AscendingIterator& operator=(const AscendingIterator& other);
        
    };

    class MagicalContainer::SideCrossIterator {
        private:
            const MagicalContainer& container;
            const MagicalContainer* point_container;

            size_t index;
            bool isOdd;
            size_t steps_back=0;
            size_t steps_forward=0;

        public:             
            
            SideCrossIterator(const MagicalContainer& container);
            SideCrossIterator(const MagicalContainer &cont, size_t index, bool isOdd = false);
            SideCrossIterator(const MagicalContainer& container, size_t index) noexcept;
            SideCrossIterator(const SideCrossIterator &other);
            ~SideCrossIterator();

            SideCrossIterator begin() const;
            SideCrossIterator end() const;
            
            SideCrossIterator& operator=(const SideCrossIterator& other);
            int operator*() const;
            SideCrossIterator& operator++();
            bool operator==(const SideCrossIterator& other) const;
            bool operator!=(const SideCrossIterator& other) const;
            bool operator<(const SideCrossIterator& other) const;
            bool operator>(const SideCrossIterator& other) const;
    };

    class MagicalContainer::PrimeIterator {
        private:

            const MagicalContainer& container;
            size_t index;


        public:
            PrimeIterator(const MagicalContainer& container);
            PrimeIterator(MagicalContainer& container , size_t index);
            PrimeIterator(const PrimeIterator& other): container(other.container) , index(other.index){}//copy
            PrimeIterator(const PrimeIterator& container , size_t index): container(container.container) , index(index){}
            ~PrimeIterator(){}

            PrimeIterator begin() const;
            PrimeIterator end() const;

            PrimeIterator& operator=(const PrimeIterator& other);
            int operator*() const;
            PrimeIterator& operator++();
            bool operator==(const PrimeIterator& other) const;
            bool operator!=(const PrimeIterator& other) const;
            bool operator<(const PrimeIterator& other) const;
            bool operator>(const PrimeIterator& other) const;

            bool isPrime(int num) const;


    };




}