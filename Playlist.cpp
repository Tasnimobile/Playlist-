/**
 * @file Playlist.cpp
 * @author Tahsinul Majumder
 * @brief Implementation of Playlist class
 * @version 0.1
 * @date 2024-07-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "Playlist.hpp"
#include <iostream>

bool Playlist::remove(const std::string& song, const std::string& artist) {
    bool is_successful = false;
    root_ptr_ = removeValue(root_ptr_, song, artist, is_successful);
    return is_successful;
}

std::shared_ptr<SongNode> Playlist::removeValue(std::shared_ptr<SongNode> sub_tree, const std::string& song, const std::string& artist, bool& success) {
    // If subtree is empty, set success flag to false and return nullptr
    if (sub_tree == nullptr) {
        success = false;
        return sub_tree;
    }
    // If the current node matches the song and artist, remove the node and set success flag to true
    if (getKey(*sub_tree) == getKey(song,artist)) {
        sub_tree = removeNode(sub_tree);
        success = true;
        return sub_tree;
    }
    // Recursively search in the left subtree if the current node key is greater than the target song and artist
    if (getKey(*sub_tree) > getKey(song,artist)) {
        sub_tree -> left_ = removeValue(sub_tree -> left_, song, artist, success);
    }
    // Recursively search in the right subtree if the current node key is less than the target song and artist
    else {
        sub_tree -> right_ = removeValue(sub_tree -> right_, song, artist, success);
    }
    return sub_tree;
}

std::shared_ptr<SongNode> Playlist::removeNode(std::shared_ptr<SongNode> node_ptr) {
    // If the node is a leaf node, reset it and return nullptr
    if (node_ptr->isLeaf()) {
        node_ptr.reset();
        return node_ptr;
    }
    // If the left child is nullptr, return the right child
    else if (node_ptr -> left_ == nullptr) {
        return node_ptr -> right_;
    }
    // If the right child is nullptr, return the left child
    else if (node_ptr -> right_ == nullptr) {
        return node_ptr -> left_;
    }
    // If there are two children, find the leftmost node in the right subtree and replace the current node
    std::string inorder_song;
    std::string inorder_artist;
    node_ptr -> right_ = removeLeftmostNode(node_ptr -> right_, inorder_song, inorder_artist);
    node_ptr -> song_ = inorder_song;
    node_ptr -> artist_ = inorder_artist;
    return node_ptr;
}

std::shared_ptr<SongNode> Playlist::removeLeftmostNode(std::shared_ptr<SongNode> node_ptr, std::string& inorder_song, std::string& inorder_artist) {
    // If the left child is nullptr, store the song and artist, remove the current node
    if (node_ptr -> left_ == nullptr) {
        inorder_song = node_ptr -> song_;
        inorder_artist = node_ptr -> artist_;
        return removeNode(node_ptr);
    }
    // Recursively search for the leftmost node
    node_ptr -> left_ = removeLeftmostNode(node_ptr -> left_, inorder_song, inorder_artist);
    return node_ptr;
}

std::vector<SongNode> Playlist::inorderTraverse() const{
    std::vector<SongNode> result;
    inorderHelper(root_ptr_,result);
    return result;
}

void Playlist::inorderHelper(std::shared_ptr<SongNode> node_ptr, std::vector<SongNode>& result) const {
    // If node is not nullptr, add the node in the result vector following inorder traversal
    if (node_ptr != nullptr) {
        inorderHelper(node_ptr -> left_, result);
        result.push_back(*node_ptr);
        inorderHelper(node_ptr -> right_, result);
    }
}

std::string Playlist::getKey(const std::string& song, const std::string& artist) const {
    return song+artist;
}

std::string Playlist::getKey(const SongNode& song) const {
    return song.song_+song.artist_;
}


Playlist::Playlist() {
    root_ptr_ = nullptr;
}

//copy constructor
Playlist::Playlist(const Playlist& other) {
    root_ptr_ = copyTree(other.root_ptr_);
}

//helper function for copy constructor
std::shared_ptr<SongNode> Playlist::copyTree(const std::shared_ptr<SongNode> old_root_ptr) {
    std::shared_ptr<SongNode> new_tree_ptr;

    //makes a pointer to point at the same things and copies the left and right and assigns to the left and right
    if (old_root_ptr != nullptr) {
        new_tree_ptr = std::make_shared<SongNode>(old_root_ptr->song_, old_root_ptr->artist_);
        new_tree_ptr->left_ = copyTree(old_root_ptr->left_);
        new_tree_ptr->right_ = copyTree(old_root_ptr->right_);
    }

    return new_tree_ptr;
}

//move constructor
Playlist::Playlist(Playlist&& other) {
    root_ptr_ = other.root_ptr_;
    other.root_ptr_.reset();
}

//destructor
Playlist::~Playlist() {
    //uncomment to test destructor
    //std::cout << "Destructor Called" << std::endl;
    destroyTree(root_ptr_);
}

//helper function for desetructor
void Playlist::destroyTree(std::shared_ptr<SongNode> sub_tree_ptr) {
    if (sub_tree_ptr != nullptr) {
        destroyTree(sub_tree_ptr->left_);
        destroyTree(sub_tree_ptr->right_);

        //uncomment to test destroyTree
        //std::cout << "deleting... " << sub_tree_ptr->song_ << " by " << sub_tree_ptr->artist_ << std::endl;

        sub_tree_ptr.reset();
    }
}

//copy assignment operator
Playlist& Playlist::operator=(const Playlist& other) {
    
    //as long as they aren't the same object
    if (this != &other) {
        destroyTree(root_ptr_);
        root_ptr_ = copyTree(other.root_ptr_);
    }

    return *this;
}

//move assignment operator
Playlist& Playlist::operator=(Playlist&& other) {

    //as long as they aren't the same object
    if (this != &other) { 
        destroyTree(root_ptr_);
        root_ptr_ = std::move(other.root_ptr_);
        other.root_ptr_ = nullptr;
    }

    return *this;
}

bool Playlist::isEmpty() const {
    return (root_ptr_ == nullptr);
}

size_t Playlist::getHeight() const {
    return getHeightHelper(root_ptr_);
}

int Playlist::getHeightHelper(std::shared_ptr<SongNode> subtree_ptr) const {
    if (subtree_ptr == nullptr)
        return 0;
    
    else
        //returns max height between the left and right subtree and adds it
        return 1 + std::max(getHeightHelper(subtree_ptr->left_), getHeightHelper(subtree_ptr->right_));
}

size_t Playlist::getNumberOfSongs() const {
    return getNumSongsHelper(root_ptr_);
}

int Playlist::getNumSongsHelper(std::shared_ptr<SongNode> subtree_ptr) const {
    if (subtree_ptr == nullptr)
        return 0;

    else
        //adds the number of nodes in the left and right subtree
        return 1 + getNumSongsHelper(subtree_ptr->left_) + getNumSongsHelper(subtree_ptr->right_);
}

bool Playlist::add(const std::string& song, const std::string& artist) {
    std::shared_ptr<SongNode> new_node_ptr = std::make_shared<SongNode>(song, artist);
    root_ptr_ = placeNode(root_ptr_, new_node_ptr);
    return true;
}

std::shared_ptr<SongNode> Playlist::placeNode(std::shared_ptr<SongNode> subtree_ptr, std::shared_ptr<SongNode> new_node_ptr) {
    if (subtree_ptr == nullptr)
        return new_node_ptr;
    else {
        //if the new node is less than, it goes on the left
        if (getKey(*subtree_ptr) > getKey(*new_node_ptr))
            subtree_ptr->left_ = placeNode(subtree_ptr->left_, new_node_ptr);
        //if the new node is greater than or equal, it goes on the right
        else
            subtree_ptr->right_ = placeNode(subtree_ptr->right_, new_node_ptr);
        return subtree_ptr;
    }
}

bool Playlist::search(const std::string& name, const std::string& artist) const {
    return searchTree(root_ptr_, name, artist);
}

bool Playlist::searchTree(std::shared_ptr<SongNode> subtree_ptr, const std::string &name, const std::string &artist) const {
    if (subtree_ptr == nullptr)
        return false;

    //a key for the current node(compare) and for the node you are searching for(key)
    std::string key = getKey(name, artist);
    std::string compare = getKey(*subtree_ptr);

    //if found
    if (key == compare)
        return true;

    //if key is less than compare then search the left subtree
    if (key < compare)
        return searchTree(subtree_ptr->left_, name, artist);

    //if key is greater than compare then search the right subtree
    return searchTree(subtree_ptr->right_, name, artist);
}

void Playlist::clear() {
    destroyTree(root_ptr_);
    root_ptr_.reset();
}

std::vector<SongNode> Playlist::preorderTraverse() const {
    std::vector<SongNode> result;
    preorderHelper(root_ptr_,result);
    return result;
}

void Playlist::preorderHelper(std::shared_ptr<SongNode> node_ptr, std::vector<SongNode>& result) const {
    // If node is not nullptr, add the node in the result vector following inorder traversal
    if (node_ptr != nullptr) {
        //root, left, right
        result.push_back(*node_ptr);
        preorderHelper(node_ptr -> left_, result);
        preorderHelper(node_ptr -> right_, result);
    }
}

std::vector<SongNode> Playlist::postorderTraverse() const {
    std::vector<SongNode> result;
    postorderHelper(root_ptr_,result);
    return result;
}

void Playlist::postorderHelper(std::shared_ptr<SongNode> node_ptr, std::vector<SongNode>& result) const {
    // If node is not nullptr, add the node in the result vector following inorder traversal
    if (node_ptr != nullptr) {
        //left, right, root
        postorderHelper(node_ptr -> left_, result);
        postorderHelper(node_ptr -> right_, result);
        result.push_back(*node_ptr);
    }
}

