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
    
    TreeNode *parent = node->parent;

    if (node->left == NULL && node->right == NULL) {
        if (parent == NULL) {
            tree->root = NULL;
        } 
        else {
            if (parent->left == node) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
        }
        free(node->pair);
        free(node);
        return;
    }

    if (node->left == NULL || node->right == NULL) {
        TreeNode* child = (node->left != NULL) ? node->left : node->right;

        if (node->parent == NULL) {
            tree->root = child;
            child->parent = NULL;
        } 
        else {
            if (node->parent->left == node)
                node->parent->left = child;
            else
                node->parent->right = child;

            child->parent = node->parent;
        }

        free(node->pair);
        free(node);
        return;
    }

    TreeNode* succ = minimum(node->right);


    node->pair->key = succ->pair->key;
    node->pair->value = succ->pair->value;
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
