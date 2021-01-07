#ifndef IDICTIONARY_H
#define IDICTIONARY_H

#include <functional>

#include "DynamicArray.h"
#include "Sort.h"
#include "Sequence.h"
#include "Pair.h"


template <typename TKey, typename TElem>
class IDictionary{
private:
    ArraySequence<Pair<TKey, TElem>> *items = new ArraySequence<Pair<TKey, TElem>>();
public:

    IDictionary()= default;

    IDictionary(Sequence<TElem>* seq, std::function<TKey(TElem)> function){
        auto iter = seq->begin();
        while(iter->isValuable()){
            Add(function(iter->GetData()), iter->GetData());
            iter->Next();
        }

    }

    TElem Get (TKey key){
        auto iter = items->begin();
        while(iter->isValuable() && iter->GetData().getLeft() != key)
            iter->Next();
        if(iter->isValuable()) return iter->GetData().getRight();
        else throw Exception(1);
    }

    bool ContainsKey(TKey key){
        for (int i = 0; i<items->GetLength(); i++)
            if(items->Get(i).getLeft() == key) return true;
        return false;
    }

    int getCount(){
        return items->GetReal();
    }

    int getCapacity(){
        return items->GetSize();
    }

    void Add(TKey key, TElem elem){
        if(!ContainsKey(key)) items->Prepend(Pair<TKey, TElem>(key, elem));
        else {
            for(int i = 0; i<items->GetLength(); i++){
                if(items->Get(i).getLeft() == key) {
                    items->Set(i, Pair<TKey, TElem>(key, elem));
                    break;
                }
            }
        }
    }

    TElem Remove(TKey key){
        for(int i = 0; i<items->GetReal(); i++){
            if(items->Get(i).getLeft() == key){
                TElem res = items->Remove(i).getRight();
                return res;
            }
            else if(i == items->GetReal()-1) throw Exception(1);
        }
    }

    std::string String()
    {
        std::string res = "";
        res = ' '+items->String();
        return res;
    }

};

#endif
