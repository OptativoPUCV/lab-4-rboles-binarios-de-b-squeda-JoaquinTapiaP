#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap *new = (TreeMap *)malloc(sizeof(TreeMap));
    if (new == NULL) return NULL;

    new->root = NULL;
    new->current = NULL;
    new->lower_than = lower_than;

    //new->lower_than = lower_than;
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    TreeNode* newNode = createTreeNode(key, value);
    
    if (tree->root == NULL) {
        tree->root = newNode;
        tree->current = newNode;
        return;
    }
    TreeNode* current = tree->root;
    TreeNode* parent = NULL;

    while (current != NULL) {
        parent = current;

        if (tree->lower_than(key, current->pair->key)) {
            current = current->left;
        } else if (tree->lower_than(current->pair->key, key)) {
            current = current->right;
        } else {
            free(newNode);
            return;
        }
    }

    newNode->parent = parent;

    if (tree->lower_than(key, parent->pair->key)) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    tree->current = newNode;
}

TreeNode * minimum(TreeNode * x){
    if (x == NULL) return NULL;

    while (x->left != NULL) {
        x = x->left;
    }

    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    if (node == NULL) return;

    // Caso 1: Nodo sin hijos (hoja)
    if (node->left == NULL && node->right == NULL) {
        if (node->parent == NULL) {
            // Es el nodo raíz
            tree->root = NULL;
        } else {
            // Actualizar el puntero del padre
            if (node->parent->left == node)
                node->parent->left = NULL;
            else
                node->parent->right = NULL;
        }
        free(node->pair);
        free(node);
        return;
    }

    // Caso 2: Nodo con un solo hijo
    if (node->left == NULL || node->right == NULL) {
        TreeNode* child = (node->left != NULL) ? node->left : node->right;
        
        // Conectar el hijo al padre del nodo actual
        child->parent = node->parent;
        
        if (node->parent == NULL) {
            // Es el nodo raíz
            tree->root = child;
        } else {
            // Actualizar el puntero del padre
            if (node->parent->left == node)
                node->parent->left = child;
            else
                node->parent->right = child;
        }
        
        free(node->pair);
        free(node);
        return;
    }

    // Caso 3: Nodo con dos hijos
    TreeNode* succ = minimum(node->right);
    
    // Copiar los datos del sucesor al nodo actual
    void* tempKey = node->pair->key;
    void* tempValue = node->pair->value;
    node->pair->key = succ->pair->key;
    node->pair->value = succ->pair->value;
    succ->pair->key = tempKey;
    succ->pair->value = tempValue;
    
    // Eliminar el sucesor (que ahora tiene los datos originales del nodo)
    removeNode(tree, succ);
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
