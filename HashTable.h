#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include "math.h"


template<class T>
class HashTable{

private:
    int m_size = 1;
    int m_currentPower = 1;
    int m_numOfElements = 0;
    int m_numOfTomb = 0;
    int m_removeCounter =0;
    T* m_table;
    T m_tomb;

public:
    HashTable(T tomb): m_tomb(tomb){
        m_table = new T[m_size]();
    }

    ~HashTable(){
        for(int i=0 ; i<m_size ; i++){
            if (m_table[i] != nullptr && m_table[i] != m_tomb)
                delete m_table[i];
        }
        delete []m_table;
    }

    T getT(int index){
        return m_table[index];
    }

    void insert (int key,T data){
        if (find(key) != -1) return;                                    // if the element is already in the table return
        int indexToInsert = findIndexToInsert(key);
        if (m_table[indexToInsert] == m_tomb) m_numOfTomb--;
        m_table[indexToInsert] = data;
        m_numOfElements++;
        updateSize();
    }

    void remove (int key){                                              // if the element is not in the table return
        if (find(key) == -1) return;
        m_table [find(key)] = m_tomb;
        m_numOfElements--;
        m_numOfTomb++;
        m_removeCounter++;
        updateSize();
        if (m_removeCounter>=m_size/3) rehash(0);
    }

    int find (int key){
        int k = 1, i = doubleHashing(key,0);
        while (m_table[i] != nullptr && m_table[i]->getPlayerId() != key){
            i= doubleHashing(key, k);
            k++;
        }
        if (m_table[i]== nullptr){
            return -1;                                              // if the ptr is not in the array return -1
        }
        else return i;                                              // if the ptr is in the array return his index
    }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------- Structure management -------------------------------------------------//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int doubleHashing(int id, int k){                                   // Hash Function for k=0
        return (id % m_size + k * (1 + id % (m_size - 2))) % m_size;
    }


    int findIndexToInsert(int key){
        int i = doubleHashing(key,0);
        int k = 1;
        while (m_table[i] != nullptr && m_table[i]->getPlayerId() != key){
            if (m_table[i]->getPlayerId()==key) return -1;
            i= doubleHashing(key, k);
            k++;
        }                                                          //if (m_table[i] == nullptr){ il peut y avoir ici un pb
            return i;
    }


    void updateSize(){
        if ((m_numOfElements+m_numOfTomb)==m_size){                // if the table is full, sizeUp
            rehash(1);
        }
        if (m_numOfElements<m_size/4 && m_size >= 1){
            rehash(-1);
        }
    }


    void rehash(int num){                                          // if num == 1 sizeUp, if num==-1 sizeDown
        if ((num!=1) && (num!=-1) && (num!=0)) return;
        int current_size= m_size;
        int counter = 0;
        m_size= pow(2,(m_currentPower+=num))-1;
        T tempArray[m_numOfElements];                               // create a tmp array to stock the real elements
        for(int i=0 ; i< current_size; i++){                        // fill it
            if(m_table[i] != m_tomb && m_table[i] != nullptr){
                tempArray[counter] = m_table[i];
                counter++;
            }
        }
        delete m_table;                                             // delete the former table
        m_table = new T[m_size]();                                    // create a new one
        for(int i=0; i < m_numOfElements; i++){                     // fill it
            m_table[findIndexToInsert(tempArray[i]->getPlayerId())] = tempArray[i];
        }
        m_numOfTomb = 0;
        m_removeCounter=0;
    }

};



#endif //HASH_TABLE_H