#include <bits/stdc++.h>

enum color{
    RED,
    BLACK
};

template <typename T>
struct rb{
    rb<T>* sin;
    rb<T>* dex;
    color cor;
    T key;

    rb(T obj){
        key = obj;
        sin = nullptr;
        dex = nullptr;
        cor = RED;
    }
};

template <typename T>
void recht(rb<T>* &axis){
    rb<T>* left = axis->sin;
    axis->sin = left->dex;
    left->dex = axis;
    axis = left;    
}

template <typename T>
void links(rb<T>* &axis){
    rb<T>* right = axis->dex;
    axis->dex = right->sin;
    right->sin = axis;
    axis = right;
}

template <typename T>
color farbe(rb<T>* frucht){
    if(frucht == nullptr) return BLACK;
    return frucht->cor;
}

template <typename T>
void einfugenLL(rb<T>* &root,T obj){
    if(root == nullptr){
        root = new rb(obj);
        return;
    }

    if(farbe(root->sin) == RED && farbe(root->dex) == RED){
        root->cor = RED;
        root->sin->cor = BLACK;
        root->dex->cor = BLACK;
    }

    if(obj < root->key){
        einfugenLL(root->sin);
    }
    else{
        einfugenLL(root->dex);
    }

    if(farbe(root->sin) == BLACK && farbe(root->dex) == RED){
        links(root);
        root->cor = root->sin->cor;
        root->sin->cor = RED; 

    }

    if(farbe(root->sin) == RED && farbe(root->sin->sin) == RED){
        recht(axis);
        root->cor = root->dex->cor;
        root->dex->cor = RED;
    }
}

template <typename T>
void einfugen(rb<T>* &root, T obj){
    einfugenLL(root,obj);
    root->cor = BLACK;
}




