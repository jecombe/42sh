#!/bin/bash
special=$'`!@#$%^&*()-_+={}|[]\\;\':",.<>?/ '
for ((i=0; i < ${#special}; i++)); do
	char="${special:i:1}"
	printf -v q_char '%q' "$char"
	if [[ "$char" != "$q_char" ]]; then
		printf 'Yes - character %s needs to be escaped\n' "$char"
	else
		printf 'No - character %s does not need to be escaped\n' "$char"
	fi
done | sort
