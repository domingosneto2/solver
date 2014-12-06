#!/bin/bash

FILES=`find .`

for FILE in $FILES; do
	if [ -f $FILE ]; then
		chmod 644 $FILE;
	fi;
done
