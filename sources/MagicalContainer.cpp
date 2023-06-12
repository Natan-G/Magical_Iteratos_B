#include "MagicalContainer.hpp"
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <math.h>

using namespace std;

namespace ariel{

    void MagicalContainer::addElement(int elem){
        //check if exists
        for(size_t i=0 ; i < vec_container.size() ; i++){
            if(vec_container.at(i) == elem)
                return;
        }
        vec_container.push_back(elem);
        //sort the vector
        sort(vec_container.begin() , vec_container.end());
    }
    

    void MagicalContainer::removeElement(int elem){
        auto it = find(vec_container.begin() , vec_container.end() ,elem);
        if(it !=vec_container.end()){
            vec_container.erase(it);
        }
        if(it == vec_container.end()){
            throw runtime_error("the elemment not exsist");
        }
    }

  
    size_t MagicalContainer::size() const{
        return vec_container.size();
    }

    MagicalContainer& MagicalContainer::operator=(const MagicalContainer& other) {
        if (this == &other) {
            return *this;
        }
        throw std::runtime_error("Assignment operator is not supported for MagicalContainer");
        return *this;
    }

    //AscendingIterator
    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const {
        return index == other.index;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const {
        return index != other.index;
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other)const{
        return (container.vec_container[index] < container.vec_container[other.index] ? true : false);
    }
    
    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other)const{
        return (container.vec_container[index] > container.vec_container[other.index] ? true : false);
    }

    int MagicalContainer::AscendingIterator::operator*() const{
        return container.vec_container[index];
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++(){
      if(index+1 > container.vec_container.size())
        throw runtime_error("Out of range!");
    
    index++;
    return *this;      
    }            

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other){
        if(this == &other)
            return *this;
        throw runtime_error("cant for MagicalContainer");
        return *this;    
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()const {
        AscendingIterator begin_itr(container);
        return begin_itr;
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()const{
        AscendingIterator end_itr(container);
        end_itr.index = container.size();
        return end_itr;
    }

    //SideCrossIterator
    MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer& container, size_t index, bool isOdd)
        : container(container), index(index), isOdd(isOdd) {}

    MagicalContainer::SideCrossIterator::SideCrossIterator( const SideCrossIterator &other) //this
        : container(other.container), index(other.index),isOdd(other.isOdd) {}

    MagicalContainer::SideCrossIterator::~SideCrossIterator() {}

    MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer& ma_container)
        : container(ma_container),index(0),isOdd(false) {}




    MagicalContainer::SideCrossIterator & MagicalContainer::SideCrossIterator::operator=(const MagicalContainer::SideCrossIterator &other) {  
        if (&container == &other.container) {
            index = other.index;
            return *this;
        }
    
        throw std::runtime_error("different containers");
    }   


    MagicalContainer::SideCrossIterator  MagicalContainer::SideCrossIterator::begin() const {
        SideCrossIterator begin_itr (container, 0, false);
        return begin_itr;
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const { 
        size_t end_index = container.vec_container.size() / 2;
        bool isEndOdd = container.vec_container.size() % 2 != 0;
        return SideCrossIterator(container, end_index, isEndOdd);
    }


    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const {
        return (container.vec_container[index] < other.container.vec_container[other.index]);
    }
    
    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const { 
        return (*this).operator*() > (other).operator*();
    }

    int MagicalContainer::SideCrossIterator::operator*() const {
        if (isOdd)
            return container.vec_container[(unsigned long)container.size() - index - 1];
        else
            return container.vec_container[index];

    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
        int hafe_continer_size = (container.vec_container.size()/2);

        if (index >= hafe_continer_size+1) {
            throw std::runtime_error("out of range");
        }
        if (isOdd) {
            ++index;
        }
    
        isOdd = !isOdd;

        if (index >= hafe_continer_size+1) {
            throw std::runtime_error("out of range");
        }
        return *this;
    }

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const {
        return (index == other.index && isOdd == other.isOdd);
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const {
        return !(*this == other);
    }

    //PrimeIterator
    bool MagicalContainer::PrimeIterator::isPrime(int num)const{
        if(num <=1)
            return false;

        for(int i=2 ; i <= sqrt(num) ; i++){
            if(num % i == 0)
                return false;
        }
        return true;
    }


    MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer &container): container(container),index(0){
        while (index < container.size() && !isPrime(container.vec_container[index])) {
        ++index;
        }
    }

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container , size_t index): container(container),index(index){
        while(index < container.size()){
            if(isPrime(container.vec_container[index])){
                break;
            }
            ++index;
        }
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other){
        if(&container != &other.container){
            throw runtime_error("different container");
        }
        index = other.index;
        return *this;
    }
    
    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other)const{
        return index == other.index;
    }
    
    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other)const{
        return index != other.index;
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other)const{
        return (container.vec_container[index] < container.vec_container[other.index]);
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other)const{
        return (container.vec_container[index] > container.vec_container[other.index]);
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++(){
        ++index;
        while(index < container.vec_container.size() && !isPrime(container.vec_container[index])){
            ++index;
        }
        if(index > container.size())
            throw runtime_error("Out of range");
        
        return *this;
    }

    int MagicalContainer::PrimeIterator::operator*()const{
        return container.vec_container[index];
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()const{
        size_t i;
        for(size_t i = 0 ; i<container.size() ; i++){
            if(isPrime(container.vec_container[i])){
                break;
            }
        }
        
        return PrimeIterator(container , i);
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()const{
        return PrimeIterator(container , container.size());
    }

}