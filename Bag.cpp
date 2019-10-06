#include "Bag.h"
#include <iostream>
#include<stdlib.h>
#include<time.h>
Bag::Bag() {
	bag=new LinkedList();
	char colors[6]= {'R','O','Y','G','B','P'};
	int shapes[6]= {1,2,3,4,5,6};
	Tile* tilesArray[72];
	int index=0;
	for(int i=0; i<6; i++) {
		for(int j=0; j<6; j++) {
			tilesArray[index]=new Tile(colors[i],shapes[j]);
			index++;
		}
	}
	for(int i=0; i<6; i++) {
		for(int j=0; j<6; j++) {
			tilesArray[index]=new Tile(colors[i],shapes[j]);
			index++;
		}
	}// two for loop create 72 tiles, temporarily store them in an array.
	srand(time(NULL));
	int random=0;
	for(int i=0; i<index; i++) {
		random=rand()%72;
		Tile* temp=tilesArray[i];
		tilesArray[i]=tilesArray[random];
		tilesArray[random]=temp;
	}//swap each elemnt with another random chosen element in the array
	 //so now we get shuffled tiles
	for(int i=0; i<index; i++) {
		bag->add(tilesArray[i]);
	}
	//add tiles into linkedlist
}
//the bool argument is to distinct it from bag(), this constructor is only used when load a game
Bag::Bag(bool empty){
	bag=new LinkedList();
}
LinkedList* Bag::getBag() {
	return bag;
}
