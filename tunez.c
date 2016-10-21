#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

void print_song_first( song_node *n ) {
  printf("[ %s, %s ]\n", n->name, n->artist);
}

//returns the number of songs in the library
int num_songs( song_node *n ) {
  int ctr = 1;
  if( n->next != 0 ) {
    ctr += num_songs( n->next );
  }
  return ctr;
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
song_node * insert_order_song( song_node *n, char a[], char b[] ) {
  if( strcmp(a, n->name) < 0 ) {
    return insert_front( n, a, b );
  }
  else {
    if( n->next != 0 ) {
      n = insert_front(insert_order_song( n->next, a, b ), n->name, n->artist );
    }
    else {
      song_node *new = (song_node *)malloc(sizeof(song_node));
      new->next = NULL;
      strcpy(new->name, a);
      strcpy(new->artist, b);
      n->next = new;
    }
  }
  return n;
}

//inserts a node alphabetically, by artist and then song
song_node * insert_order_artist( song_node *n, char a[], char b[] ) {
  if( strcmp(b, n->artist) < 0 ) {
    n = insert_front(n, a, b);
  }
  else if( strcmp(b, n->artist) == 0) {
    if( strcmp(a, n->name) < 0 ) {
      n = insert_front(n, a, b);
    }
    else {
      if( n->next != 0 ) {
	n = insert_front(insert_order_artist(n->next, a, b), n->name, n->artist);
      }
      else {
      song_node *new = (song_node *)malloc(sizeof(song_node));
      new->next = NULL;
      strcpy(new->name, a);
      strcpy(new->artist, b);
      n->next = new;
      }
    }
  }
  else {
    if( n->next != 0 ) {
      n = insert_front(insert_order_artist(n->next, a, b), n->name, n->artist);
    }
    else {
      song_node *new = (song_node *)malloc(sizeof(song_node));
      new->next = NULL;
      strcpy(new->name, a);
      strcpy(new->artist, b);
      n->next = new;
    }
  }
  return n;
}

//finds a song by song name and returns a pointer to it
song_node * find_song_song( song_node *n, char a[] ) {
  if( strcmp(n->name,a) == 0 ) {
    return n;
  }
  else {
    if( n->next == 0 ) {
      printf("Song not found\n");
      return NULL;
    }
    else {
      return find_song_song( n->next, a );
    }
  }
}

//finds a song by artist and returns the first song found by that artist
song_node * find_song_artist( song_node *n, char a[] ) {
  if( strcmp(n->artist,a) == 0 ) {
    return n;
  }
  else {
    if( n->next == 0 ) {
      printf("Artist not found\n");
      return NULL;
    }
    else {
      return find_song_artist( n->next, a );
    }
  }
}

//finds a random song in the library and returns it
song_node * find_song_random( song_node *n ) {
  srand(time(NULL));
  int r = rand() % (num_songs(n) - 1);
  while( r != 0 ) {
    n = n->next;
    r--;
  }
  return n;
}

//shuffle helper
song_node * shuffle_helper( song_node *n, int seed ) {
  srand(seed);
  int r = rand() % (num_songs(n) - 1);
  while( r != 0 ) {
    n = n->next;
    r--;
  }
  return n;
}

//'shuffles' the playlist- repeat is enabled
song_node * shuffle( song_node *n ) {
  srand(time(NULL));
  int r = rand() % (num_songs(n) % 10 + 1);
  while( r > 0 ) {
    print_song_first(shuffle_helper( n, rand() % 1234));
    r--;
  }
}

//finds a song by index
song_node * find_song_index ( song_node *n, int index ) {
  int x = 0;
  while( x < index ) {
    if( n->next == NULL ) {
      return NULL;
    }
    n = n->next;
    x++;
  }
  return n;
}

//removes a song, by name
song_node * remove_song_song( song_node *n, char a[] ) {
  if( strcmp(n->name, a) == 0 ) {
    n = n->next;
  }

  else if( n->next != 0 ) {
    n = insert_front(remove_song_song( n->next, a ), n->name, n->artist);
  }

  else {
    n->next = NULL;
  }
  return n;
}

//removes a song, by artist
song_node * remove_song_artist( song_node *n, char a[] ) {
  if( strcmp(n->artist, a) == 0 ) {
    n = n->next;
  }

  else if( n->next != 0 ) {
    n = insert_front(remove_song_artist( n->next, a ), n->name, n->artist);
  }
  return n;
}

//print all songs x
void print_letter( song_node *n, char a[] ) {
  printf("[");
  while( n != NULL ) {
    if( strncmp(a,n->name,1) == 0) {
      printf(" %s, %s ", n->name, n->artist );
    }
    n = n->next;
  }
  printf("]\n");
}

//print all artists x
void print_artist( song_node *n, char a[] ) {
  printf("[");
  while( n != NULL ) {
    if( strncmp(a,n->artist,1) == 0 ) {
      printf(" %s, %s ", n->name, n->artist );
    }
    n = n->next;
  }
  printf("]\n");
}

//all songs by artist
void print_by_artist( song_node *n, char a[] ) {
  printf("[");
  while( n != NULL ) {
    if( strcmp(a,n->artist) == 0 ) {
      printf(" %s, %s ", n->name, n->artist );
    }
    n = n->next;
  }
  printf("]\n");
}

//frees up all the memory in the song library
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
  
  song_node * list = insert_front( NULL, "alive", "pearl jam" );
  printf("list begun:\n");
  print_list( list );

  //songs + artists
  char n1[] = "sandstorm";
  char a1[] = "darude";
  char n2[] = "bad romance";
  char a2[] = "lady gaga";
  char n3[] = "hey jude";
  char a3[] = "the beatles";
  char n4[] = "dirty little secret";
  char a4[] = "all-american rejects";
  char n5[] = "hey you";
  char a5[] = "pink floyd";
  char n6[] = "i am the walrus";
  char a6[] = "the beatles";
  char n7[] = "this is halloween";
  char a7[] = "marilyn manson";

  //testing insert by song
  list = insert_order_song( list, n1, a1 );
  list = insert_order_song( list, n2, a2 );
  list = insert_order_song( list, n3, a3 );
  list = insert_order_song( list, n4, a4 );
  list = insert_order_song( list, n5, a5 );
  list = insert_order_song( list, n6, a6 );
  list = insert_order_song( list, n7, a7 );

  printf("\nElements inserted by song\n");
  print_list( list );

  //testing count songs
  printf("Testing counting songs...\n");
  printf("Num songs = %d\n", num_songs( list ));

  //testing find song, random
  printf("\nTesting find random song...\n");
  print_song_first( find_song_random( list ) );
  
  //testing find by song
  printf("\nTesting find by song...\n");
  printf("search: \"hey you\" = %ul\n", find_song_song( list, "hey you" ));
  print_song_first( find_song_song(list, "hey you"));
  printf("search: \"this is halloween\" = %ul\n", find_song_song( list, "this is halloween" ));
  print_song_first( find_song_song(list, "this is halloween"));

  //testing find by artist
  printf("\nTesting find by artist...\n");
  printf("search: \"pearl jam\" = %ul\n", find_song_artist( list, "pearl jam" ));
  print_song_first( find_song_artist(list, "pearl jam"));
  printf("search: \"the beatles\" = %ul\n", find_song_artist( list, "the beatles" ));
  print_song_first( find_song_artist(list, "the beatles"));

  //testing find by index
  printf("\nTesting find by index...\n");
  printf("search: 0 = %ul\n", find_song_index( list, 0 ));
  print_song_first( find_song_index(list, 0));
  printf("search: 6 = %ul\n", find_song_index( list, 0 ));
  print_song_first( find_song_index(list, 6));

  //testing print songs X
  printf("\ntesting print all songs starting with h\n");
  print_letter( list, "h" );
  
  //testing print artists X
  printf("\ntesting print all artists starting with p\n");
  print_artist( list, "p" );
  
  //testing all by artist
  printf("\ntesting print all songs by the beatles\n");
  print_by_artist( list, "the beatles" );

  //testing shuffle
  printf("\ntesting shuffle (repeat enabled)\n");
  shuffle(list);
  
  //testing remove by song
  printf("\nTesting remove by song...\n");
  printf("remove \"hey you\"...\n");
  list = remove_song_song(list, "hey you");
  printf("remove \"alive\"\n");
  list = remove_song_song(list, "alive");
  printf("remove \"this is halloween\"\n");
  list = remove_song_song(list, "this is halloween");
  printf("remove \"i am the walrus\"\n");
  list = remove_song_song(list, "i am the walrus");
  printf("remove \"sandstorm\"\n");
  list = remove_song_song(list, "sandstorm");
  printf("remove \"bad romance\"\n");
  list = remove_song_song(list, "bad romance");
  printf("remove \"hey jude\"\n");
  list = remove_song_song(list, "hey jude");
  printf("printing list...\n");
  print_list( list );
  
  //testing insert by artist
  printf("\nTesting insert by artist...\n");
  list = insert_order_artist( list, n1, a1 );
  list = insert_order_artist( list, n3, a3 );
  list = insert_order_artist( list, n6, a6 );
  print_list( list );
  
  //testing remove by artist
  printf("\nremove \"dirty little secret\"\n");
  list = remove_song_song(list, "dirty little secret");
  printf("remove \"hey jude\"\n");
  list = remove_song_song(list, "hey jude");
  printf("remove \"i am the walrus\"\n");
  list = remove_song_song(list, "i am the walrus");
  printf("printing list...\n");
  print_list( list );

  printf("\nFreeing library...\n");
  list = free_list( list );
  
  printf("\nAfter freeing...\n");
  print_list( list );
  
  return 0;
}
