#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tunez_struct.h"

/*

insert_front +++
print_list +++
find_song
find_song_by_artist
find_random
remove_node
free_list +++

add_song
find_song
find_song_by_artist
print_all_by_letter
print_all_by_artist
print_list
find_random / print_random / shuffle
delete_song
delete all / free_list +++

~~~~~~~~~~~~~~~~~~~~

insert nodes at the front -> insert_front
insert nodes in order
print the entire list -> print_list
find and return a pointer to an individual song based on song name
find and return a pointer to the first song of an artist based on artist name
Return a pointer to random element in the list.
remove a single node from the list
free the entire list -> free_list
Search for a song.
Search for an artist.
Print out all the entries under a certain letter.
Print out all the songs of a certain artist
Print out the entire library.
Shuffle - print out a series of randomly chosen songs.
Delete a song
Delete all the nodes. -> free_list

 */

//prints the entire list
void print_list( song_node *n ) {
  printf("[");

  while( n ) {
    printf( " %s, %s ", n->name, n->artist );
    n = n->next;
    if( n ) {
      printf("->");
    }
  }

  printf("]\n");
}

//inserts a node at the front
song_node * insert_front( song_node *n, char a[], char b[] ) {
  song_node *new = (struct song_node *)malloc(sizeof(song_node));
  new->next = n;
  strcpy(new->name,a);
  strcpy(new->artist,b);

  return new;
}

//inserts a node alphabetically, by song
song_node * insert_order( song_node *n, char a[], char b[] ) {
  if( strcmp(a, n->name) < 0 ) {
    return insert_front( n, a, b );
  }
  else {
    n = insert_front(insert_order( n->next, a, b ), n->name, n->artist );
  }
  return n;
}

song_node * free_list( song_node *n ) {
  song_node *f = n;
  while( n ) {
    n = n->next;
    printf( "freeing node: %s, %s\n", f->name, f->artist );
    free(f);
    f = n;
  }
  return n;
}


//main function
int main() {
  

  //song_node *  list[26] = (song_node *)malloc(sizeof(song_node));
  
  song_node * list = insert_front( NULL, "name", "artist" );
  print_list( list );

  
  char n1[] = "Sandstorm";
  char a1[] = "Darude";
  char n2[] = "Roar";
  char a2[] = "Perry, Katy";
  char n3[] = "Bad Romance";
  char a3[] = "Lady Gaga";
  char n4[] = "Yellow Submarine";
  char a4[] = "Beatles, The";
  char n5[] = "Hey Jude";
  char a5[] = "Beatles, The";

  list = insert_order( list, n1, a1 );
  list = insert_order( list, n2, a2 );
  list = insert_order( list, n3, a3 );
  list = insert_order( list, n4, a4 );
  list = insert_order( list, n5, a5 );

  

  print_list( list );

  list = free_list( list );
  print_list( list );
  
  return 0;
}
