typedef struct song_node {
  char name[256];
  char artist[256];
  struct song_node *next;
} song_node;

//void print_list( song_node *);
//void print_node( song_node * );
//void print_artist( song_node * );

//song_node * insert_front( song_node * );
//song_node * insert_ordered( song_node * );
//song_node * free_list( song_node * );

//other file

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
