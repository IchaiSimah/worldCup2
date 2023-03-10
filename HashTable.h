#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include "math.h"
#define POSSIBLESIZES 28
#define FIRSTPRIME 13


template<class T>
class HashTable{

private:
    int m_size = FIRSTPRIME;
    int possibleSizes[POSSIBLESIZES]= {
            13,29,53,97,193,389,769,1543,
            3079,6151,12289,24593,49157,98317,
            196613,393241,786433,1572869,3145739,6291469,
            12582917,25165843,50331653,100663319,
            201326611,402653189,805306457,1610612741
    };
    int indexOfPossibleSizes = 0;
    int m_numOfElements = 0;
    T* m_table;


public:
    HashTable() {
        m_table = new T[m_size]();
    }

    ~HashTable(){
        for(int i=0 ; i<m_size ; i++){
            if (m_table[i] != nullptr)
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
        m_table[indexToInsert] = data;
        m_numOfElements++;
        updateSize();
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
        if ((m_numOfElements)==m_size){                // if the table is full, sizeUp
            sizeUp();
        }
    }


    void sizeUp(){                                          // if num == 1 sizeUp, if num==-1 sizeDown
        int current_size= m_size;
        int counter = 0;
        m_size= possibleSizes[++indexOfPossibleSizes];
        T* tempArray= new T[m_numOfElements];                               // create a tmp array to stock the real elements
        for(int i=0 ; i< current_size; i++){                        // fill it
            if(m_table[i] != nullptr){
                tempArray[counter] = m_table[i];
                counter++;
            }
        }
        delete[] m_table;                                             // delete the former table
        m_table = new T[m_size]();                                    // create a new one
        for(int i=0; i < m_numOfElements; i++){                     // fill it
            m_table[findIndexToInsert(tempArray[i]->getPlayerId())] = tempArray[i];
        }
        delete[] tempArray;
    }


///////////////////////////////////////////////////////////////////////////////////////////////////////
//possibles sizes
/////////////////////////////////////////////////////////////////////////////////////////////////////


};


#endif //HASH_TABLE_H