#!/usr/bin/bash

for notatka in *WYKŁAD*.xopp; do 
	x=$(echo "$notatka" | sed "s/.xopp/_annotated.pdf/")
	echo "$x"; echo "$notatka"
	xournalpp -p "$x" "$notatka"
done 
