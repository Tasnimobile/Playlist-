/**
 * @file main.cpp
 * @author Tahsinul Majumder
 * @brief main file where all testing occurs
 * @version 0.1
 * @date 2024-07-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "Playlist.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void constructorTesting() {
    //constructor testing
    cout << "\nTesting constructor:" << endl;
    SongNode hello = SongNode("Hello?", "Clairo");

    //should print "hello: Hello?    Clairo"
    cout << "hello: " << hello.song_ << "\t" << hello.artist_ << endl;

    //copy constructor testing
    cout << "\nTesting copy constructor:" << endl;

    SongNode hello2 = hello;

    //should print "hello2: Hello?  Clairo"
    cout << "hello2: " << hello2.song_ << "\t" << hello2.artist_ << endl;


    //should print "hello: Hello?    Clairo"
    cout << "hello: " << hello.song_ << "\t" << hello.artist_ << endl;

    //Testing how comparing strings works
    //cout << ("hello" < "Pretty girl") << endl;

    //move constructor testing
    cout << "\nTesting move constructor: " << endl;

    SongNode hello3 = std::move(hello);

    //should print "hello3: Hello?    Clairo"
    cout << "hello3: " << hello3.song_ << "\t" << hello3.artist_ << endl;

    //should print "hello: "
    cout << "hello: " << hello.song_ << "\t" << hello.artist_ << endl;
}

void addTesting() {
    //testing add
    cout << "\nTesting add: " << endl;
    Playlist playlist;

    // Adding songs to the playlist
    playlist.add("Feel It", "D4vd");
    playlist.add("The Most Beautiful Thing", "Bruno Major");
    playlist.add("Sweet Dreams TN", "The Last Shadow Puppets");

    // inorder print

    // should print:
    // Playlist after adding songs:
    // Song: Feel It, Artist: D4vd
    // Song: Sweet Dreams TN, Artist: The Last Shadow Puppets
    // Song: The Most Beautiful Thing, Artist: Bruno Major
    // Destructor Called
    // deleting... Sweet Dreams TN by The Last Shadow Puppets
    // deleting... The Most Beautiful Thing by Bruno Major
    // deleting... Feel It by D4vd

    auto songs = playlist.inorderTraverse();
    std::cout << "\nPlaylist after adding songs:" << std::endl;
    for (int i = 0; i < songs.size(); i++) {
        const SongNode& song = songs[i];
        std::cout << "Song: " << song.song_ << ", Artist: " << song.artist_ << std::endl;
    }
}

void assignmentTesting() {
    Playlist playlist;

    //using generic names to test that they go to the left/right appropriately
    playlist.add("Song2", "Artist2");
    playlist.add("Song1", "Artist1");
    playlist.add("Song3", "Artist3");


    //testing copy assignment
    //Should print Song1, Song2, then Song3
    cout << "\nTesting copy assignment: " << endl;
    Playlist playlist2;
    playlist2 = playlist;

    cout << "\nPlaylist: " << endl;
    auto songs = playlist.inorderTraverse();
    for (int i = 0; i < songs.size(); i++) {
        const SongNode& song = songs[i];
        std::cout << "Song: " << song.song_ << ", Artist: " << song.artist_ << std::endl;
    }

    cout << "\nPlaylist2: " << endl;
    auto songs2 = playlist2.inorderTraverse();
    for (int i = 0; i < songs2.size(); i++) {
        const SongNode& song = songs2[i];
        std::cout << "Song: " << song.song_ << ", Artist: " << song.artist_ << std::endl;
    }

    //testing move assignment
    //Playlist 3 should have the values of Playlist 1, and Playlist 1 should be empty
    cout << "\nTesting move assignment: " << endl;
    Playlist playlist3;
    playlist3 = std::move(playlist);

    cout << "\nPlaylist3: " << endl;
    auto songs3 = playlist3.inorderTraverse();
    for (int i = 0; i < songs3.size(); i++) {
        const SongNode& song = songs3[i];
        std::cout << "Song: " << song.song_ << ", Artist: " << song.artist_ << std::endl;
    }

    cout << "\nPlaylist: " << endl;
    auto songs4 = playlist.inorderTraverse();
    for (int i = 0; i < songs4.size(); i++) {
        const SongNode& song = songs4[i];
        std::cout << "Song: " << song.song_ << ", Artist: " << song.artist_ << std::endl;
    }

}

void isEmptyTesting() {
    Playlist playlist;
    //playlist is empty so return true, print 1
    cout << playlist.isEmpty() << endl;

    playlist.add("Cigarettes out the Window", "TV Girl");
    //playlist has a song so return false, print 0
    cout << playlist.isEmpty() << endl;
}

void clearTesting() {
    Playlist playlist;
    playlist.add("Kingston", "Faye Webster");
    playlist.add("Tough Love", "Gracie Abrams");

    cout << "Before clear: " << endl;
    cout << "\nPlaylist: " << endl;
    auto songs = playlist.inorderTraverse();
    for (int i = 0; i < songs.size(); i++) {
        const SongNode& song = songs[i];
        std::cout << "Song: " << song.song_ << ", Artist: " << song.artist_ << std::endl;
    }

    playlist.clear();

    cout << "\nAfter clear: " << endl;
    cout << "\nPlaylist: " << endl;
    auto songs2 = playlist.inorderTraverse();
    for (int i = 0; i < songs2.size(); i++) {
        const SongNode& song = songs2[i];
        std::cout << "Song: " << song.song_ << ", Artist: " << song.artist_ << std::endl;
    }
}

void heightAndNumTesting() {
    Playlist playlist;
    // add to the right constantly
    playlist.add("Song2", "Artist");
    playlist.add("Song3", "Artist");
    playlist.add("Song4", "Artist");

    cout << "\nTesting height: " << endl;
    // height of 3
    cout << playlist.getHeight() << endl;

    //add to the left
    playlist.add("Song1", "Artist");

    //height of 3
    cout << playlist.getHeight() << endl;

    cout << "\nTesting number of nodes: " << endl;
    //4 songs
    cout << playlist.getNumberOfSongs() << endl;
}

void searchTesting() {
    Playlist playlist;

    playlist.add("Let's Fall in Love for the Night", "FINNEAS");
    playlist.add("Take A Bite", "beabadoobee");
    playlist.add("Stella Brown", "Jelani Aryeh");
    playlist.add("Honeypie", "JAWNY");

    cout << "\nTesting Search: " << endl;
    // search for a song there, prints 1
    cout << "Song exists: " << playlist.search("Honeypie", "JAWNY") << endl;

    //search for a song that doesn't exist, prints 0
    cout << "Song doesn't exist: " << playlist.search("Coming Home", "beabadoobee") << endl;
}

void orderTesting() {
    Playlist playlist;

    //using generic names to test that they go to the left/right appropriately
    playlist.add("Song2", "Artist");
    playlist.add("Song1", "Artist");
    playlist.add("Song3", "Artist");
    playlist.add("Song5", "Artist");
    playlist.add("Song4", "Artist");


    //preorder
    //should print 2, 1, 3, 4, 5
    cout << "\nPreorder: " << endl;
    auto songs = playlist.preorderTraverse();
    for (int i = 0; i < songs.size(); i++) {
        const SongNode& song = songs[i];
        std::cout << "Song: " << song.song_ << ", Artist: " << song.artist_ << std::endl;
    }


    //postorder
    //should print 1, 4, 5, 3, 2
    cout << "\nPostorder: " << endl;
    auto songs2 = playlist.postorderTraverse();
    for (int i = 0; i < songs2.size(); i++) {
        const SongNode& song = songs2[i];
        std::cout << "Song: " << song.song_ << ", Artist: " << song.artist_ << std::endl;
    }

    //inorder
    //should print 1, 2, 3, 4, 5
    cout << "\nInorder: " << endl;
    auto songs3 = playlist.inorderTraverse();
    for (int i = 0; i < songs3.size(); i++) {
        const SongNode& song = songs3[i];
        std::cout << "Song: " << song.song_ << ", Artist: " << song.artist_ << std::endl;
    }
}

void removeTesting() {
    Playlist playlist;

    //using generic names to test that they go to the left/right appropriately
    playlist.add("Song2", "Artist");
    playlist.add("Song1", "Artist");
    playlist.add("Song3", "Artist");
    playlist.add("Song5", "Artist");
    playlist.add("Song4", "Artist");

    //removing one
    playlist.remove("Song2", "Artist");

    //preorder
    //should print 3, 1, 5, 4
    cout << "\nPreorder: " << endl;
    auto songs = playlist.preorderTraverse();
    for (int i = 0; i < songs.size(); i++) {
        const SongNode& song = songs[i];
        std::cout << "Song: " << song.song_ << ", Artist: " << song.artist_ << std::endl;
    }


    //postorder
    //should print 1, 4, 5, 3
    cout << "\nPostorder: " << endl;
    auto songs2 = playlist.postorderTraverse();
    for (int i = 0; i < songs2.size(); i++) {
        const SongNode& song = songs2[i];
        std::cout << "Song: " << song.song_ << ", Artist: " << song.artist_ << std::endl;
    }

    //inorder
    //should print 1, 3, 4, 5
    cout << "\nInorder: " << endl;
    auto songs3 = playlist.inorderTraverse();
    for (int i = 0; i < songs3.size(); i++) {
        const SongNode& song = songs3[i];
        std::cout << "Song: " << song.song_ << ", Artist: " << song.artist_ << std::endl;
    }
}



int main() {

    constructorTesting();
    addTesting();
    assignmentTesting();
    isEmptyTesting();
    clearTesting();
    heightAndNumTesting();
    searchTesting();
    orderTesting();
    removeTesting();
}